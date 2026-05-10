#ifndef IPERSISTABLE_H
#define IPERSISTABLE_H

#include "volume.h"

class IPersistable {
public:
    // Updated to accept Volume and a path for VFS operations
    virtual void save(Volume& vfs, const char* path) = 0;
    virtual void load(Volume& vfs, const char* path) = 0;

    virtual ~IPersistable() {}
};

#endif
