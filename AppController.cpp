#include <SFML/Graphics.hpp>
#include "AppController.h"
#include <iostream>

using namespace std;

AppController::AppController() {
    /*vfs = new Volume((char*)"OnlineJudgeSystem");
    
    auth = new AuthManager(vfs->getRoot(), vfs->getUser(0), vfs);

    problems = new ProblemManager(vfs);*/
    currentState = STATE_STARTUP;
}

void AppController::initializeSystem() {
    cout << "Initializing Online Judge System..." << endl;
    
    problems->seedProblemBank();
    
    cout << "VFS Loaded. 50 Problems Seeded." << endl;
    currentState = STATE_AUTH;
}

void AppController::run() {
    // 1. Create the Window
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Pro Coders - Online Judge");
    window.setFramerateLimit(60);

    // 2. Load your Canva Backgrounds
    sf::Texture loginTexture;
    if (!loginTexture.loadFromFile("login.png")) {
        // If it fails, we'll know why
        std::cout << "Error: Could not find login.png!" << std::endl;
    }
    sf::Sprite background(loginTexture);

    // 3. The Main Loop (Keeps the window open)
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            
            // Handle Mouse Clicks for your buttons here later!
        }

        // 4. Rendering
        window.clear();
        window.draw(background); // Draw your Canva design
        window.display();
    }
}

AppController::~AppController() {
    delete vfs;
    delete auth;
    delete problems;
}