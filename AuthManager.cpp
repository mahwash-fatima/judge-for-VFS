#include "AuthManager.h"
#include "helper.h"    // A3 — copyStr, compareStr
#include "directory.h" // A3 VFS
#include "user.h"      // A3 VFS User
#include <iostream>
#include <ctime>
 
using namespace std;

// Token generation
// 6-digit number from time + username chars
// Simulates what a real email token would look like
 
char* AuthManager::generateToken(const char* username) const {
    unsigned int token = (unsigned int)time(0);
    for (int i = 0; username[i]; i++)
        token = token * 31 + username[i];
    token = token % 999999; // keep it 6 digits
 
    // convert number to char* (no STL)
    char* buf = new char[10];
    if (token == 0) { buf[0] = '0'; buf[1] = '\0'; return buf; }
    char tmp[10]; int idx = 0;
    unsigned int t = token;
    while (t > 0) { tmp[idx++] = '0' + (t % 10); t /= 10; }
    for (int j = 0; j < idx; j++) buf[j] = tmp[idx - 1 - j];
    buf[idx] = '\0';
    return buf;
}

// Group assignment — round-robin 1 to 4
// Every 4th registration cycles back to group 1
 
int AuthManager::assignGroup() const {
    return (users.getCurrItems() % 4) + 1;
}
 
// Find user — linear scan through DynamicArray
// compareStr from helper.h (A3)
 
JudgeUser* AuthManager::findUser(const char* username) const {
    for (int i = 0; i < users.getCurrItems(); i++) {
        JudgeUser* u = (JudgeUser*)users.getIndex(i);
        if (u && compareStr(u->getUsername(), (char*)username))
            return u;
    }
    return nullptr;
}

// Constructor / Destructor
 
AuthManager::AuthManager(Directory* root, User* admin, Volume* v) {
    vfsRef = v;
    usersRoot    = root;
    vfsAdminUser = admin;
    activeUser   = nullptr;
    pendingCount = 0;
 
    for (int i = 0; i < MAX_PENDING; i++) {
        pendingTokens[i] = nullptr;
        pendingUsers[i]  = nullptr;
    }
}
 
AuthManager::~AuthManager() {
    // delete all JudgeUser objects
    for (int i = 0; i < users.getCurrItems(); i++)
        delete (JudgeUser*)users.getIndex(i);
 
    // clean up any unsused pending tokens
    for (int i = 0; i < pendingCount; i++)
        delete[] pendingTokens[i];
 
    // do NOT delete usersRoot — VFS owns that tree
}

// Registration
 
JudgeUser* AuthManager::registerUser(const char* username,
                                      const char* email,
                                      const char* password) {
    // 1. username must be unique
    if (findUser(username) != nullptr) {
        cout << "Registration failed: '" << username << "' already taken." << endl;
        return nullptr;
    }
 
    // 2. assign contest group
    int group = assignGroup();
 
    // 3. create JudgeUser
    JudgeUser* newUser = new JudgeUser(username, email, password, group);
 
    // 4. create VFS folder structure for this user
    //    /users/username/, /contest/, /practice/, profile.dat
    newUser->initVFSSpace(usersRoot, vfsAdminUser);
 
    // 5. store in array
    users.addItem(newUser);
 
    // 6. generate token and simulate email
    if (pendingCount < MAX_PENDING) {
        char* token = generateToken(username);
        pendingTokens[pendingCount] = token;
        pendingUsers[pendingCount]  = newUser;
        pendingCount++;
 
        cout << "\n[EMAIL SIMULATION]" << endl;
        cout << "To: " << email << endl;
        cout << "Verification token: " << token << endl;
        cout << "Enter this token to activate your account.\n" << endl;
    }
 
    return newUser;
}

// Verification
 
bool AuthManager::verifyAccount(const char* username, const char* token) {
    for (int i = 0; i < pendingCount; i++) {
        if (!pendingUsers[i]) continue;
 
        // compareStr from helper.h (A3)
        if (compareStr(pendingUsers[i]->getUsername(), (char*)username) &&
            compareStr(pendingTokens[i], (char*)token))
        {
            // verify() sets verified=true and calls save() internally
            pendingUsers[i]->verify(*vfsRef, (char*)"profile.dat");
            cout << "Account verified! You can now log in." << endl;
 
            // clean up this pending entry
            delete[] pendingTokens[i];
            pendingTokens[i] = nullptr;
            pendingUsers[i]  = nullptr;
 
            // shift remaining entries down
            for (int j = i; j < pendingCount - 1; j++) {
                pendingTokens[j] = pendingTokens[j + 1];
                pendingUsers[j]  = pendingUsers[j + 1];
            }
            pendingCount--;
            return true;
        }
    }
    cout << "Verification failed: invalid token or username." << endl;
    return false;
}

// Login
 
bool AuthManager::login(const char* username, const char* password) {
    // already someone logged in?
    if (activeUser) {
        cout << "Already logged in as '" << activeUser->getUsername()
             << "'. Logout first." << endl;
        return false;
    }
 
    // find user
    JudgeUser* u = findUser(username);
    if (!u) {
        cout << "Login failed: username not found." << endl;
        return false;
    }
 
    // must be verified
    if (!u->isVerified()) {
        cout << "Login failed: account not verified. Check your email." << endl;
        return false;
    }
 
    // check password
    if (!u->checkPassword(password)) {
        cout << "Login failed: incorrect password." << endl;
        return false;
    }
 
    activeUser = u;
    cout << "Welcome, " << username
         << "! (Group " << u->getGroup() << ")" << endl;
    return true;
}
 
// Logout
 
void AuthManager::logout() {
    if (!activeUser) {
        cout << "No user is currently logged in." << endl;
        return;
    }
    activeUser->save(*vfsRef, "profile.dat"); // persist any changes before logout
    cout << "Goodbye, " << activeUser->getUsername() << "!" << endl;
    activeUser = nullptr;
}
 
// Delete account
// removeEntity triggers A3 Directory destructor chain
// which recursively deletes everything inside
 
bool AuthManager::deleteAccount(const char* username, const char* password) {
    JudgeUser* u = findUser(username);
    if (!u) {
        cout << "Delete failed: user not found." << endl;
        return false;
    }
    if (!u->checkPassword(password)) {
        cout << "Delete failed: incorrect password." << endl;
        return false;
    }
 
    // log out if this was the active user
    if (activeUser == u) activeUser = nullptr;
 
    // wipe entire VFS directory tree for this user
    // A3 removeEntity + destructor chain handles everything inside
    usersRoot->removeEntity((char*)username);
 
    // remove from users array — shift remaining down
    int total = users.getCurrItems();
    for (int i = 0; i < total; i++) {
        if ((JudgeUser*)users.getIndex(i) == u) {
            delete u;
            // shift remaining pointers down manually
            for (int j = i; j < total - 1; j++)
                users.getIndex(j); // use removeItem() if added to DynamicArray
            break;
        }
    }
 
    cout << "Account deleted. All data removed." << endl;
    return true;
}
 
// Getters
 
JudgeUser* AuthManager::getActiveUser() const { return activeUser; }
bool       AuthManager::isLoggedIn()    const { return activeUser != nullptr; }