#ifndef IPERSISTABLE_H
#define IPERSISTABLE_H
 
class IPersistable {
public:
    virtual void save() = 0;   // write state to VFS
    virtual void load() = 0;   // read state from VFS
 
    virtual ~IPersistable() {}
};
 
#endif