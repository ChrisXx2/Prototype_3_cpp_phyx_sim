#ifndef FREEPARTICLE2D_H
#define FREEPARTICLE2D_H

#include "Vector2D.h"

struct FreeParticle2D {

    double mass;
    double radius;

    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;

    FreeParticle2D(double mass, double radius,
                   const Vector2D& position, const Vector2D& velocity);

    // Adds the gravitational attraction exerted by 'other' to this particle's acceleration.
    // G is the gravitational constant (default 6.674e-11 for SI units).
    void applyGravitationalAttraction(const FreeParticle2D& other, double G = 6.674e-11);

    // Resolves an elastic collision with 'other' if the two spheres are overlapping.
    // Modifies both particles' velocities in place.
    static void resolveCollision(FreeParticle2D& a, FreeParticle2D& b);

    // Integrates velocity and position forward by deltaTime seconds (Euler step).
    void update(double deltaTime);

    double kineticEnergy() const;
    Vector2D momentum() const;

    void printState() const;

};

#endif
