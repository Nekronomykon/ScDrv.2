#include "TraitsAcquireAtoms.h"

const double TraitsBase::AngstromInBohr = 0.52917721067;

std::string TraitsBase::ScrollEmptyStrings(std::istream &in)
{
  std::string str_line;

  do
  {
    if (!std::getline(in, str_line))
      break;
    rtrim(str_line);
  } while (str_line.empty());

  return ltrim_copy(str_line);
}

size_t TraitsBase::MeasureStringGroup(std::istream &in)
{
  std::string str_line = ScrollEmptyStrings(in);

  if (str_line.empty())
    return 0; // error, 'in' is not Ok...

  size_t nRes = 0;
  do
  {
    ++nRes;
    if(!std::getline(in, str_line))
      break;
    rtrim(str_line);
  } while (!str_line.empty());
  
  rtrim(str_line);

  if (!str_line.empty()) 
    ++nRes;
  
  return nRes;
}
