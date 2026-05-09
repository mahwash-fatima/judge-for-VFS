#include "directory.h"
#include "partition.h"


class mountPoint : public Directory {
    private:
        Partition* mounted;
    public:
        mountPoint(char* n, User* o, char* gName, int cap = 50);

        void mount(Partition* p);

        void unmount();

        bool hasPartition();

        virtual double getSize() override;

        virtual ~mountPoint() override;
};