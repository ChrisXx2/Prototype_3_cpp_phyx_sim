#ifndef PROJECTILE2D_H
#define PROJECTILE2D_H

#include "Vector2D.h"
#include "SurfacePlane.h"

struct Projectile2D {

    double mass;
    double Cd;
    double radius;

    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;

    Projectile2D(double mass, double Cd, double radius,
                 const Vector2D& position, const Vector2D& velocity);

    // Resets acceleration to zero, then applies gravity and aerodynamic drag from the plane.
    // Call this at the start of each time step before any other forces.
    void computeForces(const SurfacePlane& plane);

    // Integrates velocity and position forward by deltaTime seconds (Euler step).
    void update(double deltaTime);

    double kineticEnergy() const;
    double potentialEnergy() const;
    Vector2D momentum() const;

    void printState() const;

};

#endif
