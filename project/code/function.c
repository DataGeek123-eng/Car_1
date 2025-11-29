#include "function.h"


float EncoderData0[5],EncoderData1[5],EncoderData2[5],EncoderData3[5];//每个编码器的值

//绝对值函数
float myabs(float a)
{
    float temp;
    if (a < 0)
        temp = -a;
    else
        temp =  a;
    return temp;
}




/**************************************************************************
函数功能：均值滤波
入口参数：现有数据
EncoderData是每个编码器单独存储的值
**************************************************************************/
uint8 i_value=5;
float  RecurrenceFilter(float DATA,float *EncoderData)
{
    uint8 i ;
    float sum = 0;

    for (i = 1; i < i_value; i++)
    {
        EncoderData[i - 1] = EncoderData[i];
    }
    EncoderData[i_value - 1] = DATA;
    sum = 0;
    //按照权重相加，可以去掉突变点。
    sum = EncoderData[0] * 0.05 + EncoderData[1] * 0.1 + EncoderData[2] * 0.15 + EncoderData[3] * 0.3 + EncoderData[4] * 0.4;

    return sum;
}


/**************************************************************************
函数功能：限幅函数
入口参数：幅值
**************************************************************************/
float target_limit_float(float insert, float low, float high)
{
    if (insert < low)
        return low;
    else if (insert > high)
        return high;
    else
        return insert;
}

uint8 i_va=5;
float  Recurrence(float DATA,float *error)
{
    uint8 i ;
    float sum = 0;

    for (i = 1; i < i_va; i++)
    {
       error[i - 1] = error[i];
    }
    error[i_value - 1] = DATA;
    sum = 0;
    //按照权重相加，可以去掉突变点。
    sum =error[0] * 0.2 +error[1] *0.2 +error[2] *0.2 + error[3] *0.2+ error[4] *0.2;

    return sum;
}

