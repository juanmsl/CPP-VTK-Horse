#ifndef __SHAPES_HXX__
#define __SHAPES_HXX__

#include <vtkSphere.h>
#include <vtkSphereSource.h>
#include <vtkCone.h>
#include <vtkConeSource.h>
#include <vtkCylinder.h>
#include <vtkCylinderSource.h>
#include <vtkCubeSource.h>

#include "shapesource.hxx"

class PureSphere : public Shape {
protected:
    double radius;

public:
    PureSphere(const double x = 0.0, const double y = 0.0, const double z = 0.0, const double radius = 1.0);
};

class Sphere : public ShapeSource {
protected:
    double radius;

public:
    Sphere(const double x = 0.0, const double y = 0.0, const double z = 0.0, const double radius = 1.0);
};

class PureCone : public Shape {
protected:
    double angle;

public:
    PureCone(const double x = 0.0, const double y = 0.0, const double z = 0.0, const double angle = 45.0);
};

class Cone : public ShapeSource {
protected:
    double radius;
    double height;

public:
    Cone(const double x = 0.0, const double y = 0.0, const double z = 0.0, const double radius = 1.0, const double height = 1.0);
};

class PureCylinder : public Shape {
protected:
    double radius;

public:
    PureCylinder(const double x = 0.0, const double y = 0.0, const double z = 0.0, const double radius = 1.0);
};

class Cylinder : public ShapeSource {
protected:
    double radius;
    double height;

public:
    Cylinder(const double x = 0.0, const double y = 0.0, const double z = 0.0, const double radius = 1.0, const double height = 1.0);
};

class Cube : public ShapeSource {
protected:
    double radius;
    double height;
    double length_X;
    double length_Y;
    double length_Z;

public:
    Cube(const double x = 0.0, const double y = 0.0, const double z = 0.0, const double length_X = 1.0, const double length_Y = 1.0, const double length_Z = 1.0);
};


#endif
