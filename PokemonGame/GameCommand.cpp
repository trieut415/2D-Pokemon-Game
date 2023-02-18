#include "GameCommand.h"
#include "Point2D.h"
#include <cstring>
#include <iostream>
#include "View.h"
#include "Trainer.h"
#include "PokemonCenter.h"
#include "WildPokemon.h"

void DoMoveCommand(Model& model, int trainer_id, Point2D p1)
{
    Trainer* trainer = model.GetTrainerPtr(trainer_id);
    if (trainer == 0)
    {
        cout << "Error: Please enter a valid command!" << endl;
    }
    else
    {
        cout << "Moving " << trainer->GetName() << " to " << p1<<endl;
        trainer->StartMoving(p1);
        /*for (int i =0; i < model.GetWP(); i++)
        {
            WildPokemon* wp_ptr = model.GetWildPokemonPtr(i);
            Point2D location1 = trainer->GetLocation();
            Point2D location2 = wp_ptr->GetLocation();
            if(GetDistanceBetween(location1,location2) == 0)
            {
                wp_ptr -> follow(trainer);
            }
        }*/
      //tried to make it follow, made seg faults

    }

    
}

void DoMoveToCenterCommand(Model& model, int trainer_id, int center_id)
{
    Trainer* trainer = model.GetTrainerPtr(trainer_id);
    PokemonCenter* center = model.GetPokemonCenterPtr(center_id);
    if (trainer != 0 || center != 0)
    {
        cout << "Moving " << (trainer)->GetName() << " to pokemon center " << center_id << endl;
        trainer->StartMovingToCenter(model.GetPokemonCenterPtr(center_id));
        /*        for (int i =0; i < 10; i++)
        {
            WildPokemon* wp_ptr = model.GetWildPokemonPtr(i);
            Point2D location1 = trainer->GetLocation();
            Point2D location2 = wp_ptr->GetLocation();
            if(GetDistanceBetween(location1,location2) == 0)
            {
                wp_ptr -> follow(trainer);
            }
        }*/
        //tried to make it follow, made seg faults
    }
    else
    {
        cout << "Error: Please enter a valid command!" << endl;
    }
}

void DoMoveToGymCommand(Model& model, int trainer_id, int gym_id)
{
    Trainer* trainer = model.GetTrainerPtr(trainer_id);
    PokemonGym* gym = model.GetPokemonGymPtr(gym_id);
    if (trainer == 0)
    {
        cout << "Error: Please enter a valid command!" << endl;
    }
    else if (gym == 0)
    {
        cout << "Error: Please enter a valid command!" << endl;
    }
    else
    {
        cout << "Moving " << model.GetTrainerPtr(trainer_id)->GetName() << " to gym " << trainer_id << endl;
        trainer->StartMovingToGym(model.GetPokemonGymPtr(gym_id));
        /*
                for (int i =0; i < 10; i++)
        {
            WildPokemon* wp_ptr = model.GetWildPokemonPtr(i);
            Point2D location1 = trainer->GetLocation();
            Point2D location2 = wp_ptr->GetLocation();
            if(GetDistanceBetween(location1,location2) == 0)
            {
                wp_ptr -> follow(trainer);
            }
        }*/
        //tried to make it follow, made seg faults

    }
}

void DoStopCommand(Model& model, int trainer_id)
{
    Trainer* trainer = model.GetTrainerPtr(trainer_id);
    if (trainer == 0)
    {
        cout << "Error: Please enter a valid command!" << endl;
    }
    else
    {
        cout << "Stopping " << trainer->GetName() << endl;
        trainer->Stop();
    }
}

void DoBattleCommand(Model& model, int trainer_id, unsigned int battles)
{
    Trainer* trainer = model.GetTrainerPtr(trainer_id);
    if (trainer == 0)
    {
        cout << "Error: Please enter a valid command!" << endl;
    }
    else
    {
        cout << trainer->GetName() << " is battling" << endl;
        trainer->StartBattling(battles); 
    }
}

void DoRecoverInCenterCommand(Model& model, int trainer_id, unsigned int potions_needed)
{
    Trainer* trainer = model.GetTrainerPtr(trainer_id);
    if (trainer == 0)
    {
        cout << "Error: Please enter a valid command!" << endl;
    }
    else
    {
        cout << "Recovering " << trainer->GetName() << "'s Pokemon's health" << endl;
        trainer->StartRecoveringHealth(potions_needed);
    }
}

void DoAdvanceCommand(Model& model, View& view)
{
    cout << "Advancing one tick" << endl;
    model.Update();
    model.ShowStatus();
    model.Display(view);
}

void DoRunCommand(Model& model, View& view)
{
    cout << "Advancing to next event" << endl;
    for (int i = 0; i<5; i++)
    {
        model.Update();
    }    
    model.Display(view);
}

void DoNewObjectCommand(Model& model, char type, int id, Point2D& loc)
{
    if (type == 'c')
    {
        PokemonCenter* ptr = new PokemonCenter(id, 5, 10, loc);
        model.object_ptrs.push_back(ptr);
        model.active_ptrs.push_back(ptr);
        model.center_ptrs.push_back(ptr);
    }
    else if (type == 'g')
    {
        PokemonGym* ptr = new PokemonGym(10, 2, 5, 5, id, loc);
        model.object_ptrs.push_back(ptr);
        model.active_ptrs.push_back(ptr);
        model.gym_ptrs.push_back(ptr);
    }
    else if (type == 't')
    {
        Trainer* ptr = new Trainer();
        ptr->SetLocation(loc);
        ptr->SetId(id);
        model.object_ptrs.push_back(ptr);
        model.active_ptrs.push_back(ptr);
        model.trainer_ptrs.push_back(ptr);
    }
    else if (type == 'w')
    {
        WildPokemon* ptr = new WildPokemon();
        ptr->SetLocation(loc);
        ptr->SetId(id);
        model.object_ptrs.push_back(ptr);
        model.active_ptrs.push_back(ptr);
        model.wildpokemon_ptrs.push_back(ptr);
    }
    else
    {
        throw type;
    }
}