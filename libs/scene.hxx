#ifndef __SCENE_HXX__
#define __SCENE_HXX__

#define AXES true
#define NO_AXES false

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCamera.h>
#include <vtkActor2D.h>
#include <vtkProp.h>
#include <vtkAxesActor.h>

#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkObjectFactory.h>
#include <vtkCommand.h>

#include <math.h>
#include <map>

#include "shapes/shape.hxx"

class Scene {
	protected:
		int width;
		int height;
		vtkRenderer* renderer;
		vtkRenderWindow* renderWindow;
		vtkRenderWindowInteractor* renderWindowInteractor;
		vtkCamera* camera;
        vtkAxesActor* axes;

	public:
		Scene(const int width = 500, const int height = 500, const std::string name = "VTK Scene", const bool axes = AXES);

		void setBackground(const double red, const double green, const double blue);
        void addShape(Shape& shape);
        void addActor(vtkProp3D* actor);


		void start();
};

#endif
