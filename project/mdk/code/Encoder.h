#ifndef __ENCODER_H_
#define __ENCODER_H_
#include "zf_common_headfile.h"


extern  int16 encoder_data[4];


#define PIT_CH                          (PIT_CH0 )                              // 使用的周期中断编号 如果修改 需要同步对应修改周期中断编号与 isr.c 中的调用
#define PIT_PRIORITY                    (PIT_IRQn)                              // 对应周期中断的中断编号 
        
#define ENCODER_DIR_1		                (QTIMER1_ENCODER1)                     // 带方向编码器对应使用的编码器接口 这里使用QTIMER1的ENCODER2
#define ENCODER_DIR_PULSE_1               (QTIMER1_ENCODER1_CH1_C0)              // PULSE 对应的引脚
#define ENCODER_DIR_DIR_1                 (QTIMER1_ENCODER1_CH2_C1)             // DIR 对应的引脚

#define ENCODER_DIR_2		                (QTIMER2_ENCODER1)                     
#define ENCODER_DIR_PULSE_2               (QTIMER2_ENCODER1_CH1_C3)              
#define ENCODER_DIR_DIR_2                 (QTIMER2_ENCODER1_CH2_C25)             

#define ENCODER_DIR_3		                (QTIMER3_ENCODER1)                     
#define ENCODER_DIR_PULSE_3               (QTIMER3_ENCODER1_CH1_B16)              
#define ENCODER_DIR_DIR_3                 (QTIMER3_ENCODER1_CH2_B17)             

#define ENCODER_DIR_4		                (QTIMER4_ENCODER1)                     
#define ENCODER_DIR_PULSE_4               (QTIMER4_ENCODER1_CH1_C9)             
#define ENCODER_DIR_DIR_4                 (QTIMER4_ENCODER1_CH2_C10)

void Encoder_Init();



#endif


