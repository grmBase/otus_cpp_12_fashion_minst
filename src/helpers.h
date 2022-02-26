//---------------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------------
#include <istream>
#include <vector>
//---------------------------------------------------------------------------
#include "predictor.h"
//---------------------------------------------------------------------------




bool read_features(std::istream& stream, size_t& aun_type, i_predictor::features& features);

std::vector<double> read_vector(std::istream&);