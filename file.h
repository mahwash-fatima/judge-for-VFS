#ifndef FILE_H
#define FILE_H

#include "entity.h"
#include "versionrecord.h"


class File : public fileSystemEntity {
    private:
        char* content;
        versionRecord** history;
        int versionCount;
        int versionCapacity;
    public:
        File(char* n, User* o, char* gName, char* c = nullptr);

        virtual double getSize() override;

        char* getContent();

        void saveVersion(User* modifier, char* tag);

        void displayHistory();

        void updateContent(char* newContent);

        void display(int depth);

        virtual ~File() override;
};

#endif