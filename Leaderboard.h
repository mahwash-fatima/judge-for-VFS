#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "DynamicArray.h"
#include "IScoreable.h"
#include "helper.h"

//a simple container for the ranking data
struct RankEntry {
    char* username;
    int score;
};

class Leaderboard : public IScoreable {
private:
    DynamicArray rankings; //stores RankEntry pointers

public:
    Leaderboard();
    ~Leaderboard();

    //implementation of IScoreable
    int calcScore() override; 

    //logic to add or update a user's standing
    void updateScore(const char* user, int points);
    
    //sorts the users from highest to lowest score
    void sortRankings();

    //swaps places of users according to their scores
    void swapEntries(int idx1, int idx2);

    //prints the top performers
    void displayTop() const;
};

#endif