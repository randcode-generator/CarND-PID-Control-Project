#include <iostream>
#include <fstream>
#include <stdio.h>
#include <csignal>
using namespace std;

string buildCommand(double p[]) {
  string str = "/home/eric/CarND-PID-Control-Project/build/pid ";
  str += to_string(p[0]) + " ";
  str += to_string(p[1]) + " ";
  str += to_string(p[2]);
  return str;
}

double getError() {
  ifstream s;
  s.open("out.txt");
  string str;
  s >> str;
  s.close();
  return stod(str);
}

void printError(double err, double p[]) {
  cout<<err<<" "<<p[0]<<" "<<p[1]<<" " <<p[2]<<endl;
  ofstream s;
  s.open("report.csv", ofstream::out|ofstream::app);
  string str = to_string(p[0]) + "," + to_string(p[1]) + "," + to_string(p[2]) + "," + to_string(err);
  s << str;
  s << endl;
  s.close();
}

int main() {
  remove("out.txt");
  remove("report.csv");
  double best_err = 100000000.0;
  double p[] = {0.25, 0, 30};
  double dp[] = {0.01, 0.0001, 0.01};

  string str = buildCommand(p);
  system(str.c_str());
  double err = getError();
  printError(err, p);

  while(true) {
    for(int i = 0; i < 3; i++) {
      p[i] += dp[i];
      str = buildCommand(p);
      system(str.c_str());
      double err = getError();
      printError(err, p);

      if(err < best_err) {
        best_err = err;
        dp[i] *= 1.2;
      } else {
        p[i] -= 2 * dp[i];
        str = buildCommand(p);
        system(str.c_str());
        double err = getError();
        printError(err, p);

        if(err < best_err) {
          best_err = err;
          dp[i] *= 1.2;
        } else {
          p[i] += dp[i];
          dp[i] *= 0.8;
        }
      }
    }
  }
}