#ifndef JUDGEUSER_H
#define JUDGEUSER_H
 
#include "IPersistable.h"
 
// Forward declare VFS classes so we don't pull in heavy headers here
class Directory;
class File;
 
class JudgeUser : public IPersistable {
private:
    char* username;         // unique login name
    char* email;            // used for verification
    unsigned int passHash;  // hashed password — never store plain text
    bool verified;          // account active only after email verify
    int contestGroup;       // assigned group 1-4 on registration
 
    // VFS nodes owned by this user
    Directory* userDir;     // /users/username/
    Directory* contestDir;  // /users/username/contest/
    Directory* practiceDir; // /users/username/practice/
    File* profileFile;      // /users/username/profile.dat
 
    // Serialize all fields into a pipe-delimited char*
    // Format: "username|email|passHash|verified|group"
    // Caller must delete[] the returned buffer
    char* serialize() const;
 
    // Parse a pipe-delimited char* back into fields
    void deserialize(const char* data);
 
    // Simple djb2 hash — deterministic, no STL needed
    static unsigned int hashPassword(const char* pass);
 
    // Internal helpers
    static char* copyStr(const char* s);
    static int   strLen(const char* s);
    static char* concat(const char* a, const char* b);
    static void  intToStr(unsigned int n, char* buf);
    static unsigned int strToUInt(const char* s);
 
public:
    // Create a brand-new user (registration path)
    JudgeUser(const char* username, const char* email,
              const char* password, int group);
 
    // Create an empty shell for loading from VFS
    JudgeUser();
 
    ~JudgeUser();
 
    // ── Getters ──
    const char* getUsername()   const;
    const char* getEmail()      const;
    bool        isVerified()    const;
    int         getGroup()      const;
 
    // ── Auth ──
    // Returns true if the given password matches stored hash
    bool checkPassword(const char* password) const;
 
    // Mark account as verified (called after email token check)
    void verify();
 
    // ── VFS wiring ──
    // Called once after registration to create folder structure
    // Needs the root /users/ directory from Volume
    void initVFSSpace(Directory* usersRoot, class User* vfsOwner);
 
    // ── IPersistable ──
    void save() override;  // write to profileFile in VFS
    void load() override;  // read from profileFile in VFS
 
    // Attach an already-existing VFS File node (used on load)
    void setProfileFile(File* f);
    void setUserDir(Directory* d);
};
 
#endif