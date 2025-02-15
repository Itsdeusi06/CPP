#include "ScoreManager.h"

// Constructor to initialize filename
ScoreManager::ScoreManager(string file) : filename(file) {}

// Function to save score
void ScoreManager::saveScore(int score) {
    ofstream file(filename);
    if (file.is_open()) {
        file << score;
        file.close();
    }
}

// Function to load the highest score
int ScoreManager::loadScore() {
    ifstream file(filename);
    int score = 0;
    if (file.is_open()) {
        file >> score;
        file.close();
    }
    return score;
}
