#pragma once
#include "SFML\Graphics.hpp"

#include <fstream>
#include <string>

using namespace std; 

class ScoreManager {
private:
    string filename; // File to store the score

public:
    // Constructor
    ScoreManager(std::string file);

    // Function to save the score
    void saveScore(int score);

    // Function to load the highest score
    int loadScore();
};
 

