//*************************************************参数定义/初始化区域**************************************************//
#include "zf_common_headfile.h"
#include "menu.h"
key_state_enum key_state[4];

void menu_show(void)
{
	 // 显示实际速度
        ips200_show_string(0, 0, "Actual:");
        ips200_show_int(0, 16*1, (int)encoder[0], 6);
        ips200_show_int(0, 16*2, (int)encoder[1], 6);
        ips200_show_int(0, 16*3, (int)encoder[2], 6);
        ips200_show_int(0, 16*4, (int)encoder[3], 6);
        
        // 显示目标速度
        ips200_show_string(16*9, 0, "Target:");
        ips200_show_int(16*9, 16*1, (int)motor_pid[0].Target, 6);
        ips200_show_int(16*9, 16*2, (int)motor_pid[1].Target, 6);
        ips200_show_int(16*9, 16*3, (int)motor_pid[2].Target, 6);
        ips200_show_int(16*9, 16*4, (int)motor_pid[3].Target, 6);
        
        // 显示PID输出速度
        ips200_show_string(0, 16*6, "Output:");
        ips200_show_int(0, 16*7, (int)motor_pid[0].Out, 6);
        ips200_show_int(0, 16*8, (int)motor_pid[1].Out, 6);
        ips200_show_int(0, 16*9, (int)motor_pid[2].Out, 6);
        ips200_show_int(0, 16*10, (int)motor_pid[3].Out, 6);
        
        // 显示误差
        ips200_show_string(16*9, 16*6, "Error:");
        ips200_show_int(16*9, 16*7, (int)motor_pid[0].Error1, 6);
        ips200_show_int(16*9, 16*8, (int)motor_pid[1].Error1, 6);
        ips200_show_int(16*9, 16*9, (int)motor_pid[2].Error1, 6);
        ips200_show_int(16*9, 16*10, (int)motor_pid[3].Error1, 6);
        // 显示PID参数
        ips200_show_string(0, 16*12, "PID:");
        ips200_show_float(0, 16*13, motor_pid[2].Kp, 2, 4);
        ips200_show_float(0, 16*14, motor_pid[2].Ki, 2, 4);
        ips200_show_float(0, 16*15, motor_pid[2].Kd, 2, 4);




}

void menu_value_init()
{
	flash_init();
	flash_buffer_clear();
	menu_flash_read();
}

void pid_key(uint8 i)
{
    key_state[0] = key_get_state(KEY_1);

    if (key_state[0] == KEY_SHORT_PRESS)	
    {
        motor_pid[i].Kp += 0.1;
    }
    else if (key_state[0] == KEY_LONG_PRESS)	
    {
        motor_pid[i].Kp += 0.1;
    }

    key_state[1] = key_get_state(KEY_2);

    if (key_state[1] == KEY_SHORT_PRESS)	
    {
        motor_pid[i].Kp -= 0.1;
    }
    else if (key_state[1] == KEY_LONG_PRESS)	
    {
        motor_pid[i].Kp -= 0.1;
    }
    
    key_state[2] = key_get_state(KEY_3);
    if (key_state[2] == KEY_SHORT_PRESS)	
    {
        motor_pid[i].Ki += 0.01;
    }
    else if (key_state[2] == KEY_LONG_PRESS)	
    {
        motor_pid[i].Ki += 0.01;
    }
    
    key_state[3] = key_get_state(KEY_4);
    if (key_state[3] == KEY_SHORT_PRESS)	
    {
        motor_pid[i].Ki -= 0.01;
    }
    else if (key_state[3] == KEY_LONG_PRESS)	
    {
        motor_pid[i].Ki -= 0.01;
    }
}


void Speed_key(uint8 i)
{
    static float Vx = 0, Vy = 0, Vz = 0;
    key_state[0] = key_get_state(KEY_1);
    if (key_state[0] == KEY_SHORT_PRESS)	
    {
        Vx += 100;
       
    }
    else if (key_state[0] == KEY_LONG_PRESS)	
    {
        Vx += 10;
    }

    key_state[1] = key_get_state(KEY_2);
    if (key_state[1] == KEY_SHORT_PRESS)	
    {
        Vx -= 100;
       
    }
    else if (key_state[1] == KEY_LONG_PRESS)	
    {
        Vx -= 10;
    }
    
    key_state[2] = key_get_state(KEY_3);
    if (key_state[2] == KEY_SHORT_PRESS)	
    {
        Vy += 100;
       
    }
    else if (key_state[2] == KEY_LONG_PRESS)	
    {
        Vy += 10;
    }
    key_state[3] = key_get_state(KEY_4);
    if (key_state[3] == KEY_SHORT_PRESS)	
    {
        Vy -= 100;
       
    }
    else if (key_state[3] == KEY_LONG_PRESS)	
    {
        Vy -= 10;
    }

    

    
    motion_analyse(Vx, Vy, Vz);
}

