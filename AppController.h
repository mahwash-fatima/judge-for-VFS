#ifndef APP_CONTROLLER_H
#define APP_CONTROLLER_H

#include "Volume.h"
#include "AuthManager.h"
#include "ProblemManager.h"

class AppController {
private:
    static const int STATE_STARTUP = 0;
    static const int STATE_AUTH = 1;
    static const int STATE_DASHBOARD = 2;
    static const int STATE_PRACTICE = 3;
    static const int STATE_CONTEST = 4;
    static const int STATE_EXIT = 5;

    Volume* vfs;
    AuthManager* auth;
    ProblemManager* problems;
    
    int currentState;

public:
    AppController();
    ~AppController();

    void run();
    void initializeSystem();
};

#endif