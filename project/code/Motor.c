#include "zf_common_headfile.h"
#include "math.h"

float  Speed_Target[4]={0};

void Motor_Init()
{
	pwm_channel_enum channel_list[CHANNEL_NUMBER] = {PWM_CH1_A, PWM_CH1_B, PWM_CH2_A, PWM_CH2_B,
		
	                                                 PWM_CH3_A, PWM_CH3_B, PWM_CH4_A, PWM_CH4_B};
	
	//默认PWM_DUTY_MAX=10000，可在zf_driver_pwm_h中更改
	pwm_init(PWM_CH1_A, 17000, 0);                                                // 初始化 PWM 通道 频率 17KHz 初始占空比 0%
    pwm_init(PWM_CH1_B, 17000, 0);                                                // 初始化 PWM 通道 频率 17KHz 初始占空比 0%
    pwm_init(PWM_CH2_A, 17000, 0);                                                // 初始化 PWM 通道 频率 17KHz 初始占空比 0%
    pwm_init(PWM_CH2_B, 17000, 0);                                                // 初始化 PWM 通道 频率 17KHz 初始占空比 0%
    pwm_init(PWM_CH3_A, 17000, 0); 
    pwm_init(PWM_CH3_B, 17000, 0); 
    pwm_init(PWM_CH4_A, 17000, 0); 
    pwm_init(PWM_CH4_B, 17000, 0); 
}	


//任意方向运动
void Motor_TargetSpeed(uint16_t Angle,int16_t Speed,int16_t Wv)//Wv正为顺时针，负为逆时针
{
	
	
	
	Speed_Target[0]=(sin(Angle)*Speed+cos(Angle)*Speed+Wv);
	Speed_Target[1]=(sin(Angle)*Speed-cos(Angle)*Speed-Wv);
	Speed_Target[2]=(sin(Angle)*Speed+cos(Angle)*Speed-Wv);
	Speed_Target[3]=(sin(Angle)*Speed-cos(Angle)*Speed+Wv);
	
	scale_limit(Speed_Target);//比例限幅
}


void Motor_Mode(Motor_mode M)
{
	switch (M)
	{
		case(Front):
		    Motor_TargetSpeed(90,1000,0);
			break;
		
		case(Back):
			Motor_TargetSpeed(270,1000,0);
			break;
		
		case(Left):
		    Motor_TargetSpeed(0,1000,0);
			break;
		
		case(Right):
		    Motor_TargetSpeed(180,1000,0);
			break;
		
		case(Turn_left):
		    Motor_TargetSpeed(0,0,1000);
			break;
		
		case(Turn_right):
		    Motor_TargetSpeed(0,0,-1000);
			break;
		
		default:
		
			break;
		
	}
		
}

void Motor_pwm()
{
	if(pid_motor_out[0]>0)
	{
		pwm_set_duty(PWM_CH1_A,pid_motor_out[0]);
		pwm_set_duty(PWM_CH1_B,0);
	}
	else
	{
		pwm_set_duty(PWM_CH1_A,-pid_motor_out[0]);
		pwm_set_duty(PWM_CH1_B,PWM_DUTY_MAX);
	}
	
	if(pid_motor_out[1]>0)
	{
		pwm_set_duty(PWM_CH2_A,pid_motor_out[1]);
		pwm_set_duty(PWM_CH2_B,0);
	}
	else
	{
		pwm_set_duty(PWM_CH2_A,-pid_motor_out[1]);
		pwm_set_duty(PWM_CH2_B,PWM_DUTY_MAX);
	}
	
	if(pid_motor_out[2]>0)
	{
		pwm_set_duty(PWM_CH3_A,pid_motor_out[2]);
		pwm_set_duty(PWM_CH3_B,0);
	}
	else
	{
		pwm_set_duty(PWM_CH3_A,-pid_motor_out[2]);
		pwm_set_duty(PWM_CH3_B,PWM_DUTY_MAX);
	}
	
	if(pid_motor_out[3]>0)
	{
		pwm_set_duty(PWM_CH4_A,pid_motor_out[3]);
		pwm_set_duty(PWM_CH4_B,0);
	}
	else
	{
		pwm_set_duty(PWM_CH4_A,-pid_motor_out[3]);
		pwm_set_duty(PWM_CH4_B,PWM_DUTY_MAX);
	}
	
	
}





