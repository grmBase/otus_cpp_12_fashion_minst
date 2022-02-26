//---------------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------------
#include "predictor.h"
//---------------------------------------------------------------------------


class t_linreg_predictor: public i_predictor 
{
  public:

    t_linreg_predictor(const std::vector<double>&);

    double predict(const features&) const override;
    
  protected:

    std::vector<double> m_coef;
};
//---------------------------------------------------------------------------
