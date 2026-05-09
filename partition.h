#ifndef PARTITION_H
#define PARTITION_H

class storageMedium;



class Partition {
    private:
        char* label;
        char* format;
        double capacity;
        double usedSpace;
        storageMedium* parentMedium;
        bool isMounted;
    public:
        Partition(char* l = nullptr, char* f = nullptr, double cap = 0.0, storageMedium* parent = nullptr);

        double getUsedSpace() const;

        double getCapacity() const;

        bool getMountStatus() const;

        bool setMounted(bool status);

        bool addData(double size);

        ~Partition();
};


#endif