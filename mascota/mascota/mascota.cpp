#include "Critter.h"
#include "Farm.h"

using namespace std;

/// <summary>
/// Main program that initializes the critter farm, creates critters, and provides a simple menu system to interact with them.
/// The program allows the user to choose a critter, perform actions on it through the options menu, and manage the critters within a farm.
/// It continues running until the user opts to quit or all critters are gone.
/// </summary>
/// <returns>0 on successful execution.</returns>
int main() {
    int numCritters = 0;  // Initialize the number of critters
    cout << "Creating critter farm.\n";
    Farm myFarm(3);  // Create a farm with space for 3 critters
    string setName;  // Temporary variable for setting names

    srand((int)time(0));  // Seed the random number generator

    // List of default names (used in getDefaultNames function)
    string names[numNames];  // Array to store default names
    getDefaultNames(names);  // Populate the names array with default names

    bool quit = false;  // Flag to control the main loop
    int entrada = 0;  // Unused variable (could be removed or used for further input handling)

    // Create initial critters using the names array
    myFarm.CreateCritters(names, numCritters);

    while (!quit) {
        // Display a list of all critters
        cout << "\nHere are all your critters:\n";
        myFarm.RollCall();  // Print information about each critter
        cout << "\nChoose one or " << numCritters + 1 << " to exit: ";

        // Validate user input to choose a critter or exit
        int choice = getValidatedInput(1, (numCritters + 1)) - 1; // Option to choose a critter

        if (choice == numCritters) {
            quit = true;  // Exit the program if the user chooses to quit
        }
        else {
            // Retrieve the chosen critter using the getter method
            Critter* chosenCritter = myFarm.getCritterAtChoice(choice);
            if (chosenCritter != nullptr) {
                chosenCritter->OptionsMenu();  // Show the options menu for the selected critter
                myFarm.menuOption(numCritters, choice);  // Handle the chosen option

                // If no critters are left, end the program
                if (myFarm.getNumCritters() == 0) {
                    quit = true;
                }
            }
            else {
                cout << "Invalid critter selection." << endl;  // Handle invalid critter choice
                quit = true;  // Exit on invalid selection
            }
        }
    }

    // Critters are automatically deleted when the Farm object goes out of scope
    // The destructor of the Farm class handles cleanup

    cout << "\nGoodbye!\n";  // Display a goodbye message when the program ends
    return 0;  // Return 0 to indicate successful execution
}
