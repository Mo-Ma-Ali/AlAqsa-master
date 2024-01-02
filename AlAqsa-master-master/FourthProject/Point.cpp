#include "Point.h"

Point::Point(double x, double y, double z) : x(x), y(y), z(z) {}

double Point::getX() { return x; }

double Point::getY() { return y; }

double Point::getZ() { return z; }

void Point::setX(double x) { this->x = x; }

void Point::setY(double  y) { this->y = y; }

void Point::setZ(double  z) { this->z = z; }