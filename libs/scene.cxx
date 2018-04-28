#include "scene.hxx"

Scene::Scene(const int width, const int height, const std::string name, const bool axes) {
	this->width = width;
	this->height = height;
	this->renderer = vtkRenderer::New();
	this->renderWindow = vtkRenderWindow::New();
	this->renderWindowInteractor = vtkRenderWindowInteractor::New();
	this->camera = vtkCamera::New();
    this->camera->SetPosition(0, 2, 15);

	this->renderer->SetActiveCamera(camera);
	this->renderWindow->SetWindowName(name.c_str());
	this->renderWindow->AddRenderer(this->renderer);
	this->renderWindow->SetSize(this->width, this->height);
	this->renderWindowInteractor->SetRenderWindow(this->renderWindow);
	this->renderWindowInteractor->HideCursor();

	if(axes) {
		this->axes = vtkAxesActor::New();
        this->axes->SetTotalLength(1, 1, 1);
        this->axes->AxisLabelsOff();
        this->addActor(this->axes);
	} else {
        this->axes = nullptr;
    }

	this->setBackground(255, 255, 255);
}

void Scene::setBackground(const double red, const double green, const double blue) {
	this->renderer->SetBackground(red, green, blue);
}

void Scene::addShape(Shape& shape) {
    this->renderer->AddViewProp(shape.getActor());
}

void Scene::addActor(vtkProp3D* actor) {
    this->renderer->AddViewProp(actor);
}

void Scene::start() {
	renderWindow->Render();
	renderWindowInteractor->Initialize();
	renderWindowInteractor->Start();
}
