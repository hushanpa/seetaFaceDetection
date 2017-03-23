/******************************************************************************

  Copyright (C), 2001-2015, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_ive_lpr.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software (IVE) group
  Created       : 2014/11/15
  Description   : 
  History       :
  1.Date        : 2014/11/15
    Author      : 
    Modification: Created file

  2.Date        : 2014/11/15
    Author      : 
    Modification: move lpr info from hi_ive.h to this file
******************************************************************************/

#ifndef _HI_IVE_LPR_H_
#define _HI_IVE_LPR_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#include "hi_comm_ive.h"
//if sdk environment,include "hi_common.h"
//#include "hi_common.h"

#define IVE_MAX_CHAR_POS_NUM     20
#define IVE_PLATE_CHAR_MAX_COUNT 8

/*
*Bernsen mode enum
*/
typedef enum hiIVE_BERNSEN_MODE_E
{
    IVE_BERNSEN_MODE_NORMAL =  0x0, 
    IVE_BERNSEN_MODE_THRESH =  0x1, 

    IVE_BERNSEN_MODE_BUTT
}IVE_BERNSEN_MODE_E;

/*
*Bernsen control struct
*/
typedef struct hiIVE_BERNSEN_CTRL_S
{	
    IVE_BERNSEN_MODE_E enMode;
    HI_U8 u8WinSize;  /*3 or 5*/
    HI_U8 u8Thr;  
}IVE_BERNSEN_CTRL_S;

/*
* Radon ctrl param
*/
typedef struct hiIVE_RADON_CTRL_S
{
	HI_U8 u8Theta;			/* Radon transform angle(range: 1 to 16, default: 8)*/
	HI_U8 u8Thr;			/* Gray threshold(range:1 to 255, default :80) */
}IVE_RADON_CTRL_S;

typedef struct hiIVE_LINE_FILTER_HOR_CTRL_S
{
	HI_U8 u8GapMinLen;			/*Gap min size(range:1~20,default:10) */
	HI_U8 u8DensityThr;			/*Density threshold(range:1~50,default:20) */
	HI_U8 u8HorThr;				/*Horizontal size threshold(range:1~50,default:20)*/
}IVE_LINE_FILTER_HOR_CTRL_S;

/*
* AdpThresh ctrl param
*/
typedef struct hiIVE_ADP_THRESH_CTRL_S
{
	HI_U8  u8RateThr;			/*Adaptive threshold ratio(range: 12~40,default:30)*/
}IVE_ADP_THRESH_CTRL_S;

/*
* NoiseRemoveHor ctrl param
*/
typedef struct hiIVE_NOISE_REMOVE_HOR_CTRL_S
{
	HI_U8 u8HorThr;						/*Horizontal threshold(range:1~50,default£º25) */
}IVE_NOISE_REMOVE_HOR_CTRL_S;

/*
* Plate type info
*/
typedef struct hiIVE_PLATE_INFO_S
{
	HI_U8		u8CharNum;				                        /*Plate characters number(range:3~7)*/
	HI_U8		u8BigGapIdx;			                        /*Plate big gap position (range:0~u8CharNum-1)*/
	HI_U4Q12	u4q12GapRate;			                        /*Gap distance ratio (range:0~4096)*/
	HI_U4Q12	u4q12BigGapRate;		                        /*Big gap distance ratio(range:0~4096) */
	HI_U8Q8		u8q8TrustyFactor;		                        /*Trusty factor weight (range:0~8192)*/
	HI_U8Q8	    u8q8BlockWeight[IVE_PLATE_CHAR_MAX_COUNT];	    /*Block weight (range:0~2048), can't be all of 0*/
	HI_U8Q8		u8q8GapWeight[IVE_PLATE_CHAR_MAX_COUNT];		/*Character weight (range:0~2048)*/
	HI_U8Q8		u8q8AveRate[IVE_PLATE_CHAR_MAX_COUNT];		    /*Plate average weight(range:0~2048) */
	HI_U8       au8Reserved[IVE_PLATE_CHAR_MAX_COUNT];		    /*Reserved */
}IVE_PLATE_INFO_S;

/*
* PlateCharPos output
*/
typedef struct hiIVE_PLATE_CHAR_POS_OUT_S
{
	HI_U16 u16CharPos[IVE_MAX_CHAR_POS_NUM];    /*Character block position*/
	HI_S32 s32CharDis;							/*Character distance*/
	HI_S16 s16PlateTrusty;						/*Plate trusty*/
	HI_U8  u8PlateType;							/*Plate type */
}IVE_PLATE_CHAR_POS_OUT_S;

/*
* PlayteCharPos ctrl param
*/
typedef struct hiIVE_PLATE_CHAR_POS_CTRL_S
{
	IVE_RECT_U16_S stRect;						/*Character block position*/
	HI_U8  u8PlateTypeNum;						/*Plate type number(range:1~8)*/
}IVE_PLATE_CHAR_POS_CTRL_S;

/*
* LPCL back_plate
*/
typedef enum  hiIVE_LPCL_BACK_PLATE_MODE_E
{
	IVE_LPCL_BACK_PLATE_MODE_DISABLE = 0x0, /*Plate is in front of the car*/
	IVE_LPCL_BACK_PLATE_MODE_ENABLE  = 0x1, /*Plate is in back of the car*/
	IVE_LPCL_BACK_PLATE_MODE_BUTT
} IVE_LPCL_BACK_PLATE_MODE_E;

/*
* LPCL big_plate
*/
typedef enum  hiIVE_LPCL_BIG_PLATE_MODE_E
{
	IVE_LPCL_BIG_PLATE_MODE_DISABLE = 0x0, /*Small Plate, generally with plate width smaller than 120 pixel*/
	IVE_LPCL_BIG_PLATE_MODE_ENABLE  = 0x1, /*Big plate, generally with plate with bigger than 120 pixel*/
	IVE_LPCL_BIG_PLATE_MODE_BUTT
} IVE_LPCL_BIG_PLATE_MODE_E;

/*
* LPCL motor_plate
*/
typedef enum  hiIVE_LPCL_MOTOR_PLATE_MODE_E
{
	IVE_LPCL_MOTOR_PLATE_MODE_DISABLE = 0x0, /*No recognize motor plate*/
	IVE_LPCL_MOTOR_PLATE_MODE_ENABLE  = 0x1, /*Recognize motor plate*/
	IVE_LPCL_MOTOR_PLATE_MODE_BUTT
} IVE_LPCL_MOTOR_PLATE_MODE_E;

/*
* LPCL infrared_plate
*/
typedef enum  hiIVE_LPCL_INFRARED_PLATE_MODE_E
{
	IVE_LPCL_INFRARED_PLATE_MODE_DISABLE = 0x0, /*Plate image is not infrared image*/
	IVE_LPCL_INFRARED_PLATE_MODE_ENABLE  = 0x1, /*Plate image is infrared image*/
	IVE_LPCL_INFRARED_PLATE_MODE_BUTT
} IVE_LPCL_INFRARED_PLATE_MODE_E;

/*
*IPCL plate recognize configuration
*/
typedef struct hiIVE_LPCL_PLATE_MODE_S
{
	IVE_LPCL_BACK_PLATE_MODE_E     enBackPlateMode;     /*Configuration of plate position*/
	IVE_LPCL_BIG_PLATE_MODE_E      enBigPlateMode;      /*Configuration of plate size*/
	IVE_LPCL_MOTOR_PLATE_MODE_E    enMotorPlateMode;    /*Configuration of whether recognize motor plate*/
	IVE_LPCL_INFRARED_PLATE_MODE_E enInfraredPlateMode; /*Configuration of whether image is infrared*/
}IVE_LPCL_PLATE_MODE_S;

/*
* LPCL_GatSmth ctrl struct
*/
typedef struct hiIVE_LPCL_GATSMTH_CTRL_S
{
	IVE_LPCL_PLATE_MODE_S	astPlateMode[8];		/*Plate recognize configuration of every image*/
	HI_U8					u8ImgNum;		        /*The actual number of valid input images*/
	HI_U8					u8Reserved[3];
}IVE_LPCL_GATSMTH_CTRL_S;

/*
* LPCL experience threshold
*/
typedef struct hiIVE_LPCL_THR_S
{
	HI_U8   u8HopThr;           /*Gray difference threshold (range:1~255; default: 6)*/
	HI_U8   u8DistThr;          /*Two feature points distance threshold (range:1~255; default: 4)*/
	HI_U8   u8RangeThr;         /*Three feature points distance threshold (range:1~255; default: 16)*/
	HI_U8   u8WaveWidthThr;     /*Wave pixel width threshold (range:1~255; default: 40)*/
	HI_U8   u8WaveNodeThr;      /*Wave node threshold (range:2~255; default: 5)*/
	HI_U8   u8DelHopThr;        /*Wave feature points delete thresh (range:1~255; default: 5)*/
	HI_U8   u8DelLenThr;        /*Wave length delete thresh (range:1~255; default: 20)*/
	HI_U8   u8Reserved;
}IVE_LPCL_THR_S;

/*
* LPCL ctrl
*/
typedef struct hiIVE_LPCL_CTRL_S
{
	IVE_LPCL_PLATE_MODE_S   stPlateMode;   /*License plate recognition mode*/
	IVE_LPCL_THR_S			stCoareLocThr; /*Experience threshold for plate location*/
} IVE_LPCL_CTRL_S;

/*
* LPCL strip unit struct
*/
typedef struct hiIVE_LPCL_STRIP_S
{
	HI_U16 u16OrgStartCol; /*Plate strip feature's unadjusted left coordinate*/
	HI_U16 u16OrgEndCol;   /*Plate strip feature's unadjusted right coordinate*/
	HI_U16 u16StartCol;    /*Plate strip feature left coordinate*/
	HI_U16 u16EndCol;      /*Plate strip feature right coordinate*/
	HI_U16 u16StripRow;    /*Plate strip feature row index*/
} IVE_LPCL_STRIP_S;

/*
* LPCL strip feature
*/
typedef struct hiIVE_LPCL_STRIP_FEATRUE_S
{
	HI_U32			  u32StripNum;        /*Number of output strip feature (range: 0~2048)*/
	IVE_LPCL_STRIP_S  astStripList[2048]; /*Plate strip feature array*/
}IVE_LPCL_STRIP_FEATURE_S;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif


