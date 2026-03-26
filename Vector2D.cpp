#include <iostream>
#include <cmath>
#include "Vector2D.h"

Vector2D::Vector2D(double x, double y) : x(x), y(y) {}
Vector2D::Vector2D() : x(0), y(0) {}

double Vector2D::Magnitude() const {
    return sqrt(x * x + y * y);
}

double Vector2D::Angle() const {
    return atan2(y, x);
}

void Vector2D::getPolarCoordinates(double& r, double& theta) const {
    r = Magnitude();
    theta = Angle();
    printf("Polar coordinates: (r: %f, theta: %f)\n", r, theta);
}

Vector2D Vector2D::unitVector() const {
    double mag = Magnitude();
    if (mag == 0.0) {
        return Vector2D(0, 0);
    }
    return Vector2D(x / mag, y / mag);
}

double Vector2D::dotProduct(const Vector2D& v2) const {
    return x * v2.x + y * v2.y;
}

Vector2D Vector2D::operator+(const Vector2D& v2) const {
    return Vector2D(x + v2.x, y + v2.y);
}

Vector2D Vector2D::operator-(const Vector2D& v2) const {
    return Vector2D(x - v2.x, y - v2.y);
}

Vector2D Vector2D::operator*(double coeff) const {
    return Vector2D(x * coeff, y * coeff);
}

Vector2D Vector2D::operator/(double coeff) const {
    return Vector2D(x / coeff, y / coeff);
}

Vector2D& Vector2D::operator+=(const Vector2D& v2) {
    x += v2.x;
    y += v2.y;
    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& v2) {
    x -= v2.x;
    y -= v2.y;
    return *this;
}

Vector2D& Vector2D::operator*=(double coeff) {
    x *= coeff;
    y *= coeff;
    return *this;
}

Vector2D& Vector2D::operator/=(double coeff) {
    x /= coeff;
    y /= coeff;
    return *this;
}

Vector2D Vector2D::rotate(double angle) const {
    double cosA = cos(angle);
    double sinA = sin(angle);
    return Vector2D(x * cosA - y * sinA, x * sinA + y * cosA);
}

Vector2D Vector2D::projectOnto(const Vector2D& v2) const {
    double magSq = v2.x * v2.x + v2.y * v2.y;
    if (magSq == 0.0) return Vector2D(0, 0);
    double coeff = dotProduct(v2) / magSq;
    return Vector2D(v2.x * coeff, v2.y * coeff);
}

Vector2D Vector2D::reflectAcross(const Vector2D& normal) const {
    double dot = dotProduct(normal);
    return Vector2D(x - 2.0 * dot * normal.x, y - 2.0 * dot * normal.y);
}

Vector2D Vector2D::perpendicular() const {
    return Vector2D(-y, x);
}

double Vector2D::angleBetween(const Vector2D& v2) const {
    double mag1 = Magnitude();
    double mag2 = v2.Magnitude();
    if (mag1 == 0.0 || mag2 == 0.0) return 0.0;
    return acos(dotProduct(v2) / (mag1 * mag2));
}

double Vector2D::distanceTo(const Vector2D& v2) const {
    double dx = v2.x - x;
    double dy = v2.y - y;
    return sqrt(dx * dx + dy * dy);
}
