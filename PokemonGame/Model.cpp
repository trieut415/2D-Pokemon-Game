#include <iostream>
#include "Model.h"
#include "GameObject.h"
#include "Trainer.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "View.h"
#include "WildPokemon.h"
#include "Point2D.h"

using namespace std;

Model::Model()
{
    time = 0;
    Point2D c1_loc(1,20);    
    PokemonCenter* c1Ptr = new PokemonCenter(1, 1, 100, c1_loc);
    object_ptrs.push_back(c1Ptr); 
    active_ptrs.push_back(c1Ptr); 
    center_ptrs.push_back(c1Ptr); 

    Point2D c2_loc(10,20);
    PokemonCenter* c2Ptr = new PokemonCenter(2, 2, 200, c2_loc);
    object_ptrs.push_back(c2Ptr); 
    active_ptrs.push_back(c2Ptr);
    center_ptrs.push_back(c2Ptr); 

    Point2D t1_loc(5,1);
    Trainer* t1Ptr = new Trainer("Ash", 1, 'T', 1, t1_loc);
    object_ptrs.push_back(t1Ptr); 
    active_ptrs.push_back(t1Ptr); 
    trainer_ptrs.push_back(t1Ptr); 

    Point2D t2_loc(10,1);
    Trainer* t2Ptr = new Trainer("Misty", 2, 'T', 2, t2_loc);
    object_ptrs.push_back(t2Ptr);
    active_ptrs.push_back(t2Ptr); 
    trainer_ptrs.push_back(t2Ptr); 

    Point2D g1_loc(0,0);
    PokemonGym* g1Ptr = new PokemonGym(10, 1, 2, 3, 1, g1_loc);
    object_ptrs.push_back(g1Ptr); 
    active_ptrs.push_back(g1Ptr); 
    gym_ptrs.push_back(g1Ptr); 

    Point2D g2_loc(5,5);
    PokemonGym* g2Ptr = new PokemonGym(20, 5, 7.5, 4, 2, g2_loc);
    object_ptrs.push_back(g2Ptr);
    active_ptrs.push_back(g2Ptr); 
    gym_ptrs.push_back(g2Ptr); 

    Point2D w1_loc(10,12);
    WildPokemon* w1ptr = new WildPokemon("Snorlax", 5, 5, false, 1, w1_loc);
    object_ptrs.push_back(w1ptr); 
    active_ptrs.push_back(w1ptr); 
    wildpokemon_ptrs.push_back(w1ptr);

    Point2D w2_loc(15, 5);
    WildPokemon* w2ptr = new WildPokemon("Pikachu", 5, 5, false, 2, w2_loc);
    object_ptrs.push_back(w2ptr); 
    active_ptrs.push_back(w2ptr); 
    wildpokemon_ptrs.push_back(w2ptr);

    cout << "Model default constructed" << endl;
    ShowStatus();
}

Model::~Model()
{
    object_ptrs.clear();
    cout << "Model destructed" << endl;
}

Trainer* Model::GetTrainerPtr(int id)
{
    for (auto i = trainer_ptrs.begin(); i != trainer_ptrs.end(); i++)
    {
        auto ptr = *i;
        if (ptr != NULL)
        {
            if (ptr->GetId() == id)
                return ptr;
        }
        else
        {
            return 0;
        }
    }
    return 0;
    
}

PokemonCenter* Model::GetPokemonCenterPtr(int id)
{
    for (auto i = center_ptrs.begin(); i != center_ptrs.end(); i++)
    {
        auto ptr = *i;
        if (ptr != NULL)
        {
            if (ptr->GetId() == id)
            {
                return ptr;
            }
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

PokemonGym* Model::GetPokemonGymPtr(int id)
{
    for (auto i = gym_ptrs.begin(); i != gym_ptrs.end(); i++)
    {
        auto ptr = *i;
        if (ptr != NULL)
        {
            if (ptr->GetId() == id)
                return ptr;
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

WildPokemon* Model::GetWildPokemonPtr(int id)
{
    for (auto i = wildpokemon_ptrs.begin(); i != wildpokemon_ptrs.end(); i++)
    {
        auto ptr = *i;
        if (ptr != NULL)
        {
            if (ptr->GetId() == id)
            {
                return ptr;
            }
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

bool Model::Update()
{
    time++;
    for (auto i = active_ptrs.begin(); i != active_ptrs.end(); i++)
    {
        auto ptr = *i;
        if (ptr->ShouldBeVisible() == false)
        {
            active_ptrs.erase(i);
            cout << "Dead object removed" << endl;
        }
    }

    bool maybe = false;
    for (auto i = object_ptrs.begin(); i != object_ptrs.end(); i++)
    {
        auto ptr = *i;
        bool call = ptr->Update();
        if (call == true)
        {
            int count = 0;
            for (auto j = gym_ptrs.begin(); j != gym_ptrs.end(); j++)
            {
                auto gptr = *j;
                if (gptr->passed()){
                    count++;
                    
                }
            }
            if (count == trainer_ptrs.size())
            {
                cout << "GAME OVER: You lose! All of your Trainers' pokemon have fainted!" << endl;
                exit(0);
            }
            maybe = true;
        }
    }
    checkTrainerWildPokemon();   
    return maybe;
}

void Model::ShowStatus()
{
    cout << "Time: " << time << endl;
    for (auto i = object_ptrs.begin(); i != object_ptrs.end(); i++)
    {
        auto ptr = *i;
        ptr->ShowStatus();
    }
}

void Model::Display(View& view)
{
    view.Clear();
    for (auto i = active_ptrs.begin(); i != active_ptrs.end(); i++)
    {
        auto ptr = *i;
        view.Plot(ptr);
    }
    view.Draw();
}

bool Model::checkTrainerWildPokemon()
{
    Point2D w1_loc = this->GetWildPokemonPtr(1)->GetLocation();
    Point2D w2_loc = this->GetWildPokemonPtr(2)->GetLocation();
    Point2D t1_loc = this->GetTrainerPtr(1)->GetLocation();
    Point2D t2_loc = this->GetTrainerPtr(2)->GetLocation();

    if (GetDistanceBetween(w1_loc, t1_loc) == 0)
    {
        GetTrainerPtr(1)->StartFollow(this, 1, 1);
        WildPokemon* wild = this->GetWildPokemonPtr(1);
        wild->follow(GetTrainerPtr(1));
        wild->SetState(2);
        return true;
    }
    else if (GetDistanceBetween(w1_loc, t2_loc) == 0)
    {
        GetTrainerPtr(2)->StartFollow(this, 2, 1);
        WildPokemon* wild = this->GetWildPokemonPtr(1);
        wild->follow(GetTrainerPtr(1));
        wild->SetState(2);
        return true;
    }
    else if (GetDistanceBetween(w2_loc, t1_loc) == 0)
    {
        GetTrainerPtr(1)->StartFollow(this, 1, 2); 
        WildPokemon* wild = this->GetWildPokemonPtr(2);
        wild->follow(GetTrainerPtr(2));
        wild->SetState(2);
        return true;
    }
    else if (GetDistanceBetween(w2_loc, t2_loc) == 0)
    {
        GetTrainerPtr(2)->StartFollow(this, 2, 2); 
        WildPokemon* wild = this->GetWildPokemonPtr(2);
        wild->follow(GetTrainerPtr(2));
        wild->SetState(2);
        return true;
    }
    else 
    {
        return false;
    }

}
int Model::GetWP() 
{
    return wildpokemon_ptrs.size();
}

int Model::GetSize() 
{
    return object_ptrs.size();
}

