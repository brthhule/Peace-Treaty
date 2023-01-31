#include <iostream>
#include "Participants.h""

using namespace std;

class PlayerAction
{
public:
	PlayerAction();
	PlayerAction(Participants *newP);
	char randomAction();
	int initialDecision();
private:
	Participants *participant;
}