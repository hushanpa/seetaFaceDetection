#include "hi_ive/Integ.h"
#include "hi_ive/sample_assist.h"
#include "hi_ive/sample_file.h"
#include "hi_ive/sample_define.h"
#include "hi_ive/mpi_ive.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

HI_VOID Integ(IVE_INTEG_OUT_CTRL_E enOutCtrl,int* imageData, int width, int height)
{
	IVE_SRC_IMAGE_S stSrc;
	IVE_DST_IMAGE_S stDst;
	IVE_INTEG_CTRL_S stCtrl;
	HI_S32 s32Result ;
	HI_U16 u16Width;
	HI_U16 u16Height;
	HI_CHAR fileName[HI_MAX_FILE_LEN];
	FILE *fp;
	IVE_HANDLE handle;
	//HI_DOUBLE dTime;
	HI_CHAR info[HI_INFO_LEN];
	memset(&stSrc,0,sizeof(IVE_SRC_IMAGE_S));
	memset(&stDst,0,sizeof(IVE_DST_IMAGE_S));
	memset(&stCtrl,0,sizeof(IVE_INTEG_CTRL_S));

	fp = NULL;
	u16Width = width;
	u16Height = height;

	s32Result = HI_CreateIveImage(&stSrc,IVE_IMAGE_TYPE_U8C1,u16Width,u16Height);
	HI_CHECK_ET_GOTO(s32Result,HI_FAILURE,FAILURE);
	switch (enOutCtrl)
	{
	case  IVE_INTEG_OUT_CTRL_COMBINE:
		strcpy_s(info,HI_INFO_LEN,"Histogram combine time =");
		s32Result = HI_CreateIveImage(&stDst,IVE_IMAGE_TYPE_U64C1,u16Width,u16Height);
		break;
	case IVE_INTEG_OUT_CTRL_SUM:
		strcpy_s(info,HI_INFO_LEN,"Histogram sum time =");
		s32Result = HI_CreateIveImage(&stDst,IVE_IMAGE_TYPE_U32C1,u16Width,u16Height);
		break;
	case IVE_INTEG_OUT_CTRL_SQSUM:
		strcpy_s(info,HI_INFO_LEN,"Histogram sqsum time =");
		s32Result = HI_CreateIveImage(&stDst,IVE_IMAGE_TYPE_U64C1,u16Width,u16Height);
		break;
	default:
		s32Result = HI_FAILURE;
		break;
	}
	
	HI_CHECK_ET_GOTO(s32Result,HI_FAILURE,FAILURE);

	stCtrl.enOutCtrl = enOutCtrl;
	for (int i = 0; i < height; i++)
	{

		for (int j = 0; j < width; j++)
		{
			*(stSrc.pu8VirAddr[0] + i*stSrc.u16Stride[0] + j) = (HI_U8)(*(imageData + i*width+j));
		}
	}

	
	//dTime = (HI_DOUBLE)HI_GetTickCount();
	s32Result = HI_MPI_IVE_Integ(&handle,&stSrc,&stDst,&stCtrl,HI_FALSE);
	HI_CHECK_ET_GOTO(s32Result,HI_FAILURE,FAILURE);		
	//dTime = (HI_DOUBLE)HI_GetTickCount() - dTime;


	//printf("%s %g ms\n",info, dTime/((HI_DOUBLE)HI_GetTickFrequency()*1000.));

	switch (enOutCtrl)
	{
	case IVE_INTEG_OUT_CTRL_SUM:
		for (int i = 0; i < height; i++)
		{

			for (int j = 0; j < width; j++)
			{
				*(imageData + i*width + j) = *((HI_U32*)stDst.pu8VirAddr[0] + i*stDst.u16Stride[0] + j);

			}
		}
		break;
	case IVE_INTEG_OUT_CTRL_SQSUM:
		for (int i = 0; i < height; i++)
		{

			for (int j = 0; j < width; j++)
			{
				*((unsigned int*)imageData + i*width + j) = (unsigned int)*((HI_U64*)stDst.pu8VirAddr[0] + i*stDst.u16Stride[0] + j);

			}
		}
		break;
	default:
		s32Result = HI_FAILURE;
		break;
	}
	

FAILURE:

	HI_FCLOSE(fp);
	HI_DestroyIveImage(&stSrc);
	HI_DestroyIveImage(&stDst);
	
}
/*
HI_VOID IntegSampleCombine(HI_VOID)
{
	Integ(IVE_INTEG_OUT_CTRL_COMBINE);
}
*/
HI_VOID IntegSampleSum(int* imageData, int width, int height)
{
	Integ(IVE_INTEG_OUT_CTRL_SUM, imageData, width, height);
}
HI_VOID IntegSampleSqsum(int* imageData, int width, int height)
{
	Integ(IVE_INTEG_OUT_CTRL_SQSUM, imageData, width, height);
}