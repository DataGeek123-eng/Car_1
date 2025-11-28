#include "zf_common_headfile.h"




pid_data motor_pid_1 = PID_CREATE(50,0,0,0);
pid_data motor_pid_2 = PID_CREATE(50,0,0,0);
pid_data motor_pid_3 = PID_CREATE(50,0,0,0);
pid_data motor_pid_4 = PID_CREATE(50,0,0,0);


float pid_motor_out[4] = {0, 0, 0, 0};//pid传出
float pid_speed_error1[4] = {0, 0, 0, 0}; // 本次误差
float pid_speed_error2[4] = {0, 0, 0, 0}; // 上次误差
float pid_speed_error3[4] = {0, 0, 0, 0}; // 上上次误差

float my_abs(float i)
{
	if(i<0)
		i=-i;
	return i;
}


void scale_limit(float data[4])//比例限幅
{
	uint8 i=0;
	float max=0;
    for(i=0;i<4;i++)
    {
		if(max<my_abs(data[i]))
			max=data[i];
	
    }	
	
	if(max>OUT_Max)
	{
		for(i=0;i<4;i++)
		{
			data[i]=(data[i]*OUT_Max)/max;
		}
	}
	
}




void pid_motor(void)
{
    uint8  j;

    
    for (j = 0; j < 3; j++)
    {    
		pid_speed_error3[j] = pid_speed_error2[j]; // 上次误差给上上次误差
        pid_speed_error2[j] = pid_speed_error1[j]; // 本次误差给上此误差		   
    }
	
    pid_speed_error1[0] = Speed_Target[0] - encoder_data[0];
    pid_speed_error1[1] = Speed_Target[1] - encoder_data[1];
	pid_speed_error1[2] = Speed_Target[2] - encoder_data[2];
	pid_speed_error1[3] = Speed_Target[3] - encoder_data[3];

 // 输出增量= P * （ 本次误差 —— 上次误差） + I * 本次误差 + D * （ 本次误差 —— 2*上次误差 + 上上次误差）
    pid_motor_out[0] = pid_motor_out[0] + (motor_pid_1.kp * (pid_speed_error1[0] - pid_speed_error2[0]) + motor_pid_1.ki * pid_speed_error1[0] + motor_pid_1.kd * (pid_speed_error1[0] - 2 * pid_speed_error2[0] + pid_speed_error3[0]));
    pid_motor_out[1] = pid_motor_out[1] + (motor_pid_2.kp * (pid_speed_error1[1] - pid_speed_error2[1]) + motor_pid_2.ki * pid_speed_error1[1] + motor_pid_2.kd * (pid_speed_error1[1] - 2 * pid_speed_error2[1] + pid_speed_error3[1]));
	pid_motor_out[2] = pid_motor_out[2] + (motor_pid_3.kp * (pid_speed_error1[2] - pid_speed_error2[2]) + motor_pid_3.ki * pid_speed_error1[2] + motor_pid_3.kd * (pid_speed_error1[2] - 2 * pid_speed_error2[2] + pid_speed_error3[2]));
	pid_motor_out[3] = pid_motor_out[3] + (motor_pid_4.kp * (pid_speed_error1[3] - pid_speed_error2[3]) + motor_pid_4.ki * pid_speed_error1[3] + motor_pid_4.kd * (pid_speed_error1[3] - 2 * pid_speed_error2[3] + pid_speed_error3[3]));
	      
	scale_limit(pid_motor_out);//比例限幅

//	motorset_speed(0, target_limit_float(pid_motor_out[0],-10000,10000));
//	motorset_speed(1, target_limit_float(pid_motor_out[1],-10000,10000));
//	motorset_speed(2, target_limit_float(pid_motor_out[2],-10000,10000));
	
}







