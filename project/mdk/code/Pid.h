#ifndef __PID_H_
#define __PID_H_
#include "zf_common_headfile.h"

#define OUT_Max      10000

#define KP           1500
#define KI           KP/200
#define KD           300
#define I_Max        500

typedef struct {
    float kp;    //P
    float ki;    //I
    float kd;	//D
    float i_max; //integrator_max
//    float p_max; //integrator_max
//    float d_max; //integrator_max

//    float low_pass;

//    float out_p;
//    float out_i;
//    float out_d;
//	float PID_out;

//    float error;
//    float pre_error;
//    float pre_pre_error;
} pid_data;


#define PID_CREATE(_kp, _ki, _kd, max_i) \
    {                                    \
        .kp = _kp,                       \
        .ki = _ki,                       \
        .kd = _kd,                       \
		.i_max = max_i,                  \
	}
/*        .low_pass = _low_pass,           \
        .out_p = 0,                      \
        .out_i = 0,                      \
        .out_d = 0,                      \
        .p_max = max_p,                  \
        
        .d_max = max_d,                  \
*/
    
///////////////////以上不太好懂，chat_gpt一下



extern pid_data motor_pid_1;
extern pid_data motor_pid_2;
extern pid_data motor_pid_3;
extern pid_data motor_pid_4;
extern float pid_motor_out[4];





void scale_limit(float data[4]);
float my_abs(float i);
void pid_motor(void);


#endif


