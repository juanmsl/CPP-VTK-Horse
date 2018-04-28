#include <vtkMarchingContourFilter.h>
#include <vtkTextureMapToPlane.h>
#include "shape.hxx"

int Shape::resolution = 20;
int Shape::bounds = 10;

Shape::Shape(const double x, const double y, const double z) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->source = nullptr;
    this->implicitSource = nullptr;
    this->mapper = nullptr;
    this->actor = nullptr;
    this->transform = vtkTransform::New();
}

Shape::Shape(vtkPolyDataAlgorithm *source, const double x, const double y, const double z) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->source = source;
    this->implicitSource = nullptr;
    this->mapper = nullptr;
    this->actor = nullptr;
    this->transform = vtkTransform::New();
}

vtkPolyDataAlgorithm* Shape::getSource() {
    if(this->source == nullptr) {
        vtkSampleFunction* sampleFunction = vtkSampleFunction::New();
        sampleFunction->SetSampleDimensions(resolution, resolution, resolution);
        sampleFunction->SetImplicitFunction(this->implicitSource);
        sampleFunction->SetModelBounds(-bounds, bounds, -bounds, bounds, -bounds, bounds);
        sampleFunction->ComputeNormalsOff();

        vtkContourFilter* countourFilter = vtkContourFilter::New();
        countourFilter->SetInputConnection(sampleFunction->GetOutputPort());
        countourFilter->GenerateValues(1, 1, 1);

        this->source = countourFilter;
    }
    this->source->Update();
    return this->source;
}

vtkImplicitFunction* Shape::getImplicitSource() {
    return this->implicitSource;
}

vtkTransform* Shape::getTransform() {
    return this->transform;
}

vtkPolyDataMapper* Shape::getMapper() {
    if(this->mapper == nullptr) {
        this->mapper = vtkPolyDataMapper::New();
        this->mapper->SetInputConnection(this->getSource()->GetOutputPort());
        this->mapper->ScalarVisibilityOff();
    }
    this->mapper->Update();
    return this->mapper;
}

vtkActor* Shape::getActor() {
    if(this->actor == nullptr) {
        this->actor = vtkActor::New();
        this->actor->SetMapper(this->getMapper());
    }
    return this->actor;
}

vtkPolyData* Shape::getOutput() {
    return this->getSource()->GetOutput();
}

vtkAlgorithmOutput* Shape::getOutputPort() {
    return this->getSource()->GetOutputPort();
}

void Shape::setColorRGB(const double red, const double green, const double blue) {
    this->getActor()->GetProperty()->SetColor(red / 255.0, green / 255.0, blue / 255.0);
}

void Shape::applyTexture(const char* texturefile) {
    vtkImageReader2Factory* imageReaderFactory = vtkImageReader2Factory::New();
    vtkImageReader2* imageReader = imageReaderFactory->CreateImageReader2(texturefile);
    imageReader->SetFileName(texturefile);
    imageReader->Update();

    vtkTexture* texture = vtkTexture::New();
    texture->SetInputConnection(imageReader->GetOutputPort());
    texture->Update();

    vtkTextureMapToPlane* textureMapToPlane = vtkTextureMapToPlane::New();
    textureMapToPlane->SetInputConnection(this->getOutputPort());
    textureMapToPlane->Update();

    this->getMapper()->SetInputConnection(textureMapToPlane->GetOutputPort());
    this->getMapper()->Update();
    this->getActor()->SetTexture(texture);
}

void Shape::translate(const double x, const double y, const double z) {
    this->transform->Translate(x, y, z);
}

void Shape::scale(const double x, const double y, const double z) {
    this->transform->Scale(x, y, z);
}

void Shape::rotate(double angle, const double x, const double y, const double z, const bool deg) {
    if(!deg) {
        angle *= (180.0 / PI);
    }
    this->transform->RotateWXYZ(angle, x, y, z);
}