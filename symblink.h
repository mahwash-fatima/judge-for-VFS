#include "entity.h"


class symbLink : public fileSystemEntity {
    private:
        fileSystemEntity* targetPath;
    public:
        symbLink(char* n, User* o, char* gName, fileSystemEntity* target = nullptr);

        virtual double getSize() override;

        bool checkDangling();

        fileSystemEntity* getTargetPath();

        void setTargetPath(fileSystemEntity* target);

        void display(int depth);

        virtual ~symbLink() override;
};