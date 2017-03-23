/******************************************************************************

  Copyright (C), 2001-2015, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : mpi_ive_lpr.h
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
    Modification: move lpr function from mpi_ive.h to this file
******************************************************************************/

#ifndef _HI_MPI_IVE_LPR_H_
#define _HI_MPI_IVE_LPR_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */
#include "hi_ive_lpr.h"

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_Bernsen
*   Description  : Image binaryzation using Bernsen method or its extensional method.
*   Parameters   : IVE_HANDLE            *pIveHandle        Returned handle ID of a task
*                  IVE_SRC_IMAGE_S       *pstSrc            Input source. Only the U8C1 input format is supported.
*                  IVE_DST_IMAGE_S       *pstDst            Output result 
*				   IVE_BERNSEN_CTRL_S    *pstBernsenCtrl    Control parameter
*                  HI_BOOL                bInstant          For details, see HI_MPI_IVE_DMA.
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 64x64 pixels to 1920x1024 pixels.
*                  The physical addresses of the input data and output data must be 16-byte-aligned.
*                  The stride must be 16-pixel-aligned.
*   History:
* 
*       1.  Date         : 2013-08-15
*           Author       : 
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_Bernsen(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc,
	IVE_DST_IMAGE_S *pstDst, IVE_BERNSEN_CTRL_S *pstBernsenCtrl, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_Radon
*   Description  : Plate horizontal tilt angle estimation using radon transform.
*   Parameters   : IVE_HANDLE			*pIveHandle       Returned handle ID of a task
*				   IVE_SRC_IMAGE_S		*pstSrc			  Input gray image
*				   IVE_DST_IMAGE_S		*pstDst			  Angle project image
*                  IVE_RADON_CTRL_S     *pstRadonCtrl	  Radon tranform parameters
*                  HI_BOOL				 bInstant         For details, see HI_MPI_IVE_DMA.
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : 
*   History:
* 
*       1.  Date         : 2013-10-29
*           Author       :  
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_Radon(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc, IVE_DST_IMAGE_S *pstDst, 
	IVE_RADON_CTRL_S *pstRadonCtrl, HI_BOOL bInstant);
/*****************************************************************************
*   Prototype    : HI_MPI_IVE_LineFilterHor
*   Description  : Horizontal density filter task for binary images 
*   Parameters   : IVE_HANDLE                   *pIveHandle            Returned handle ID of a task
*				   IVE_IMAGE_S                  *pstSrcDst		           Input Binary image
*				   IVE_LINE_FILTER_HOR_CTRL_S   *pstLineFltHorCtrl     Horizontal Line Filter parameters
*                  HI_BOOL                       bInstant              For details, see HI_MPI_IVE_DMA.
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : 
*   History:
* 
*       1.  Date         : 2013-10-29
*           Author       : 
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_LineFilterHor(IVE_HANDLE *pIveHandle, IVE_IMAGE_S *pstSrcDst, 
	IVE_LINE_FILTER_HOR_CTRL_S *pstLineFltHorCtrl, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_AdpThresh
*   Description  : Adaptive thresh
*   Parameters   : IVE_HANDLE			      *pIveHandle         Returned handle ID of a task
*				   IVE_SRC_IMAGE_S		      *pstSrc			  Gray image
*				   IVE_SRC_IMAGE_S		      *pstInteg		      Integer image
*				   IVE_DST_IMAGE_S		      *pstDst			  Binary image
*				   IVE_ADP_THRESH_CTRL_S      *pstAdpThrCtrl      Adaptive threshold parameters
*                  HI_BOOL				       bInstant           For details, see HI_MPI_IVE_DMA.
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : 
*   History:
* 
*       1.  Date         : 2013-10-29
*           Author       : 
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_AdpThresh(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstSrc, IVE_SRC_IMAGE_S *pstInteg,
	IVE_DST_IMAGE_S *pstDst, IVE_ADP_THRESH_CTRL_S *pstAdpThrCtrl, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_NoiseRemoveHor
*   Description  : Horizontal noise removal task for binary images 
*   Parameters   : IVE_HANDLE                 *pIveHandle              Returned handle ID of a task
*				   IVE_IMAGE_S	              *pstSrcDst               Binary image
*				   IVE_NOISE_REMOVE_CTRL_S    *pstNoiseRemoveHorCtrl   Remove image noise parameters
*                  HI_BOOL                     bInstant                For details, see HI_MPI_IVE_DMA.
*   Return Value : HI_SUCCESS: Success; Error codes: Failure.
*   Spec         : 
*   History:
* 
*       1.  Date         : 2013-10-29
*           Author       : 
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_NoiseRemoveHor(IVE_HANDLE *pIveHandle, IVE_IMAGE_S *pstSrcDst,
	IVE_NOISE_REMOVE_HOR_CTRL_S *pstNoiseRemoveHorCtrl, HI_BOOL bInstant);
/*****************************************************************************
*   Prototype    : HI_MPI_IVE_PlateCharPos
*   Description  : License plate character split (character location) task. The license plate 
*                  characters with only one large gap can be split 
*   Parameters   : IVE_HANDLE			       *pIveHandle              Returned handle ID of a task
*				   IVE_SRC_IMAGE_S		       *pstEnegyHist	        Energy Hist image														
*				   IVE_SRC_MEM_INFO_S	       *pstPlateInfo	        Plate model information
*				   IVE_DST_MEM_INFO_S          *pstCharPos              Output of characters information
*                  IVE_PLATE_CHAR_POS_CTRL_S   *pstPlateCharPosCtrl     Plate char position parameters
*                  HI_BOOL				        bInstant                For details, see HI_MPI_IVE_DMA.
*   Return Value : HI_SUCCESS: Success; Error codes: Failure.
*   Spec         : 
*   History:
* 
*       1.  Date         : 2013-10-29
*           Author       : 
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_PlateCharPos(IVE_HANDLE *pIveHandle, IVE_SRC_IMAGE_S *pstEnegyHist, IVE_SRC_MEM_INFO_S *pstPlateInfo,
	IVE_DST_MEM_INFO_S *pstCharPos, IVE_PLATE_CHAR_POS_CTRL_S *pstPlateCharPosCtrl, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_LPCL_GatSmth
*   Description  : Down sampled the input image and smooth the sampled data.
*                  1. Four times down sampling in vertical direction
*                  2. Smooth the sampled data in horizontal direction
*   Parameters   : IVE_SRC_IMAGE_S			astSrc				Input array of images, only U8C1 images are supported.
*				   IVE_DST_IMAGE_S	        astDst			    Output array of images, only U8C1 images are supported.
*				   IVE_CNN_CTRL_S          *pstGatSmthCtrl	    Control parameters
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : 
*   History:
* 
*       1.  Date         : 2015-05-28
*           Author       : 
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_LPCL_GatSmth(IVE_SRC_IMAGE_S astSrc[], IVE_DST_IMAGE_S astDst[], 
	IVE_LPCL_GATSMTH_CTRL_S *pstGatSmthCtrl);


/*****************************************************************************
*   Prototype    : HI_MPI_IVE_LPCL_GetWave
*   Description  : Get wave features and pixels' attribute for obtain plate strip feature.
*   Parameters   : IVE_HANDLE			    *pIveHandle     IveHandle of a called function 
*				   IVE_IMAGE_S			    *pstGatSmth	    Input U8C1 image(output of HI_MPI_IVE_LPCL_GatSmth)
*				   IVE_SRC_IMAGE_S			*pstMask		Input U8C1 binary image. Mask data of the ROI(area of interest)	
*				   IVE_DST_IMAGE_S			*pstPixFlag		HLS property of pixel 
*                  IVE_DST_MEM_INFO_S		*pstWaveHls		Output wave features and position of HLS points
*				   IVE_LPCL_CTRL_S			*pstLpclCtrl    Control parameters
*                  HI_BOOL				     bInstant       For details, see HI_MPI_IVE_DMA.
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The size of the input data ranges from 64x16 pixels to 2048x400 pixels.
*   History:
* 
*       1.  Date         : 2015-05-28
*           Author       : 
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_LPCL_GetWave(IVE_HANDLE *pIveHandle, IVE_IMAGE_S *pstGatSmth,
	IVE_SRC_IMAGE_S *pstMask, IVE_DST_IMAGE_S *pstPixFlag, IVE_DST_MEM_INFO_S *pstWaveHls,
	IVE_LPCL_CTRL_S *pstLpclCtrl, HI_BOOL bInstant);

/*****************************************************************************
*   Prototype    : HI_MPI_IVE_LPCL_GetStrip
*   Description  : Filter wave features and adjust the borders of remain wave to get strip feature
*   Parameters   : IVE_SRC_IMAGE_S		   *pstGatSmth        Input U8C1 image(output of HI_MPI_IVE_LPCL_GetWave)
*				   IVE_SRC_IMAGE_S	       *pstPixFlag        HLS property of pixel  
*				   IVE_SRC_MEM_INFO_S	   *pstWaveHls        Wave features and position of HLS points  
*				   IVE_DST_MEM_INFO_S	   *pstStripFeature   Output plate strip feaures (IVE_LPCL_STRIP_FEATURE_S)
*				   IVE_LPCL_CTRL_S         *pstLpclCtrl       Control parameters
*   Return Value : HI_SUCCESS: Success;Error codes: Failure.
*   Spec         : The max number of strip features is 2048.
*   History:
* 
*       1.  Date         : 2015-05-28
*           Author       : 
*           Modification : Created function
*
*****************************************************************************/
HI_S32 HI_MPI_IVE_LPCL_GetStrip(IVE_SRC_IMAGE_S *pstGatSmth, IVE_SRC_IMAGE_S *pstPixFlag,
	IVE_SRC_MEM_INFO_S *pstWaveHls, IVE_DST_MEM_INFO_S *pstStripFeature, IVE_LPCL_CTRL_S *pstLpclCtrl);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
