#include "PID.h"

using namespace std;

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;

  p_error = i_error = d_error = 0;
}

void PID::UpdateError(double cte) {
  p_error = cte;
  i_error += cte;
  d_error = cte - prev_cte;
  prev_cte = cte;
  steering = (-Kp * p_error) - (Ki * i_error) - (Kd * d_error);
}

