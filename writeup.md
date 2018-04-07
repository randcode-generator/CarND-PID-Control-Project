# CarND-Controls-PID

This is a writeup for the PID controller project. In this project, we will use PID control the steering wheel.

# Background
PID stands for Proportional, Integral, and Derivative.

PID is the sum of all the following:

1) Proportional: -Kp * CTE
2) Integral: -Ki * sum of all CTE
3) Derivative: -Kd * previous CTE - current CTE

Therefore:

SA = -Kp * CTE - Ki * total_CTE - Kd * delta_CTE

Note: 
1) CTE - Cross Track Error. 
2) Kp - Proportional coefficient
3) Ki - Integral coefficient
4) Kd - Derivative coefficient
5) SA - Steering angle

# How it works
1) The simulator returns the CTE
2) Apply the PID formula to get the steering angle
3) Modulo the angle by 2 pi
4) Convert from radian to degrees
5) Divide by 25 so it's between -1 and 1
6) Check to see if the CTE is between -0.2 and 0.2. If the CTE is out of range, set the throttle to negative so the car will slow down
7) Check to see if the speed is less than 20. If so, set the throttle to positive 1 so it speeds up

# Finding Coefficients
1) Manual tuning
    * Trial and Error
    * Looking at how often the car oscillates and if it drives safely
2) Twiddle
    * Use Twiddle to find optimized values from manual tuning
    * Wrote a separate program (train.cpp) to run the pid program
    * The program records the PID coefficients and the total CTE from the pid program

# Building Twiddle program
`cd build`

`g++ -o train ../src/train.cpp`

To stop the twiddle program (Not sure if there's a better way)

`killall train && killall pid`

# Reflection
1) With just P alone:
    * The car oscillates
    * The larger the CTE, the larger the steering angle
    * The smaller the CTE, the smaller the steering angle
2) With just I alone:
    * The car will run off the road
    * Runs in circles regardless of Ki value
3) With just D alone:
    * The car will run off the road
    * The difference between the current CTE and previous CTE is usually small, so the steering angle will be small
4) With just P and D:
    * The total error will be high because the car seems to always bear right. The CTE is positive if the car is right of the track and negative if the car is left of the track
    * Less oscillations
    * Drives pretty smoothly, high total error though
    * P: 0.272, I: 0, D: 30.002
5) With P, I, and D:
    * When the total error is too high, the car bears left (negative CTE) to help reduce the total error
    * The car always tries to be on track and reduce total error, therefore, it creates a lot of mini-oscillations
    * Drives not as smooth as P and D, low total error though
    * P: 0.253652, I: 0.000827, D: 30.02371
    
