#include "InteractorHighlightMouse.h"

#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>


typedef vtkSmartPointer<vtk::MouseInteractorHighLightActor> NewInteractorMouseHighlight;

namespace vtk
{
  vtkStandardNewMacro(MouseInteractorHighLightActor);
  // Handle mouse events

  MouseInteractorHighLightActor::MouseInteractorHighLightActor(){}

  void MouseInteractorHighLightActor::OnLeftButtonDown()
  {
    int *clickPos = this->GetInteractor()->GetEventPosition();

    // Pick from this location.
    vtkNew<vtkPropPicker> picker;
    picker->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());
    this->LastPickedActor = picker->GetActor();

    // If we picked something before, remove the silhouette actor and
    // generate a new one
    if (this->LastPickedActor)
    {
      this->GetDefaultRenderer()->RemoveActor(this->SilhouetteActor);

      // Highlight the picked actor by generating a silouhette
      // this->Silhouette->SetInputData(
      // /* ???? */  dynamic_cast<vtkPolyDataMapper *>(this->LastPickedActor->GetMapper())->GetInput()) 
      // );
      this->GetDefaultRenderer()->AddActor(this->SilhouetteActor);
    }

    // Forward events
    vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
  }
  void MouseInteractorHighLightActor::SetSilhouette(vtkPolyDataSilhouette *silhouette)
  {
    this->Silhouette = silhouette;
  }
  void MouseInteractorHighLightActor::SetSilhouetteActor(vtkActor *silhouetteActor)
  {
    this->SilhouetteActor = silhouetteActor;
  }
} // namespace vtk
