#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "PORT_interface.h"
#include "CLCD_interface.h"
#include "KPD_interface.h"
#include "KPD_cfg.h"
#include "s_w_priv.h"
#include "s_w_interface.h"
#include <util/delay.h>

	_sTime_t Local_sTime[8] = {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}};




void main(void){

	PORT_voidInit();
	CLCD_voidInit();

	uint8 Local_u8PatternArrow[8] = {0b00000000,0b00000100,0b00001110,0b00010101,0b00000100,0b00000100, 0b00000100,0};
	uint8 Local_u8PatternErase[8] = {0,0,0,0,0,0, 0,0};

	uint8 Local_u8InputCounter = 0;
	uint8 Local_u8PressedVal;

	CLCD_voidGoToXY(0,0);
	CLCD_u8SendNumber(Local_sTime[0].time);
	CLCD_voidGoToXY(1,0);
	CLCD_u8SendNumber(Local_sTime[1].time);
	CLCD_voidGoToXY(2,0);
	CLCD_u8SendString(":");
	CLCD_voidGoToXY(3,0);
	CLCD_u8SendNumber(Local_sTime[2].time);
	CLCD_voidGoToXY(4,0);
	CLCD_u8SendNumber(Local_sTime[3].time);
	CLCD_voidGoToXY(5,0);
	CLCD_u8SendString(":");
	CLCD_voidGoToXY(6,0);
	CLCD_u8SendNumber(Local_sTime[4].time);
	CLCD_voidGoToXY(7,0);
	CLCD_u8SendNumber(Local_sTime[5].time);
	CLCD_u8SendSpecialCharacter(0,Local_u8PatternArrow,0,1);



	while(1){


		for(Local_u8InputCounter = 0; Local_u8InputCounter < MAX_ARR;Local_u8InputCounter++){

			if(Local_u8InputCounter == 2 || Local_u8InputCounter == 5 ){
				continue;
			}

			CLCD_u8SendSpecialCharacter(Local_u8InputCounter,Local_u8PatternArrow,Local_u8InputCounter,1);

			while(1){
				do{

					Local_u8PressedVal = KPD_u8GetPressedKey();


				}while(Local_u8PressedVal == KPD_u8NO_PRESSED_KEY_VAL);


				if(Local_u8PressedVal <= 9 ){

					CLCD_voidGoToXY(Local_u8InputCounter,0);
					Local_sTime[Local_u8InputCounter].time = Local_u8PressedVal;
					CLCD_u8SendNumber(Local_sTime[Local_u8InputCounter].time);

				}else{
					CLCD_u8SendSpecialCharacter(Local_u8InputCounter,Local_u8PatternErase,Local_u8InputCounter,1);

					break;
				}
			}
		}


		while(1){

			updateTimeInSeconds() ;
			updateTimeInMinutes();
			updateTimeInHours();

			if(Local_sTime[4].time == 0 && Local_sTime[3].time == 0 && Local_sTime[6].time == 0 && Local_sTime[7].time == 0 && Local_sTime[1].time == 0 && Local_sTime[0].time == 0){

				break;
			}


		}
		if(Local_sTime[4].time == 0 && Local_sTime[3].time == 0 && Local_sTime[6].time == 0 && Local_sTime[7].time == 0 && Local_sTime[1].time == 0 && Local_sTime[0].time == 0){
			CLCD_voidSendCmd(CLCD_u8CLEAR_LCD);
			CLCD_voidGoToXY(2,0);
			CLCD_u8SendString("Time Finished");
			DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN2, DIO_u8PIN_HIGH);
			break;
		}
	}

}
