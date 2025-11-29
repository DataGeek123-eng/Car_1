#include "vofa.h"

//发送
uint8 tail[4] = {0x00, 0x00, 0x80, 0x7f}; // vofa协议帧尾
float wireless_TX_data[COUNT_TX];//蓝牙串口发送数据数组COUNT_TX在vofa.h

void vofa_init(void)
{
   wireless_uart_init();
}

void vofa_tx(void)
{
    wireless_uart_send_buffer((uint8 *)wireless_TX_data, 4*4); // 一个浮点
    wireless_uart_send_buffer(tail, 4);
}

