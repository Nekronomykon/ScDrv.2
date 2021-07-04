#include "ViewMolecule.h"

#include <vtkActor.h>
#include <vtkBMPWriter.h>
#include <vtkImageWriter.h>
#include <vtkInteractorStyleRubberBandPick.h>
#include <vtkJPEGWriter.h>
#include <vtkMoleculeMapper.h>
#include <vtkPNGWriter.h>
#include <vtkPNMWriter.h>
#include <vtkPostScriptWriter.h>
#include <vtkRenderWindow.h>
#include <vtkTIFFWriter.h>
#include <vtkWindowToImageFilter.h>

#include <QByteArray>

#include "ChooseColor.h"
#include "InteractorHighlightMouse.h"

typedef vtkSmartPointer<MouseInteractorHighLightActor> AMouseInStyHighlight;

typedef vtkSmartPointer<vtkInteractorStyleRubberBandPick> AnInterStyleRBPick;

vtkNew<vtkNamedColors> ViewMolecule::colors_bg;

vtkStdString ViewMolecule::name_bg_color("alice_blue");

ViewMolecule::ViewMolecule(QWidget* parent, Qt::WindowFlags flags)
  : Superclass(parent, flags)
  , color_bg_(colors_bg->GetColor3d(name_bg_color.c_str()).GetData())
  ,
  //             ^^^^  ViewMolecule::LastBgColorPtr()... Gainsboro?
  styleMol_(StyleMapMolecule::styleFast)
  , actorMol_(AnActor::New())
  , mapperMol_(AMapMol::New())
  , track_camera_(AnInterStyleRBPick::New())
{
  // vtkRenderWindow *pRW = this->renderWindow();

  //
  this->doRender();
}

void ViewMolecule::doRender()
{
  vtkRenderWindow* pRW = this->renderWindow();
  pRW->RemoveRenderer(renderer_);
  renderer_->RemoveActor(actorMol_);
  //
  renderer_->SetBackground(color_bg_.GetData());
  styleMol_.SetupMoleculeMapper(mapperMol_);
  actorMol_->SetMapper(mapperMol_);
  //
  renderer_->AddActor(actorMol_);
  pRW->AddRenderer(renderer_);
  //
  pRW->Render();
}

void ViewMolecule::adjustBgColor()
{
  setBgColor(ChooseColor::getDefaultColorName());
}
void ViewMolecule::setBgColor(const QString& name)
{

  int ncmp = name_color_bg_.compare(name);
  if (ncmp) {
    name_color_bg_ = name; // == resetBgColor()
    QByteArray name_bytes = name.toLatin1();
    vtkColor3d color_new_bg = colors_bg->GetColor3d(name_bytes.data());
    if (color_new_bg != color_bg_) {
      color_bg_ = color_new_bg;
      this->doRender();
    }
  }
}
//

bool ViewMolecule::setMoleculeStyle(const StyleMapMolecule& style)
{
  bool bRes(true); // (style_mol_ != style);
  if (bRes) {
    styleMol_ = style;
    this->doRender();
  }
  return bRes;
}

void ViewMolecule::mapMolecule(vtkMolecule* pMol)
{
}

template <class W>
bool ViewMolecule::writeImageFormat(const QString& fileName, bool rgba,
                                    int scale)
{
  assert(!fileName.isEmpty());
  if (fileName.isEmpty())
    return false;
  vtkRenderWindow* renWin = this->renderWindow();
  vtkNew<W> writer;
  vtkNew<vtkWindowToImageFilter> window_to_image_filter;
  window_to_image_filter->SetInput(renWin);
  window_to_image_filter->SetScale(scale); // image quality
  if (rgba) {
    window_to_image_filter->SetInputBufferTypeToRGBA();
  } else {
    window_to_image_filter->SetInputBufferTypeToRGB();
  }
  // Read from the front buffer.
  window_to_image_filter->ReadFrontBufferOff();
  window_to_image_filter->Update();

  QByteArray fn(fileName.toLocal8Bit());
  writer->SetFileName(fn.data());
  writer->SetInputConnection(window_to_image_filter->GetOutputPort());
  writer->Write();

  return true;
}

void ViewMolecule::writeImage(const std::string& fileName, bool rgba)
{
  /*
  vtkRenderWindow *renWin = this->renderWindow();
  if (!fileName.empty())
  {
    std::string fn = fileName;
    std::string ext;
    auto found = fn.find_last_of(".");
    if (found == std::string::npos)
    {
      ext = ".png";
      fn += ext;
    }
    else
    {
      ext = fileName.substr(found, fileName.size());
    }
    std::locale loc;
    std::transform(ext.begin(), ext.end(), ext.begin(),
                   [=](char const &c) { return std::tolower(c, loc); });
    vtkSmartPointer<vtkImageWriter> writer; // =
  vtkSmartPointer<vtkImageWriter>::New(); if (ext == ".bmp")
    {
      writer = vtkSmartPointer<vtkBMPWriter>::New();
    }
    else if (ext == ".jpg")
    {
      writer = vtkSmartPointer<vtkJPEGWriter>::New();
    }
    else if (ext == ".pnm")
    {
      writer = vtkSmartPointer<vtkPNMWriter>::New();
    }
    else if (ext == ".ps")
    {
      if (rgba)
      {
        rgba = false;
      }
      writer = vtkSmartPointer<vtkPostScriptWriter>::New();
    }
    else if (ext == ".tiff")
    {
      writer = vtkSmartPointer<vtkTIFFWriter>::New();
    }
    else
    {
      writer = vtkSmartPointer<vtkPNGWriter>::New();
    }
    vtkNew<vtkWindowToImageFilter> window_to_image_filter;
    window_to_image_filter->SetInput(renWin);
    window_to_image_filter->SetScale(1); // image quality
    if (rgba)
    {
      window_to_image_filter->SetInputBufferTypeToRGBA();
    }
    else
    {
      window_to_image_filter->SetInputBufferTypeToRGB();
    }
    // Read from the front buffer.
    window_to_image_filter->ReadFrontBufferOff();
    window_to_image_filter->Update();

    writer->SetFileName(fn.c_str());
    writer->SetInputConnection(window_to_image_filter->GetOutputPort());
    writer->Write();
  }
  else
  {
    std::cerr << "No filename provided." << std::endl;
  }
*/
  // return;
}
