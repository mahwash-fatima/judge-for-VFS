#ifndef USER_H
#define USER_H

#include "problem.h"

class User {
    private:
        char* userName;
        int userID;
        char* directoryPath; 
        char* userRole; 
        Difficulty assignedTier; 

    public:
        User(char* name = nullptr, int id = 0, char* path = nullptr, char* role = nullptr, Difficulty tier = Difficulty::EASY);

        int getUserId();
        char* getUserName();
        bool isRootUser();
        
        Difficulty getAssignedTier();
        void setAssignedTier(Difficulty tier);

        ~User();
};

#endif
