#ifndef Elements_h
#define Elements_h

#ifdef _MSC_VER
#pragma once
#else  // !_MSC_VER
#endif //  _MSC_VER

#include <vtkNew.h>
#include "ElementData.h"

/*=========================================================================

  Program:   Visualization Toolkit
  Module:    PeriodicElements.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   PeriodicElements
 * @brief   Access to information about the elements.
 *
 *
 * Sourced from the Blue Obelisk Data Repository
 *
 * @sa
 * ElementData ElementDataParser
*/

//#include "vtkDomainsChemistryModule.h" // For export macro
#include "vtkObject.h"
#include "vtkNew.h" // Needed for the static data member

class ElementData;
class vtkColor3f;
class vtkLookupTable;
class vtkStdString;

class /*VTKDOMAINSCHEMISTRY_EXPORT*/ PeriodicElements : public vtkObject
{
public:
  vtkTypeMacro(PeriodicElements, vtkObject)
  void PrintSelf(ostream& os, vtkIndent indent) override;
  static PeriodicElements * New();

  //@{
  /**
   * Access the static ElementData object for raw access to
   * BODR data.
   */
  vtkGetNewMacro(DataOfElements, ElementData)
  //@}

  /**
   * Returns the number of elements in the periodic table.
   */
  static unsigned short NumberOfElements();

  /**
   * Given an atomic number, returns the symbol associated with the
   * element
   */
  const char * GetSymbol(unsigned short atomicNum);

  /**
   * Given an atomic number, returns the name of the element
   */
  const char * GetElementName(unsigned short atomicNum);

  //@{
  /**
   * Given a case-insensitive string that contains the symbol or name
   * of an element, return the corresponding atomic number.
   */
  unsigned short GetAtomicNumber(const vtkStdString &str);
  unsigned short GetAtomicNumber(const char *str);
  //@}

  /**
   * Given an atomic number, return the covalent radius of the atom
   */
  float GetCovalentRadius(unsigned short atomicNum);

  /**
   * Given an atomic number, returns the van der Waals radius of the
   * atom
   */
  float GetVDWRadius(unsigned short atomicNum);

  /**
   * Given an atomic number, returns the van der Waals radius of the
   * atom
   */
  float GetMaxVDWRadius();

  /**
   * Fill the given vtkLookupTable to map atomic numbers to the
   * familiar RGB tuples provided by the Blue Obelisk Data Repository
   */
  void GetDefaultLUT(vtkLookupTable *);

  /**
   * Given an atomic number, return the familiar RGB tuple provided by
   * the Blue Obelisk Data Repository
   */
  void GetDefaultRGBTuple(unsigned short atomicNum, float rgb[3]);

  /**
   * Given an atomic number, return the familiar RGB tuple provided by
   * the Blue Obelisk Data Repository
   */
  vtkColor3f GetDefaultRGBTuple(unsigned short atomicNum);

protected:
  PeriodicElements();
  ~PeriodicElements() override;

  static vtkNew<ElementData> DataOfElements;

private:
  PeriodicElements(const PeriodicElements&) = delete;
  void operator=(const PeriodicElements&) = delete;
};

#endif // !Elements_h
