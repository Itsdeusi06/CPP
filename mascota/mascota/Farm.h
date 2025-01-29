#pragma once  // Ensures the header file is included only once during compilation

#include <vector>
#include "Critter.h"

using namespace std;

/// <summary>
/// The Farm class manages a collection of Critters. 
/// It allows adding, displaying, creating, and deleting critters, as well as managing their interactions.
/// </summary>
class Farm
{
public:
	/// <summary>
	/// Constructor for the Farm class.
	/// Initializes the farm and reserves space for a given number of critters.
	/// </summary>
	/// <param name="space">The initial number of critter slots to reserve (default is 1).</param>
	Farm(int space = 1);

	/// <summary>
	/// Destructor for the Farm class.
	/// Cleans up dynamically allocated Critter objects.
	/// </summary>
	~Farm();

	/// <summary>
	/// Adds a new Critter to the farm.
	/// </summary>
	/// <param name="aCritter">Pointer to the Critter object to be added.</param>
	void Add(Critter* aCritter);

	/// <summary>
	/// Calls each Critter to "speak" (displays their status).
	/// </summary>
	void RollCall() const;

	/// <summary>
	/// Displays and handles the menu options for interacting with the farm.
	/// Options include exiting, changing, creating, or deleting critters.
	/// </summary>
	/// <param name="numCritters">Reference to the total number of critters in the farm.</param>
	/// <param name="choice">The index of the currently selected critter.</param>
	void menuOption(int& numCritters, int choice);

	/// <summary>
	/// Creates new Critters with default names and adds them to the farm.
	/// </summary>
	/// <param name="names">Array of default names for new Critters.</param>
	/// <param name="numCritters">Reference to the total number of critters, which is updated accordingly.</param>
	void CreateCritters(const std::string names[], int& numCritters);

	/// <summary>
	/// Deletes a Critter from the farm based on the specified choice index.
	/// </summary>
	/// <param name="choice">The index of the Critter to be removed.</param>
	void delete_element(int choice);

	/// <summary>
	/// Retrieves a pointer to a Critter at a specified index.
	/// </summary>
	/// <param name="choice">The index of the desired Critter.</param>
	/// <returns>Pointer to the selected Critter, or nullptr if the index is invalid.</returns>
	Critter* getCritterAtChoice(int choice) const;

	/// <summary>
	/// Gets the total number of critters currently in the farm.
	/// </summary>
	/// <returns>The number of Critters in the farm.</returns>
	int getNumCritters() const;

private:
	vector<Critter*> m_Critters; // Vector that stores pointers to Critter objects
};
