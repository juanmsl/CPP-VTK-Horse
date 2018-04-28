#ifndef __SHAPE_HXX__
#define __SHAPE_HXX__

#define PI 3.14159265359
#define DEG true
#define RAD false
#define UNION vtkBooleanOperationPolyDataFilter::OperationType::VTK_UNION
#define DIFFERENCE vtkBooleanOperationPolyDataFilter::OperationType::VTK_DIFFERENCE
#define INTERSECTION vtkBooleanOperationPolyDataFilter::OperationType::VTK_INTERSECTION

#include <vtkImplicitFunction.h>
#include <vtkTransform.h>
#include <vtkAlgorithmOutput.h>
#include <vtkTransformFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkSampleFunction.h>
#include <vtkContourFilter.h>
#include <vtkProperty.h>
#include <vtkImageReader2Factory.h>
#include <vtkImageReader2.h>
#include <vtkTransformTextureCoords.h>
#include <vtkTextureMapToSphere.h>
#include <vtkTexture.h>
#include <vtkActor.h>

class Shape {
public:
    static int resolution;
    static int bounds;

protected:
    double x;
    double y;
    double z;
    vtkPolyDataAlgorithm* source;
    vtkImplicitFunction* implicitSource;
    vtkTransform* transform;
    vtkPolyDataMapper* mapper;
    vtkActor* actor;

public:
    Shape(const double x = 0.0, const double y = 0.0, const double z = 0.0);
    Shape(vtkPolyDataAlgorithm* source, const double x = 0.0, const double y = 0.0, const double z = 0.0);

    virtual vtkPolyDataAlgorithm* getSource();
    virtual vtkImplicitFunction* getImplicitSource();
    virtual vtkTransform* getTransform();
    virtual vtkPolyDataMapper* getMapper();
    virtual vtkActor* getActor();
    virtual vtkPolyData* getOutput();
    virtual vtkAlgorithmOutput* getOutputPort();

    virtual void setColorRGB(const double red, const double green, const double blue);
    virtual void applyTexture(const char* texturefile);
    virtual void translate(const double x = 0.0, const double y = 0.0, const double z = 0.0);
    virtual void scale(const double x = 1.0, const double y = 1.0, const double z = 1.0);
    virtual void rotate(double angle, const double x, const double y, const double z, const bool deg = DEG);
};

#endif