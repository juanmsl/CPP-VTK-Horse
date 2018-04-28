#include "shapesource.hxx"

ShapeSource::ShapeSource(const double x, const double y, const double z) : Shape(x, y, z) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->transformFilter = nullptr;
    this->triangleFilter = nullptr;
    this->transform = vtkTransform::New();
}

vtkTriangleFilter* ShapeSource::getTriangleFilter() {
    if(this->triangleFilter == nullptr) {
        this->triangleFilter = vtkTriangleFilter::New();
        this->triangleFilter->SetInputConnection(this->source->GetOutputPort());
    }
    this->triangleFilter->Update();
    return this->triangleFilter;
}

vtkTransformFilter* ShapeSource::getTransformFilter() {
    if(this->transformFilter == nullptr) {
        this->transformFilter = vtkTransformFilter::New();
        this->transformFilter->SetTransform(this->transform);
        this->transformFilter->SetInputConnection(this->getTransformFilter()->GetOutputPort());
    }
    this->transformFilter->Update();
    return this->transformFilter;
}

vtkPolyDataMapper* ShapeSource::getMapper() {
    if(this->mapper == nullptr) {
        this->mapper = vtkPolyDataMapper::New();
        this->mapper->SetInputConnection(this->source->GetOutputPort());
        this->mapper->ScalarVisibilityOff();
    }
    this->mapper->Update();
    return this->mapper;
}

vtkActor* ShapeSource::getActor() {
    if(this->actor == nullptr) {
        this->actor = vtkActor::New();
        this->actor->SetMapper(this->getMapper());
    }
    return this->actor;
}