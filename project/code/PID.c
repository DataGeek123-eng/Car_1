#include "PID.h"

pid_param_t base_pid=PID_CREATE(512,13,0,0,0,0,0);//在pid.h里结构体在这调用


float pid_motor_out[4] = {0, 0, 0, 0};//pid传出
float pid_speed_error1[4] = {0, 0, 0, 0}; // 本次误差
float pid_speed_error2[4] = {0, 0, 0, 0}; // 上次误差
float pid_integral[4] = {0, 0, 0, 0}; // 积分项

void pid_motor(void)
{
    float p_term, i_term, d_term;
 
    pid_speed_error1[0] = motor_target_speed[0] - encoder[0];
    pid_speed_error1[1] = motor_target_speed[1] - encoder[1];
    pid_speed_error1[2] = motor_target_speed[2] - encoder[2];
    pid_speed_error1[3] = motor_target_speed[3] - encoder[3];

    for (uint8 j = 0; j < 4; j++)
    {    
        pid_speed_error1[j] = motor_target_speed[j] - encoder[j];
        // 计算比例项
        p_term = base_pid.kp * pid_speed_error1[j];
        
        // 计算积分项
        pid_integral[j] += pid_speed_error1[j];
        i_term = base_pid.ki * pid_integral[j];
        
        // 计算微分项
        d_term = base_pid.kd * (pid_speed_error1[j] - pid_speed_error2[j]);
        
        // 位置式PID输出 = P项 + I项 + D项
        pid_motor_out[j] = p_term + i_term + d_term;
        
        // 更新上次误差
        pid_speed_error2[j] = pid_speed_error1[j];
    }
    
	motorset_speed(0, target_limit_float(pid_motor_out[0],-4000,4000));
	motorset_speed(1, target_limit_float(pid_motor_out[1],-4000,4000));
	motorset_speed(2, target_limit_float(pid_motor_out[2],-4000,4000));
	motorset_speed(3, target_limit_float(pid_motor_out[3],-4000,4000));
} 
