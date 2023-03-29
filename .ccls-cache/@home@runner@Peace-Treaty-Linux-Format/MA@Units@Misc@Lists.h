#ifndef LISTS_H
#define LISTS_H

#include <iostream>
#include <string>

#include "OtherFunctions.h"

class Lists
{
public:
	//Constructors
    Lists(int identifier);
    void listOfHelp ();
    char listOfActions();

    private:
        int identifier;
			OtherFunctions OF;
};

#endif