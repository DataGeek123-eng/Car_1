#include "PID.h"

pid_param_t base_pid=PID_CREATE(512,13,0,0,0,0,0);//在pid.h里结构体在这调用
// pid_param_t angle2_pid=PID_CREATE(2.5,0,0.79,0,0,0,0);
// pid_param_t angle_pid=PID_CREATE(3.95,0,0.68,0,0,0,0);
// pid_param_t turn_pid=PID_CREATE(0.63,0,0.38,0,0,0,0);
// pid_param_t turn_x_pid=PID_CREATE(1.23,0,0.55,0,0,0,0);//横向PID矫正
// pid_param_t return_pid=PID_CREATE(0.39,0,0.26,0,0,0,0);//返回主赛道pid
// pid_param_t rectify_pid=PID_CREATE(1.5,0,0.23,0,0,0,0);//环岛矫正PID
// pid_param_t photo_pidx=PID_CREATE(0.23,0,0.31,0,0,0,0);//卡片矫正PID
// pid_param_t photo_pidy=PID_CREATE(0.23,0,0.28,0,0,0,0);//卡片矫正PID
// pid_param_t photo_x_mcx=PID_CREATE(0.35,0,0.31,0,0,0,0);//MCX卡片矫正PID
// pid_param_t photo_y_mcx=PID_CREATE(0.35,0,0.28,0,0,0,0);//MCX卡片矫正PID
// pid_param_t dist_pidy=PID_CREATE(1.2,0,0.40,0,0,0,0);//卡片矫正PID
// pid_param_t dist_pidx=PID_CREATE(0.8,0,0.30,0,0,0,0);//卡片矫正PID
// pid_param_t dis_large_pidy=PID_CREATE(2.3,0,0.37,0,0,0,0);//卡片矫正PID
// pid_param_t dis_large_pidx=PID_CREATE(2.3,0,0.25,0,0,0,0);//卡片矫正PID



float pid_motor_out[4] = {0, 0, 0, 0};//pid传出
float pid_speed_error1[4] = {0, 0, 0, 0}; // 本次误差
float pid_speed_error2[4] = {0, 0, 0, 0}; // 上次误差
float pid_speed_error3[4] = {0, 0, 0, 0}; // 上上次误差

void pid_motor(void)
{
    uint8 i, j;
 
    pid_speed_error1[0] = motor_target_speed[0] - encoder[0];
    pid_speed_error1[1] = motor_target_speed[1] - encoder[1];
    pid_speed_error1[2] = motor_target_speed[2] - encoder[2];
    pid_speed_error1[3] = motor_target_speed[3] - encoder[3];

// 输出增量= P * （ 本次误差 —— 上次误差） + I * 本次误差 + D * （ 本次误差 —— 2*上次误差 + 上上次误差）
    pid_motor_out[0] = pid_motor_out[0] + (base_pid.kp * (pid_speed_error1[0] - pid_speed_error2[0]) + base_pid.ki * pid_speed_error1[0] + base_pid.kd * (pid_speed_error1[0] - 2 * pid_speed_error2[0] + pid_speed_error3[0]));
    pid_motor_out[1] = pid_motor_out[1] + (base_pid.kp * (pid_speed_error1[1] - pid_speed_error2[1])+ base_pid.ki * pid_speed_error1[1] + base_pid.kd*(pid_speed_error1[1] - 2 * pid_speed_error2[1] + pid_speed_error3[1]));
    pid_motor_out[2] = pid_motor_out[2] + (base_pid.kp * (pid_speed_error1[2] - pid_speed_error2[2]) + base_pid.ki * pid_speed_error1[2] + base_pid.kd * (pid_speed_error1[2] - 2 * pid_speed_error2[2] + pid_speed_error3[2]));
    pid_motor_out[3] = pid_motor_out[3] + (base_pid.kp * (pid_speed_error1[3] - pid_speed_error2[3]) + base_pid.ki* pid_speed_error1[3] + base_pid.kd  * (pid_speed_error1[3] - 2 * pid_speed_error2[3] + pid_speed_error3[3]));
    for (j = 0; j < 4; j++)
    {    
        pid_speed_error2[j] = pid_speed_error1[j]; // 本次误差给上此误差
        pid_speed_error3[j] = pid_speed_error2[j]; // 上次误差给上上次误差
		
       
    }
	motorset_speed(0, target_limit_float(pid_motor_out[0],-4000,4000));
	motorset_speed(1, target_limit_float(pid_motor_out[1],-4000,4000));
	motorset_speed(2, target_limit_float(pid_motor_out[2],-4000,4000));
	motorset_speed(3, target_limit_float(pid_motor_out[3],-4000,4000));
} 
