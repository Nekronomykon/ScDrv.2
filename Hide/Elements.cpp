#include "Elements.h"
/*=========================================================================

  Program:   Local Fork of Visualization Toolkit
  Module:    PeriodicElements.cpp

  Copyright (c) ScrewDriver te Blackheadborough
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notice for more information.

  =========================================================================*/

#include <vtkAbstractArray.h>
#include <vtkBlueObeliskData.h>
#include <vtkColor.h>
#include <vtkDebugLeaks.h>
#include <vtkFloatArray.h>
#include <vtkLookupTable.h>
#include <vtkMutexLock.h>
#include <vtkObjectFactory.h>
#include <vtkStdString.h>
#include <vtkStringArray.h>
#include <vtkUnsignedShortArray.h>

#include <cassert>
#include <cctype>
#include <cstring>

// Setup static variables
vtkNew<ElementData> PeriodicElements::DataOfElements;

//----------------------------------------------------------------------------
vtkStandardNewMacro(PeriodicElements);

//----------------------------------------------------------------------------
PeriodicElements::PeriodicElements()
{
  this->DataOfElements->GetWriteMutex()->Lock();

  if (!this->DataOfElements->IsInitialized())
  {
    this->DataOfElements->Initialize();
  }

  this->DataOfElements->GetWriteMutex()->Unlock();
}

//----------------------------------------------------------------------------
PeriodicElements::~PeriodicElements() = default;

//----------------------------------------------------------------------------
void PeriodicElements::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  os << indent << "DataOfElements:\n";
  DataOfElements->PrintSelf(os, indent.GetNextIndent());
}


//----------------------------------------------------------------------------
unsigned short PeriodicElements::NumberOfElements()
{
  return DataOfElements->GetNumberOfElements();
}

//----------------------------------------------------------------------------
const char * PeriodicElements::GetSymbol(unsigned short atomicNum)
{
  if (atomicNum > NumberOfElements())
  {
    vtkWarningMacro("Atomic number out of range ! Using 0 instead of " << atomicNum);
    atomicNum = 0;
  }

  return DataOfElements->GetSymbols()->GetValue(atomicNum).c_str();
}

//----------------------------------------------------------------------------
const char * PeriodicElements::GetElementName(unsigned short atomicNum)
{
  if (atomicNum > this->NumberOfElements())
  {
    vtkWarningMacro("Atomic number out of range ! Using 0 instead of " << atomicNum);
    atomicNum = 0;
  }

  return DataOfElements->GetNames()->GetValue(atomicNum).c_str();
}

//----------------------------------------------------------------------------
unsigned short PeriodicElements::GetAtomicNumber(const vtkStdString &str)
{
  return this->GetAtomicNumber(str.c_str());
}

//----------------------------------------------------------------------------
unsigned short PeriodicElements::GetAtomicNumber(const char *str)
{
  // If the string is null or the BODR object is not initialized, just
  // return 0.
  if (!str)
  {
    return 0;
  }

  // First attempt to just convert the string to an integer. If this
  // works, return the integer
  int atoi_num = atoi(str);
  if (atoi_num > 0 &&
      atoi_num <= static_cast<int>(NumberOfElements()))
  {
    return static_cast<unsigned short>(atoi_num);
  }

  // Convert str to lowercase
  int i = 0;
  char *lowerStr = new char[strlen(str) + 1];
  strcpy(lowerStr, str);
  while (char &c = lowerStr[i++])
  {
    c = tolower(c);
  }

  // Cache pointers:
  vtkStringArray *lnames = this->DataOfElements->GetLowerNames();
  vtkStringArray *lsymbols = this->DataOfElements->GetLowerSymbols();
  const unsigned short numElements = NumberOfElements();

  // Compare with other lowercase strings
  for (unsigned short ind = 0; ind <= numElements; ++ind)
  {
    if (lnames->GetValue(ind).compare(lowerStr) == 0 ||
        lsymbols->GetValue(ind).compare(lowerStr) == 0)
    {
      delete [] lowerStr;
      return ind;
    }
  }

  // Manually test some non-standard names:
  // - Deuterium
  if (strcmp(lowerStr, "d") == 0 ||
      strcmp(lowerStr, "deuterium") == 0 )
  {
    delete [] lowerStr;
    return 1;
  }
  // - Tritium
  else if (strcmp(lowerStr, "t") == 0 ||
           strcmp(lowerStr, "tritium") == 0 )
  {
    delete [] lowerStr;
    return 1;
  }
  // - Aluminum (vs. Aluminium)
  else if (strcmp(lowerStr, "aluminum") == 0)
  {
    delete [] lowerStr;
    return 13;
  }

  delete [] lowerStr;
  return 0;
}

//----------------------------------------------------------------------------
float PeriodicElements::GetCovalentRadius(unsigned short atomicNum)
{
  if (atomicNum > NumberOfElements())
  {
    vtkWarningMacro("Atomic number out of range ! Using 0 instead of " << atomicNum);
    atomicNum = 0;
  }

  return DataOfElements->GetCovalentRadii()->GetValue(atomicNum);
}

//----------------------------------------------------------------------------
float PeriodicElements::GetVDWRadius(unsigned short atomicNum)
{
  if (atomicNum > NumberOfElements())
  {
    vtkWarningMacro("Atomic number out of range ! Using 0 instead of " << atomicNum);
    atomicNum = 0;
  }

  return DataOfElements->GetVDWRadii()->GetValue(atomicNum);
}

//----------------------------------------------------------------------------
float PeriodicElements::GetMaxVDWRadius()
{
  float maxRadius = 0;
  for(unsigned short i = 0; i < NumberOfElements(); i++)
  {
    maxRadius = std::max(maxRadius, this->GetVDWRadius(i));
  }
  return maxRadius;
}

//----------------------------------------------------------------------------
void PeriodicElements::GetDefaultLUT(vtkLookupTable *lut)
{
  const unsigned short numColors = NumberOfElements() + 1;
  vtkFloatArray *colors = DataOfElements->GetDefaultColors();
  lut->SetNumberOfColors(numColors);
  lut->SetIndexedLookup(true);
  float rgb[3];
  for (vtkIdType i = 0; static_cast<unsigned int>(i) < numColors; ++i)
  {
    colors->GetTypedTuple(i, rgb);
    lut->SetTableValue(i, rgb[0], rgb[1], rgb[2]);
    lut->SetAnnotation(i, this->GetSymbol(static_cast<unsigned short>(i)));
  }
}

//----------------------------------------------------------------------------
void PeriodicElements::GetDefaultRGBTuple(unsigned short atomicNum,
 float rgb[3])
{
  DataOfElements->GetDefaultColors()->GetTypedTuple(atomicNum, rgb);
}

//----------------------------------------------------------------------------
vtkColor3f PeriodicElements::GetDefaultRGBTuple(unsigned short atomicNum)
{
  vtkColor3f result;
  DataOfElements->GetDefaultColors()->GetTypedTuple(atomicNum
                                                          , result.GetData());
  return result;
}
