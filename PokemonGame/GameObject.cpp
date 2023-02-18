#include "GameObject.h"
#include <string>
#include <iostream>

using namespace std;


GameObject::GameObject(char in_code) 
{
    display_code = in_code;
    id_num = 1;
    state = 0;
    cout << "GameObject constructed" << endl;
}

GameObject::GameObject(Point2D in_loc, int in_id, char in_code) 
{ 
    display_code = in_code;
    id_num = in_id;
    state = 0;
    location = in_loc;
    cout << "GameObject constructed" << endl;
}

Point2D GameObject::GetLocation() 
{
    return location;
}

int GameObject::GetId() 
{
    return id_num; 
}

int GameObject::GetState() 
{
    return state;
}

void GameObject::ShowStatus() 
{
    cout << display_code << " " << id_num << " at " << location << endl;
}

void GameObject::DrawSelf(char* ptr)
{
    *ptr = display_code;
    int id = '0' + id_num;
    *(ptr+1) = id;
}

GameObject::~GameObject()
{
    cout << "GameObject destructed" << endl;
}

