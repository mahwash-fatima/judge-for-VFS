#include "versionrecord.h"
#include "helper.h"


versionRecord :: versionRecord(int version, User* m, char* tag) {
    version = versionNo;
    modifier = m;
    versionCreated = time(0);

    if(tag != nullptr)
    {
        changeTag = copyStr(tag);
    }
    else
        changeTag = nullptr;
}

int versionRecord :: getVersionNo() {
    return versionNo;
}

time_t versionRecord :: getCreationTime() {
    return versionCreated;
}

char* versionRecord :: getChangeTag() {
    return changeTag;
}

versionRecord :: ~versionRecord() {
    if(changeTag != nullptr)
        delete[] changeTag;
}
