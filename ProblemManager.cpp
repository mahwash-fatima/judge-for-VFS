#include "ProblemManager.h"
#include "problem.h"
#include "directory.h"

ProblemManager::ProblemManager(Volume* volume) : vfs(volume) {}

// Problem bank seeded into VFS at startup
void ProblemManager::seedProblemBank() {
    for (int d = 1; d <= 5; d++) {
        Difficulty currentDiff = (Difficulty)d;
        for (int i = 1; i <= 10; i++) {
            int id = (d * 100) + i;
            Problem* p = new Problem(id, "Sample Title", "Solve this...", currentDiff);
            
            // Add mandatory test cases
            p->addTestCase("input_data", "expected_output");

            // Store in the local bank (void* array)
            problemBank.addItem(p);

            // Save to VFS partition
            char path[50];
            // Logic to generate path: /system/problems/easy/p101.dat
            p->save(*vfs, path);
        }
    }
}

ProblemManager::~ProblemManager() {
    for (int i = 0; i < problemBank.getCurrItems(); i++) {
        Problem* p = (Problem*)problemBank.getIndex(i);
        delete p;
    }
}

DynamicArray ProblemManager::getProblemsByDifficulty(Difficulty diff) {
    DynamicArray filtered;
    for (int i = 0; i < problemBank.getCurrItems(); i++) {
        Problem* p = (Problem*)problemBank.getIndex(i);
        if (p->getDifficulty() == diff) {
            filtered.addItem(p);
        }
    }
    return filtered;
}