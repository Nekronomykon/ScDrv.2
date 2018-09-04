#ifndef ELEMENTDATAPARSER_H
#define ELEMENTDATAPARSER_H

/*=========================================================================

  Program:   Visualization Toolkit
  Module:    ElementDataParser.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   ElementDataParser
 * @brief   Fill an ElementData container with data from the BODR XML dataset.
 *
 *
 * The Blue Obelisk Data Repository is a free, open repository of
 * chemical information. This class extracts the BODR information into
 * vtk arrays, which are stored in a ElementData object.
 *
 * \warning The ElementDataParser class should never need to be
 * used directly. For convenient access to the BODR data, use
 * vtkPeriodicTable. For access to the raw arrays produced by this
 * parser, see the ElementData class. A static
 * ElementData object is accessible via
 * vtkPeriodicTable::GetBlueObeliskData().
 *
 * @sa
 * vtkPeriodicTable ElementData
*/

// #include "vtkDomainsChemistryModule.h" // For export macro
#include <vtkXMLParser.h>

#include <vtkSmartPointer.h> // For vtkSmartPointer

class vtkAbstractArray;
class ElementData;
class vtkFloatArray;
class vtkStdString;
class vtkStringArray;
class vtkUnsignedShortArray;

class /*VTKDOMAINSCHEMISTRY_EXPORT*/ ElementDataParser
  : public vtkXMLParser
{
 public:
  vtkTypeMacro(ElementDataParser, vtkXMLParser);
  void PrintSelf(ostream& os, vtkIndent indent) override;
  static ElementDataParser * New();

  /**
   * Set the target ElementData object that this parser will
   * populate
   */
  virtual void SetTarget(ElementData *bodr);

  /**
   * Start parsing
   */
  int Parse() override;

  //@{
  /**
   * These are only implemented to prevent compiler warnings about hidden
   * virtual overloads. This function simply call Parse(); the arguments are
   * ignored.
   */
  int Parse(const char *) override;
  int Parse(const char *, unsigned int) override;
  //@}

protected:
  explicit ElementDataParser();
  ~ElementDataParser() override;

  void StartElement(const char *name, const char **attr) override;
  void EndElement(const char *name) override;

  void CharacterDataHandler(const char *data, int length) override;

  void SetCurrentValue(const char *data, int length);
  void SetCurrentValue(const char *data);

  ElementData *Target;

  bool IsProcessingAtom;
  void NewAtomStarted(const char **attr);
  void NewAtomFinished();

  bool IsProcessingValue;
  void NewValueStarted(const char **attr);
  void NewValueFinished();

  std::string CharacterDataValueBuffer;

  enum AtomValueType {
    None = 0,
    AtomicNumber,
    Symbol,
    Name,
    PeriodicTableBlock,
    ElectronicConfiguration,
    Family,
    Mass,
    ExactMass,
    IonizationEnergy,
    ElectronAffinity,
    PaulingElectronegativity,
    CovalentRadius,
    VDWRadius,
    DefaultColor,
    BoilingPoint,
    MeltingPoint,
    Period,
    Group
  } CurrentValueType;

  int CurrentAtomicNumber;
  vtkStdString *CurrentSymbol;
  vtkStdString *CurrentName;
  vtkStdString *CurrentPeriodicTableBlock;
  vtkStdString *CurrentElectronicConfiguration;
  vtkStdString *CurrentFamily;
  float CurrentMass;
  float CurrentExactMass;
  float CurrentIonizationEnergy;
  float CurrentElectronAffinity;
  float CurrentPaulingElectronegativity;
  float CurrentCovalentRadius;
  float CurrentVDWRadius;
  float CurrentDefaultColor[3];
  float CurrentBoilingPoint;
  float CurrentMeltingPoint;
  unsigned int CurrentPeriod;
  unsigned int CurrentGroup;

private:
  ElementDataParser(const ElementDataParser&) = delete;
  void operator=(const ElementDataParser&) = delete;

  //@{
  /**
   * Resize array if needed and set the entry at ind to val.
   */
  static void ResizeArrayIfNeeded(vtkAbstractArray *arr, vtkIdType ind);
  static void ResizeAndSetValue(vtkStdString *val,
                                vtkStringArray *arr,
                                vtkIdType ind);
  static void ResizeAndSetValue(float val,
                                vtkFloatArray *arr,
                                vtkIdType ind);
  static void ResizeAndSetValue(unsigned short val,
                                vtkUnsignedShortArray *arr,
                                vtkIdType ind);
  //@}

  //@{
  /**
   * Parse types from const char *
   */
  static int parseInt(const char *);
  static float parseFloat(const char *);
  static void parseFloat3(const char * str, float[3]);
  static unsigned short parseUnsignedShort(const char *);
  //@}

  //@{
  /**
   * Convert a string to lower case. This will modify the input string
   * and return the input pointer.
   */
  static vtkStdString * ToLower(vtkStdString *);
};
  //@}


#endif // ELEMENTDATAPARSER_H
