#include <iostream>
#include <cstdlib> // for exit()

void use_arguments(int argc, char* argv[]) {
    bool testSeen = false;

    for (int i = 1; i < argc; ++i) { //because argv[0]is the program's name
        std::string arg = argv[i];

        if (arg == "--help") {
            std::cout << "Help text goes here." << std::endl;
            exit(0);
        } else if (arg == "--test") {
            if (testSeen) {
                std::cerr << "Error: '--test' argument seen more than once." << std::endl;
                exit(1);
            }
            std::cout << "Tests passed" << std::endl;
            testSeen = true;
        } else {
            std::cerr << "Error: Unrecognized argument '" << arg << "'." << std::endl;
            exit(1);
        }
    }
}

