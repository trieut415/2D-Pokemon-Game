#include <iostream>
#include "PokemonGym.h"
#include "Building.h"

using namespace std;

PokemonGym::PokemonGym(): Building()
{
    display_code = 'G';
    state = NOT_DEFEATED;
    max_number_of_battles = 10;
    num_battle_remaining = max_number_of_battles;
    health_cost_per_battle = 1;
    PokeDollar_cost_per_battle = 1.0;
    experience_per_battle = 2;
    cout << "PokemonGym default constructed" << endl;
}

PokemonGym::PokemonGym(unsigned int max_battle, unsigned int health_loss, double PokeDollar_cost, unsigned int exp_per_battle, int in_id, Point2D in_loc):Building('G', in_id, in_loc){
    id_num = in_id;
    max_number_of_battles = max_battle;
    health_cost_per_battle = health_loss;
    experience_per_battle = exp_per_battle;
    PokeDollar_cost_per_battle = PokeDollar_cost;
    location = in_loc;
    display_code = 'G';
    state = NOT_DEFEATED;
    num_battle_remaining = max_number_of_battles;
    cout << "PokemonGym constructed" << endl;
}



double PokemonGym::GetPokeDollarCost(unsigned int battle_qty)
{
    return battle_qty * PokeDollar_cost_per_battle;
}

unsigned int PokemonGym::GetHealthCost(unsigned int battle_qty)
{
    return battle_qty * health_cost_per_battle;
}

unsigned int PokemonGym::GetNumBattlesRemaining()
{
    return num_battle_remaining;
}

bool PokemonGym::IsAbleToBattle(unsigned int battle_qty, double budget, unsigned int health)
{
    if (budget < GetPokeDollarCost(battle_qty))
    {
        return false;
    }
    else if (health < GetHealthCost(battle_qty))
    {
        return false;
    }
    else
    {
        return true;
    }
}

unsigned int PokemonGym::TrainPokemon(unsigned int battle_units)
{
    if (battle_units > num_battle_remaining)
    {
        int battles = num_battle_remaining;
        num_battle_remaining = 0;
        return experience_per_battle * battles;
    }
    else
    {
        num_battle_remaining -= battle_units;
        return experience_per_battle * battle_units;
    }
}

unsigned int PokemonGym::GetExperiencePerBattle()
{
    return experience_per_battle;
}

bool PokemonGym::Update()
{
    if (passed() == true)
        return false;
    else if (num_battle_remaining == 0)
    {
        state = DEFEATED;
        display_code = 'g';
        cout << display_code << " " << id_num << " has been beaten" << endl;
        return true;
    }
    else
    {
        return false;
    }
}

bool PokemonGym::passed()
{
    if (num_battle_remaining == 0){
        return true;
    }
    else
    {
        return false;
    }
}

void PokemonGym::ShowStatus()
{
    cout << "PokemonGymStatus: ";
    Building::ShowStatus();
    cout << "Max number of battles: " << max_number_of_battles << endl;
    cout << "Health cost per battle: " << health_cost_per_battle << endl;
    cout << "PokeDollar per battle: " << PokeDollar_cost_per_battle << endl;
    cout << "Experience per battle: " << experience_per_battle << endl;
    if (num_battle_remaining == 1)
    {
        cout << num_battle_remaining << " battle is remaining for this PokemonGym" << endl;
    }
    else
    {
        cout << num_battle_remaining << " battles are remaining for this PokemonGym" << endl;
    }
}

PokemonGym::~PokemonGym()
{
    cout << "PokemonGym destructed" << endl;
}







