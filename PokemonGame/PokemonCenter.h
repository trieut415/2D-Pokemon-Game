#ifndef POKEMONCENTER_H
#define POKEMONCENTER_H

#include <iostream>
#include "Building.h"
#include "Point2D.h"
using namespace std;

class PokemonCenter: public Building
{
    enum PokemonCenterStates
    {
        POTIONS_AVAILABLE = 0,
        NO_POTIONS_AVAILABLE = 1
    };
public:
    PokemonCenter();
    PokemonCenter(int, double, unsigned int, Point2D);
    
    bool HasPotions();
    unsigned int GetNumPotionRemaining();
    bool CanAffordPotion(unsigned int, double);
    double GetPokeDollarCost(unsigned int);
    unsigned int DistributePotion(unsigned int);
    bool Update();
    void ShowStatus();
    ~PokemonCenter();
private:
    unsigned int potion_capacity;
    unsigned int num_potions_remaining;
    double pokedollar_cost_per_potion;
};

#endif

