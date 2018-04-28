#ifndef __BOOLEAN_UNION_HXX__
#define __BOOLEAN_UNION_HXX__

#include <vtkTriangleFilter.h>
#include <vtkBooleanOperationPolyDataFilter.h>
#include <vtkTransformFilter.h>

#include "shapesource.hxx"

class BooleanUnion : public ShapeSource {
public:
    BooleanUnion(ShapeSource& a, ShapeSource& b, const int operation);

private:
    void init(vtkTriangleFilter* a, vtkTriangleFilter* b, const int operation);
};

#endif
