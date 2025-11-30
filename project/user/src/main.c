/*********************************************************************************************************************
* RT1064DVL6A Opensourec Library 即（RT1064DVL6A 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
* 
* 本文件是 RT1064DVL6A 开源库的一部分
* 
* RT1064DVL6A 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
* 
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
* 
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
* 
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
* 
* 文件名称          main
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          IAR 8.32.4 or MDK 5.33
* 适用平台          RT1064DVL6A
* 店铺链接          https://seekfree.taobao.com/
* 
* 修改记录
* 日期              作者                备注
* 2022-09-21        SeekFree            first version
********************************************************************************************************************/

#include "zf_common_headfile.h"
void pid_key(void);
// 打开新的工程或者工程移动了位置务必执行以下操作
// 第一步 关闭上面所有打开的文件
// 第二步 project->clean  等待下方进度条走完

// 本例程是开源库移植用空工程
#define IPS200_TYPE     (IPS200_TYPE_SPI)  
int32 speeed=0;
key_state_enum key_state[4];
int main(void)
{
    
    clock_init(SYSTEM_CLOCK_600M);  // 不可删除
    debug_init();                   // 调试端口初始化 
	system_delay_ms(2000); 
    key_init(10);                                                  
    vofa_init();  
    ips200_set_dir(IPS200_PORTAIT);
    ips200_set_font(IPS200_8X16_FONT);
    ips200_set_color(RGB565_WHITE, RGB565_BLACK);
    ips200_init(IPS200_TYPE);
    interrupt_global_enable(0); 
     
    motorinit_pwm_init();
    Encoder_init();
    pit_ms_init(PIT_CH0, 1);   // 初始化 PIT_CH0 为周期中断 1ms 周期
    interrupt_set_priority(PIT_IRQn, 0);
	
    motor_target_speed[0] = 0;
    motor_target_speed[1] = 500;
    motor_target_speed[2] = 500;
    motor_target_speed[3] = 500;
		
//		motorset_speed(1, 2000);

    // 此处编写用户代码 例如外设初始化代码等
    while(1)
    {
        pid_key();
		    speeed=vofa_Rx();
        if(speeed!=100000)
        {
            motor_target_speed[0] = speeed;
            motor_target_speed[1] = speeed;
            motor_target_speed[2] = speeed;
            motor_target_speed[3] = speeed;
        }
		
       wireless_TX_data[0] = encoder[0];
       wireless_TX_data[1] = motor_target_speed[0];
       wireless_TX_data[2] = pid_motor_out[0];
       vofa_tx();
		
        // 显示实际速度
        ips200_show_string(0, 0, "Actual:");
        ips200_show_int(0, 16*1, (int)encoder[0], 6);
        ips200_show_int(0, 16*2, (int)encoder[1], 6);
        ips200_show_int(0, 16*3, (int)encoder[2], 6);
        ips200_show_int(0, 16*4, (int)encoder[3], 6);
        
        // 显示目标速度
        ips200_show_string(16*9, 0, "Target:");
        ips200_show_int(16*9, 16*1, (int)motor_target_speed[0], 6);
        ips200_show_int(16*9, 16*2, (int)motor_target_speed[1], 6);
        ips200_show_int(16*9, 16*3, (int)motor_target_speed[2], 6);
        ips200_show_int(16*9, 16*4, (int)motor_target_speed[3], 6);
        
        // 显示PID输出速度
        ips200_show_string(0, 16*6, "Output:");
        ips200_show_int(0, 16*7, (int)pid_motor_out[0], 6);
        ips200_show_int(0, 16*8, (int)pid_motor_out[1], 6);
        ips200_show_int(0, 16*9, (int)pid_motor_out[2], 6);
        ips200_show_int(0, 16*10, (int)pid_motor_out[3], 6);
        
        // 显示误差
        ips200_show_string(16*9, 16*6, "Error:");
        ips200_show_int(16*9, 16*7, (int)pid_speed_error1[0], 6);
        ips200_show_int(16*9, 16*8, (int)pid_speed_error1[1], 6);
        ips200_show_int(16*9, 16*9, (int)pid_speed_error1[2], 6);
        ips200_show_int(16*9, 16*10, (int)pid_speed_error1[3], 6);
        // 显示PID参数
        ips200_show_string(0, 16*12, "PID:");
        ips200_show_float(0, 16*13, base_pid.kp, 2, 4);
        ips200_show_float(0, 16*14, base_pid.ki, 2, 4);
        ips200_show_float(0, 16*15, base_pid.kd, 2, 4);
    }


}

// 定义PID调节按键
void pid_key(void)
{
    key_state[0] = key_get_state(KEY_1);

    if (key_state[0] == KEY_SHORT_PRESS)	
    {
        base_pid.kd += 0.1;
    }
    else if (key_state[0] == KEY_LONG_PRESS)	
    {
        base_pid.kd += 0.1;
    }

    key_state[1] = key_get_state(KEY_2);

    if (key_state[1] == KEY_SHORT_PRESS)	
    {
        base_pid.kd -= 0.1;
    }
    else if (key_state[1] == KEY_LONG_PRESS)	
    {
        base_pid.kd -= 0.1;
    }
    
    key_state[2] = key_get_state(KEY_3);
    if (key_state[2] == KEY_SHORT_PRESS)	
    {
        base_pid.ki += 0.01;
    }
    else if (key_state[2] == KEY_LONG_PRESS)	
    {
        base_pid.ki += 0.01;
    }
    
    key_state[3] = key_get_state(KEY_4);
    if (key_state[3] == KEY_SHORT_PRESS)	
    {
        base_pid.ki -= 0.01;
    }
    else if (key_state[3] == KEY_LONG_PRESS)	
    {
        base_pid.ki -= 0.01;
    }
}