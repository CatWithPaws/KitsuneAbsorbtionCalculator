#include <cmath>

#define KT_ABSORBED_DAMAGE 0
#define KT_REGENERATED_CHAKRA 1
#define KT_STORED_DAMAGE 2
#define KT_HEALED 3

class KitsuneAbsorption{
    public:

    int Level = 0;
    int WisdomModifier = 0;
    int TailsCount = 1;
    int AbsorptionCapacity = 0;
    bool IsVestmentsOfInvertedRealityEquipped = false; //Обладунок перевернутої реалності
    bool IsCrystalOfNineTailsEquiped = false;

    KitsuneAbsorption(int level, int wisdomModifier, int tailsCount)
    : Level(level),WisdomModifier(wisdomModifier),TailsCount(tailsCount), AbsorptionCapacity((5 * wisdomModifier) + level)
    {}

    int* Absorb(int phycDamage, int magDamage);
    int BasicAbsorption();
    int VestmentAbsorption(int damage,int* healed);
    inline int CalcRegeneratedChakra(int absorbedDamage)  { return (int)trunc((float)absorbedDamage/(float)10);}
};