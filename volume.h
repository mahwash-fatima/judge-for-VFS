#include "directory.h"
#include "user.h"
#include "storage.h"
#include "partition.h"


class Volume {
    private:
        char* volName;
        Directory* rootDirectory;
        User** userRegistry;
        int userCount;
        int userCapacity;
        Partition** mountedPartitions;
        int partitionCount;
        int partitionCapacity;
        storageMedium** deviceList;
        int deviceCount;
        int deviceCapacity;
    public:
        Volume(char* name = nullptr);

        bool registerUser(User* newUser);

        User** getUserRegistry();

        bool addStorageMedium(storageMedium* device);

        bool mountPartition(Partition* p, Directory* mountPnt);

        bool isNameUnique(Directory* parent, char* name);

        bool IsOwnerRegistered(User* u);

        double getCombinedCapacity();

        double getTotalUsedSpace();

        Directory* getRoot();

        User* getUser(int id);

        void displayUserRegistry();

        void displaySystemSummary();

        ~Volume();
};