#ifndef __SHAPE_SOURCE_HXX__
#define __SHAPE_SOURCE_HXX__

#include <vtkPolyDataAlgorithm.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkTransformFilter.h>
#include <vtkTriangleFilter.h>

#include "shape.hxx"

class ShapeSource : public Shape {
protected:
    double x;
    double y;
    double z;
    vtkTransform* transform;
    vtkTransformFilter* transformFilter;
    vtkTriangleFilter* triangleFilter;

public:
    ShapeSource(const double x = 0.0, const double y = 0.0, const double z = 0.0);

    virtual vtkTriangleFilter* getTriangleFilter();
    virtual vtkTransformFilter* getTransformFilter();
    virtual vtkPolyDataMapper* getMapper();
    virtual vtkActor* getActor();
};


#endif
