#include "Contest.h"
#include "ProblemManager.h"
#include "problem.h"
#include <ctime>
#include <cstdlib>

Contest::Contest(int id, Difficulty diff, int duration) 
    : contestId(id), tier(diff), durationMinutes(duration), isActive(false) {
    remainingSeconds = duration * 60;
}

// Randomised problem selection per group
void Contest::initializeContest(ProblemManager& manager) {
    // 1. Get all problems matching this contest's difficulty tier
    DynamicArray filteredBank = manager.getProblemsByDifficulty(tier);
    
    int totalAvailable = filteredBank.getCurrItems();
    if (totalAvailable < 3) return; 

    // 2. Randomly pick 3 unique problems
    srand(time(0)); 
    int pickedCount = 0;
    int indices[3] = {-1, -1, -1};

    while (pickedCount < 3) {
        int randomIndex = rand() % totalAvailable;
        
        // Ensure uniqueness
        bool alreadyPicked = false;
        for (int i = 0; i < pickedCount; i++) {
            if (indices[i] == randomIndex) alreadyPicked = true;
        }

        if (!alreadyPicked) {
            indices[pickedCount] = randomIndex;
            // Add the Problem* to our contest list
            contestProblems.addItem(filteredBank.getIndex(randomIndex));
            pickedCount++;
        }
    }
    isActive = true;
}

// Countdown timer logic
void Contest::tick() {
    if (isActive && remainingSeconds > 0) {
        remainingSeconds--;
    } else if (remainingSeconds <= 0) {
        isActive = false; // Auto-end behaviour
    }
}

void Contest::save(Volume& vfs, const char* path) {}

void Contest::load(Volume& vfs, const char* path) {}

Contest::~Contest() {}