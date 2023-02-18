#ifndef TRAINER_H
#define TRAINER_H

#include <iostream>
#include <vector>

#include <string>
#include "Point2D.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "GameObject.h"
#include "WildPokemon.h"
#include "Model.h"
using namespace std;

class Model; 
class WildPokemon;

class Trainer: public GameObject
{
    enum TrainerStates 
    { 
        STOPPED = 0,
        MOVING = 1,
        FAINTED = 2,
        AT_CENTER = 3,
        IN_GYM = 4,
        MOVING_TO_CENTER = 5,
        MOVING_TO_GYM = 6,
        BATTLING_IN_GYM = 7,
        RECOVERING_HEALTH = 8
    };

    public:
        Trainer();
        Trainer(char);
        Trainer(string, int, char, unsigned int, Point2D);
        
        void StartMoving(Point2D);
        void StartMovingToGym(PokemonGym* gym);
        void StartMovingToCenter(PokemonCenter* center);
        void StartBattling(unsigned int num_battles);
        void StartRecoveringHealth(unsigned int num_potions);
        void Stop();
        bool hasFainted();
        bool ShouldBeVisible();
        void ShowStatus();
        bool Update();
        string GetName(); 
        void StartFollow(Model*, int, int); 
        void DecrementHealth(); 
        void SetLocation(Point2D); 
        void SetId(int id);
        Point2D GetLocation();
        virtual ~Trainer();

    protected:
        bool UpdateLocation();
        void SetupDestination(Point2D dest);

    private:
        double speed, PokeDollars;
        bool is_at_center, is_IN_GYM;
        unsigned int health, experience, battles_to_buy, potions_to_buy;
        string name;
        PokemonCenter* current_center;
        PokemonGym* current_gym;
        Point2D destination;
        Vector2D delta;
        vector<WildPokemon*> pokeVec;
};


double GetRandomAmountOfPokeDollars();


#endif