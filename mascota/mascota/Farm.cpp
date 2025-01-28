#include "Farm.h"



Farm::Farm(int space) {
	m_Critters.reserve(space);
}

Farm::~Farm() {
    for (Critter* critter : m_Critters) {
            delete critter; // Delete each dynamically allocated Critter
        }
        cout << "All critters have been deleted." << endl;
}

void Farm::menuOption(const Critter& aCritter, int& numCritters) {

    int entrada = 0;
    // List of default names (used in getDefaultNames function)
    string names[numNames];      // Array for default 
    // Populate the names array
    getDefaultNames(names);

    cout << "\n\nChoose an option:";
    cout << "\n\t0 - EXIT\n\t1 - Create critter\n\n";

    entrada = getValidatedInput(0, 2);

    switch (entrada) {
    case 0:
        break;
    case 1:
        CreateCritters(names, numCritters);
        break;
    default:
        cout << "Invalid option. Try again.\n";
    }

}

void Farm::Add(Critter* aCritter) {
	m_Critters.push_back(aCritter);
}





void Farm::RollCall() const {
    int i = 1;

    // Verifica que haya critters para mostrar
    if (m_Critters.empty()) {
        cout << "No critters available." << endl;
        return;
    }

    for (std::vector<Critter*>::const_iterator iter = m_Critters.begin(); iter != m_Critters.end(); ++iter) {
        cout << "\t" << i << " - " << **iter << " here." << endl;  // Use overloaded << operator
        i++;
    }
}


void Farm::CreateCritters(const std::string names[], int& numCritters) {
    int newCritters = 0; // Número de critters a crear en esta llamada
    cout << "newcritters i num Critters funcio crate critters " << newCritters << " " << numCritters;
    cout << "How many critters would you like to create? ";
    cin >> newCritters;

    // Añadir nuevos critters
    for (int i = 0; i < newCritters; ++i) {
        int randomIndex = rand() % 100; // Índice aleatorio para los nombres
        Critter* newCritter = new Critter(names[randomIndex], rand() % 6, rand() % 6);  // Dynamically allocate a new Critter 
        Add(newCritter);  // Add the new critter to the farm  
    }

    // Incrementar el número total de critters creados
    numCritters += newCritters;
}

Critter* Farm::getCritterAtIndex(int index) const {
    if (index >= 0 && index < m_Critters.size()) {
        return m_Critters[index];  // Return the critter pointer at the given index
    }
    return nullptr;  // Return nullptr if the index is invalid
}
int Farm::getNumCritters() const {
    return m_Critters.size();  // Return the number of critters in the farm
}