/*
 * GraphLCD driver library
 *
 * vuplus4k.c  -  VUPLUS4K OLED driver class (vusolo4k, vuduo4k)
 *
 * This file is released under the GNU General Public License. Refer
 * to the COPYING file distributed with this package.
 *
 * (c) redblue 2019
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
#include "vuplus4k.h"

namespace GLCD
{

cDriverVUPLUS4K::cDriverVUPLUS4K(cDriverConfig * config)
:	cDriver(config),
	fd(-1)
{
}

cDriverVUPLUS4K::~cDriverVUPLUS4K()
{
	DeInit();
}

int lcd_read_value(const char *filename)
{
	int value = 0;
	FILE *fd = fopen(filename, "r");
	if (fd) {
		int tmp;
		if (fscanf(fd, "%x", &tmp) == 1)
			value = tmp;
		fclose(fd);
	}
	return value;
}

int cDriverVUPLUS4K::Init()
{
	int x;

	width = config->width;
	if (width <= 0)
		width = lcd_read_value(XRES);

	height = config->height;
	if (height <= 0)
		height = lcd_read_value(YRES);

	bpp = lcd_read_value(BPP);

	switch (bpp)
	{
		case 8:
			stride_bpp_value = 1;
			break;
		case 15:
		case 16:
			stride_bpp_value = 2;
			break;
		case 24:
		case 32:
			stride_bpp_value = 4;
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
		fd = open("/dev/dbox/lcd0", O_RDWR);
		if (fd == -1)
			fd = open("/dev/lcd0", O_RDWR);
		if (fd == -1)
			fd = open("/dev/dbox/oled0", O_RDWR);
		if (fd == -1)
			fd = open("/dev/oled0", O_RDWR);
	}
	else
	{
		fd = open(config->device.c_str(), O_RDWR);
	}

	if (fd == -1) {
		printf("cannot open lcd device\n");
		return -1;
	}

	int tmp = LCD_MODE_BIN;
	if (ioctl(fd, LCD_IOCTL_ASC_MODE, &tmp)) {
		printf("failed to set lcd bin mode\n");
	}

	newLCD = new uint16_t[height * stride];
	if (newLCD)
		memset(newLCD, 0, height * stride);
	oldLCD = new uint16_t[height * stride];
	if (oldLCD)
		memset(oldLCD, 0, height * stride);

	syslog(LOG_INFO, "%s: current lcd is %dx%d, %dbpp, vuplus4k lcd device was opened successfully\n", config->name.c_str(), width, height, bpp);

	*oldConfig = *config;

	// clear display
	Clear();
	//Refresh(true);

	syslog(LOG_INFO, "%s: VUPLUS4K initialized.\n", config->name.c_str());
	return 0;
}

int cDriverVUPLUS4K::DeInit()
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

int cDriverVUPLUS4K::CheckSetup()
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

void cDriverVUPLUS4K::Clear()
{
	memset(newLCD, 0, width * height);
}

void cDriverVUPLUS4K::SetPixel(int x, int y, uint32_t data)
{
	if (x >= width || y >= height)
		return;

	if (config->upsideDown)
	{
		x = width - 1 - x;
		y = height - 1 - y;
	}

	uint32_t red, green, blue;
	blue = (data & 0x000000FF) >> 0;
	green = (data & 0x0000FF00) >> 8;
	red = (data & 0x00FF0000) >> 16;

	unsigned char* row_pointers_bit_shift = (unsigned char*) &newLCD[0];
	int row_pointers_2_ptr = (y * width + x) * stride_bpp_value;

 	if (config->invert) {
		blue = 255 - blue;
		green = 255 - green;
		red = 255 - red;
	}

	row_pointers_bit_shift[row_pointers_2_ptr+0]=blue;
	row_pointers_bit_shift[row_pointers_2_ptr+1]=green;
	row_pointers_bit_shift[row_pointers_2_ptr+2]=red;
	row_pointers_bit_shift[row_pointers_2_ptr+3]=0xff;
}

void cDriverVUPLUS4K::Refresh(bool refreshAll)
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

void cDriverVUPLUS4K::SetBrightness(unsigned int brightness)
{
	int value = 0;
	value = 255 * brightness / 10;

	FILE *f = fopen("/proc/stb/lcd/oled_brightness", "w");
	if (!f)
		f = fopen("/proc/stb/fp/oled_brightness", "w");
	if (f)
	{
		if (fprintf(f, "%d", value) == 0)
			printf("write /proc/stb/lcd/oled_brightness failed!! (%m)\n");
		fclose(f);
	}
}

} // end of namespace
