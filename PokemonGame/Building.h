#ifndef BUILDING_H
#define BUILDING_H

#include <iostream>

#include "Point2D.h"
#include "GameObject.h"

using namespace std;

class Building: public GameObject
{
    public:
        Building();
        Building(char);
        Building(char, int, Point2D);
        void AddOneTrainer();
        void RemoveOneTrainer();
        void ShowStatus();
        bool ShouldBeVisible();
        virtual ~Building();
    private:
        unsigned int trainer_count;
};

#endif