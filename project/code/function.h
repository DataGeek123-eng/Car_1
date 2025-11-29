#ifndef __FUNCTION_H
#define __FUNCTION_H
#include "zf_common_headfile.h"

extern float EncoderData0[5],EncoderData1[5],EncoderData2[5],EncoderData3[5];
float myabs(float a);
float  RecurrenceFilter(float DATA,float *EncoderData);
float target_limit_float(float insert, float low, float high);

#endif