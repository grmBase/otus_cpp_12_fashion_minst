//---------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> //nth_element
//---------------------------------------------------------------------------
#include "helpers.h"
#include "linreg_predictor.h"
#include "consts.h"
//---------------------------------------------------------------------------


struct
{
  bool operator()(const std::pair<double, size_t>& a, const std::pair<double, size_t>& b) const
  {
    return a.first > b.first;
  }
} custom_greather;
//---------------------------------------------------------------------------


int main(int argc, char* argv[])
{

  if(argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <.csv> <model>" << std::endl;
    return EXIT_FAILURE;
  }


  std::vector<t_linreg_predictor> vec_predicotrs;
  {
    std::ifstream istream{ argv[1] };
    auto coef = read_vector(istream);
    istream.close();

    for(size_t i=0; i<cun_num_of_models; ++i)
    {
      std::vector<double> tmp;

      tmp.reserve(cun_num_of_coeff);
      for(size_t j=0; j< cun_num_of_coeff; j++)
      {
        tmp.push_back(coef[i * cun_num_of_coeff + j]);
      }

      vec_predicotrs.emplace_back(std::move(tmp));
    }
  }

  std::string str_test_data = argv[2];
  std::ifstream data{str_test_data};

  {
    i_predictor::features features{};
    size_t un_type = 0;

    size_t un_success = 0;
    size_t un_fail = 0;
    while(read_features(data, un_type, features))
    {
      std::vector<std::pair<double, size_t>> vec_predictions;

      for(size_t i=0; i<vec_predicotrs.size(); ++i)
      {
        vec_predictions.emplace_back(vec_predicotrs[i].predict(features), i);
      }

      std::nth_element(vec_predictions.begin(), vec_predictions.begin() + 1, vec_predictions.end(), custom_greather);

      //std::cout << vec_predictions[0].first << ", second: " << vec_predictions[0].second << std::endl;


      if (!vec_predictions.size()) {
        std::cerr << "zero size list???" << std::endl;
        break;
      }

      if(vec_predictions[0].second != un_type) {
        un_fail ++;
        std::cerr << "prediction failed. expected: " << un_type << ", received: " << vec_predictions[0].second << std::endl;
      }
      else {
        un_success ++;
        //std::cout << "ok" << std::endl;
      }
    };


    double rate = 0;
    if(double(un_success) + double(un_fail)) // защита от деление на 0
    {
      rate = double(un_success) / (double(un_success) + double(un_fail));
    }
    
    std::cout << "sucesses: " << un_success << ", fails: " << un_fail 
      << ", rate: " << rate << std::endl;
  };

  data.close();
}
//---------------------------------------------------------------------------
