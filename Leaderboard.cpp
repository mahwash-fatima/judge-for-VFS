#include "Leaderboard.h"
#include <iostream>

using namespace std;

Leaderboard::Leaderboard() : rankings() {}

void Leaderboard::updateScore(const char* user, int points) {
    // Check if the user already exists in our rankings
    for (int i = 0; i < rankings.getCurrItems(); i++) {
        RankEntry* entry = (RankEntry*)rankings.getIndex(i);
        if (compareStr(entry->username, (char*)user)) { //
            entry->score += points;
            sortRankings(); // Re-sort after update
            return;
        }
    }

    // If new user, create an entry
    RankEntry* newEntry = new RankEntry;
    newEntry->username = copyStr((char*)user); //
    newEntry->score = points;
    rankings.addItem(newEntry);
    sortRankings();
}

void Leaderboard::sortRankings() {
    int n = rankings.getCurrItems();
    if (n < 2) return;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            //retrieve current and next entries
            RankEntry* a = (RankEntry*)rankings.getIndex(j);
            RankEntry* b = (RankEntry*)rankings.getIndex(j + 1);

            //if the person below has a higher score, swap them
            if (a->score < b->score) {
                swapEntries(j, j + 1);
            }
        }
    }
}

void Leaderboard::swapEntries(int idx1, int idx2) {
    //take both entries
    void* temp1 = rankings.getIndex(idx1);
    void* temp2 = rankings.getIndex(idx2);

    //use the new setIndex to swap their positions
    rankings.setIndex(idx1, temp2);
    rankings.setIndex(idx2, temp1);
}

int Leaderboard::calcScore() {
    // Return the average or total score of the top performer
    if (rankings.getCurrItems() == 0) return 0;
    return ((RankEntry*)rankings.getIndex(0))->score;
}

void Leaderboard::displayTop() const {
    cout << "\n--- GLOBAL LEADERBOARD ---" << endl;
    for (int i = 0; i < rankings.getCurrItems(); i++) {
        RankEntry* e = (RankEntry*)rankings.getIndex(i);
        cout << i + 1 << ". " << e->username << " : " << e->score << " pts" << endl;
    }
}

Leaderboard::~Leaderboard() {
    for (int i = 0; i < rankings.getCurrItems(); i++) {
        RankEntry* e = (RankEntry*)rankings.getIndex(i);
        delete[] e->username;
        delete e;
    }
}