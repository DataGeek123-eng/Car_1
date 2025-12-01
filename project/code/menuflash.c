#include "menuflash.h"
#include "PID.h"
#include "zf_common_headfile.h"

void menu_flash_read()
{
	 if(flash_check(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX))                      // 判断是否有数据
    {
        flash_read_page_to_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);  
        motor_pid[0].Kp = Kp_store;
        motor_pid[0].Ki = Ki_store;
        motor_pid[0].Kd = Kd_store;
    }
}

void menu_flash_write()
{
	flash_buffer_clear();
	Kp_store = motor_pid[0].Kp;
	Ki_store = motor_pid[0].Ki;
	Kd_store = motor_pid[0].Kd;
	flash_write_page_from_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);
}
