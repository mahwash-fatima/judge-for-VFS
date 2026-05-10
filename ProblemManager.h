#ifndef PROBLEMMANAGER_H
#define PROBLEMMANAGER_H

#include "problem.h"
#include "volume.h"
#include "DynamicArray.h"

class ProblemManager {
private:
    DynamicArray problemBank; 
    Volume* vfs;

public:
    ProblemManager(Volume* volume);
    
    ~ProblemManager() {
        for (int i = 0; i < problemBank.getCurrItems(); i++) {
            delete (Problem*)problemBank.getIndex(i);
        }
    }

    void seedProblemBank();
    
    DynamicArray getProblemsByDifficulty(Difficulty diff);
};

#endif