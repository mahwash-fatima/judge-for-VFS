#include "AppController.h"
#include <iostream>

int main() {
    std::cout << "--- PROGRAM STARTING ---" << std::endl;
    
    AppController app;
    
    std::cout << "--- CALLING RUN ---" << std::endl;
    app.run();
    
    std::cout << "--- PROGRAM FINISHED ---" << std::endl;
    
    // This will keep the terminal open so you can read the output
    std::cout << "Press Enter to close..." << std::endl;
    std::cin.get();
    
    return 0;
}