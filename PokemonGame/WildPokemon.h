#ifndef WILDPOKEMON_H
#define WILDPOKEMON_H

#include "GameObject.h"
#include "Trainer.h"
#include <string>
#include <iostream>
#include "Point2D.h"

using namespace std;

class Trainer;


class WildPokemon: public GameObject
{
    enum WildPokemonState
    {
        IN_ENVIRONMENT = 0,
        DEAD = 1,
        IN_TRAINER = 2
    };

    protected:
        double attack, health;
        bool variant, in_combat;
        string name;
        Trainer* current_trainer;
    public:
        WildPokemon();
        WildPokemon(string, double, double, bool, int, Point2D);
        void follow(Trainer* t);
        bool get_variant();
        double get_attack();
        double get_health();
        bool get_in_combat();
        bool Update();
        void ShowStatus();
        bool IsAlive();
        bool ShouldBeVisible();
        string GetName();
        void updatelocation(Point2D);
        void SetState(int);
        void SetLocation(Point2D);
        void SetId(int);
        Point2D GetLocation();
};

#endif