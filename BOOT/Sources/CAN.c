

/**********************************************************************************************************************
* MODULES USED 
**********************************************************************************************************************/
#include "CAN.h"
#include "CANcomm.h"
#include "uds_service.h"


/**********************************************************************************************************************
* DEFINITIONS AND MACROS
**********************************************************************************************************************/


/**********************************************************************************************************************
* TYPEDEFS AND STRUCTURES
**********************************************************************************************************************/


/**********************************************************************************************************************
* PROTOTYPES OF FUNCTIONS
**********************************************************************************************************************/
void ZTai_UDS_Send(uint8_t* data, uint8_t Length);
uint32_t GetTime(void);

/**********************************************************************************************************************
* DECLARATIONS OF VARIABLES
**********************************************************************************************************************/
uint32_t Time = 0U;


/*--------------------------------------------------------------------------*/
/* Function  | Initialize UDS                                               */
/* Name      | Init_UDS                                                     */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void Init_UDS(void)
{
    uds_init();
}


/*--------------------------------------------------------------------------*/
/* Function  | TASK of UDS                                                  */
/* Name      | TASK_UDS                                                     */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void TASK_UDS(void)
{
	Time++;
    uds_main();
}


/*--------------------------------------------------------------------------*/
/* Function  | User module of CAN Send                                      */
/* Name      | ZTai_UDS_Send                                                */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void ZTai_UDS_Send(uint8_t* data, uint8_t Length)
{
    (void)CANComm_SendFrameExt(PhysResp_ID | CAN_EXTENDED_FRAME_ID, 0, Length, data);
}


/*--------------------------------------------------------------------------*/
/* Function  | Called by CAN RX interrupt                                   */
/* Name      | RXMESSAGE                                                    */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Nothing                                                      */
/*--------------------------------------------------------------------------*/
void RXMESSAGE(void)
{
    uint32_t ID;
    uint8_t dummy1, dummy2;
    uint8_t Length;
    uint8_t data[8];

	CANComm_ReadFrame(&ID, &dummy1, &dummy2, &Length, data);
	
	if (ID == FuncReq_ID)
	{
		uds_get_frame(1, data, Length);
	}

    if (ID == PhysReq_ID)
	{
		uds_get_frame(0, data, Length);
	}
}


/*--------------------------------------------------------------------------*/
/* Function  | Return Time tick (ms)                                        */
/* Name      | GetTime                                                      */
/*--------------------------------------------------------------------------*/
/* Parameter | Nothing                                                      */
/* Return    | Time tick                                                    */
/*--------------------------------------------------------------------------*/
uint32_t GetTime(void)
{
	return Time;
}
