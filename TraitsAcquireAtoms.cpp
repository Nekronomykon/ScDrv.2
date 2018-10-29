#include "TraitsAcquireAtoms.h"

const double TraitsBase::AngstromInBohr = 0.52917721067;

size_t TraitsBase::MeasureStringGroup(std::istream &in)
{
  std::string str_line;
  if (!in || !std::getline(in, str_line))
    return 0;
  rtrim(str_line);
  if (str_line.empty())
  {
    do
    {
      if (!std::getline(in, str_line))
        return 0;
      rtrim(str_line);
    } while (str_line.empty());
  }
  size_t nRes = 0;
  do
  {
    ++nRes;
    if (!std::getline(in, str_line))
      return 0;
    rtrim(str_line);
  } while (!str_line.empty());
  return nRes;
}
