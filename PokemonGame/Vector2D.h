#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>
using namespace std;


class Vector2D
{
public:
    double x, y; 
    Vector2D();
    Vector2D(double, double);
};

const Vector2D operator* (const Vector2D&, double);
const Vector2D operator/ (const Vector2D&, double);
ostream& operator << (ostream&, Vector2D&);

#endif
