#include "WildPokemon.h"

WildPokemon::WildPokemon(): GameObject('W')
{
    attack = 5;
    health = 2;
    variant = false;
    in_combat = false;
    state = IN_ENVIRONMENT;
}

WildPokemon::WildPokemon(string in_name, double in_attack, double in_health, bool in_variant, int in_id, Point2D in_loc): GameObject(in_loc, in_id, 'W')
{
    name = in_name;
    attack = in_attack;
    variant = in_variant;
    id_num = in_id;
    location = in_loc;
    health = in_health;
    state = IN_ENVIRONMENT;
}

void WildPokemon::follow(Trainer* t)
{
    current_trainer = t;
    state = IN_TRAINER;
    location = t->GetLocation();
}

bool WildPokemon::get_variant()
{
    return variant;
}

double WildPokemon::get_attack()
{
    return attack;
}

double WildPokemon::get_health()
{
    return health;
}

bool WildPokemon::get_in_combat()
{
    return in_combat;
}


bool WildPokemon::Update()
{
    if (health <= 0)
    {
        state = DEAD;
        return false;
    }
    else if (current_trainer != NULL)
    {
        state = IN_TRAINER;
        current_trainer->DecrementHealth();
        location = current_trainer->GetLocation();
        return true;
    }
    else
    {
        state = IN_ENVIRONMENT;
        return true;
    }
}

void WildPokemon::ShowStatus()
{
    cout << "Wild Pokemon Status: " << endl;
    GameObject::ShowStatus();
    cout << "Health: " << health << endl;

    if (state == IN_ENVIRONMENT)
    {
        cout << name << " is in environment" << endl;
    }
    else if (state == DEAD)
    {
        cout << name << " is DEAD" << endl;
    }
    else if (state == IN_TRAINER)
    {
        cout << name << " is following trainer " << current_trainer->GetId() << endl;
    }
}

bool WildPokemon::IsAlive()
{
    if (state == DEAD)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool WildPokemon::ShouldBeVisible()
{
    if (IsAlive() == true){
        return true;
    }
    else
    {
        return false;
    }
}

void WildPokemon::SetState(int s)
{
    if (s == 0)
    {
        state = IN_ENVIRONMENT;
    }
    else if (s == 1)
    {
        state = DEAD;
    }
    else if (s == 2)
    {
        state = IN_TRAINER;
    }
    else
    {
        cout << "Not valid State" << endl;
    }
}
void WildPokemon::updatelocation(Point2D loc)
{
    location = loc;
}

void WildPokemon::SetId(int id)
{
    id_num = id;
}


void WildPokemon::SetLocation(Point2D loc)
{
    location = loc;
}

string WildPokemon::GetName()
{
    return name;
}

Point2D WildPokemon::GetLocation()
{
    return location;
}


