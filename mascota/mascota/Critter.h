#pragma once  // Ensures the header file is included only once in the compilation process

#include <string>
#include <iostream>
#include <random>
#include <stdlib.h>

using namespace std;

const int numNames = 100; // Maximum number of default names for critters

// Function declarations

/// <summary>
/// Validates user input, ensuring it falls within the specified range.
/// </summary>
/// <param name="min">Minimum valid value.</param>
/// <param name="max">Maximum valid value.</param>
/// <returns>Validated integer input within the range.</returns>
int getValidatedInput(int min, int max);

/// <summary>
/// Populates an array with default names for critters.
/// </summary>
/// <param name="names">Array to store default names.</param>
void getDefaultNames(string names[]);

/// <summary>
/// Represents a virtual pet (Critter) with attributes such as hunger, boredom, and time.
/// The Critter class provides functionalities for interaction and state management.
/// </summary>
class Critter
{
public:

    /// <summary>
    /// Constructor for initializing a Critter with a name, hunger level, boredom level, and time factor.
    /// Default values are provided for flexibility.
    /// </summary>
    /// <param name="name">Critter's name (default: "New Critter").</param>
    /// <param name="hunger">Initial hunger level (default: 0, meaning not hungry).</param>
    /// <param name="boredom">Initial boredom level (default: 0, meaning not bored).</param>
    /// <param name="time">Time factor affecting Critter's behavior (default: 1).</param>
    Critter(const string& name = "New Critter", int hunger = 0, int boredom = 0, int time = 1);

    /// <summary>
    /// Destructor for the Critter class, responsible for cleanup when an instance is destroyed.
    /// </summary>
    ~Critter();

    /// <summary>
    /// Retrieves the current hunger level of the Critter.
    /// </summary>
    /// <returns>Hunger level as an integer.</returns>
    int GetHunger() const;

    /// <summary>
    /// Modifies the Critter's hunger level based on internal logic.
    /// </summary>
    void SetHunger();

    /// <summary>
    /// Structure representing a type of food that can affect the Critter's hunger level.
/// </summary>
    struct Food {
        string name;  // Name of the food
        int hungerValue;  // The amount by which hunger is reduced when consumed
    };

    /// <summary>
    /// Retrieves the Critter's name.
    /// </summary>
    /// <returns>The name of the Critter as a string.</returns>
    string GetName() const;

    /// <summary>
    /// Modifies the Critter's name based on user input or logic.
    /// </summary>
    void SetName();

    /// <summary>
    /// Retrieves the current boredom level of the Critter.
    /// </summary>
    /// <returns>Boredom level as an integer.</returns>
    int GetBoredom() const;

    /// <summary>
    /// Sets the Critter's boredom level to a specified value.
    /// </summary>
    /// <param name="boredom">New boredom level.</param>
    void SetBoredom(int boredom);

    /// <summary>
    /// Makes the Critter talk, displaying its current mood based on hunger and boredom levels.
    /// </summary>
    void Talk();

    /// <summary>
    /// Allows the user to play with the Critter, reducing boredom.
    /// </summary>
    void Play();

    /// <summary>
    /// Displays a greeting message from the Critter.
    /// </summary>
    void Greet();

    /// <summary>
    /// Tells a story related to the Critter.
    /// </summary>
    void Story();

    /// <summary>
    /// Displays the available options for interacting with the Critter.
    /// </summary>
    void OptionsMenu();

    /// <summary>
    /// Friend function that allows another function to peek at the Critter's private attributes.
    /// </summary>
    /// <param name="aCritter">The Critter object to inspect.</param>
    friend void Peek(const Critter& aCritter);

    /// <summary>
    /// Overloads the output stream operator to print Critter details in a formatted way.
    /// </summary>
    /// <param name="out">Output stream reference.</param>
    /// <param name="critter">Critter object to display.</param>
    /// <returns>Reference to the output stream.</returns>
    friend std::ostream& operator<<(std::ostream& out, const Critter& critter);

private:

    int m_Hunger; // Represents how hungry the Critter is (higher value means more hunger)
    int m_Boredom; // Represents how bored the Critter is (higher value means more boredom)
    string m_Name; // The name of the Critter
    int m_time; // Time factor influencing Critter's activities

    /// <summary>
    /// Increments hunger and boredom over time to simulate the passage of time.
    /// </summary>
    /// <param name="time">The amount of time that has passed.</param>
    void passTime(int time);

    /// <summary>
    /// Generates a Critter figure based on an integer input.
    /// </summary>
    /// <param name="figura">An integer representing the figure type.</param>
    /// <returns>A string representation of the Critter figure.</returns>
    string Critter_figure(int figura);
};
