#include <iostream>
#include "PokemonCenter.h"

using namespace std;

PokemonCenter::PokemonCenter(): Building()
{
    display_code = 'C';
    potion_capacity = 100;
    num_potions_remaining = potion_capacity;
    pokedollar_cost_per_potion = 5;
    state = POTIONS_AVAILABLE;
    cout << "PokemonCenter default constructed" << endl;
}

PokemonCenter::PokemonCenter(int in_id, double potion_cost, unsigned int potion_cap, Point2D in_loc): Building('C', in_id, in_loc)
{
    id_num = in_id;
    location = in_loc;
    pokedollar_cost_per_potion = potion_cost;
    potion_capacity = potion_cap;
    display_code = 'C';
    num_potions_remaining = potion_capacity;
    state = POTIONS_AVAILABLE;
    cout << "PokemonCenter constructed" << endl;
}



bool PokemonCenter::HasPotions()
{
    if (potion_capacity == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

unsigned int PokemonCenter::GetNumPotionRemaining()
{
    return num_potions_remaining;
}

bool PokemonCenter::CanAffordPotion(unsigned int potion, double budget)
{
    if (potion*pokedollar_cost_per_potion > budget)
    {
        return false;
    }
    else
    {
        return true;
    }
}

double PokemonCenter::GetPokeDollarCost(unsigned int potion)
{
    double totCost = potion * pokedollar_cost_per_potion;
    return totCost;
}

unsigned int PokemonCenter::DistributePotion(unsigned int potion_needed)
{
    if (num_potions_remaining >= potion_needed)
    {
        num_potions_remaining -= potion_needed;
        return potion_needed; 
    }
    else
    {
        int potions = num_potions_remaining;
        num_potions_remaining = 0;
        return potions;
    }
}

bool PokemonCenter::Update()
{
    if (num_potions_remaining == 0)
    {
        display_code = 'c';
        state = NO_POTIONS_AVAILABLE;
        cout << "PokemonCenter (" << id_num << ") has ran out of potions." << endl;
        return true;
    }
    else
    {    
        return false;
    }
}

void PokemonCenter::ShowStatus()
{
    cout << "PokemonCenter Status: " << endl;
    Building::ShowStatus();
    cout << "PokeDollars per potion: " << pokedollar_cost_per_potion << endl;
    if (num_potions_remaining != 1)
    {
        cout << "has " << num_potions_remaining << " potions remaining." << endl;
    }
    else
    {
        cout << "has " << num_potions_remaining << " potion remaining." << endl;
    }
}

PokemonCenter::~PokemonCenter()
{
    cout << "PokemonCenter destructed" << endl;
}


