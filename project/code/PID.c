#include "PID.h"


PID_t motor_pid[4] = {
    {
        .Target = 0,
        .Kp = 0.8,
        .Ki = 0.32,
        .Kd = 0.3,
        .OutMax = OUT_Max,
        .max_output_i = OUT_Max * ratio_i,
    },
    {
        .Target = 0,
        .Kp = 0.8,
        .Ki = 0.32,
        .Kd = 0.3,
        .OutMax = OUT_Max,
        .max_output_i = OUT_Max * ratio_i,
    },
    {
        .Target = 0,
        .Kp = 1.6,
        .Ki = 0.41,
        .Kd = 0.3,
        .OutMax = OUT_Max,
        .max_output_i = OUT_Max * ratio_i,
    },
    {
        .Target = 0,
        .Kp = 0.8,
        .Ki = 0.32,
        .Kd = 0.3,
        .OutMax = OUT_Max,
        .max_output_i = OUT_Max * ratio_i,
    }
};

// float pid_motor_out[4] = {0, 0, 0, 0};//pid传出
// float pid_speed_error1[4] = {0, 0, 0, 0}; // 本次误差
// float pid_speed_error2[4] = {0, 0, 0, 0}; // 上次误差
// float pid_integral[4] = {0, 0, 0, 0}; // 积分项

void pid_motor(void)
{
    for (uint8 j = 0; j < 4; j++)
    {
        motor_pid[j].Actual = encoder[j];
        PID_Update(&motor_pid[j]);
    }
    
	motorset_speed(1, motor_pid[0].Out);
	motorset_speed(2, motor_pid[1].Out);
	motorset_speed(3, motor_pid[2].Out);
	motorset_speed(4, motor_pid[3].Out);
}

void PID_Update(PID_t *p)
{
    float p_item,i_item,d_item;
	p->Error1 = p->Error0;
	p->Error0 = p->Target - p->Actual;

	// P
    p_item = p->Kp * p->Error0;

	// I
	if (p->Ki != 0)
	{
		p->ErrorInt += p->Error0;
	}
	else
	{
		p->ErrorInt = 0;
	}
    i_item = p->Ki * p->ErrorInt;
    
    // 积分项限幅
    if (p->max_output_i != 0)
    {
        i_item = target_limit_float(i_item,-p->max_output_i,p->max_output_i);
    }

	// d
    d_item = p->Kd * (p->Error0 - p->Error1);
    
	p->Out = p_item+i_item+d_item;
    
    p->Out = target_limit_float(p->Out,-p->OutMax,p->OutMax);
	
    
}

