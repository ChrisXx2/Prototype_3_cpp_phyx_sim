#include <cstdio>
#include <cmath>
#include "FreeParticle2D.h"
#include "Vector2D.h"

FreeParticle2D::FreeParticle2D(double mass, double radius,
                               const Vector2D& position, const Vector2D& velocity)
    : mass(mass), radius(radius),
      position(position), velocity(velocity), acceleration(0.0, 0.0) {}

void FreeParticle2D::applyGravitationalAttraction(const FreeParticle2D& other, double G) {
    double dist = position.distanceTo(other.position);

    // Avoid singularity when particles are extremely close or overlapping.
    double minDist = radius + other.radius;
    if (dist < minDist) dist = minDist;

    // F = G * m1 * m2 / r^2, directed toward the other particle.
    double forceMag = G * mass * other.mass / (dist * dist);

    Vector2D direction = (other.position - position).unitVector();
    Vector2D force = direction * forceMag;

    // a = F / m
    acceleration += force / mass;
}

void FreeParticle2D::resolveCollision(FreeParticle2D& a, FreeParticle2D& b) {
    double dist = a.position.distanceTo(b.position);
    double minDist = a.radius + b.radius;

    if (dist >= minDist) return;

    // Collision normal pointing from b to a.
    Vector2D normal = (a.position - b.position).unitVector();

    // Relative velocity along the normal.
    Vector2D relVel = a.velocity - b.velocity;
    double relSpeed = relVel.dotProduct(normal);

    // Particles already separating; no impulse needed.
    if (relSpeed > 0.0) return;

    // Elastic impulse scalar.
    double impulse = (2.0 * relSpeed) / (a.mass + b.mass);

    a.velocity -= normal * (impulse * b.mass);
    b.velocity += normal * (impulse * a.mass);

    // Positional correction: push particles apart so they no longer overlap.
    double overlap = minDist - dist;
    double totalMass = a.mass + b.mass;
    a.position += normal * (overlap * b.mass / totalMass);
    b.position -= normal * (overlap * a.mass / totalMass);
}

void FreeParticle2D::update(double deltaTime) {
    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;

    // Acceleration is re-accumulated each step from scratch.
    acceleration = Vector2D(0.0, 0.0);
}

double FreeParticle2D::kineticEnergy() const {
    double speed = velocity.Magnitude();
    return 0.5 * mass * speed * speed;
}

Vector2D FreeParticle2D::momentum() const {
    return velocity * mass;
}

void FreeParticle2D::printState() const {
    printf("  position:     (%.4f, %.4f) m\n", position.x, position.y);
    printf("  velocity:     (%.4f, %.4f) m/s\n", velocity.x, velocity.y);
    printf("  KE: %.4f J   |   speed: %.4f m/s\n",
           kineticEnergy(), velocity.Magnitude());
}
