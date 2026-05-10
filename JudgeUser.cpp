#include "JudgeUser.h"
#include "directory.h"   // A3 VFS Directory
#include "file.h"        // A3 VFS File
#include "user.h"        // A3 VFS User (for VFS ownership)
#include <iostream>
 
using namespace std;
 
// Copy a c-string into a new heap buffer
char* JudgeUser::copyStr(const char* s) {
    if (!s) return nullptr;
    int l = strLen(s);
    char* d = new char[l + 1];
    for (int i = 0; i < l; i++) d[i] = s[i];
    d[l] = '\0';
    return d;
}
 
// Manual strlen
int JudgeUser::strLen(const char* s) {
    int l = 0;
    while (s[l]) l++;
    return l;
}
 
// Concatenate two c-strings into a new buffer
// Caller must delete[]
char* JudgeUser::concat(const char* a, const char* b) {
    int la = strLen(a), lb = strLen(b);
    char* r = new char[la + lb + 1];
    for (int i = 0; i < la; i++) r[i]       = a[i];
    for (int i = 0; i < lb; i++) r[la + i]  = b[i];
    r[la + lb] = '\0';
    return r;
}
 
// Convert unsigned int to char* digits
void JudgeUser::intToStr(unsigned int n, char* buf) {
    if (n == 0) { buf[0] = '0'; buf[1] = '\0'; return; }
    char tmp[20];
    int i = 0;
    while (n > 0) { tmp[i++] = '0' + (n % 10); n /= 10; }
    for (int j = 0; j < i; j++) buf[j] = tmp[i - 1 - j];
    buf[i] = '\0';
}
 
// Parse char* digits back into unsigned int
unsigned int JudgeUser::strToUInt(const char* s) {
    unsigned int result = 0;
    for (int i = 0; s[i]; i++)
        result = result * 10 + (s[i] - '0');
    return result;
}
 
// djb2 hash — fast, deterministic, no collisions for typical passwords
unsigned int JudgeUser::hashPassword(const char* pass) {
    unsigned int h = 5381;
    for (int i = 0; pass[i]; i++)
        h = ((h << 5) + h) + (unsigned char)pass[i];
    return h;
}

// Serialize / Deserialize
// Format: "username|email|passHash|verified|group"
 
char* JudgeUser::serialize() const {
    // convert numeric fields to strings
    char hashBuf[20];  intToStr(passHash, hashBuf);
    char grpBuf[4];    intToStr((unsigned int)contestGroup, grpBuf);
    const char* ver = verified ? "1" : "0";
 
    // build: username|email|hash|verified|group
    char* t1 = concat(username, "|");
    char* t2 = concat(t1, email);       delete[] t1;
    char* t3 = concat(t2, "|");         delete[] t2;
    char* t4 = concat(t3, hashBuf);     delete[] t3;
    char* t5 = concat(t4, "|");         delete[] t4;
    char* t6 = concat(t5, ver);         delete[] t5;
    char* t7 = concat(t6, "|");         delete[] t6;
    char* result = concat(t7, grpBuf);  delete[] t7;
 
    return result; // caller must delete[]
}
 
void JudgeUser::deserialize(const char* data) {
    // parse pipe-delimited string back into fields
    // fields: username | email | passHash | verified | group
    if (!data) return;
 
    int len = strLen(data);
    char* buf = new char[len + 1];
    for (int i = 0; i <= len; i++) buf[i] = data[i];
 
    const char* fields[5];
    int fieldCount = 0;
    fields[fieldCount++] = buf;
 
    // replace '|' with '\0' to split in-place
    for (int i = 0; i < len && fieldCount < 5; i++) {
        if (buf[i] == '|') {
            buf[i] = '\0';
            fields[fieldCount++] = buf + i + 1;
        }
    }
 
    if (fieldCount < 5) {
        cout << "JudgeUser::deserialize — malformed data" << endl;
        delete[] buf;
        return;
    }
 
    delete[] username;
    delete[] email;
    username     = copyStr(fields[0]);
    email        = copyStr(fields[1]);
    passHash     = strToUInt(fields[2]);
    verified     = (fields[3][0] == '1');
    contestGroup = (int)strToUInt(fields[4]);
 
    delete[] buf;
}

// Constructors / Destructor
 
// Full constructor — used at registration
JudgeUser::JudgeUser(const char* uname, const char* em,
                     const char* password, int group) {
    username     = copyStr(uname);
    email        = copyStr(em);
    passHash     = hashPassword(password);
    verified     = false;   // must verify email before login
    contestGroup = group;
 
    userDir     = nullptr;
    contestDir  = nullptr;
    practiceDir = nullptr;
    profileFile = nullptr;
}
 
// Empty constructor — used when loading from VFS
JudgeUser::JudgeUser() {
    username     = nullptr;
    email        = nullptr;
    passHash     = 0;
    verified     = false;
    contestGroup = 0;
 
    userDir     = nullptr;
    contestDir  = nullptr;
    practiceDir = nullptr;
    profileFile = nullptr;
}
 
JudgeUser::~JudgeUser() {
    delete[] username;
    delete[] email;
    // NOTE: do NOT delete VFS nodes here —
    // the VFS Directory destructor handles its own tree.
    // Deleting here would cause a double-free.
}
 
// Getters
 
const char* JudgeUser::getUsername() const { return username; }
const char* JudgeUser::getEmail()    const { return email;    }
bool        JudgeUser::isVerified()  const { return verified; }
int         JudgeUser::getGroup()    const { return contestGroup; }
 
// Auth
 
bool JudgeUser::checkPassword(const char* password) const {
    // hash the input and compare — never compare plain text
    return hashPassword(password) == passHash;
}
 
void JudgeUser::verify() {
    verified = true;
    save(); // immediately persist the verified flag to VFS
}
 
// VFS Space Initialisation
// Called once after registration
// Creates the folder structure under /users/username/
 
void JudgeUser::initVFSSpace(Directory* usersRoot, User* vfsOwner) {
    if (!usersRoot || !vfsOwner) return;
 
    // create /users/username/
    userDir = new Directory(username, vfsOwner, (char*)"users", 20);
    usersRoot->addEntity(userDir);
 
    // create /users/username/contest/
    contestDir = new Directory((char*)"contest", vfsOwner, (char*)"users", 20);
    userDir->addEntity(contestDir);
 
    // create /users/username/practice/
    practiceDir = new Directory((char*)"practice", vfsOwner, (char*)"users", 20);
    userDir->addEntity(practiceDir);
 
    // create /users/username/profile.dat with initial serialized data
    char* data = serialize();
    profileFile = new File((char*)"profile.dat", vfsOwner, (char*)"users", data);
    userDir->addEntity(profileFile);
    delete[] data;
}

// IPersistable — save / load
 
void JudgeUser::save() {
    // write current state into the VFS File node
    if (!profileFile) {
        cout << "JudgeUser::save — no VFS profile file attached" << endl;
        return;
    }
    char* data = serialize();
    profileFile->updateContent(data); // A3 File method
    delete[] data;
}
 
void JudgeUser::load() {
    // read from VFS File node and reconstruct fields
    if (!profileFile) {
        cout << "JudgeUser::load — no VFS profile file attached" << endl;
        return;
    }
    const char* data = profileFile->getContent(); // A3 File method
    deserialize(data);
}

// VFS node attachment (used by AuthManager on load)
 
void JudgeUser::setProfileFile(File* f)      { profileFile = f; }
void JudgeUser::setUserDir(Directory* d)     { userDir = d;     }