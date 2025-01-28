#pragma once
#include <string>
#include <iostream>
#include <random>
#include <stdlib.h>

using namespace std;

const int numNames = 100; // Maximum number of names 

// Input validation function to avoid repetition
int getValidatedInput(int min, int max);
// Input for get default names
void getDefaultNames(string names[]);

class Critter
{
public:
    
    // Constructor that initializes both hunger and name    
    Critter(const string& name = "New Critter", int hunger = 0, int boredom = 0, int time = 1);   ///// hunger 0 = no gana, boredom 0 = no aburrit hunger 10 = molta gana, boredom 10 = molt aburrit /////
    ~Critter();
    // Getter and setter for hunger
    int GetHunger() const;
    void SetHunger();
    struct Food {
        string name;
        int hungerValue;
    };

    // Getter and setter for name
    string GetName() const;
    void SetName();

    // Getter and setter for boredom
    int GetBoredom() const;
    void SetBoredom(int boredom);

    // Member functions for critter actions
    void Talk();
    void Play();
    void Greet();
    void Story();
    void OptionsMenu();
    

    // Declare friend functions
    friend void Peek(const Critter& aCritter);
    friend std::ostream& operator<<(std::ostream& out, const Critter& critter);

private:
    
    int m_Hunger;
    int m_Boredom;
    string m_Name;
    int m_time;
    void passTime(int time);
    string Critter_figure(int figura);
};

