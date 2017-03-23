
#include "hi_ive\sample_assist.h"
#include "hi_ive\sample_define.h"
#include <stdlib.h>
#if defined WIN32 || defined _WIN32 || defined WINCE
#include <Windows.h>
#else
#include <time.h>
#endif

HI_U16 HI_CalcStride(HI_U16 u16Width, HI_U8 u8Align)
{
	HI_U16 u16stride = u16Width + (u8Align - u16Width%u8Align)%u8Align;
	return u16stride;
}
HI_S32 HI_CreateIveImage(IVE_IMAGE_S *pstImage,IVE_IMAGE_TYPE_E enType, HI_U16 u16Width, HI_U16 u16Height)
{
	HI_U16 u16Stride;	
	HI_S32 s32Succ;

	HI_CHECK_ET_NULL_RET(pstImage,HI_FAILURE);

	pstImage->enType = enType;
	pstImage->u16Width = u16Width;
	pstImage->u16Height = u16Height;

	u16Stride = HI_CalcStride(u16Width, HI_IVE2_STRIDE_ALIGN);
	s32Succ = HI_SUCCESS;

	switch(enType)
	{
	case IVE_IMAGE_TYPE_U8C1:
	case IVE_IMAGE_TYPE_S8C1:
		{
			pstImage->pu8VirAddr[0] = (HI_U8*)malloc(u16Stride * u16Height);
			HI_CHECK_ET_NULL_RET(pstImage->pu8VirAddr[0],HI_FAILURE);

			pstImage->u32PhyAddr[0] = (HI_U32)pstImage->pu8VirAddr[0];
			pstImage->u16Stride[0] = u16Stride;
		}
		break;
	case IVE_IMAGE_TYPE_YUV420SP: 
		{
			pstImage->pu8VirAddr[0] = (HI_U8*)malloc(u16Stride * u16Height * 3/2);	
			HI_CHECK_ET_NULL_RET(pstImage->pu8VirAddr[0],HI_FAILURE);

			pstImage->pu8VirAddr[1] = pstImage->pu8VirAddr[0] + u16Stride * u16Height;
			pstImage->u32PhyAddr[0] = (HI_U32)pstImage->pu8VirAddr[0];
			pstImage->u32PhyAddr[1] = (HI_U32)pstImage->pu8VirAddr[1];
			pstImage->u16Stride[0] = u16Stride;
			pstImage->u16Stride[1]  = pstImage->u16Stride[0];
		}
		break;
	case IVE_IMAGE_TYPE_YUV422SP:
		{
			pstImage->pu8VirAddr[0] = (HI_U8*)malloc(u16Stride * u16Height * 2);	
			HI_CHECK_ET_NULL_RET(pstImage->pu8VirAddr[0],HI_FAILURE);

			pstImage->pu8VirAddr[1] = pstImage->pu8VirAddr[0] + u16Stride * u16Height;
			pstImage->u32PhyAddr[0] = (HI_U32)pstImage->pu8VirAddr[0];
			pstImage->u32PhyAddr[1] = (HI_U32)pstImage->pu8VirAddr[1];
			pstImage->u16Stride[0] = u16Stride;
			pstImage->u16Stride[1]  = pstImage->u16Stride[0];
		}
		break;
	case IVE_IMAGE_TYPE_YUV420P:
		{
			HI_U16 u16Stide2;

			u16Stide2= HI_CalcStride(u16Width/2, HI_IVE2_STRIDE_ALIGN);
			pstImage->pu8VirAddr[0] = (HI_U8*)malloc(u16Stride * u16Height + u16Stide2 * u16Height);	
			HI_CHECK_ET_NULL_RET(pstImage->pu8VirAddr[0],HI_FAILURE);


			pstImage->pu8VirAddr[1] = pstImage->pu8VirAddr[0] + u16Stride * u16Height;
			pstImage->pu8VirAddr[2] = pstImage->pu8VirAddr[1] + u16Stide2 * u16Height/2;
			pstImage->u32PhyAddr[0] = (HI_U32)pstImage->pu8VirAddr[0];
			pstImage->u32PhyAddr[1] = (HI_U32)pstImage->pu8VirAddr[1];
			pstImage->u32PhyAddr[2] = (HI_U32)pstImage->pu8VirAddr[2];
			pstImage->u16Stride[0] = u16Stride;
			pstImage->u16Stride[1]  = u16Stide2;
			pstImage->u16Stride[2]  = pstImage->u16Stride[1];
		}
		break;
	case IVE_IMAGE_TYPE_YUV422P:
		{
			HI_U16 u16Stide2; 

			u16Stide2 = HI_CalcStride(u16Width/2, HI_IVE2_STRIDE_ALIGN);
			pstImage->pu8VirAddr[0] = (HI_U8*)malloc(u16Stride * u16Height + u16Stide2 * u16Height*2);
			HI_CHECK_ET_NULL_RET(pstImage->pu8VirAddr[0],HI_FAILURE);			
			pstImage->pu8VirAddr[1] = pstImage->pu8VirAddr[0] + u16Stride * u16Height;
			pstImage->pu8VirAddr[2] = pstImage->pu8VirAddr[1] + u16Stide2 * u16Height;
			pstImage->u32PhyAddr[0] = (HI_U32)pstImage->pu8VirAddr[0];
			pstImage->u32PhyAddr[1] = (HI_U32)pstImage->pu8VirAddr[1];
			pstImage->u32PhyAddr[2] = (HI_U32)pstImage->pu8VirAddr[2];
			pstImage->u16Stride[0] = u16Stride;
			pstImage->u16Stride[1]  = u16Stide2;
			pstImage->u16Stride[2]  = pstImage->u16Stride[1];
		}
		break;
	case IVE_IMAGE_TYPE_S8C2_PACKAGE:
		{
			pstImage->pu8VirAddr[0] = (HI_U8*)malloc(u16Stride * u16Height * 2);
			HI_CHECK_ET_NULL_RET(pstImage->pu8VirAddr[0],HI_FAILURE);

			pstImage->pu8VirAddr[1] = pstImage->pu8VirAddr[0] + 1;
			pstImage->u32PhyAddr[0] = (HI_U32)pstImage->pu8VirAddr[0];
			pstImage->u32PhyAddr[1] = (HI_U32)pstImage->pu8VirAddr[1];
			pstImage->u16Stride[0] = u16Stride;
			pstImage->u16Stride[1]  = pstImage->u16Stride[0];
		}
		break;
	case IVE_IMAGE_TYPE_S8C2_PLANAR:
		{
			pstImage->pu8VirAddr[0] = (HI_U8*)malloc(u16Stride * u16Height * 2);
			HI_CHECK_ET_NULL_RET(pstImage->pu8VirAddr[0],HI_FAILURE);

			pstImage->pu8VirAddr[1] = pstImage->pu8VirAddr[0] + u16Stride * u16Height;
			pstImage->u32PhyAddr[0] = (HI_U32)pstImage->pu8VirAddr[0];
			pstImage->u32PhyAddr[1] = (HI_U32)pstImage->pu8VirAddr[1];
			pstImage->u16Stride[0] = u16Stride;
			pstImage->u16Stride[1]  = pstImage->u16Stride[0];
		}
		break;
	case IVE_IMAGE_TYPE_S16C1:
	case IVE_IMAGE_TYPE_U16C1:
		{
			pstImage->pu8VirAddr[0] = (HI_U8*)malloc(u16Stride * u16Height * 2);
			HI_CHECK_ET_NULL_RET(pstImage->pu8VirAddr[0],HI_FAILURE);

			pstImage->u32PhyAddr[0] = (HI_U32)pstImage->pu8VirAddr[0];
			pstImage->u16Stride[0] = u16Stride;
		}
		break;
	case IVE_IMAGE_TYPE_U8C3_PACKAGE:
		{
			pstImage->pu8VirAddr[0] = (HI_U8*)malloc(u16Stride * u16Height * 3);
			HI_CHECK_ET_NULL_RET(pstImage->pu8VirAddr[0],HI_FAILURE);

			pstImage->pu8VirAddr[1] = pstImage->pu8VirAddr[0] + 1;
			pstImage->pu8VirAddr[2] = pstImage->pu8VirAddr[1] + 1;
			pstImage->u32PhyAddr[0] = (HI_U32)pstImage->pu8VirAddr[0];
			pstImage->u32PhyAddr[1] = (HI_U32)pstImage->pu8VirAddr[1];
			pstImage->u32PhyAddr[2] = (HI_U32)pstImage->pu8VirAddr[2];
			pstImage->u16Stride[0] = u16Stride;
			pstImage->u16Stride[1] = pstImage->u16Stride[0];
			pstImage->u16Stride[2] = pstImage->u16Stride[0];
		}
		break;
	case IVE_IMAGE_TYPE_U8C3_PLANAR:
		{
			pstImage->pu8VirAddr[0] = (HI_U8*)malloc(u16Stride * u16Height * 3);
			HI_CHECK_ET_NULL_RET(pstImage->pu8VirAddr[0],HI_FAILURE);

			pstImage->pu8VirAddr[1] = pstImage->pu8VirAddr[0] + u16Stride * u16Height;
			pstImage->pu8VirAddr[2] = pstImage->pu8VirAddr[1] + u16Stride * u16Height;
			pstImage->u32PhyAddr[0] = (HI_U32)pstImage->pu8VirAddr[0];
			pstImage->u32PhyAddr[1] = (HI_U32)pstImage->pu8VirAddr[1];
			pstImage->u32PhyAddr[2] = (HI_U32)pstImage->pu8VirAddr[2];
			pstImage->u16Stride[0] = u16Stride;
			pstImage->u16Stride[1] = pstImage->u16Stride[0];
			pstImage->u16Stride[2] = pstImage->u16Stride[0];
		}
		break;
	case IVE_IMAGE_TYPE_S32C1:
	case IVE_IMAGE_TYPE_U32C1:
		{
			pstImage->pu8VirAddr[0] = (HI_U8*)malloc(u16Stride * u16Height * 4);
			HI_CHECK_ET_NULL_RET(pstImage->pu8VirAddr[0],HI_FAILURE);

			pstImage->u32PhyAddr[0] = (HI_U32)pstImage->pu8VirAddr[0];
			pstImage->u16Stride[0] = u16Stride;
		}
		break;
	case IVE_IMAGE_TYPE_S64C1:
	case IVE_IMAGE_TYPE_U64C1:
		{
			pstImage->pu8VirAddr[0] = (HI_U8*)malloc(u16Stride * u16Height * 8);
			HI_CHECK_ET_NULL_RET(pstImage->pu8VirAddr[0],HI_FAILURE);

			pstImage->u32PhyAddr[0] = (HI_U32)pstImage->pu8VirAddr[0];
			pstImage->u16Stride[0] = u16Stride;
		}
		break;
	default:
		{
			s32Succ = HI_FAILURE;
		}
		break;
	}

	return s32Succ;
}

HI_S32 HI_DestroyIveImage(IVE_IMAGE_S *pstImage)
{

	HI_CHECK_ET_NULL_RET(pstImage,HI_FAILURE);

	HI_FREE(pstImage->pu8VirAddr[0]);

	return HI_SUCCESS;
}

HI_S32 comp(const HI_VOID *a,const HI_VOID *b)
{
	return  *(HI_U8 *)(*(HI_U32 *)b) - *(HI_U8 *)(*(HI_U32 *)a);
}

HI_S64 HI_GetTickCount(HI_VOID)
{
	HI_S64 s32Tick = 0;

#if defined WIN32 || defined _WIN32 || defined WINCE
	LARGE_INTEGER counter;
	QueryPerformanceCounter( &counter );
	s32Tick = (HI_S64)counter.QuadPart;
#elif defined __linux || defined __linux__
	struct timespec tp;
	clock_gettime(CLOCK_MONOTONIC, &tp);
	s32Tick =  (HI_S64)tp.tv_sec*1000000000 + tp.tv_nsec;
#else
	struct timeval tv;
	struct timezone tz;
	gettimeofday( &tv, &tz );
	s32Tick =  (HI_S64)tv.tv_sec*1000000 + tv.tv_usec;
#endif

	return s32Tick;
}

HI_DOUBLE HI_GetTickFrequency(HI_VOID)
{
	HI_DOUBLE dFre = 1.0;
#if defined WIN32 || defined _WIN32 || defined WINCE
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	dFre =  (HI_DOUBLE)freq.QuadPart;
#elif defined __linux || defined __linux__
	dFre =  1e9;
#else
	dFre =  1e6;
#endif

	return (dFre * 1e-6);

}

HI_S32 HI_GenRand(HI_S32 s32Max,HI_S32 s32Min)
{
	HI_S32 s32Result = 0;

	if (s32Min >= 0)
	{
		s32Result = s32Min + rand()%(s32Max - s32Min + 1);
	}
	else 
	{		
		s32Result = rand() % (s32Max - s32Min + 1);
		s32Result = s32Result > s32Max ?   s32Max - s32Result: s32Result;
	}

	return s32Result;
}
