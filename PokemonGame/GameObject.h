#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
#include "Point2D.h"
using namespace std;

class GameObject{
    public:

        GameObject(char);
        GameObject(Point2D, int, char);
        Point2D GetLocation();
        int GetId();
        int GetState();
        virtual void ShowStatus();
        virtual bool Update() = 0;
        virtual bool ShouldBeVisible() = 0;
        void DrawSelf(char* ptr);
        virtual ~GameObject();
    protected:
        Point2D location;
        int id_num;
        char display_code;
        char state;
};


#endif
