#ifndef USER_H
#define USER_H


class User {
    private:
        char* userName;
        int userID;
        char* directoryPath; //home directory path
        char* userRole; //should be "root"(super) or "standard"
    public:
        User(char* name = nullptr, int id = 0, char* path = nullptr, char* role = nullptr);

        int getUserId();

        char* getUserName();

        bool isRootUser();

        ~User();
};

#endif
