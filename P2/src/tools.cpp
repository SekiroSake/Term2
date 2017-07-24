#include <iostream>
#include "tools.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
    /**
     TODO:
     * Calculate the RMSE here.
     */
    VectorXd rmse;
    //Filter inputs
    if(estimations.size()==0 or estimations.size()!=ground_truth.size()){
        std::cout << "Input Error!"<<std::endl;
        return rmse;
    }
    //Init
    rmse = VectorXd(estimations[0].size());
    rmse.fill(0.0);
    
    VectorXd residuals;
    for(int i=0;i<estimations.size();++i){
        residuals = estimations[i] - ground_truth[i];
        residuals = residuals.array()*residuals.array();
        rmse = rmse + residuals;
    }
    
    //Refine RMSE
    rmse = rmse / estimations.size();
    rmse = rmse.array().sqrt();
    
    return rmse;
}
