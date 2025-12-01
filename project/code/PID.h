#ifndef __PID_H
#define __PID_H
#include "zf_common_headfile.h"

// max_output_i！=0时，积分项输出限幅

typedef struct {
	float Target;
	float Actual;
	float Out;
	
	float Kp;
	float Ki;
	float Kd;
	
	float Error0;
	float Error1;
	float ErrorInt;
	
	float OutMax;
    
    float max_output_i;
} PID_t;

// #define PID_CREATE(_kp, _ki, _kd, _low_pass, max_p, max_i, max_d, max_out) \
//     {                                    \
//         .kp = _kp,                       \
//         .ki = _ki,                       \
//         .kd = _kd,                       \
//         .low_pass = _low_pass,           \
//         .out_p = 0,                      \
//         .out_i = 0,                      \
//         .out_d = 0,                      \
//         .p_max = max_p,                  \
//         .i_max = max_i,                  \
//         .d_max = max_d,                  \
// 		.out_max = max_out,                  \
//     }
///////////////////以上不太好懂，chat_gpt一下	

extern PID_t motor_pid[4];
// extern float pid_motor_out[4];
// extern float pid_speed_error1[4];
// extern float pid_speed_error2[4];

void PID_Update(PID_t *p);
void pid_motor(void);
#endif