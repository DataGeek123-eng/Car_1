#ifndef __PID_H
#define __PID_H
#include "zf_common_headfile.h"
typedef struct {
    float kp;    //P
    float ki;    //I
    float kd;	//D
    float i_max; //integrator_max
    float p_max; //integrator_max
    float d_max; //integrator_max
	float out_max; //integrator_max

    float low_pass;

    float out_p;
    float out_i;
    float out_d;
	float PID_out;

    float error;
    float pre_error;
    float pre_pre_error;
} pid_param_t;

#define PID_CREATE(_kp, _ki, _kd, _low_pass, max_p, max_i, max_d, max_out) \
    {                                    \
        .kp = _kp,                       \
        .ki = _ki,                       \
        .kd = _kd,                       \
        .low_pass = _low_pass,           \
        .out_p = 0,                      \
        .out_i = 0,                      \
        .out_d = 0,                      \
        .p_max = max_p,                  \
        .i_max = max_i,                  \
        .d_max = max_d,                  \
		.out_max = max_out,                  \
    }
///////////////////以上不太好懂，chat_gpt一下	

		
		
///useless		
extern pid_param_t base_pid;
extern float pid_motor_out[4];
extern float pid_speed_error1[4];
extern float pid_speed_error2[4];
extern float P_yaw;
extern float I_yaw;
extern float D_yaw;
///useless	
		
		
void pid_motor(void);
#endif