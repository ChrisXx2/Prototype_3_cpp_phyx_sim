#ifndef VECTOR2D_H
#define VECTOR2D_H

struct Vector2D {

    double x;
    double y;

    Vector2D(double x, double y);
    Vector2D();

    double Magnitude() const;
    double Angle() const;

    void getPolarCoordinates(double& r, double& theta) const;

    Vector2D unitVector() const;

    double dotProduct(const Vector2D& v2) const;

    Vector2D operator+(const Vector2D& v2) const;
    Vector2D operator-(const Vector2D& v2) const;
    Vector2D operator*(double coeff) const;
    Vector2D operator/(double coeff) const;

    Vector2D& operator+=(const Vector2D& v2);
    Vector2D& operator-=(const Vector2D& v2);
    Vector2D& operator*=(double coeff);
    Vector2D& operator/=(double coeff);

    Vector2D rotate(double angle) const;
    Vector2D projectOnto(const Vector2D& v2) const;
    Vector2D reflectAcross(const Vector2D& normal) const;
    Vector2D perpendicular() const;

    double angleBetween(const Vector2D& v2) const;
    double distanceTo(const Vector2D& v2) const;

};

#endif
