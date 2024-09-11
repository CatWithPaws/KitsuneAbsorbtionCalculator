#include "Dice.h"
#include <iostream>
#include "KitsuneAbsorption.h"

int KitsuneAbsorption::BasicAbsorption()
{
    if (TailsCount < 5)
    {
        return Dice::RollDice(1, 6) + WisdomModifier;
    }
    else if (TailsCount < 9)
    {
        return Dice::RollDice(2, 6) + WisdomModifier;
    }
    else
    {
        return Dice::RollDice(3, 6) + WisdomModifier;
    }
}

int *KitsuneAbsorption::Absorb(int physicsDamage, int magicDamage)
{
    int *absorptionProperties = new int[4] {0};

    int absorbedPhysDamage = 0;
    int absorbedMagDamage = 0;

    int healed = 0;

    absorbedMagDamage = VestmentAbsorption(magicDamage,&healed);

    std::cout << "Absorbed Mag Damage by Vest of Inverted Reality " << absorbedMagDamage << std::endl;
    std::cout << "Healed By Vest of Inverted Reality" << healed << std::endl;

    absorptionProperties[KT_HEALED] += healed;
    absorptionProperties[KT_ABSORBED_DAMAGE] += absorbedMagDamage;
    
    int absorbedMagDamageByBasicAbsorption = BasicAbsorption();
    absorptionProperties[KT_ABSORBED_DAMAGE] += absorbedMagDamageByBasicAbsorption;
    absorbedMagDamage += absorbedMagDamageByBasicAbsorption;

    std::cout << "Absorbed Magic Damage by basic absorption " << absorbedMagDamage << std::endl;

    int regeneratedChakra = CalcRegeneratedChakra(absorbedMagDamage);
    

    absorptionProperties[KT_REGENERATED_CHAKRA] += regeneratedChakra;

    absorbedPhysDamage = BasicAbsorption();
    absorptionProperties[KT_STORED_DAMAGE] += absorbedPhysDamage;

    std::cout << "Absorbed Phys Damage by basic absorption " << absorbedPhysDamage << std::endl;

    return absorptionProperties;
}

int KitsuneAbsorption::VestmentAbsorption(int damage, int* healed){
    if(!IsVestmentsOfInvertedRealityEquipped) return 0;
    int absorbedDamage = 0;
    if(damage >= 20){
        absorbedDamage = (int)ceil((float)damage/2);
        int healsCount = (int)ceil((float)absorbedDamage/10);
        *healed += WisdomModifier;
        *healed += Dice::RollDice(healsCount,8);
    }

    return absorbedDamage;


}