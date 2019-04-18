#ifndef MoleculeMapper_h
#define MoleculeMapper_h

/*=========================================================================

  Program:   Visualization Toolkit Local Fork
  Module:    MapperMolecule.h

  Copyright (c) ScrewDriver te Blackheadborough
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   MapperMolecule
 * @brief   Mapper that draws vtkMolecule objects
 *
 *
 * MapperMolecule uses glyphs (display lists) to quickly render a
 * molecule.
*/

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

// #include "vtkDomainsChemistryModule.h" // For export macro
#include <vtkNew.h>          // For vtkNew<>
#include <vtkSmartPointer.h> // For vtkSmartPointer<>

#include <vtkMapper.h>

class vtkActor;
class vtkGlyph3DMapper;
class vtkIdTypeArray;
class vtkStringArray;
class vtkMolecule;
class vtkPeriodicTable;
class vtkPolyData;
class vtkPolyDataMapper;
class vtkRenderer;
class vtkSelection;
class vtkSphereSource;
class vtkTrivialProducer;

#include "MoleculeMapperStyle.h"

// typedef vtkSmartPointer<vtkGlyph3DMapper> Glyph3DMap;
typedef vtkNew<vtkGlyph3DMapper> Glyph3DMap;

namespace vtk
{
class /*VTKDOMAINSCHEMISTRY_EXPORT*/ MapperMolecule : public vtkMapper
{
public:
  typedef MoleculeMapperStyle MMStyle;

  static MapperMolecule *New();
  vtkTypeMacro(MapperMolecule, vtkMapper);
  void PrintSelf(ostream &os, vtkIndent indent) override;

  //@{
  /**
     * Get/Set the input vtkMolecule.
     */
  void SetInputData(vtkMolecule *in);
  vtkMolecule *GetInput();
  //@}
  MoleculeMapperStyle &Style() { return styleMap_; }
  const MoleculeMapperStyle &CurrentStyle() const { return styleMap_; }
  MoleculeMapperStyle GetStyle() const { return styleMap_; }
  void ResetStyleToDefault()
  { /*return*/
    this->SetStyle(styleFast);
  }
  void SetStyle(const MoleculeMapperStyle &msty)
  {
    if (styleMap_ != msty)
      this->GlyphDataInitialized = false;

    styleMap_ = msty;
  }

  /**
    * Predefined styles in use:
    */
  void UseBallAndStickSettings() { this->SetStyle(styleBallSticks); }
  bool IsSetBallsSticks() const { return (styleMap_ == styleBallSticks); }

  void UseSticksOnlySettings() { this->SetStyle(styleSticks); }
  bool IsSetSticksOnly() const { return (styleMap_ == styleSticks); }

  void UseSpaceFillSettings() { this->SetStyle(styleCPK); }
  bool IsSetSpaceFill() const { return (styleMap_ == styleCPK); }

  void UseFastRenderSettings() { this->SetStyle(styleFast); }
  bool IsSetFastRender() const { return (styleMap_ == styleFast); }

  //@{
  /**
     * Get/Set whether or not to render the unit cell lattice, if present.
     * Default: On.
     */
  vtkGetMacro(RenderLattice, bool);
  vtkSetMacro(RenderLattice, bool);
  vtkBooleanMacro(RenderLattice, bool);
  //@}

  //@{
  /**
     * Get/Set the color of the bonds as an rgb tuple.
     * Default: {50, 50, 50} (dark grey)
     */
  vtkGetVector3Macro(BondColor, unsigned char);
  vtkSetVector3Macro(BondColor, unsigned char);
  //@}

  //@{
  /**
     * Get/Set the color of the bonds as an rgb tuple.
     * Default: {255, 255, 255} (white)
     */
  vtkGetVector3Macro(LatticeColor, unsigned char);
  vtkSetVector3Macro(LatticeColor, unsigned char);
  //@}

  //@{
  /**
       * Extract the ids atoms and/or bonds rendered by this molecule from a
       * vtkSelection object. The vtkIdTypeArray
       */
  virtual void GetSelectedAtomsAndBonds(vtkSelection *selection,
                                        vtkIdTypeArray *atomIds,
                                        vtkIdTypeArray *bondIds);

  virtual void GetSelectedAtoms(vtkSelection *selection,
                                vtkIdTypeArray *atomIds)
  {
    this->GetSelectedAtomsAndBonds(selection, atomIds, nullptr);
  }

  virtual void GetSelectedBonds(vtkSelection *selection,
                                vtkIdTypeArray *bondIds)
  {
    this->GetSelectedAtomsAndBonds(selection, nullptr, bondIds);
  }
  //@}

  //@{
  /**
     * Reimplemented from base class
     */
  void Render(vtkRenderer *, vtkActor *) override;
  void ReleaseGraphicsResources(vtkWindow *) override;
  double *GetBounds() override;
  void GetBounds(double bounds[6]) override { vtkAbstractMapper3D::GetBounds(bounds); }
  int FillInputPortInformation(int port, vtkInformation *info) override;
  bool GetSupportsSelection() override { return true; }
  //@}

  //@{
  /**
     * Get/Set the atomic radius array name. Default: "radii"
     * It is only used when AtomicRadiusType is set to CustomArrayRadius.
     */
  vtkGetStringMacro(AtomicRadiusArrayName);
  vtkSetStringMacro(AtomicRadiusArrayName);
  //@}

  /**
     * Get/Set Atoms/Bonds mappers (still Get only :)
     *  
     **/
  vtkGlyph3DMapper *GetAtomMapper() const { return glyphAtoms_.Get(); }
  vtkGlyph3DMapper *GetBondMapper() const { return glyphBonds_.Get(); }

protected:
  MapperMolecule();
  ~MapperMolecule() override;

  //@{
  /**
     * Customize atom rendering
     */
  // bool RenderAtoms;
  // int AtomicRadiusType;
  // float AtomicRadiusScaleFactor;
  char *AtomicRadiusArrayName;
  //@}

  //@{
  /**
     * Customize bond rendering
     */
  unsigned char BondColor[3];
  //@}

  bool RenderLattice;

  /**
     * Internal render methods
     */
  void GlyphRender(vtkRenderer *ren, vtkActor *act);

  //@{
  /**
     * Cached variables and update methods
     */
  vtkNew<vtkPolyData> AtomGlyphPolyData;
  vtkNew<vtkTrivialProducer> AtomGlyphPointOutput;
  vtkNew<vtkPolyData> BondGlyphPolyData;
  vtkNew<vtkTrivialProducer> BondGlyphPointOutput;
  vtkNew<vtkStringArray> dataAtomsLabel_;
  vtkNew<vtkStringArray> dataBondsLabel_;
  //
  bool GlyphDataInitialized;
  virtual void UpdateGlyphPolyData();
  virtual void UpdateAtomGlyphPolyData();
  virtual void UpdateBondGlyphPolyData();
  //
  bool areLabelDataInitialized_;
  virtual void UpdateAtomLabel();
  virtual void UpdateBondLabel();
  //@}

  /**
     * Periodic table for lookups
     */
  vtkNew<vtkPeriodicTable> PeriodicTable;
  vtkNew<vtkPolyDataMapper> LatticeMapper;

private:
  //@{
  /**
     * Internal mappers
     */
  Glyph3DMap glyphAtoms_;
  Glyph3DMap glyphBonds_;
  //@}

  unsigned char LatticeColor[3];
  vtkNew<vtkPolyData> LatticePolyData;
  virtual void UpdateLatticePolyData();

  /**
     * padding value for the viewport
     **/

  double pad_;

  /* */
  MoleculeMapperStyle styleMap_;
  /**
    * predefined styles:
     */
  static const MoleculeMapperStyle styleFast;
  static const MoleculeMapperStyle styleSticks;
  static const MoleculeMapperStyle styleBallSticks;
  static const MoleculeMapperStyle styleCPK;

  // delete:
  MapperMolecule(const MapperMolecule &) = delete;
  void operator=(const MapperMolecule &) = delete;
};

} // namespace vtk

#endif // !MoleculeMapper_h
