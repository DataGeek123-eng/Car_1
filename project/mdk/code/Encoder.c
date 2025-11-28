#include "zf_common_headfile.h"


int16 encoder_data[4] = {0};

void Encoder_Init()
{
	encoder_dir_init(ENCODER_DIR_1, ENCODER_DIR_PULSE_1, ENCODER_DIR_DIR_1);
	encoder_dir_init(ENCODER_DIR_2, ENCODER_DIR_PULSE_2, ENCODER_DIR_DIR_2);
	encoder_dir_init(ENCODER_DIR_3, ENCODER_DIR_PULSE_3, ENCODER_DIR_DIR_3);
	encoder_dir_init(ENCODER_DIR_4, ENCODER_DIR_PULSE_4, ENCODER_DIR_DIR_4);
	
	pit_ms_init(PIT_CH, 100);                                                   // 初始化 PIT1 为周期中断 100ms 周期

    interrupt_set_priority(PIT_PRIORITY, 0);                                    // 设置 PIT1 对周期中断的中断优先级为 0
	
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     PIT 的周期中断处理函数 这个函数将在 PIT 对应的定时器中断调用 详见 isr.c
// 参数说明     void
// 返回参数     void
// 使用示例     pit_handler();
//-------------------------------------------------------------------------------------------------------------------
void pit_handler (void)
{
    
    encoder_data[0] = encoder_get_count(ENCODER_DIR_1);// 获取编码器计数
    encoder_clear_count(ENCODER_DIR_1);// 清空编码器计数                          
     
	encoder_data[1] = encoder_get_count(ENCODER_DIR_2);// 获取编码器计数
    encoder_clear_count(ENCODER_DIR_2);// 清空编码器计数
	
	encoder_data[2] = encoder_get_count(ENCODER_DIR_3);// 获取编码器计数
    encoder_clear_count(ENCODER_DIR_3);// 清空编码器计数
	
	encoder_data[3] = encoder_get_count(ENCODER_DIR_4);// 获取编码器计数
    encoder_clear_count(ENCODER_DIR_4);// 清空编码器计数
	
	pid_motor();
	Motor_pwm();
}


