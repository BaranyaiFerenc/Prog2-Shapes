#include "vector.h"
#include <cmath>

# define PI 3.14159265358979323846

Vector Vector::operator+(const Vector& v) const {
    return Vector(x + v.x, y + v.y);
}

Vector Vector::operator-(const Vector& v) const {
    return Vector(x - v.x, y - v.y);
}

Vector Vector::operator*(double d) const {
    return Vector(x * d, y * d);
}

Vector Vector::operator*(const Vector& v) const
{
    return Vector(x*v.x, y*v.y);
}

void Vector::operator=(const Vector& v) {
    if (this != &v) {
        x = v.x;
        y = v.y;
    }
}

void Vector::operator+=(const Vector& v) {
    x += v.x;
    y += v.y;
}

void Vector::operator-=(const Vector& v) {
    x -= v.x;
    y -= v.y;
}

std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "(" << v.getX() << "; " << v.getY() << ")";
    return os;
}

double Vector::Length() const
{
    return std::sqrt(x * x + y * y);
}

Vector Vector::getDirection() const
{
    double length = this->Length();

    return Vector(x / length, y / length);
}

Vector Vector::Round() const
{
    return Vector(int(round(x)), int(round(y)));
}

Vector Vector::Rotate(double deg) const
{
    double rad = (PI / 180)*deg;

    double newX = x* cos(rad)-y* sin(rad);
    double newY = x* sin(rad)+y* cos(rad);

    return Vector(newX, newY);
}