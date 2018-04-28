#include <vtkTransformFilter.h>
#include "booleanunion.hxx"

BooleanUnion::BooleanUnion(ShapeSource& a, ShapeSource& b, const int operation) {
    vtkTriangleFilter* tri_a = vtkTriangleFilter::New();
    vtkTriangleFilter* tri_b = vtkTriangleFilter::New();
    tri_a->SetInputConnection(a.getOutputPort());
    tri_b->SetInputConnection(b.getOutputPort());
    tri_a->Update();
    tri_b->Update();

    this->init(tri_a, tri_b, operation);
}

void BooleanUnion::init(vtkTriangleFilter* a, vtkTriangleFilter* b, const int operation) {
    vtkBooleanOperationPolyDataFilter* booleanOperation = vtkBooleanOperationPolyDataFilter::New();
    booleanOperation->SetInputData(0, a->GetOutput());
    booleanOperation->SetInputData(1, b->GetOutput());
    booleanOperation->SetOperation(operation);
    booleanOperation->Update();

    this->source = booleanOperation;
}