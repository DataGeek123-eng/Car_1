#ifndef __MENUFLASH_H
#define __MENUFLASH_H
#include <stdint.h> 
#define FLASH_SECTION_INDEX       (127)                                         // 存储数据用的扇区 倒数第一个扇区
#define FLASH_PAGE_INDEX          (FLASH_PAGE_3)     
#define Kp_store                  flash_union_buffer[0].float_type
#define Ki_store                  flash_union_buffer[1].float_type
#define Kd_store                  flash_union_buffer[2].float_type


void menu_flash_read();
void menu_flash_write();


extern uint32_t read_buf[5];
extern uint32_t write_buf[5];
#endif
