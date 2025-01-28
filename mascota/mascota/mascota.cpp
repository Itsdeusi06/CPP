#include "Critter.h"
#include "Farm.h"

using namespace std;

int main() {
    int numCritters = 0;  // Initialize the number of critters
    cout << "Creating critter farm.\n";
    Farm myFarm(3);
    string setName;

    srand((int)time(0));

    // List of default names (used in getDefaultNames function)
    string names[numNames];  // Array for default names
    getDefaultNames(names);  // Populate the names array

    bool quit = false;
    int entrada = 0;

    // Create initial critters
    myFarm.CreateCritters(names, numCritters);

    while (!quit) {
        cout << "numCritters before loop: " << numCritters << endl;

        // Display all critters
        cout << "\nHere are all your critters:\n";
        myFarm.RollCall();
        cout << "\nChoose one or " << numCritters + 1 << " to exit: ";

        int choice = getValidatedInput(1, (numCritters + 1)) - 1; // Option to choose a critter

        if (choice == numCritters) {
            quit = true;
        }
        else {
            // Access critter using the getter method
            Critter* chosenCritter = myFarm.getCritterAtIndex(choice);
            if (chosenCritter != nullptr) {
                chosenCritter->OptionsMenu();  // Assuming this function exists for the Critter object
                myFarm.menuOption(*chosenCritter, numCritters);

                // Check if there are any critters left
                if (myFarm.getNumCritters() == 0) {
                    quit = true;
                }
            }
            else {
                cout << "Invalid critter selection." << endl;
                quit = true;
            }
        }
    }

    // At the end, critters are deleted by the destructor of the Farm class
    // No need to manually call Delete() here

    cout << "\nGoodbye!\n";
    return 0;
}
