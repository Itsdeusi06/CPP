#include "Farm.h"   


/// <summary>
/// Constructor for Farm that reserves space for Critters.
/// Note: This does NOT create Critters, it only reserves space in the vector.
/// </summary>
/// <param name="space">Number of slots to reserve for Critters.</param>
Farm::Farm(int space) {
	m_Critters.reserve(space);
}

/// <summary>
/// Destructor of Farm, which deletes all Critters in the vector.
/// </summary>
Farm::~Farm() {
    for (Critter* critter : m_Critters) {
        delete critter; // Free allocated memory
    }
    m_Critters.clear(); // Ensure vector is empty after deletion
    cout << "All critters have been deleted." << endl;
}


/// <summary>
/// Funtion for the menu Option of Exit, change, create or delete critter
/// </summary>
/// <param name="numCritters">This saves the total number of Critters are, came from mascota.cpp</param>
/// <param name="choice">This saves the choice of the critter is beeing used now, cames form mascota.cpp</param>
void Farm::menuOption(int& numCritters, int choice) {

    // Users menu option
    int entrada = 0;
    // Array for default
    string names[numNames];       
    // Populate the names array
    getDefaultNames(names);

    cout << "\n\nChoose an option:";
    cout << "\n\t0 - EXIT/Change Critter\n\t1 - Create critter\n\t2 - Delete critter\n\n";

    // This funcion check if the Input of entrada is between 0 n 2
    entrada = getValidatedInput(0, 2);

    // switch to do an option or an other
    switch (entrada) {
    case 0: // if its 0 will go to start, where you can chose a critter or leve with the number specified
        break;
    case 1: // if its 1 will go to the funcion that create new critters
        CreateCritters(names, numCritters);
        break;
    case 2: // if its 2 will go to the function that delete the actual critter
        delete_element(choice);
        numCritters--; // The number of critters must decrease 1 (i should put this in the funcion so i can called from the main with out makeing the decrease)
        break;
    default:    // hard to get this option bc entrada is allready beeing checked
        cout << "Invalid option. Try again.\n";
    }

}

/// <summary>
/// This funcion will put the new critters crated on the vector 
/// </summary>
/// <param name="aCritter">this pass the point of the critter,ro later put it in the vector, cames from the create critter funciton</param>
void Farm::Add(Critter* aCritter) {
	m_Critters.push_back(aCritter);
}

/// <summary>
/// Deletes a Critter at a given index.
/// </summary>
/// <param name="choice">Index of the Critter to delete.</param>
void Farm::delete_element(int choice) {
    if (choice < 0 || choice >= m_Critters.size()) {
        cout << "Invalid choice. No critter deleted." << endl;
        return;
    }

    delete m_Critters[choice]; // Free allocated memory
    m_Critters.erase(m_Critters.begin() + choice); // Remove from vector
}


/// <summary>
/// Displays all Critters in the Farm with their hunger and boredom levels.
/// </summary>
void Farm::RollCall() const {
    if (m_Critters.empty()) {
        cout << "No critters available." << endl;
        return;
    }

    int i = 1;
    for (const Critter* critter : m_Critters) {
        cout << "\t" << i++ << " - " << *critter << " here." << endl; // use overloaded << funciton
    }
}

/// <summary>
/// Creates new Critters with random hunger and boredom levels.
/// </summary>
/// <param name="names">Array of available names.</param>
/// <param name="numCritters">Reference to the total Critter count.</param>
void Farm::CreateCritters(const std::string names[], int& numCritters) {
    int newCritters = 0;

    cout << "How many critters would you like to create? ";
    cin >> newCritters;

    // Input validation
    if (cin.fail() || newCritters < 1) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. No critters created.\n";
        return;
    }

    for (int i = 0; i < newCritters; ++i) {
        int randomIndex = rand() % 100;
        Critter* newCritter = new Critter(names[randomIndex], rand() % 6, rand() % 6);
        Add(newCritter);
    }

    numCritters += newCritters;
}


/// <summary>
/// function to get critter choice, with pointer form
/// </summary>
/// <param name="choice">this is the number of the actual critter, came from mascota.cpp</param>
/// <returns>return the critter pointer of the choice</returns>
Critter* Farm::getCritterAtChoice(int choice) const {
    // if the choice is between 0 and the number of the vector
    if (choice >= 0 && choice < m_Critters.size()) {
        return m_Critters[choice];  // Return the critter pointer at the given choice
    }
    return nullptr;  // Return nullptr if the index is invalid 
}

/// <summary>
/// function to get the max actual number of the vector farm
/// </summary>
/// <returns>return the size of the vector</returns>
int Farm::getNumCritters() const {
    return m_Critters.size();  // Return the number of critters in the farm
}