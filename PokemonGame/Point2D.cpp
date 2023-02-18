#include <iostream>
#include "Point2D.h"

using namespace std;

Point2D::Point2D() 
{
    x = 0;
    y = 0;
}

Point2D::Point2D(double in_x, double in_y)
{
    x = in_x;
    y = in_y;
}

double GetDistanceBetween(Point2D& p1, Point2D& p2)
{
    double distance = sqrt(pow(p2.x-p1.x,2) + pow(p2.y-p1.y,2));
    return distance;
}

ostream& operator<< (ostream& newCOUT, Point2D& p)
{
    newCOUT << "(" << p.x << ", " << p.y << ")" << endl;
    return newCOUT;   
}

const Point2D operator+ (const Point2D& p, const Vector2D& v)
{
    return Point2D(p.x + v.x, p.y + v.x);
}

const Vector2D operator- (const Point2D& p1, const Point2D& p2)
{
    double diff_x = p2.x - p1.x;
    double diff_y = p2.y - p1.y;
    return Vector2D(diff_x, diff_y);
}