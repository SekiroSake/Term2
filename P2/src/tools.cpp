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
    //Filter input
    if(estimations.size()==0 or estimations.size()!=ground_truth.size()){
        std::cout << "Error in inputs" << std::endl;
        return rmse;
    }
    
    //Init
    rmse = VectorXd(estimations[0].size());
    rmse.fill(0.0);
    
    VectorXd residuals;
    
    //accumulate squared residuals
    for(int i=0; i < estimations.size(); ++i){
        residuals = estimations[i]-ground_truth[i];
        residuals = residuals.array()*residuals.array();
        rmse = rmse + residuals;
    }
    
    //calculate retVal
    rmse = rmse / estimations.size();
    rmse = rmse.array().sqrt();
    
    return rmse;
}
