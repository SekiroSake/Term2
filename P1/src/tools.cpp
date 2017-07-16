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
  VectorXd rmse(4);
  rmse << 0,0,0,0;
	if(estimations.size()==0 or estimations.size()!=ground_truth.size()){
    cout << "Error in inputs" << endl;
    return rmse;
    }

  VectorXd residuals(4);
	//accumulate squared residuals
	for(int i=0; i < estimations.size(); ++i){
    residuals = estimations[i]-ground_truth[i];
    residuals = residuals.array()*residuals.array();
    rmse = rmse + residuals;
	}

	//calculate the mean
  rmse = rmse / estimations.size();

	//calculate the squared root
	// ... your code here
  rmse = rmse.array().sqrt();  
  
  return rmse;
}

MatrixXd Tools::CalculateJacobian(const VectorXd& x_state) {
  /**
  TODO:
    * Calculate a Jacobian here.
  */ 
	MatrixXd Hj(3,4);
	//recover state parameters
    float px = x_state(0);
	float py = x_state(1);
	float vx = x_state(2);
	float vy = x_state(3);

  float rho_2 = pow(px,2) + pow(py,2);
  float rho = pow(rho_2,0.5);
  float rho_32 = pow(rho_2,1.5);
    
	if (rho_2 < 0.001){
    cout << "Error - division by zero" << endl;
	}else{
	//compute the Jacobian matrix
    Hj << px/rho, py/rho, 0, 0,
          -py/rho_2, px/rho_2, 0, 0,
          py*(vx*py-vy*px)/rho_32, px*(vy*px-vx*py)/rho_32, px/rho, py/rho;
	}
	return Hj; 
}
