#include "implicitunion.hxx"

ImplicitUnion::ImplicitUnion(Shape& a, Shape& b, const int operation) {
    vtkImplicitBoolean* implicitBoolean_a = vtkImplicitBoolean::New();
    vtkImplicitBoolean* implicitBoolean_b = vtkImplicitBoolean::New();
    vtkImplicitBoolean* implicitBoolean = vtkImplicitBoolean::New();
    implicitBoolean_a->AddFunction(a.getImplicitSource());
    implicitBoolean_b->AddFunction(b.getImplicitSource());
    implicitBoolean_a->SetTransform(a.getTransform());
    implicitBoolean_b->SetTransform(b.getTransform());

    implicitBoolean->AddFunction(implicitBoolean_a);
    implicitBoolean->AddFunction(implicitBoolean_b);
    implicitBoolean->SetOperationType(operation);

    this->implicitSource = implicitBoolean;
}