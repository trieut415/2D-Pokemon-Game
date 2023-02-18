#include <iostream>

#include "Vector2D.h"

using namespace std;

Vector2D::Vector2D() 
{
    x = 0.0;
    y = 0.0;
}

Vector2D::Vector2D(double in_x, double in_y) 
{
    x = in_x;
    y = in_y;
}

const Vector2D operator * (const Vector2D& v1, double d)
{
    return Vector2D((v1.x)*d, (v1.y)*d);
}

const Vector2D operator / (const Vector2D& v1, double d)
{
    if (d != 0) 
    {
        return Vector2D((v1.x) / d, (v1.y) / d);
    }
    else
    {
        return Vector2D(v1.x,v1.y);
    }
}

ostream& operator << (ostream& newCOUT, Vector2D& v1)
{
    double myx = v1.x;
    double myy = v1.y;
    newCOUT << "<" << myx << ", " << myy << ">";
    return newCOUT;
}





