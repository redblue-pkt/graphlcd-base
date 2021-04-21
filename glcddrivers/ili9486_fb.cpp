/*
 * GraphLCD driver library
 *
 * vuplus4k.c  -  VUPLUS4K OLED driver class (vusolo4k, vuduo4k)
 *
 * This file is released under the GNU General Public License. Refer
 * to the COPYING file distributed with this package.
 *
 * (c) redblue 2021
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdint.h>
#include <syslog.h>
#include <cstring>
#include <byteswap.h>

#include "common.h"
#include "config.h"
#include "ili9486_fb.h"

namespace GLCD
{

cDriverILI9486FB::cDriverILI9486FB(cDriverConfig * config)
:	cDriver(config),
	fd(-1)
{
}

cDriverILI9486FB::~cDriverILI9486FB()
{
	DeInit();
}

int cDriverILI9486FB::Init()
{
	int x;

	width = config->width;
	if (width <= 0)
		width = WIDTH_MAX;

	height = config->height;
	if (height <= 0)
		height = HEIGHT_MAX;

	bpp = BPP_MAX;

	switch (bpp)
	{
		case 8:
			stride_bpp_value = 2;
			break;
		case 15:
		case 16:
			stride_bpp_value = 4;
			break;
		case 24:
		case 32:
			stride_bpp_value = 6;
			break;
		default:
			stride_bpp_value = (bpp + 7) / 8;
	}

	stride = width * stride_bpp_value;

	for (unsigned int i = 0; i < config->options.size(); i++)
	{
		if (config->options[i].name == "")
		{
		}
	}

	if (config->device == "")
	{
		fd = open("/dev/fb1", O_RDWR);
	}
	else
	{
		fd = open(config->device.c_str(), O_RDWR);
	}

	if (fd == -1) {
		printf("cannot open lcd device\n");
		return -1;
	}

	newLCD = new uint16_t[height * stride];
	if (newLCD)
		memset(newLCD, 0, height * stride);
	oldLCD = new uint16_t[height * stride];
	if (oldLCD)
		memset(oldLCD, 0, height * stride);

	syslog(LOG_INFO, "%s: current lcd is %dx%d, %dbpp, ili9486fb lcd device was opened successfully\n", config->name.c_str(), width, height, bpp);

	*oldConfig = *config;

	// clear display
	Clear();
	//Refresh(true);

	syslog(LOG_INFO, "%s: ILI9486FB initialized.\n", config->name.c_str());
	return 0;
}

int cDriverILI9486FB::DeInit()
{
	if (newLCD)
	{
		delete[] newLCD;
		newLCD = 0;
	}
	if (oldLCD)
	{
		delete[] oldLCD;
		oldLCD = 0;
	}
	if (-1 != fd)
	{
        	close(fd);
		fd=-1;
	}
	return 0;
}

int cDriverILI9486FB::CheckSetup()
{
	if (config->width != oldConfig->width ||
		config->height != oldConfig->height)
		{
		DeInit();
		Init();
		return 0;
	}

	if (config->upsideDown != oldConfig->upsideDown ||
		config->invert != oldConfig->invert)
	{
		oldConfig->upsideDown = config->upsideDown;
		oldConfig->invert = config->invert;
		return 1;
	}
	return 0;
}

void cDriverILI9486FB::Clear()
{
	memset(newLCD, 0, width * height);
}

void cDriverILI9486FB::SetPixel(int x, int y, uint32_t data)
{
	unsigned char col1, col2;
	uint32_t colraw;

	if (x >= width || y >= height)
		return;

	colraw = ((data & 0x00FF0000) >> (16 + 8 - 5) << 11) |	// red
		 ((data & 0x0000FF00) >> ( 8 + 8 - 6) << 5) |	// green
		 ((data & 0x000000FF) >> ( 0 + 8 - 5) << 0);	// blue

	col1 = colraw & 0x0000FF;
	col2 = (colraw & 0x00FF00) >> 8;

	unsigned char* buffer = (unsigned char*) &newLCD[0];
	int location = (y * width + x) * stride_bpp_value / 2;

	buffer[location + 0] = col1;
	buffer[location + 1] = col2;
}

void cDriverILI9486FB::Refresh(bool refreshAll)
{
	int i;
	char fileName[256];
	char str[32];
	FILE * fp;
	unsigned char c;

	if (CheckSetup() > 0)
		refreshAll = true;

	for (i = 0; i < height * stride; i++)
	{
		if (newLCD[i] != oldLCD[i])
		{
			refreshAll = true;
			break;
		}
	}

	if (refreshAll)
	{
		for (i = 0; i < height * stride; i++)
		{
			oldLCD[i] = newLCD[i];
		}
		unsigned char* row_pointers_bit_shift = (unsigned char*) &newLCD[0];
		{
			write(fd, row_pointers_bit_shift, height * stride);
		}
	}
}

void cDriverILI9486FB::SetBrightness(unsigned int brightness)
{
}

} // end of namespace
