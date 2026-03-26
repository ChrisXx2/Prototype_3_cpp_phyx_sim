#include <cstdio>
#include "Projectile2D.h"
#include "SurfacePlane.h"
#include "Vector2D.h"

Projectile2D::Projectile2D(double mass, double Cd, double radius,
                            const Vector2D& position, const Vector2D& velocity)
    : mass(mass), Cd(Cd), radius(radius),
      position(position), velocity(velocity), acceleration(0.0, 0.0) {}

void Projectile2D::computeForces(const SurfacePlane& plane) {
    // Reset acceleration each step; forces are re-derived from current state.
    acceleration = Vector2D(0.0, 0.0);

    // Gravity acts downward.
    Vector2D gravity(0.0, -plane.gravity * mass);

    // Aerodynamic drag.
    Vector2D drag = plane.dragForce(Cd, radius, velocity);

    Vector2D netForce = gravity + drag;
    acceleration = netForce / mass;
}

void Projectile2D::update(double deltaTime) {
    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;
}

double Projectile2D::kineticEnergy() const {
    double speed = velocity.Magnitude();
    return 0.5 * mass * speed * speed;
}

double Projectile2D::potentialEnergy() const {
    // Uses position.y as height above the ground reference.
    // Gravity value is not stored here; caller should pass it if needed.
    // Stored as mgh with g = 9.81 as a display convenience.
    return mass * 9.81 * position.y;
}

Vector2D Projectile2D::momentum() const {
    return velocity * mass;
}

void Projectile2D::printState() const {
    printf("  position:     (%.4f, %.4f) m\n", position.x, position.y);
    printf("  velocity:     (%.4f, %.4f) m/s\n", velocity.x, velocity.y);
    printf("  acceleration: (%.4f, %.4f) m/s^2\n", acceleration.x, acceleration.y);
    printf("  KE: %.4f J   |   speed: %.4f m/s\n",
           kineticEnergy(), velocity.Magnitude());
}
