/*
 * GraphLCD driver library
 *
 * vusolo4k.c  -  VUSOLO4K OLED driver class
 *
 * This file is released under the GNU General Public License. Refer
 * to the COPYING file distributed with this package.
 *
 * (c) redblue
 */


#ifndef _GLCDDRIVERS_ILI9486FB_H_
#define _GLCDDRIVERS_ILI9486FB_H_

#include "driver.h"

#define WIDTH_MAX 480
#define HEIGHT_MAX 320
#define BPP_MAX 16

namespace GLCD
{

class cDriverConfig;

class cDriverILI9486FB : public cDriver
{
private:
	int fd;
	uint16_t * newLCD;
	uint16_t * oldLCD;
	int bpp;
	int stride;
	int stride_bpp_value;

	int CheckSetup();

public:
	cDriverILI9486FB(cDriverConfig * config);
	virtual ~cDriverILI9486FB();

	virtual int Init();
	virtual int DeInit();

	virtual void Clear();
	virtual void SetPixel(int x, int y, uint32_t data);
	//virtual void Set8Pixels(int x, int y, unsigned char data);
	virtual void Refresh(bool refreshAll = false);
	virtual void SetBrightness(unsigned int percent);
};

} // end of namespace

#endif
