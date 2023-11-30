#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "PORT_interface.h"
#include "CLCD_interface.h"
#include "KPD_interface.h"
#include "KPD_cfg.h"
#include "s_w_priv.h"
#include "s_w_interface.h"
#include <util/delay.h>



extern _sTime_t Local_sTime[8];
void updateTimeInSeconds()
{

	while(1){

		if(Local_sTime[7].time == 0 && Local_sTime[6].time > 0){
			Local_sTime[6].time--;
			Local_sTime[7].time = 9;
			CLCD_voidGoToXY(6,0);
			CLCD_u8SendNumber(Local_sTime[6].time);
			CLCD_voidGoToXY(7,0);
			CLCD_u8SendNumber(Local_sTime[7].time);
			_delay_ms(1000);

		}else if(Local_sTime[7].time > 0){


			(Local_sTime[7].time)--;
			CLCD_voidGoToXY(7,0);
			CLCD_u8SendNumber(Local_sTime[7].time);
			_delay_ms(1000);
		}else{
			break;
		}
	}

}


void updateTimeInMinutes()
{
	if (Local_sTime[4].time > 0 || Local_sTime[3].time > 0) {
		if (Local_sTime[4].time == 0 && Local_sTime[3].time > 0) {
			Local_sTime[3].time--;
			Local_sTime[4].time = 9;
			CLCD_voidGoToXY(4, 0);
			CLCD_u8SendNumber(Local_sTime[4].time);
			CLCD_voidGoToXY(3, 0);
			CLCD_u8SendNumber(Local_sTime[3].time);

			Local_sTime[6].time = 6;
			Local_sTime[7].time = 0;
			CLCD_voidGoToXY(6, 0);
			CLCD_u8SendNumber(Local_sTime[6].time);
			CLCD_voidGoToXY(7, 0);
			CLCD_u8SendNumber(Local_sTime[7].time);
		} else if (Local_sTime[4].time > 0) {
			(Local_sTime[4].time)--;
			CLCD_voidGoToXY(4, 0);
			CLCD_u8SendNumber(Local_sTime[4].time);
			Local_sTime[6].time = 6;
			Local_sTime[7].time = 0;
			CLCD_voidGoToXY(6, 0);
			CLCD_u8SendNumber(Local_sTime[6].time);
			CLCD_voidGoToXY(7, 0);
			CLCD_u8SendNumber(Local_sTime[7].time);
		}
	}
}



void updateTimeInHours()
{
	if (Local_sTime[4].time == 0 && Local_sTime[3].time == 0 && Local_sTime[6].time == 0 && Local_sTime[7].time == 0) {
		if (Local_sTime[1].time == 0 && Local_sTime[0].time > 0) {
			Local_sTime[0].time--;
			Local_sTime[1].time = 9;
			CLCD_voidGoToXY(0, 0);
			CLCD_u8SendNumber(Local_sTime[0].time);
			CLCD_voidGoToXY(1, 0);
			CLCD_u8SendNumber(Local_sTime[1].time);

			Local_sTime[3].time = 6;
			Local_sTime[4].time = 0;
			CLCD_voidGoToXY(4, 0);
			CLCD_u8SendNumber(Local_sTime[4].time);
			CLCD_voidGoToXY(3, 0);
			CLCD_u8SendNumber(Local_sTime[3].time);
		} else if (Local_sTime[1].time > 0) {
			(Local_sTime[1].time)--;
			CLCD_voidGoToXY(1, 0);
			CLCD_u8SendNumber(Local_sTime[1].time);
			Local_sTime[3].time = 6;
			Local_sTime[4].time = 0;
			CLCD_voidGoToXY(4, 0);
			CLCD_u8SendNumber(Local_sTime[4].time);
			CLCD_voidGoToXY(3, 0);
			CLCD_u8SendNumber(Local_sTime[3].time);
		}
	}

}

