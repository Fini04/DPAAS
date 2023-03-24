#include <Arduino.h>

class Akku
{
private:
    byte akkuMagContent[3];
    uint akkuMagPos[3];

public:
    // Posotion of the akku spots
    Akku(uint pPos1, uint pPos2, uint pPos3);
    uint getFreePos();
    uint getFullPos();
    // bool getContentOf(byte x);
    // uint getPositionOf(byte x);
    void updateCap(uint x, byte full);
};