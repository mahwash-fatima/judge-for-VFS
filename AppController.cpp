#include <SFML/Graphics.hpp>
#include "AppController.h"
#include <iostream>

using namespace std;

AppController::AppController() {
    //vfs = new Volume((char*)"OnlineJudgeSystem");
    
    //auth = new AuthManager(vfs->getRoot(), vfs->getUser(0), vfs);

    //problems = new ProblemManager(vfs);
    currentState = STATE_STARTUP;
}

void AppController::initializeSystem() {
    cout << "Initializing Online Judge System..." << endl;
    
    //problems->seedProblemBank();
    
    cout << "VFS Loaded. 50 Problems Seeded." << endl;
    currentState = STATE_AUTH;
}

void AppController::run() {
    //initialize logic systems
    //initializeSystem();

    cout << "Starting window..." << std::endl;
    //setup SFML window
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Pro Coders - Online Judge");
    window.setFramerateLimit(60);

    //load the background
    sf::Texture loginBgTex;
    if (!loginBgTex.loadFromFile("./background.png")) {
        //if it fails, check if the file name is background.png
        std::cout << "Error: Could not find background.png" << std::endl;
        return;
    }
    sf::Sprite loginBg(loginBgTex);

    //main app loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        switch (currentState) {
            case STATE_AUTH:
                window.draw(loginBg);
                break;

            case STATE_DASHBOARD:
                break;
        }

        window.display();
    }
}

AppController::~AppController() {
    //delete vfs;
    //delete auth;
    //delete problems;
}