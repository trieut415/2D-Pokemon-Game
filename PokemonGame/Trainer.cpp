#include <iostream>
#include "Trainer.h"
#include "Point2D.h"
#include "Vector2D.h"

#include "GameObject.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Model.h"
#include "WildPokemon.h"
#include <math.h>

using namespace std;

Trainer::Trainer(): GameObject('T')
{
    is_at_center = false;
    is_IN_GYM = false;
    health = 20;
    experience = 0;
    PokeDollars = 0;
    battles_to_buy = 0;
    potions_to_buy = 0;
    current_center = NULL;
    current_gym = NULL; 
    speed = 5;
    cout << "Trainer default constructed" << endl;
}

Trainer::Trainer(char in_code): GameObject(in_code)
{
    is_at_center = false;
    is_IN_GYM = false;
    health = 20;
    experience = 0;
    PokeDollars = 0;
    battles_to_buy = 0;
    potions_to_buy = 0;
    current_center = NULL;
    current_gym = NULL;

    speed = 5;
    cout << "Trainer constructed" << endl;
    state = STOPPED;
}

Trainer::Trainer(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc): GameObject(in_loc, in_id, in_code)
{
    is_at_center = false;
    is_IN_GYM = false;
    health = 20;
    experience = 0;
    PokeDollars = 0;
    battles_to_buy = 0;
    potions_to_buy = 0;
    current_center = NULL;
    current_gym = NULL;
    speed = in_speed;
    name = in_name;
    cout << "Trainer constructed" << endl;
}

void Trainer::SetupDestination(Point2D dest)
{
    delta = (dest - location) * (speed / GetDistanceBetween(dest, location)) * (-1);
    destination = dest;

    if (state == AT_CENTER)
    {
        current_center->RemoveOneTrainer();
    }
    else if (state == IN_GYM)
    {
        current_center->RemoveOneTrainer();
    }

}

void Trainer::StartMoving(Point2D dest)
{
    SetupDestination(dest);
    if (state == FAINTED)
    {
        cout << display_code << " " << id_num << ": My pokemon have fainted. I may move but you cannot see me." << endl;
    }
    else if ((GetDistanceBetween(destination, location)) == 0)
    {
        cout << display_code << " " << id_num << ": I'm already there. See?" << endl;
        state = STOPPED;
    }
    else
    {
        state = MOVING;
        cout << display_code << " " << id_num << ": On my way." << endl;
    }
}

void Trainer::StartMovingToGym(PokemonGym* gym)
{
    Point2D gymLocation = gym->GetLocation();
    int gymId = gym->GetId();
    SetupDestination(gymLocation);
    current_gym = gym;
    if (state == FAINTED)
    {
        cout << display_code << " " << id_num << ": My pokemon have fainted so I can't move to the gym..." << endl;
    }
    else if ((GetDistanceBetween(destination, location)) == 0)
    {
        cout << display_code << " " << id_num << ": I'm already at the PokemonGym!" << endl;
        state = IN_GYM;
        is_IN_GYM = true;
    }
    else
    {
        cout << display_code << " " << id_num << ": On my way to gym" << gymId << endl;
        state = MOVING_TO_GYM;
    }
}

void Trainer::StartMovingToCenter(PokemonCenter* center)
{
    Point2D centerLocation = center->GetLocation();
    int centerId = center->GetId();
    SetupDestination(centerLocation);
    current_center = center;
    if (state == FAINTED)
    {
        cout << display_code << " " << id_num << ": My pokemon have fainted so I should have gone to the center..." << endl;   
    }
    else if ((GetDistanceBetween(destination, location)) == 0)
    {
        cout << display_code << " " << id_num << ": I'm already at the Pokemon Center!" << endl;
        state = AT_CENTER;
        is_at_center = true;
    }
    else
    {
        cout << display_code << " " << id_num << ": On my way to Center" << center->GetId() << endl;
        state = MOVING_TO_CENTER;
    }
}

void Trainer::StartBattling(unsigned int num_battles)
{
    double cost_per_fight = current_gym->GetPokeDollarCost(num_battles);
    int fights_left = current_gym->GetNumBattlesRemaining();
    bool gym_done = current_gym->passed();
    if (state == FAINTED)
    {
        cout << display_code << " " << id_num << ": My Pokemon have fainted so no more battles for me..." << endl;
    }
    else if (state != IN_GYM)
    {
        cout << display_code << " " << id_num << ": I can only battle in a PokemonGym!" << endl;
    }
    else if (fights_left < num_battles)
    {
        cout << display_code << " " << id_num << ": Cannot battle! This PokemonGym has no more trainers to battle!" << endl;
    }
    else if (PokeDollars < (cost_per_fight))
    {
        cout << display_code << " " << id_num << ": Not enough money for battles" << endl;
    }
    else
    {
        battles_to_buy = num_battles;
        state = BATTLING_IN_GYM;
        cout << display_code << id_num << " started to battle at PokemonGym " << current_gym->GetId() << " with " << num_battles << " battles" << endl;
        Update();
    }
}

void Trainer::StartRecoveringHealth(unsigned int num_potions)
{
    bool canAfford = current_center->CanAffordPotion(potions_to_buy, PokeDollars);
    cout << display_code << " " << id_num;
    if (state != AT_CENTER)
    {
        cout << "I can only recover health at a Pokemon Center" << endl;
    }
    else if (canAfford == false)
    {
        cout << "Not enough money to recover health." << endl;
    }
    else if ((current_center->GetNumPotionRemaining()) < 1)
    {
        cout << "Cannot recover! No potion remaining in this Pokemon Center";
    }
    else 
    {
        cout << "Started recovering " << num_potions << " potions at Pokemon Center " << (current_center->GetId()) << endl;
        state = RECOVERING_HEALTH;
        potions_to_buy = current_center->DistributePotion(num_potions);
        health += potions_to_buy * 5;
    }
}

void Trainer::Stop()
{
    state = STOPPED;
    cout << display_code << " " << id_num << ": Stopping..." << endl;
}

bool Trainer::hasFainted()
{
    if (health == 0)
    {
        state = FAINTED;
        return true;
    }
    else 
    {
        return false;
    }
}

bool Trainer::ShouldBeVisible()
{
    if (hasFainted() == true)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Trainer::ShowStatus()
{
    cout << name << " status: " << endl;
    GameObject::ShowStatus();
    cout << "Health: " << health << endl;
    cout << "PokeDollars: " << PokeDollars << endl;
    cout << "Experience: " << experience << endl;

    switch (state)
    {
        case 0:
        {
            cout << "stopped" << endl;
            break;
        }
        case 1:
        {
            cout << " moving at a speed of " << speed << " to destination " << destination << " at each step of " << delta << endl;
            break;
        }
        case 2:
        {
            cout << "Fainted." << endl;
        }
        case 3:
        {
            cout << " inside Pokemon Center " << (current_center->GetId()) << endl;
            break;
        }
        case 4:
        {
            cout << " inside PokemonGym " << (current_gym->GetId()) << endl;
            break;
        }
        case 5:
        { 
            cout << " heading to Pokemon Center " << (current_center->GetId()) << " at a speed of " << speed << " at each step of " << delta << endl;
            break;
        }
        case 6:
        {
            cout << " heading to PokemonGym " << (current_gym->GetId()) << " at a speed of " << speed << " at each step of " << delta << endl;
            break;
        }
        case 7:
        {
            cout << " battling in PokemonGym " << (current_gym->GetId()) << endl;
            break;
        }
        case 8:
        {
            cout << " recovering health in Pokemon Center " << (current_center->GetId()) << endl;
            break;
        }
        default:
        {
            cout << "Fainted" << endl;
        }
        
    }
}

bool Trainer::Update()
{
    switch (state)
    {
        case 0: 
        {
            return false;
            break;
        }
        case 1:
        {
            if (UpdateLocation() == true)
            {
                state = STOPPED;
                return true;
            }
            else 
            {
                state = MOVING;
                return false;
            }
            break;
        }
        case 3:
        {
            state = AT_CENTER;
            return false;
        }
        case 4:
        {
            state = IN_GYM;
            return false;
        }
        case 5:
        {            
            if (UpdateLocation() == true)
            {
                current_center->AddOneTrainer();
                state = AT_CENTER;
                return true;
            }
            else 
            {
                return false;
            }
            break;
        }
        case 6:
        {            
            if (UpdateLocation() == true)
            {
                current_gym->AddOneTrainer();
                state = IN_GYM;
                return true;
            }
            else
            {
                state = MOVING_TO_GYM;
                return false;
            }
            break;
        }
        case 7:
            {
            unsigned int healthCost = current_gym->GetHealthCost(battles_to_buy);
            health -= healthCost;

            double battleCost = current_gym->GetPokeDollarCost(battles_to_buy);
            PokeDollars -= battleCost;

            unsigned int experience_per_battle = current_gym->TrainPokemon(battles_to_buy);
            experience += experience + experience_per_battle;

            cout << "**" << name << " completed " << battles_to_buy;
            if (battles_to_buy == 1)
            {
                cout << "battle" << endl;
            }
            else
            {
                cout << "battles" << endl;
            }
            cout << "**" << name << " gained " << experience_per_battle*battles_to_buy << "experience!" << endl;

            state = IN_GYM;
            return true;
            break;
        }
        case 8:
            {
            unsigned int healthpoints_recovered = potions_to_buy * 7;
            unsigned int current_dollar_cost = current_center->GetPokeDollarCost(potions_to_buy);
            PokeDollars = PokeDollars - current_dollar_cost;

            cout << "** " << name << " recovered " << healthpoints_recovered << " health! **" << endl;
            cout << "** " << name << " bought " << potions_to_buy;
            if(potions_to_buy == 1)
            {
                cout << " potion! **" << endl;
            }
            else 
            {
                cout << " potions! **" << endl;

            state = AT_CENTER;
            return true;
            break;  
            }
        }
        default:
            return false;
    }
}

bool Trainer::UpdateLocation()
{
    cout << display_code << " " << id_num;
    if ((fabs(destination.x - location.x) < fabs(delta.x)) && (fabs(destination.y - location.y) < fabs(delta.y))){
        location.x = destination.x;
        location.y = destination.y;
        cout << " I'm there!" << endl;
    
        return true;
    }
    else 
    {
        location.x += delta.x;
        location.y += delta.y;
        for (int i = 0; i < pokeVec.size(); i++){
            pokeVec[i]->updatelocation(location);
        }

        cout << " step..." << endl;
        if (health != 0)
        health--;
        PokeDollars += GetRandomAmountOfPokeDollars();
        return false;
    }
}

Trainer::~Trainer()
{
    cout << "Trainer destructed" << endl;
}

string Trainer::GetName()
{
    return name;
}

double GetRandomAmountOfPokeDollars()
{
    srand (time (NULL) );
    double high = 2.0;
    double low = 1.0;
    double random_money = low + static_cast<double>(rand()) * static_cast<double>(high - low) / RAND_MAX;
    return random_money;
}

void Trainer::StartFollow(Model* model, int trainer_id, int wildPokemon_id)
{
    cout << "Wild Pokemon " << model->GetWildPokemonPtr(wildPokemon_id)->GetId() << model->GetWildPokemonPtr(wildPokemon_id)->GetName() << " is following " << model->GetTrainerPtr(trainer_id)->GetName() << endl;
    pokeVec.push_back(model->GetWildPokemonPtr(wildPokemon_id));
}

void Trainer::DecrementHealth()
{
    health--;
}

void Trainer::SetLocation(Point2D L)
{
    location = L;
}

void Trainer::SetId(int id)
{
    id_num = id;
}

Point2D Trainer::GetLocation()
{
    return location;
}






