#ifndef JUDGEUSER_H
#define JUDGEUSER_H
 
#include "IPersistable.h"
 
// Forward declarations — avoids heavy includes in header
class Directory;
class File;
class User;
 
class JudgeUser : public IPersistable {
private:
    char*        username;
    char*        email;
    unsigned int passHash;     // djb2 hash of password — never plain text
    bool         verified;     // false until email token is confirmed
    int          contestGroup; // 1 to 4, assigned on registration
 
    // VFS nodes — owned by the VFS tree, NOT by JudgeUser
    Directory* userDir;        // /users/username/
    Directory* contestDir;     // /users/username/contest/
    Directory* practiceDir;    // /users/username/practice/
    File*      profileFile;    // /users/username/profile.dat
 
    // Serialize all fields into one pipe-delimited char*
    // Format: "username|email|passHash|verified|group"
    // Caller must delete[] the returned buffer
    char* serialize() const;
 
    // Split a pipe-delimited char* back into fields
    void deserialize(const char* data);
 
    // djb2 hash — same input always gives same number, cannot be reversed
    static unsigned int hashPassword(const char* pass);
 
    // helpers NOT available in helper.h or String.h
    static char*        concat(const char* a, const char* b);
    static void         intToStr(unsigned int n, char* buf);
    static unsigned int strToUInt(const char* s);
 
public:
    // Registration path — all fields provided upfront
    JudgeUser(const char* username, const char* email,
              const char* password, int group);
 
    // Load path — empty shell, fields filled by load()
    JudgeUser();
 
    ~JudgeUser();
 
    // ── Getters ──
    const char* getUsername()   const;
    const char* getEmail()      const;
    bool        isVerified()    const;
    int         getGroup()      const;
 
    // ── Auth ──
    bool checkPassword(const char* password) const;
    void verify(); // marks verified=true and calls save()
 
    // ── VFS ──
    // Creates /users/username/ folder structure in VFS
    // Call once after registration
    void initVFSSpace(Directory* usersRoot, User* vfsOwner);
 
    // Attach existing VFS nodes (used by AuthManager when loading)
    void setProfileFile(File* f);
    void setUserDir(Directory* d);
 
    // Getters for directories (needed by ContestManager)
    Directory* getContestDir()  const;
    Directory* getPracticeDir() const;
 
    // ── IPersistable ──
    void save() override; // write to VFS profileFile
    void load() override; // read from VFS profileFile
};
 
#endif