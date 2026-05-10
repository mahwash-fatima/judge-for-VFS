#include "JudgeUser.h"
#include "helper.h"    // A3 — copyStr, compareStr (no need to rewrite)
#include "directory.h" // A3 VFS Directory
#include "file.h"      // A3 VFS File
#include "user.h"      // A3 VFS User
#include <iostream>
 
using namespace std;

// Helpers that are NOT in helper.h or String.h
// Only these three are defined here
 
// Concatenate two c-strings into a new heap buffer
// Caller must delete[]
char* JudgeUser::concat(const char* a, const char* b) {
    int la = 0; while (a[la]) la++;
    int lb = 0; while (b[lb]) lb++;
    char* r = new char[la + lb + 1];
    for (int i = 0; i < la; i++) r[i]      = a[i];
    for (int i = 0; i < lb; i++) r[la + i] = b[i];
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
 
// Parse char* digits into unsigned int
unsigned int JudgeUser::strToUInt(const char* s) {
    unsigned int r = 0;
    for (int i = 0; s[i]; i++) r = r * 10 + (s[i] - '0');
    return r;
}

// djb2 password hash
// Converts any password string into a single number
// Same input → always same output (deterministic)
// Cannot be reversed — only the number is ever stored
 
unsigned int JudgeUser::hashPassword(const char* pass) {
    unsigned int h = 5381;
    for (int i = 0; pass[i]; i++)
        h = ((h << 5) + h) + (unsigned char)pass[i];
    return h;
}

// Serialize / Deserialize
// Format: "username|email|passHash|verified|group"
 
char* JudgeUser::serialize() const {
    char hashBuf[20]; intToStr(passHash, hashBuf);
    char grpBuf[4];   intToStr((unsigned int)contestGroup, grpBuf);
    const char* ver = verified ? "1" : "0";
 
    // build string piece by piece using concat
    // copyStr is from helper.h (A3)
    char* t1  = concat(username, "|");
    char* t2  = concat(t1, email);      delete[] t1;
    char* t3  = concat(t2, "|");        delete[] t2;
    char* t4  = concat(t3, hashBuf);    delete[] t3;
    char* t5  = concat(t4, "|");        delete[] t4;
    char* t6  = concat(t5, ver);        delete[] t5;
    char* t7  = concat(t6, "|");        delete[] t6;
    char* out = concat(t7, grpBuf);     delete[] t7;
    return out; // caller must delete[]
}
 
void JudgeUser::deserialize(const char* data) {
    if (!data) return;
 
    // copyStr from helper.h (A3) — no need to rewrite
    char* buf = copyStr(data);
    int   len = 0; while (buf[len]) len++;
 
    // split on '|' by replacing with '\0' in-place
    const char* fields[5];
    int fc = 0;
    fields[fc++] = buf;
    for (int i = 0; i < len && fc < 5; i++) {
        if (buf[i] == '|') {
            buf[i] = '\0';
            fields[fc++] = buf + i + 1;
        }
    }
 
    if (fc < 5) {
        cout << "JudgeUser::deserialize — malformed data" << endl;
        delete[] buf;
        return;
    }
 
    // free old values before overwriting
    delete[] username;
    delete[] email;
 
    // copyStr from helper.h (A3)
    username     = copyStr(fields[0]);
    email        = copyStr(fields[1]);
    passHash     = strToUInt(fields[2]);
    verified     = (fields[3][0] == '1');
    contestGroup = (int)strToUInt(fields[4]);
 
    delete[] buf;
}
 
// Constructors / Destructor
 
// Registration path
JudgeUser::JudgeUser(const char* uname, const char* em,
                     const char* password, int group) {
    // copyStr from helper.h (A3)
    username     = copyStr(uname);
    email        = copyStr(em);
    passHash     = hashPassword(password);
    verified     = false;
    contestGroup = group;
 
    userDir      = nullptr;
    contestDir   = nullptr;
    practiceDir  = nullptr;
    profileFile  = nullptr;
}
 
// Load path — empty shell
JudgeUser::JudgeUser() {
    username     = nullptr;
    email        = nullptr;
    passHash     = 0;
    verified     = false;
    contestGroup = 0;
 
    userDir      = nullptr;
    contestDir   = nullptr;
    practiceDir  = nullptr;
    profileFile  = nullptr;
}
 
JudgeUser::~JudgeUser() {
    delete[] username;
    delete[] email;
    // do NOT delete VFS nodes — VFS Directory destructor
    // handles its own tree. Deleting here = double free.
}
 
// Getters
 
const char* JudgeUser::getUsername()   const { return username;     }
const char* JudgeUser::getEmail()      const { return email;        }
bool        JudgeUser::isVerified()    const { return verified;     }
int         JudgeUser::getGroup()      const { return contestGroup; }
Directory*  JudgeUser::getContestDir() const { return contestDir;   }
Directory*  JudgeUser::getPracticeDir()const { return practiceDir;  }
 
// Auth
 
bool JudgeUser::checkPassword(const char* password) const {
    // hash the input and compare numbers — never compare plain text
    return hashPassword(password) == passHash;
}
 
void JudgeUser::verify() {
    verified = true;
    save(); // immediately persist verified flag to VFS
}
 
// VFS Space Initialisation
// Creates folder structure under /users/username/
// Called once right after registration
 
void JudgeUser::initVFSSpace(Directory* usersRoot, User* vfsOwner) {
    if (!usersRoot || !vfsOwner) return;
 
    // /users/username/
    userDir = new Directory(username, vfsOwner, (char*)"users", 20);
    usersRoot->addEntity(userDir);
 
    // /users/username/contest/
    contestDir = new Directory((char*)"contest", vfsOwner, (char*)"users", 20);
    userDir->addEntity(contestDir);
 
    // /users/username/practice/
    practiceDir = new Directory((char*)"practice", vfsOwner, (char*)"users", 20);
    userDir->addEntity(practiceDir);
 
    // /users/username/profile.dat — initial serialized data
    char* data  = serialize();
    profileFile = new File((char*)"profile.dat", vfsOwner, (char*)"users", data);
    userDir->addEntity(profileFile);
    delete[] data;
}

// IPersistable — save / load
 
void JudgeUser::save() {
    if (!profileFile) {
        cout << "JudgeUser::save — no VFS profile file attached" << endl;
        return;
    }
    char* data = serialize();
    profileFile->updateContent(data); // A3 File::updateContent
    delete[] data;
}
 
void JudgeUser::load() {
    if (!profileFile) {
        cout << "JudgeUser::load — no VFS profile file attached" << endl;
        return;
    }
    const char* data = profileFile->getContent(); // A3 File::getContent
    deserialize(data);
}

// VFS node attachment
 
void JudgeUser::setProfileFile(File* f)  { profileFile = f; }
void JudgeUser::setUserDir(Directory* d) { userDir = d;     }