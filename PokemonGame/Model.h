#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>
#include <list>

#include "GameObject.h"
#include "Trainer.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "View.h"
#include "WildPokemon.h"


using namespace std;
class Trainer;
class WildPokemon;

class Model
{
    public:
        int time;
        list<GameObject*> object_ptrs, active_ptrs;
        list<Trainer*> trainer_ptrs;
        list<PokemonCenter*> center_ptrs;
        list<PokemonGym*> gym_ptrs;
        list<WildPokemon*> wildpokemon_ptrs;
    public:
        Model();
        ~Model();
        Trainer* GetTrainerPtr(int id);
        PokemonCenter* GetPokemonCenterPtr(int id);
        PokemonGym* GetPokemonGymPtr(int id);
        WildPokemon* GetWildPokemonPtr(int id);
        virtual bool Update();
        void Display(View& view);
        void ShowStatus();
        bool checkTrainerWildPokemon();
                int GetWP();
        int GetSize();
};

#endif
