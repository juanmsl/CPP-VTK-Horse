#ifndef __PARAMS_MANAGER_HXX__
#define __PARAMS_MANAGER_HXX__

#define FLAT 0
#define GOURAUD 1
#define PHONG 2

#include <iostream>

class ParamsManager {
public:
    bool wired;
    std::string texture;
    int mapping;
    std::string filename;
    std::string output;
    int resolution;

    ParamsManager(int argc, char* argv[]);

private:
    void showHelp(const char* command);
};


#endif
