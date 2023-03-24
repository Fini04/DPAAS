#include "./hpp/akku.hpp"
// Battery-Magazine overview
Akku::Akku(uint pPos1, uint pPos2, uint pPos3)
{
    akkuMagPos[0] = pPos1;
    akkuMagPos[1] = pPos2;
    akkuMagPos[2] = pPos3;

    akkuMagContent[0] = 0; // Magazine empty
    akkuMagContent[1] = 1; // Magazine full
    akkuMagContent[2] = 0;
}
// returns empty magazine position
uint Akku::getFreePos()
{
    for (size_t i = 0; i < sizeof(akkuMagContent); i++)
    {
        if (akkuMagContent[i] == 0)
        {
            return akkuMagPos[i];
        }
    }
    return 0;
}
// returns full magazine position
uint Akku::getFullPos()
{
    for (byte i = 2; i >= 0; i--)
    {
        if (akkuMagContent[i] == 1)
        {
            return akkuMagPos[i];
        }
    }
    // return;
}
// sets new loaded magazine position full
void Akku::updateCap(uint x, byte full)
{
    for (byte i = 0; i < sizeof(akkuMagContent); i++)
    {
        if (x == akkuMagPos[i])
        {
            akkuMagContent[i] = full;
        }
    }
}