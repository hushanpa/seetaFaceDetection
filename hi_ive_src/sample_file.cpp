#include "hi_ive\sample_file.h"
#include "hi_ive\sample_define.h"

HI_S32 HI_ReadFile(IVE_SRC_IMAGE_S *pstImage,FILE *fp)
{
	HI_U16 y;
	HI_S32 u32Succ;
	HI_U8 *pData;


	HI_CHECK_ET_NULL_RET(pstImage,HI_FAILURE);
	HI_CHECK_ET_NULL_RET(fp,HI_FAILURE);

	if (feof(fp)) 
	{		
		fseek(fp, 0 , SEEK_SET);
	}

	u32Succ = HI_SUCCESS;

	switch(pstImage->enType)
	{
	case IVE_IMAGE_TYPE_U8C1:
		{
			pData = pstImage->pu8VirAddr[0];
			for (y = 0; y < pstImage->u16Height; y++,pData += pstImage->u16Stride[0])
			{
				if (1 != fread(pData,pstImage->u16Width,1,fp))
				{
					u32Succ = HI_FAILURE;
					break;
				}
			}

		}
		break;
	case IVE_IMAGE_TYPE_YUV420SP:
		{
			pData = pstImage->pu8VirAddr[0];
			for (y = 0; y < pstImage->u16Height; y++,pData += pstImage->u16Stride[0])
			{
				if (1 != fread(pData,pstImage->u16Width,1,fp))
				{
					u32Succ = HI_FAILURE;
					break;
				}
			}

			pData = pstImage->pu8VirAddr[1];
			for (y = 0; y < pstImage->u16Height/2; y++,pData += pstImage->u16Stride[1])
			{
				if (1 != fread(pData,pstImage->u16Width,1,fp))
				{
					u32Succ = HI_FAILURE;
					break;
				}
			}
		}
		break;
	case IVE_IMAGE_TYPE_YUV422SP:
		{
			pData = pstImage->pu8VirAddr[0];
			for (y = 0; y < pstImage->u16Height; y++,pData += pstImage->u16Stride[0])
			{
				if (1 != fread(pData,pstImage->u16Width,1,fp))
				{
					u32Succ = HI_FAILURE;
					break;
				}
			}

			pData = pstImage->pu8VirAddr[1];
			for (y = 0; y < pstImage->u16Height; y++,pData += pstImage->u16Stride[1])
			{
				if (1 != fread(pData,pstImage->u16Width,1,fp))
				{
					u32Succ = HI_FAILURE;
					break;
				}
			}
		}
		break;
	case IVE_IMAGE_TYPE_U8C3_PACKAGE:
		{
			pData = pstImage->pu8VirAddr[0];
			for (y = 0; y < pstImage->u16Height; y++,pData += pstImage->u16Stride[0] * 3)
			{
				if (1 != fread(pData,pstImage->u16Width * 3,1,fp))
				{
					u32Succ = HI_FAILURE;
					break;
				}
			}
		}
		break;
	case IVE_IMAGE_TYPE_U8C3_PLANAR:
		{
			for (int i = 0; i < 3 ;i++)
			{
				pData = pstImage->pu8VirAddr[i];
				for (y = 0; y < pstImage->u16Height; y++,pData += pstImage->u16Stride[i] )
				{
					if (1 != fread(pData,pstImage->u16Width,1,fp))
					{
						u32Succ = HI_FAILURE;
						break;
					}
				}
			}
			
		}
		break;
	case IVE_IMAGE_TYPE_S16C1:
	case IVE_IMAGE_TYPE_U16C1:
		{
			pData = pstImage->pu8VirAddr[0];
			for (y = 0; y < pstImage->u16Height; y++,pData += pstImage->u16Stride[0] * 2 )
			{
				if (2 != fread(pData,pstImage->u16Width,2,fp))
				{
					u32Succ = HI_FAILURE;
					break;
				}
			}
		}
		break;
	default:
		u32Succ = HI_FAILURE;
		break;
	}

	return u32Succ;
}