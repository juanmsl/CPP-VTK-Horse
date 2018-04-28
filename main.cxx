#include <vtkPolyDataWriter.h>
#include <vtkPolyDataReader.h>
#include <vtkTextureMapToPlane.h>
#include "libs/scene.hxx"
#include "libs/horse.hxx"
#include "paramsmanager.hxx"

void generateHorseFromFile(Scene* scene, const std::string filename, const bool wired, const std::string texturefile, const int mapping);
void generateHorse(Scene* scene, const bool wired, const std::string texturefile, const int mapping, const std::string write);

int main(int argc, char* argv[]) {

    ParamsManager paramsManager(argc, argv);

    bool generateFromFile = paramsManager.filename != "";
    bool wired = paramsManager.wired;
    std::string texture = paramsManager.texture;
    int mapping = paramsManager.mapping;
    std::string filename = paramsManager.filename;
    std::string write = paramsManager.output;

    Shape::bounds = 6;
    Shape::resolution = paramsManager.resolution;

    Scene scene(800, 600, "VTK Bump", AXES);

    if(generateFromFile) {
        generateHorseFromFile(&scene, filename, wired, texture, mapping);
    } else {
        generateHorse(&scene, wired, texture, mapping, write);
    }

    scene.start();

	return EXIT_SUCCESS;
}

void generateHorse(Scene* scene, const bool wired, const std::string texturefile, const int mapping, const std::string write) {
    Horse horse;

    if(wired) {
        horse.getActor()->GetProperty()->SetRepresentationToWireframe();
    }

    if(write != "") {
        std::cout << "Writing..." << std::endl;
        vtkPolyDataWriter* polyDataWriter = vtkPolyDataWriter::New();
        polyDataWriter->SetFileName(write.c_str());
        polyDataWriter->SetInputData(horse.getSource()->GetOutput());
        polyDataWriter->Update();
        polyDataWriter->Write();
        std::cout << "Finish writing" << std::endl;
    }

    if(texturefile != "") {
        std::cout << "Applying texture..." << std::endl;
        horse.applyTexture(texturefile.c_str());
        std::cout << "Finish texture" << std::endl;
    }

    std::cout << "Mapping..." << std::endl;
    switch(mapping) {
        case GOURAUD:
            horse.getActor()->GetProperty()->SetInterpolationToGouraud();
            break;
        case PHONG:
            horse.getActor()->GetProperty()->SetInterpolationToPhong();
            break;
        case FLAT: default:
            horse.getActor()->GetProperty()->SetInterpolationToFlat();
    }
    std::cout << "Finish mapping..." << std::endl;

    std::cout << "Adding to scene..." << std::endl;
    scene->addShape(horse);
    std::cout << "Finish horse" << std::endl;
}

void generateHorseFromFile(Scene* scene, const std::string filename, const bool wired, const std::string texturefile, const int mapping) {
    vtkPolyDataReader* polyDataReader = vtkPolyDataReader::New();
    polyDataReader->SetFileName(filename.c_str());
    polyDataReader->Update();

    vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
    mapper->SetInputConnection(polyDataReader->GetOutputPort());
    mapper->ScalarVisibilityOff();
    mapper->Update();

    vtkActor* actor = vtkActor::New();
    actor->SetMapper(mapper);

    if(texturefile != "") {
        std::cout << "Applying texture..." << std::endl;
        vtkImageReader2Factory* imageReaderFactory = vtkImageReader2Factory::New();
        vtkImageReader2* imageReader = imageReaderFactory->CreateImageReader2(texturefile.c_str());
        imageReader->SetFileName(texturefile.c_str());
        imageReader->Update();

        vtkTexture* textura = vtkTexture::New();
        textura->SetInputConnection(imageReader->GetOutputPort());
        textura->Update();

        vtkTextureMapToPlane* textureMapToPlane = vtkTextureMapToPlane::New();
        textureMapToPlane->SetInputConnection(polyDataReader->GetOutputPort());

        mapper->SetInputConnection(textureMapToPlane->GetOutputPort());
        mapper->Update();
        actor->SetTexture(textura);
        std::cout << "Finish texture" << std::endl;
    }

    if(wired) {
        actor->GetProperty()->SetRepresentationToWireframe();
    }

    switch(mapping) {
        case GOURAUD:
            actor->GetProperty()->SetInterpolationToGouraud();
            break;
        case PHONG:
            actor->GetProperty()->SetInterpolationToPhong();
            break;
        case FLAT: default:
            actor->GetProperty()->SetInterpolationToFlat();
    }

    scene->addActor(actor);
}
