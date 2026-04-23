#include <cmath>
#include "Vector2D.h"
#include "SurfacePlane.h"

SurfacePlane::SurfacePlane(double gravity, double airDensity)
    : gravity(gravity), airDensity(airDensity) {}

Vector2D SurfacePlane::dragForce(double dragCoeff, double radius, const Vector2D& velocity) const {
    double speed = velocity.Magnitude();
    if (speed == 0.0) return Vector2D(0.0, 0.0);

    double crossSection = M_PI * radius * radius;
    double magnitude = 0.5 * airDensity * dragCoeff * crossSection * speed * speed;

    // Drag opposes the direction of motion.
    Vector2D dragDir = velocity.unitVector() * (-1.0);
    return dragDir * magnitude; 
}