//---------------------------------------------------------------------------
#include <string>
#include <sstream>
#include <iterator>
#include <stdlib.h>
#include <iostream>
//---------------------------------------------------------------------------
#include "helpers.h"
#include "consts.h"
//---------------------------------------------------------------------------



void split(const std::string& str, char ac_sep, 
  size_t& aun_type, std::vector<double>& avec_res)
{
  bool f_first = true;

  std::string::size_type start = 0;
  while(start < str.length())
  {
    char* pEnd = nullptr;
    if(f_first) {
      f_first = false;
      aun_type = std::strtol(str.c_str() + start, &pEnd, 10);
    }
    else {
      int tmp = std::strtol(str.c_str() + start, &pEnd, 10);
      avec_res.push_back(tmp);
    }  

    start = (pEnd - str.c_str() + 1);
  }
}
//---------------------------------------------------------------------------



bool read_features(std::istream& stream, size_t& aun_type, i_predictor::features& features) {

  features.clear();
  features.reserve(cun_num_of_coeff - 1);

  std::string line;
  std::getline(stream, line);

  if (line.length() == 0) {
    return false;
  }

  split(line, ',', aun_type, features);

  return true;
}
//---------------------------------------------------------------------------



std::vector<double> read_vector(std::istream& stream) 
{
  std::vector<double> result;

  std::copy(std::istream_iterator<double>(stream),
            std::istream_iterator<double>(),
            std::back_inserter(result));
  return result;
}
//---------------------------------------------------------------------------