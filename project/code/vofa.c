#include "vofa.h"

//发送
uint8 data_len,data_buffer[32];
uint8 tail[4] = {0x00, 0x00, 0x80, 0x7f}; // vofa协议帧尾
float wireless_TX_data[COUNT_TX];//蓝牙串口发送数据数组COUNT_TX在vofa.h

void vofa_init(void)
{
   wireless_uart_init();
}

void vofa_tx(uint8 motor)
{

    if(motor==5)
    {
        wireless_TX_data[0] = motor_pid[0].Actual;
        wireless_TX_data[1] = motor_pid[0].Target;
        wireless_TX_data[2] = motor_pid[0].Out;
        wireless_TX_data[3] = motor_pid[0].Error1;

        wireless_TX_data[4] = motor_pid[1].Actual;
        wireless_TX_data[5] = motor_pid[1].Target;
        wireless_TX_data[6] = motor_pid[1].Out;
        wireless_TX_data[7] = motor_pid[1].Error1;
        
        wireless_TX_data[8] = motor_pid[2].Actual;
        wireless_TX_data[9] = motor_pid[2].Target;
        wireless_TX_data[10] = motor_pid[2].Out;
        wireless_TX_data[11] = motor_pid[2].Error1;

        wireless_TX_data[12] = motor_pid[3].Actual;
        wireless_TX_data[13] = motor_pid[3].Target;
        wireless_TX_data[14] = motor_pid[3].Out;
        wireless_TX_data[15] = motor_pid[3].Error1;

        wireless_uart_send_buffer((uint8 *)wireless_TX_data, 16*4); 
    }
    else
    {
        wireless_TX_data[0] = motor_pid[motor].Actual;
        wireless_TX_data[1] = motor_pid[motor].Target;
        wireless_TX_data[2] = motor_pid[motor].Out;
        wireless_TX_data[3] = motor_pid[motor].Error1;
        wireless_uart_send_buffer((uint8 *)wireless_TX_data, 4*4); // 一个浮点
    }
    wireless_uart_send_buffer(tail, 4);
}

int32 vofa_Rx(void)
{
    data_len = wireless_uart_read_buffer(data_buffer, 32);   
    if (data_len != 0)
    {
        // 直接转换接收到的字符串为整数
        int int_value = 0;
        
        // 遍历接收缓冲区，将数字字符转换为整数
        for(uint8_t i = 0; i < data_len; i++)
        {
            if(data_buffer[i] >= '0' && data_buffer[i] <= '9')
            {
                int_value = int_value * 10 + (data_buffer[i] - '0');
            }
        } 
        return int_value;   

    }
    return 100000;
}
