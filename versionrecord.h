#ifndef VERSION_RECORD_H
#define VERSION_RECORD_H

#include <ctime>
#include "user.h"


class versionRecord {
    private:
        int versionNo;
        time_t versionCreated;
        User* modifier;
        char* changeTag;
    public:
        versionRecord(int version = 0, User* m = nullptr, char* tag = nullptr);

        int getVersionNo();

        time_t getCreationTime();

        char* getChangeTag();

        ~versionRecord();
};


#endif