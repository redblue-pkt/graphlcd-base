/*
 * GraphLCD driver library
 *
 * vusolo4k.c  -  VUSOLO4K OLED driver class
 *
 * This file is released under the GNU General Public License. Refer
 * to the COPYING file distributed with this package.
 *
 * (c) redblue 2018
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
#include "vusolo4k.h"

namespace GLCD
{

cDriverVUSOLO4K::cDriverVUSOLO4K(cDriverConfig * config)
:	cDriver(config),
	fd(-1)
{
}

cDriverVUSOLO4K::~cDriverVUSOLO4K()
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

int cDriverVUSOLO4K::Init()
{
	int x;

	width = config->width;
	if (width <= 0)
		width = lcd_read_value(XRES);

	height = config->height;
	if (height <= 0)
		height = lcd_read_value(YRES);

	bpp = lcd_read_value(BPP);

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

	newLCD = new uint16_t[width * height * 4];
	if (newLCD)
		memset(newLCD, 0, width * height * 4);
	oldLCD = new uint16_t[width * height * 4];
	if (oldLCD)
		memset(oldLCD, 0, width * height * 4);

	syslog(LOG_INFO, "%s: current lcd is %dx%d, %dbpp, vusolo4k lcd device was opened successfully\n", config->name.c_str(), width, height, bpp);

	*oldConfig = *config;

	// clear display
	Clear();
	//Refresh(true);

	syslog(LOG_INFO, "%s: VUSOLO4K initialized.\n", config->name.c_str());
	return 0;
}

int cDriverVUSOLO4K::DeInit()
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

int cDriverVUSOLO4K::CheckSetup()
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

void cDriverVUSOLO4K::Clear()
{
	memset(newLCD, 0, width * height);
}

void cDriverVUSOLO4K::SetPixel(int x, int y, uint32_t data)
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
	int row_pointers_2_ptr = (y * width + x) * 4;

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

void cDriverVUSOLO4K::Refresh(bool refreshAll)
{
	int i;
	char fileName[256];
	char str[32];
	FILE * fp;
	unsigned char c;

	if (CheckSetup() > 0)
		refreshAll = true;

	for (i = 0; i < width * height * 4; i++)
	{
		if (newLCD[i] != oldLCD[i])
		{
			refreshAll = true;
			break;
		}
	}

	if (refreshAll)
	{
		for (i = 0; i < width * height * 4; i++)
		{
			oldLCD[i] = newLCD[i];
		}
		unsigned char* row_pointers_bit_shift = (unsigned char*) &newLCD[0];
		{
			int w=-1;
			w = write(fd, row_pointers_bit_shift, height * width * 4);
			printf("write ret : %d\n",w);
			//ret = ioctl(lcdfd, 0);
			printf("write to /dev/dbox/oled0 : %d\n",w);
		}
	}
}

void cDriverVUSOLO4K::SetBrightness(unsigned int brightness)
{
	int value = 0;
	switch(brightness) {
		case 0:
			value = 0;
			break;
		case 1:
			value = 25;
			break;
		case 2:
			value = 51;
			break;
		case 3:
			value = 76;
			break;
		case 4:
			value = 102;
			break;
		case 5:
			value = 127;
			break;
		case 6:
			value = 153;
			break;
		case 7:
			value = 178;
			break;
		case 8:
			value = 204;
			break;
		case 9:
			value = 229;
			break;
		case 10:
			value = 255;
			break;
	}

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
