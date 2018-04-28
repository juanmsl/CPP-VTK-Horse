#ifndef __IMPLICIT_UNION_HXX__
#define __IMPLICIT_UNION_HXX__

#include <vtkImplicitFunction.h>
#include <vtkActor.h>
#include <vtkImplicitBoolean.h>
#include <vtkSampleFunction.h>
#include <vtkContourFilter.h>

#include "shape.hxx"

class ImplicitUnion : public Shape {
public:
    ImplicitUnion(Shape& a, Shape& b, const int operation);
};


#endif
