#ifndef SURFACEPLANE_H
#define SURFACEPLANE_H

struct SurfacePlane {

    double gravity;
    double airDensity;

    SurfacePlane(double gravity, double airDensity);

    // Returns the drag force vector acting on a sphere moving through this plane's atmosphere.
    // dragCoeff: dimensionless drag coefficient of the sphere (Cd)
    // radius:    radius of the sphere in meters
    // velocity:  current velocity vector of the sphere
    Vector2D dragForce(double dragCoeff, double radius, const Vector2D& velocity) const;

};

#include "Vector2D.h"

#endif
