//---------------------------------------------------------------------------
#include <numeric>   // inner_product()
#include <stdexcept> // invalid_argument
//---------------------------------------------------------------------------
#include "linreg_predictor.h"
//---------------------------------------------------------------------------


t_linreg_predictor::t_linreg_predictor(const std::vector<double>& acoef)
  : m_coef{acoef}
{
}
//---------------------------------------------------------------------------


double t_linreg_predictor::predict(const features& afeat) const
{
  if(afeat.size() + 1 != m_coef.size()) {
    throw std::invalid_argument{"Incorrect feature vector size"};
  }

  return std::inner_product(afeat.begin(), afeat.end(), ++m_coef.begin(), m_coef.front());
}
//---------------------------------------------------------------------------