#include <iostream>
#include <ctime>
#include <cstdlib>

// Include headers in order of dependency
#include "user.h"
#include "directory.h"
#include "volume.h"
#include "problem.h"
#include "ProblemManager.h"
#include "Contest.h"

using namespace std;

int main() {
    cout << "--- BACKEND INITIALIZATION ---" << endl;

    // 1. Initialize Volume
    Volume myVFS((char*)"JudgeDrive");

    // 2. Initialize Problem Manager and Seed VFS
    // This feeds the 50 problems into the VFS directories
    ProblemManager pManager(&myVFS);
    cout << "Seeding 50 problems into VFS..." << endl;
    pManager.seedProblemBank();

    // 3. Create and Register User
    srand(time(0));
    Difficulty assignedTier = (Difficulty)((rand() % 3) + 1);

    // Note: User constructor updated to include Difficulty as discussed
    User* student = new User(
        (char*)"Alice_Coder", 
        101, 
        (char*)"/home/alice", 
        (char*)"standard", 
        assignedTier
    );

    if (myVFS.registerUser(student)) {
        cout << "User registered successfully." << endl;
        cout << "Username: " << student->getUserName() << " | Tier: " << (int)student->getAssignedTier() << endl;
    }

    // 4. Initialize Contest Logic
    // This picks 3 random problems from the 50 seeded earlier based on Alice's tier
    Contest activeContest(2024, student->getAssignedTier(), 60);
    activeContest.initializeContest(pManager);

    cout << "\n--- System Status Check ---" << endl;
    myVFS.displaySystemSummary();

    cout << "\nBackend integration successful. Ready for SFML." << endl;

    return 0;
}