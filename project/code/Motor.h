#ifndef __MOTOR_H_
#define __MOTOR_H_
#include "zf_common_headfile.h"

extern float  Speed_Target[4];


#define CHANNEL_NUMBER          (8)//pwm个数
#define PWM_CH1_A                 (PWM1_MODULE3_CHA_D0)
#define PWM_CH1_B                 (PWM1_MODULE3_CHB_D1)
#define PWM_CH2_A                 (PWM2_MODULE3_CHA_D2)
#define PWM_CH2_B                 (PWM2_MODULE3_CHB_D3)
#define PWM_CH3_A                 (PWM1_MODULE0_CHA_D12)
#define PWM_CH3_B                 (PWM1_MODULE0_CHB_D13)
#define PWM_CH4_A                 (PWM1_MODULE1_CHA_D14)
#define PWM_CH4_B                 (PWM1_MODULE1_CHB_D15)




typedef enum                                                                                            
{
	
	Front,//前进
	
	Back,//后退
	
	Left,//向左
	
	Right,//向右
	
	Turn_left,//左转
	
	Turn_right,//右转
	
}Motor_mode;


void Motor_Mode(Motor_mode M);
void Motor_Init();
void Motor_TargetSpeed(uint16_t Angle,int16_t Speed,int16_t Wv);
void Motor_pwm();


#endif

