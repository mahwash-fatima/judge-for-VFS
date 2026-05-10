#ifndef CONTEST_H
#define CONTEST_H

#include "IPersistable.h"
#include "DynamicArray.h"
#include "ProblemManager.h"
#include "problem.h"

class Contest : public IPersistable {
private:
    int contestId;
    int durationMinutes;
    int remainingSeconds;
    Difficulty tier;
    DynamicArray contestProblems; 
    bool isActive;

public:
    Contest(int id, Difficulty diff, int duration = 60);
    ~Contest();

    void initializeContest(ProblemManager& manager);

    void tick(); 
    int getRemainingTime() const;

    // IPersistable: Mid-contest save and resume
    void save(Volume& vfs, const char* path) override;
    void load(Volume& vfs, const char* path) override;

    bool isFinished() const { return remainingSeconds <= 0 || !isActive; }
};

#endif