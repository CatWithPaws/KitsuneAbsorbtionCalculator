#include "Dice.h"
#include <iostream>
#include "KitsuneAbsorption.h"

int KitsuneAbsorption::BasicAbsorption()
{
    if (TailsCount < 5)
    {
        return Dice::RollDice(1, 4) + WisdomModifier;
    }
    else if (TailsCount < 9)
    {
        return Dice::RollDice(2, 4) + WisdomModifier;
    }
    else
    {
        return Dice::RollDice(3, 4) + WisdomModifier;
    }
}

int *KitsuneAbsorption::Absorb(int damage)
{
    int *absorptionProperties = new int[4] {0};

    int absorbedDamage = 0;
    int healed = 0;
    absorbedDamage = VestmentAbsorption(damage,&healed);

    std::cout << "Absorbed Damage by Vest of Inverted Reality " << absorbedDamage << std::endl;
    std::cout << "Healed By Vest of Inverted Reality" << healed << std::endl;

    absorptionProperties[KT_ABSORBED_DAMAGE] += absorbedDamage;
    
    absorptionProperties[KT_HEALED] += healed;
    
    absorbedDamage = BasicAbsorption();
    
    std::cout << "Absorbed Damage by basic absorption " << absorbedDamage << std::endl;
    
    int regeneratedChakra = CalcRegeneratedChakra(absorbedDamage);

    absorptionProperties[KT_ABSORBED_DAMAGE] += absorbedDamage;
    absorptionProperties[KT_REGENERATED_CHAKRA] += regeneratedChakra;
    absorptionProperties[KT_STORED_DAMAGE] += absorbedDamage;

    return absorptionProperties;
}

int KitsuneAbsorption::VestmentAbsorption(int damage, int* healed){
    int absorbedDamage = 0;
    if(!IsVestmentsOfInvertedRealityEquipped) return 0;

    if(damage >= 20){
        absorbedDamage = (int)ceil(damage/2);
    }

    *healed = absorbedDamage;
    return absorbedDamage;


}