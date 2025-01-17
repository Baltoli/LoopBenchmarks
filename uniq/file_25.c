typedef unsigned char uint8;
typedef unsigned short uint16;
typedef signed char int8;
typedef signed short int16;

static uint8
addAndClamp (uint8 a, int16 b)
{
  b = a + b;

  if ((uint16) b > 255U)
    {
      if (b < 0)
	return 0;
      else if (b > 255)
	return 255;
    }

  return (uint8) b;
}

uint8
subAndClamp (uint8 a, int16 b)
{
  b = a - b;

  if ((uint16) b > 255U)
    {
      if (b < 0)
	return 0;
      else if (b > 255)
	return 255;
    }

  return (uint8) b;
}

static void
loop_25(uint8* gMCUBufG, uint8* gMCUBufB, int16 *gCoeffBuf, uint8 srcOfs, uint8 dstOfs)
{
  // Cb - affects G and B
  uint8 x, y;
  int16 *pSrc = gCoeffBuf + srcOfs;
  uint8 *pDstG = gMCUBufG + dstOfs;
  uint8 *pDstB = gMCUBufB + dstOfs;
  for (y = 0; y < 4; y++)
    {
      for (x = 0; x < 4; x++)
	{
	  uint8 cb = (uint8) * pSrc++;
	  int16 cbG, cbB;

	  cbG = ((cb * 88U) >> 8U) - 44U;
	  pDstG[0] = subAndClamp (pDstG[0], cbG);
	  pDstG[1] = subAndClamp (pDstG[1], cbG);
	  pDstG[8] = subAndClamp (pDstG[8], cbG);
	  pDstG[9] = subAndClamp (pDstG[9], cbG);

	  cbB = (cb + ((cb * 198U) >> 8U)) - 227U;
	  pDstB[0] = addAndClamp (pDstB[0], cbB);
	  pDstB[1] = addAndClamp (pDstB[1], cbB);
	  pDstB[8] = addAndClamp (pDstB[8], cbB);
	  pDstB[9] = addAndClamp (pDstB[9], cbB);

	  pDstG += 2;
	  pDstB += 2;
	}

      pSrc = pSrc - 4 + 8;
      pDstG = pDstG - 8 + 16;
      pDstB = pDstB - 8 + 16;
    }
}
