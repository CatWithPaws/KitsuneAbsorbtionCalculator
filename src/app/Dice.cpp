#include "Dice.h"
#include "random"
#include "time.h"
#include <iostream>

void Dice::Init(){
    srand(time(NULL));
}

int Dice::RollDice(int rollCount, int diceCount)
{
    

    int resultRoll = 0;
    std::cout << "Rolling " << rollCount << "d" << diceCount << std::endl;

    for (size_t i = 0; i < rollCount; i++)
    {
        int roll = (rand() % diceCount) + 1;
        std::cout << "Rolled " << roll<< std::endl;       
        resultRoll += roll;
    }
    
    std::cout << "Summary: " << resultRoll<< std::endl;

    return resultRoll;
}