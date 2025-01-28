#pragma once
#include <vector>
#include "Critter.h"
using namespace std;
class Farm
{
public:
	Farm(int space = 1);
	~Farm();
	void Add(Critter* aCritter);
	void RollCall() const;
	void menuOption(const Critter& aCritter, int& numCritters);
	// Declare the CreateCritters function
	void CreateCritters(const std::string names[], int& numCritters);
	//vector<Critter> m_Critters; 

	 // Public getter functions
	Critter* getCritterAtIndex(int index) const;  // Get critter by index
	int getNumCritters() const;  // Get the number of critters


private:
	std::vector<Critter*> m_Critters; // Vector of pointers to Critter
};