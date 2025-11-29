#include "motor.h"

float motor_target_speed[4];
float encoder[4],encoder_distant[4]={0};

float X_Encode, Y_Encode, X_Encode_last, Y_Encode_last,Y_Encode_last_handle,Y_distance, X_distance,Y_distance_handle; //四个轮子平均位移 ,x,y轴编码积分器累积值 ,x，y轴距离

float KX = 4.0f, KY = 4.093333f;

void motorinit_pwm_init(void)
{
    //最大占空比值PWM_DUTY_MAX 可以在fsl_pwm.h文件中修改 默认为50000
    //对于一个PWM模块 包含的所有通道只能输出频率一样 占空比不一样的 PWM RT1021只有两个PWM模块 每个模块有8个通道
    pwm_init(MOTOR1_A, 17000, 0);
    pwm_init(MOTOR1_B, 17000, 0);
    pwm_init(MOTOR2_A, 17000, 0);
    pwm_init(MOTOR2_B, 17000, 0);
    pwm_init(MOTOR3_A, 17000, 0);
    pwm_init(MOTOR3_B, 17000, 0);
    pwm_init(MOTOR4_A, 17000, 0);
    pwm_init(MOTOR4_B, 17000, 0);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      控制电机PWM通道赋值
//  @param      ch         选择电机通道（0,1,2,3）
//  @param      speed      对应电机的速度
//-------------------------------------------------------------------------------------------------------------------
void motorset_speed(uint8 ch, int32 speed)
{
//    speed = target_limit_int(speed, -3000, 3000);

    switch (ch)
    {
    case 1:
    {
        if (speed >= 0)
        {
            pwm_set_duty(MOTOR1_A, 10000);
            pwm_set_duty(MOTOR1_B, (uint32)speed);
        }
        else
        {
            pwm_set_duty(MOTOR1_A, 0);
            pwm_set_duty(MOTOR1_B, (uint32)-speed);
        }
    }
    break;
    case 2:
    {
        if (speed >= 0)
        {
            pwm_set_duty(MOTOR2_A,10000);
            pwm_set_duty(MOTOR2_B, (uint32)speed);
        }
        else
        {
            pwm_set_duty(MOTOR2_A, 0);
            pwm_set_duty(MOTOR2_B, (uint32)-speed);
        }
    }
    break;
    case 3:
    {
        if (speed >= 0)
        {
            pwm_set_duty(MOTOR3_A, 0);
            pwm_set_duty(MOTOR3_B, (uint32)speed);
        }
        else
        {
            pwm_set_duty(MOTOR3_A, 10000);
            pwm_set_duty(MOTOR3_B, (uint32)-speed);
        }
    }
    break;
    case 4:
    {
        if (speed >= 0)
        {
            pwm_set_duty(MOTOR4_A, 10000);
            pwm_set_duty(MOTOR4_B, (uint32)speed);
        }
        else
        {
            pwm_set_duty(MOTOR4_A, 0);
            pwm_set_duty(MOTOR4_B, (uint32)-speed);
        }
    }
    break;
    }

}


void motion_analyse(float Vx, float Vy, float Vz)//麦轮速度解析
{
    motor_target_speed[0] = (Vy - Vx +Vz);
    motor_target_speed[1] = (Vy + Vx -Vz);
    motor_target_speed[2] = (Vy - Vx -Vz);
    motor_target_speed[3] = (Vy + Vx +Vz);
}

void Turn_analyse(float Vx, float Vy, float Vz)//麦轮差速转向速度解析
{
    motor_target_speed[0] = (Vy -Vx +1*Vz);
    motor_target_speed[1] = (Vy +Vx -1*Vz);
    motor_target_speed[2] = (Vy - Vx - 1.4*Vz);
    motor_target_speed[3] = (Vy + Vx + 1.4*Vz);
}


void Encoder_init(void)
{
    encoder_dir_init(ENCODER_1, ENCODER_1_LSB, ENCODER_1_DIR); // 初始化编码器模块与引脚 方向编码器模式
    encoder_dir_init(ENCODER_2, ENCODER_2_LSB, ENCODER_2_DIR); // 初始化编码器模块与引脚 方向编码器模式
    encoder_dir_init(ENCODER_3, ENCODER_3_LSB, ENCODER_3_DIR); // 初始化编码器模块与引脚 方向编码器模式
    encoder_dir_init(ENCODER_4, ENCODER_4_LSB, ENCODER_4_DIR);
}

void Encoder_get(void)
{
	// encoder[0] = RecurrenceFilter(encoder_get_count(ENCODER_1),EncoderData0);//递推得到每个编码器的值
	// encoder[1] = RecurrenceFilter(-encoder_get_count(ENCODER_2),EncoderData1);
	// encoder[2] = RecurrenceFilter(-encoder_get_count(ENCODER_3),EncoderData2);
	// encoder[3] = RecurrenceFilter(encoder_get_count(ENCODER_4),EncoderData3);
	 encoder[0] = -encoder_get_count(ENCODER_1);
	 encoder[1] = encoder_get_count(ENCODER_2);
	 encoder[2] = -encoder_get_count(ENCODER_3);
	 encoder[3] = encoder_get_count(ENCODER_4);


}


void Encoder_clear(void)
{
    encoder_clear_count(ENCODER_1);
    encoder_clear_count(ENCODER_2);   
    encoder_clear_count(ENCODER_3); 
	encoder_clear_count(ENCODER_4);  
}

uint8 Encode_distance(void)
{
//     Y_Encode = (encoder[0] + encoder[1] + encoder[2] + encoder[3]) / 4.0f;//求合速度
//     X_Encode = (encoder[1] + encoder[3] -	 encoder[2] - encoder[0]) / 4.0f;
 
//     X_distance = X_distance + KX * ((X_Encode + X_Encode_last) * dtt / 2.0f);//权值求平均KX就是一个常数
//     Y_distance = Y_distance + KY * ((Y_Encode + Y_Encode_last) * dtt / 2.0f);
//     Y_distance_handle= Y_distance_handle + KY * ((Y_Encode + Y_Encode_last) * dtt / 2.0f);
//     X_Encode_last = X_Encode;
//     Y_Encode_last = Y_Encode;
// 	  Y_Encode_last_handle=Y_Encode;
//    return 1;

    encoder_distant[0] += encoder[0];    
    encoder_distant[1] += encoder[1];    
    encoder_distant[2] += encoder[2];    
    encoder_distant[3] += encoder[3];    
    return 1;

}