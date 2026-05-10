#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H
 
#include "JudgeUser.h"
#include "DynamicArray.h"
 
class Directory;
class User;
 
class AuthManager {
private:
    DynamicArray users;        // all registered JudgeUser*
    JudgeUser*   activeUser;   // currently logged-in user (nullptr = nobody)
    Directory*   usersRoot;    // VFS /users/ directory
    User*        vfsAdminUser; // A3 VFS root user — owns judge directories
 
    // Pending verification: simple parallel arrays
    static const int MAX_PENDING = 50;
    char*      pendingTokens[MAX_PENDING];
    JudgeUser* pendingUsers[MAX_PENDING];
    int        pendingCount;
 
    // Generate a 6-digit numeric token from username + time
    char* generateToken(const char* username) const;
 
    // Linear scan through users array
    JudgeUser* findUser(const char* username) const;
 
    // Round-robin group assignment 1→4
    int assignGroup() const;
 
public:
    // usersRoot  = VFS Directory at /users/
    // adminUser  = A3 VFS User* (root) that owns judge directories
    AuthManager(Directory* usersRoot, User* adminUser);
    ~AuthManager();
 
    // ── Registration ──
    // Returns nullptr if username already taken
    // Prints token to console (simulates email send)
    JudgeUser* registerUser(const char* username,
                            const char* email,
                            const char* password);
 
    // ── Verification ──
    // Returns true if token matched — account now active
    bool verifyAccount(const char* username, const char* token);
 
    // ── Login / Logout ──
    bool login(const char* username, const char* password);
    void logout();
 
    // ── Delete account ──
    // Wipes VFS directory tree + removes from users array
    bool deleteAccount(const char* username, const char* password);
 
    // ── Getters ──
    JudgeUser* getActiveUser() const;
    bool       isLoggedIn()    const;
};
 
#endif