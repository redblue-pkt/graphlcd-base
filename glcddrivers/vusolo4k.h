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


#ifndef _GLCDDRIVERS_VUSOLO4K_H_
#define _GLCDDRIVERS_VUSOLO4K_H_

#include "driver.h"

namespace GLCD
{

#define XRES "/proc/stb/lcd/xres"
#define YRES "/proc/stb/lcd/yres"
#define BPP "/proc/stb/lcd/bpp"

#ifndef LCD_IOCTL_ASC_MODE
#define LCDSET                                  0x1000
#define LCD_IOCTL_ASC_MODE              (21|LCDSET)
#define LCD_MODE_ASC                    0
#define LCD_MODE_BIN                    1
#endif

#define FP_IOCTL_LCD_DIMM       3

class cDriverConfig;

class cDriverVUSOLO4K : public cDriver
{
private:
	int fd;
	uint16_t * newLCD;
	uint16_t * oldLCD;
	int bpp;

	int CheckSetup();

public:
	cDriverVUSOLO4K(cDriverConfig * config);
	virtual ~cDriverVUSOLO4K();

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
