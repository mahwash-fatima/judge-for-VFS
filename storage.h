#ifndef STORAGE_MEDIUM_H
#define STORAGE_MEDIUM_H


class Partition;


//storage medium class declaration only
class storageMedium {
    private:
        double totalMemory;
        double usedMemory;
        bool mounted;
        char* techType;
        Partition** partitions; //COMPOSITION relationship with Partition class
        int partitionCount;
    public:
        storageMedium(double total = 0.0, char* type = nullptr, bool m = false); //constructor to initialize some members to default values

        double getRemainingCapacity();

        void mount();

        void unmount();

        double getCapacity();

        Partition* getPartition(int index);

        void addPartition(double newMemory, char* label, char* format);

        ~storageMedium();
};


#endif