#ifndef Interactor_Highlight_Mouse__h__
#define Interactor_Highlight_Mouse__h__

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <vtkActor.h>
#include <vtkPolyDataSilhouette.h>
#include <vtkInteractorStyleTrackballCamera.h>

#include <vtkPropPicker.h>

namespace vtk
{
  // Handle mouse events
  class MouseInteractorHighLightActor
      : public vtkInteractorStyleTrackballCamera
  {
  public:
    static MouseInteractorHighLightActor *New();
    vtkTypeMacro(MouseInteractorHighLightActor,
                 vtkInteractorStyleTrackballCamera);

    MouseInteractorHighLightActor();
    ~MouseInteractorHighLightActor() override = default;

    virtual void OnLeftButtonDown() override;

    void SetSilhouette(vtkPolyDataSilhouette *silhouette);

    void SetSilhouetteActor(vtkActor *silhouetteActor);

  private:
    vtkActor *LastPickedActor = nullptr;
    vtkActor *SilhouetteActor = nullptr;
    vtkPolyDataSilhouette *Silhouette = nullptr;
  };

} // namespace vtk

#endif // !Interactor_Highlight_Mouse__h
