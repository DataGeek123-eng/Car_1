#ifndef VOFA_H
#define VOFA_H	
#include "zf_common_headfile.h"

#define COUNT_TX 32//可装载30个float数据
extern float wireless_TX_data[COUNT_TX];//蓝牙串口发送数据数组COUNT_TX在vofa.h
void vofa_init(void);
void vofa_tx(uint8 motor);
int32 vofa_Rx(void);

#endif
