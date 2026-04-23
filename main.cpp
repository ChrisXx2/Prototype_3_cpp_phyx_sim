#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <limits>
#include <fstream>
#include <string>

#include "Vector2D.h"
#include "SurfacePlane.h"
#include "Projectile2D.h"
#include "FreeParticle2D.h"

// ---------------------------------------------------------------------------
// Input helpers. used to prevent invalid inputs and crashes
// ---------------------------------------------------------------------------

static double readDouble(const char* prompt) {
    double val;
    while (true) {
        printf("%s", prompt);
        if (std::cin >> val) return val;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        printf("Invalid input. Please enter a number.\n");
    }
}

static int readPositiveInt(const char* prompt) {
    int val;
    while (true) {
        printf("%s", prompt);
        if (std::cin >> val && val > 0) return val;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        printf("Invalid input. Please enter a positive integer.\n");
    }
}

// ---------------------------------------------------------------------------
// Ze kalkoolations
// ---------------------------------------------------------------------------

static void runProjectileSimulation() {
    printf("\n--- Projectile Simulation Setup ---\n");

    double g      = readDouble("Gravitational acceleration (m/s^2, e.g. 9.81): ");
    double rho    = readDouble("Air density (kg/m^3, e.g. 1.225 for sea level): ");

    SurfacePlane plane(g, rho);

    double mass   = readDouble("Projectile mass (kg): ");
    double Cd     = readDouble("Drag coefficient (dimensionless, e.g. 0.47 for a sphere): ");
    double radius = readDouble("Radius (m): ");

    double px     = readDouble("Initial position x (m): ");
    double py     = readDouble("Initial position y (m): ");
    double vx     = readDouble("Initial velocity x (m/s): ");
    double vy     = readDouble("Initial velocity y (m/s): ");

    double dt     = readDouble("Time step (s, e.g. 0.01): ");
    int    steps  = readPositiveInt("Number of steps: ");
    int    printEvery = readPositiveInt("Print state every N steps: ");

    Projectile2D proj(mass, Cd, radius, Vector2D(px, py), Vector2D(vx, vy));

    printf("\n--- Simulation Start ---\n");
    printf("t = 0.0000 s\n");
    proj.printState();

    for (int i = 1; i <= steps; i++) {
        proj.computeForces(plane);
        proj.update(dt);

        if (i % printEvery == 0) {
            printf("\nt = %.4f s\n", i * dt);
            proj.printState();
        }

        // Stop if the projectile hits the ground.
        if (proj.position.y < 0.0) {
            printf("\nProjectile reached ground at t = %.4f s\n", i * dt);
            printf("Impact position x: %.4f m\n", proj.position.x);
            break;
        }
    }

    printf("\n--- Simulation End ---\n");
    
    printf("\n 1 - Export");
    printf("\n 2 - Exit");

    int optionss;
    std::cin >> optionss;

    switch (optionss)
    {
    case 1:
        printf("Not implemented yet");
        break;

    case 2:
        break;
    
    default:
        printf("Unknown choice. Exiting.\n");
        return;
    }

}

static void runFreeParticleSimulation() {
    printf("\n--- Free Particle System Setup ---\n");

    int n = readPositiveInt("Number of particles: ");
    double G = readDouble("Gravitational constant G (e.g. 6.674e-11 for SI, or larger for visible effects): ");

    std::vector<FreeParticle2D> particles;
    particles.reserve(n);

    for (int i = 0; i < n; i++) {
        printf("\nParticle %d:\n", i + 1);
        double mass   = readDouble("  Mass (kg): ");
        double radius = readDouble("  Radius (m): ");
        double px     = readDouble("  Initial position x (m): ");
        double py     = readDouble("  Initial position y (m): ");
        double vx     = readDouble("  Initial velocity x (m/s): ");
        double vy     = readDouble("  Initial velocity y (m/s): ");

        particles.emplace_back(mass, radius, Vector2D(px, py), Vector2D(vx, vy));
    }

    double dt         = readDouble("\nTime step (s): ");
    int    steps      = readPositiveInt("Number of steps: ");
    int    printEvery = readPositiveInt("Print state every N steps: ");

    printf("\n--- Simulation Start ---\n");

    for (int i = 1; i <= steps; i++) {
        // Accumulate gravitational forces between all pairs.
        for (int a = 0; a < n; a++) {
            for (int b = a + 1; b < n; b++) {
                particles[a].applyGravitationalAttraction(particles[b], G);
                particles[b].applyGravitationalAttraction(particles[a], G);
            }
        }

        // Resolve collisions.
        for (int a = 0; a < n; a++) {
            for (int b = a + 1; b < n; b++) {
                FreeParticle2D::resolveCollision(particles[a], particles[b]);
            }
        }

        // Integrate. Note: update() resets acceleration to zero after stepping.
        for (int a = 0; a < n; a++) {
            particles[a].update(dt);
        }

        if (i % printEvery == 0) {
            printf("\nt = %.4f s\n", i * dt);

            Vector2D totalMomentum(0.0, 0.0);
            double   totalKE = 0.0;

            for (int a = 0; a < n; a++) {
                printf("  Particle %d:\n", a + 1);
                particles[a].printState();
                totalMomentum += particles[a].momentum();
                totalKE += particles[a].kineticEnergy();
            }

            printf("  System total KE: %.6f J\n", totalKE);
            printf("  System momentum: (%.6f, %.6f) kg*m/s\n",
                   totalMomentum.x, totalMomentum.y);
        }
    }

    printf("\n--- Simulation End ---\n");

    printf("\n 1 - Export");
    printf("\n 2 - Back to menu");
    printf("\n 3 - Exit");

    int optionss;
    std::cin >> optionss;

    switch (optionss)
    {
    case 1:
        printf("Not implemented yet");
        break;

    case 2:
        break;
    
    default:
        printf("Unknown choice. Exiting.\n");
        return;
    }


}

// ---------------------------------------------------------------------------
// Za beginning of main() and user interaction
// ---------------------------------------------------------------------------

int main() {
    printf("Physics Simulator\n");
    printf("=================\n");
    printf("Select a simulation mode:\n");
    printf("  1 - Projectile on a surface plane (gravity + air resistance)\n");
    printf("  2 - Particles in a closed system (mutual gravitational attraction)\n");
    printf("Choice: ");

    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            runProjectileSimulation();
            break;
        case 2:
            runFreeParticleSimulation();
            break;
        default:
            printf("Unknown choice. Exiting.\n");
            return 1;
    }

    return 0;
}
