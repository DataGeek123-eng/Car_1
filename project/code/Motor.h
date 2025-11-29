
#ifndef MOTOR_H

#define MOTOR_H
#include "zf_common_headfile.h"
//////////////////////////


            ////车头//////
//////00000电机和编码器///////////////11111电机和编码器/////



#define MOTOR1_A   PWM1_MODULE0_CHB_D13   //定义1电机正转PWM引脚
#define MOTOR1_B   PWM1_MODULE0_CHA_D12   //定义1电机反转PWM引脚

#define MOTOR2_A    PWM1_MODULE1_CHB_D15   //定义2电机正转PWM引脚
#define MOTOR2_B    PWM1_MODULE1_CHA_D14  //定义2电机反转PWM引脚

#define MOTOR3_A   PWM1_MODULE3_CHB_D1   //定义3电机正转PWM引脚
#define MOTOR3_B   PWM1_MODULE3_CHA_D0   //定义3电机反转PWM引脚

#define MOTOR4_A   PWM2_MODULE3_CHA_D2  //定义4电机正转PWM引脚
#define MOTOR4_B   PWM2_MODULE3_CHB_D3  //定义4电机反转PWM引脚

// 编码
#define ENCODER_1                       (QTIMER1_ENCODER1)
#define ENCODER_1_LSB                   (QTIMER1_ENCODER1_CH1_C0)
#define ENCODER_1_DIR                   (QTIMER1_ENCODER1_CH2_C1)
                                        
#define ENCODER_2                       (QTIMER1_ENCODER2)
#define ENCODER_2_LSB                   (QTIMER1_ENCODER2_CH1_C2)
#define ENCODER_2_DIR                   (QTIMER1_ENCODER2_CH2_C24)
                                        
#define ENCODER_3                       (QTIMER2_ENCODER1)
#define ENCODER_3_LSB                   (QTIMER2_ENCODER1_CH1_C3)
#define ENCODER_3_DIR                   (QTIMER2_ENCODER1_CH2_C25)
                                        
#define ENCODER_4                       (QTIMER3_ENCODER2)
#define ENCODER_4_LSB                   (QTIMER3_ENCODER2_CH1_B18)
#define ENCODER_4_DIR                   (QTIMER3_ENCODER2_CH2_B19)


extern float motor_target_speed[4];//从其他地方传入的目标数据
extern float encoder[4],encoder_distant[4];//四个编码器速度和距离
extern float X_Encode, Y_Encode, X_Encode_last, Y_Encode_last,Y_Encode_last_handle, Y_distance, X_distance,Y_distance_handle; //四个轮子平均位移 ,x,y轴编码积分器累积值 ,x，y轴距离




void motorinit_pwm_init(void);
void motorset_speed(uint8 ch, int32 speed);
void motion_analyse(float Vx, float Vy, float Vz);
void Encoder_get(void);//获得编码器值
void Encoder_init(void);
void Encoder_clear(void);//编码器标志位清除
void Turn_analyse(float Vx, float Vy, float Vz);//麦轮差速转向速度解析
uint8 Encode_distance(void);//编码器积分距离



#endif