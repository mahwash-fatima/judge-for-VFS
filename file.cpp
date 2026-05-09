#include <iostream>
#include "helper.h"
#include "entity.h"
#include "file.h"

using namespace std;



File :: File(char* n, User* o, char* gName, char* c) : fileSystemEntity(n, o, gName) {
    content = copyStr(c);

    versionCapacity = 10;
    versionCount = 0;

    history = new versionRecord* [versionCapacity];

    for(int i = 0; i < versionCapacity; i++)
        history[i] = nullptr;
}


double File :: getSize() {
    if(content == nullptr)
        return 0.0;
    else
    {
        int len = 0;

        while(content[len] != '\0')
            len++;

        return len;
    }
}


char* File :: getContent() {
    return content;
}


void File :: saveVersion(User* modifier, char* tag) {
    if(versionCount < versionCapacity)
    {
        history[versionCount] = new versionRecord(versionCount + 1, modifier, tag);
        versionCount++;
    }
    else
        cout << "\nNo more versions can be added!" << endl;
}


void File :: displayHistory() {
    cout << "VERSION HISTORY" << endl;

    for(int i = 0; i < versionCapacity; i++)
    {
        if(history[i] != nullptr)
        {
            cout << "Version no. : " << history[i]->getVersionNo() << endl;
            cout << "Change tag : " << history[i]->getChangeTag() << endl;
        }
        cout << endl;
    }
}


void File :: updateContent(char* newContent) {
    if(content != nullptr)
        delete[] content;

    content = copyStr(newContent);

    modifiedTime = time(0);
}

void File::display(int depth) {
    for (int i = 0; i < depth; i++) cout << "    ";
    cout << "FILE: " << getName() << endl;
}

File :: ~File() {
    if (history != nullptr) {
        for (int i = 0; i < versionCapacity; i++)
        {
            if(history[i] != nullptr)
                delete history[i];
        }
        delete[] history;
    }

    delete[] content;
}
