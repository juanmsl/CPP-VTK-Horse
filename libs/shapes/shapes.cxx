#include "shapes.hxx"

PureSphere::PureSphere(const double x, const double y, const double z, const double radius) : Shape(x, y, z) {
    this->radius = radius;
    vtkSphere* sphere = vtkSphere::New();
    sphere->SetRadius(this->radius);
    sphere->SetCenter(this->x, this->y, this->z);

    this->implicitSource = sphere;
}

Sphere::Sphere(const double x, const double y, const double z, const double radius): ShapeSource(x, y, z) {
    this->radius = radius;
    vtkSphereSource* sphereSource = vtkSphereSource::New();
    sphereSource->SetCenter(this->x, this->y, this->z);
    sphereSource->SetRadius(this->radius);
    sphereSource->SetPhiResolution(this->resolution);
    sphereSource->SetThetaResolution(this->resolution);
    sphereSource->Update();
    this->source = sphereSource;
}

PureCone::PureCone(const double x, const double y, const double z, const double angle) : Shape(x, y, z) {
    this->angle = angle;
    vtkCone* cone = vtkCone::New();
    cone->SetAngle(angle);

    this->implicitSource = cone;
}

Cone::Cone(const double x, const double y, const double z, const double radius, const double height) : ShapeSource(x, y, z) {
    this->radius = radius;
    this->height = height;
    vtkConeSource* coneSource = vtkConeSource::New();
    coneSource->SetCenter(this->x, this->y, this->z);
    coneSource->SetHeight(this->height);
    coneSource->SetRadius(this->radius);
    coneSource->SetResolution(this->resolution);
    coneSource->Update();
    this->source = coneSource;
}

PureCylinder::PureCylinder(const double x, const double y, const double z, const double radius) : Shape(x, y, z) {
    this->radius = radius;
    vtkCylinder* cylinder = vtkCylinder::New();
    cylinder->SetCenter(this->x, this->y, this->z);
    cylinder->SetRadius(this->radius);

    this->implicitSource = cylinder;
}

Cylinder::Cylinder(const double x, const double y, const double z, const double radius, const double height) : ShapeSource(x, y, z) {
    this->radius = radius;
    this->height = height;
    vtkCylinderSource* cylinderSource = vtkCylinderSource::New();
    cylinderSource->SetCenter(this->x, this->y, this->z);
    cylinderSource->SetHeight(this->height);
    cylinderSource->SetRadius(this->radius);
    cylinderSource->SetResolution(this->resolution);
    cylinderSource->Update();
    this->source = cylinderSource;
}

Cube::Cube(const double x, const double y, const double z, const double length_X, const double length_Y, const double length_Z) : ShapeSource(x, y, z) {
    this->radius = radius;
    this->height = height;
    this->length_X = length_X;
    this->length_Y = length_Y;
    this->length_Z = length_Z;
    vtkCubeSource* cubeSource = vtkCubeSource::New();
    cubeSource->SetCenter(this->x, this->y, this->z);
    cubeSource->SetXLength(this->length_X);
    cubeSource->SetYLength(this->length_Y);
    cubeSource->SetZLength(this->length_Z);
    cubeSource->Update();
    this->source = cubeSource;
}
