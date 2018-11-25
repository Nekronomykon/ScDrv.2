#include "TraitsAcquireAtoms.h"

using namespace std;

const double TraitsBase::AngstromInBohr = 0.52917721067;

string TraitsBase::ScrollEmptyStrings(BaseInput& in)
{
  string str_line;

  do
  {
    if (!getline(in, str_line))
      break;
    rtrim(str_line);
  } while (str_line.empty());

  return ltrim_copy(str_line);
}

size_t TraitsBase::MeasureStringGroup(BaseInput& in)
{
  string str_line = ScrollEmptyStrings(in);

  if (str_line.empty())
    return 0; // error, 'in' is not Ok...

  size_t nRes = 0;
  do
  {
    ++nRes;
    if(!getline(in, str_line))
      break;
    rtrim(str_line);
  } while (!str_line.empty());
  
  rtrim(str_line);

  if (!str_line.empty()) 
    ++nRes;
  
  return nRes;
}

bool TraitsBase::ScrollDownTo(BaseInput & in, const char * key_ptr)
{
  string key(key_ptr);
  if (key.empty()) 
    return false;

  string one_line;
  if (!std::getline(in, one_line))
    return false;
  do
  {
    rtrim(one_line);
    if (one_line.empty())
      continue;
    if (!one_line.compare(key))
      return true;
  } while (std::getline(in, one_line));

  return false;
}
