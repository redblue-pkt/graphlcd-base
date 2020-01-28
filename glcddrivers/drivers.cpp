/*
 * GraphLCD driver library
 *
 * drivers.c  -  global driver constants and functions
 *
 * This file is released under the GNU General Public License. Refer
 * to the COPYING file distributed with this package.
 *
 * (c) 2004 Andreas Regel <andreas.regel AT powarman.de>
 */

#include <string.h>

#include "drivers.h"
#ifdef HAVE_DRIVER_SIMLCD
#include "simlcd.h"
#endif
#ifdef HAVE_DRIVER_GU140X32F
#include "gu140x32f.h"
#endif
#ifdef HAVE_DRIVER_GU256X64372
#include "gu256x64-372.h"
#endif
#ifdef HAVE_DRIVER_GU256X643900
#include "gu256x64-3900.h"
#endif
#ifdef HAVE_DRIVER_HD61830
#include "hd61830.h"
#endif
#ifdef HAVE_DRIVER_KS0108
#include "ks0108.h"
#endif
#ifdef HAVE_DRIVER_SED1330
#include "sed1330.h"
#endif
#ifdef HAVE_DRIVER_SED1520
#include "sed1520.h"
#endif
#ifdef HAVE_DRIVER_T6963C
#include "t6963c.h"
#endif
#ifdef HAVE_DRIVER_FRAMEBUFFER
#include "framebuffer.h"
#endif
#include "image.h"
#ifdef HAVE_DRIVER_NORITAKE800
#include "noritake800.h"
#endif
#ifdef HAVE_DRIVER_AVRCTL
#include "avrctl.h"
#endif
#include "network.h"
#ifdef HAVE_DRIVER_GU126X64DK610A4
#include "gu126x64D-K610A4.h"
#endif
#ifdef HAVE_DRIVER_DM140GINK
#include "dm140gink.h"
#endif
#include "serdisp.h"
#ifdef HAVE_DRIVER_G15DAEMON
#include "g15daemon.h"
#endif
#include "usbserlcd.h"
#ifdef HAVE_DRIVER_ST7565RREEL
#include "st7565r-reel.h"
#endif
#ifdef HAVE_DRIVER_FUTABAMDM166A
#include "futabaMDM166A.h"
#endif
#ifdef HAVE_DRIVER_AX206DPF
#include "ax206dpf.h"
#endif
#ifdef HAVE_DRIVER_PICOLCD256X64
#include "picoLCD_256x64.h"
#endif
#ifdef HAVE_DRIVER_VNCSERVER
#include "vncserver.h"
#endif
#ifdef HAVE_DRIVER_SSD1306
#include "ssd1306.h"
#endif
#ifdef HAVE_DRIVER_ILI9341
#include "ili9341.h"
#endif
#ifdef HAVE_DRIVER_VUPLUS4K
#include "vuplus4k.h"
#endif

namespace GLCD
{

tDriver drivers[] =
{
#ifdef HAVE_DRIVER_SIMLCD
    {"simlcd",        kDriverSimLCD},
#endif
#ifdef HAVE_DRIVER_GU140X32F
    {"gu140x32f",     kDriverGU140X32F},
#endif
#ifdef HAVE_DRIVER_GU256X64372
    {"gu256x64-372",  kDriverGU256X64_372},
#endif
#ifdef HAVE_DRIVER_GU256X643900
    {"gu256x64-3900", kDriverGU256X64_3900},
#endif
#ifdef HAVE_DRIVER_HD61830
    {"hd61830",       kDriverHD61830},
#endif
#ifdef HAVE_DRIVER_KS0108
    {"ks0108",        kDriverKS0108},
#endif
#ifdef HAVE_DRIVER_SED1330
    {"sed1330",       kDriverSED1330},
#endif
#ifdef HAVE_DRIVER_SED1520
    {"sed1520",       kDriverSED1520},
#endif
#ifdef HAVE_DRIVER_T6963C
    {"t6963c",        kDriverT6963C},
#endif
#ifdef HAVE_DRIVER_FRAMEBUFFER
    {"framebuffer",   kDriverFramebuffer},
#endif
    {"image",         kDriverImage},
#ifdef HAVE_DRIVER_NORITAKE800
    {"noritake800",   kDriverNoritake800},
#endif
#ifdef HAVE_DRIVER_AVRCTL
    {"avrctl",        kDriverAvrCtl},
#endif
    {"network",       kDriverNetwork},
#ifdef HAVE_DRIVER_GU126X64DK610A4
    {"gu126x64D-K610A4", kDriverGU126X64D_K610A4},
#endif
#ifdef HAVE_DRIVER_DM140GINK
    {"dm140gink",     kDriverDM140GINK},
#endif
    {"usbserlcd",     kDriverUSBserLCD},
#ifdef HAVE_DRIVER_ST7565RREEL
    {"st7565r-reel",  kDriverST7565RReel},
#endif
#ifdef HAVE_DRIVER_FUTABAMDM166A
    {"futabaMDM166A", kDriverFutabaMDM166A},
#endif
    {"serdisp",       kDriverSerDisp},
#ifdef HAVE_DRIVER_G15DAEMON
    {"g15daemon",     kDriverG15daemon},
#endif
#ifdef HAVE_DRIVER_AX206DPF
    {"ax206dpf",      kDriverAX206DPF},
#endif
#ifdef HAVE_DRIVER_PICOLCD256X64
    {"picolcd256x64", kDriverPicoLCD_256x64},
#endif
#ifdef HAVE_DRIVER_VNCSERVER
    {"vncserver",     kDriverVncServer},
#endif
#ifdef HAVE_DRIVER_SSD1306
    {"ssd1306",       kDriverSSD1306},
#endif
#ifdef HAVE_DRIVER_ILI9341
    {"ili9341",       kDriverILI9341},
#endif
#ifdef HAVE_DRIVER_VUPLUS4K
    {"vuplus4k",      kDriverVUPLUS4K},
#endif
    {"",              kDriverUnknown}
};

tDriver * GetAvailableDrivers(int & count)
{
    for (count = 0; drivers[count].name.length() > 0; count++)
        ;
    return drivers;
}

int GetDriverID(const std::string & driver)
{
    for (int i = 0; drivers[i].name.length() > 0; i++)
        if (drivers[i].name == driver)
            return drivers[i].id;
    return kDriverUnknown;
}

cDriver * CreateDriver(int driverID, cDriverConfig * config)
{
    switch (driverID)
    {
#ifdef HAVE_DRIVER_SIMLCD
        case kDriverSimLCD:
            return new cDriverSimLCD(config);
#endif
#ifdef HAVE_DRIVER_GU140X32F
        case kDriverGU140X32F:
            return new cDriverGU140X32F(config);
#endif
#ifdef HAVE_DRIVER_GU256X64372
        case kDriverGU256X64_372:
            return new cDriverGU256X64_372(config);
#endif
#ifdef HAVE_DRIVER_GU256X643900
        case kDriverGU256X64_3900:
            return new cDriverGU256X64_3900(config);
#endif
#ifdef HAVE_DRIVER_HD61830
        case kDriverHD61830:
            return new cDriverHD61830(config);
#endif
#ifdef HAVE_DRIVER_KS0108
        case kDriverKS0108:
            return new cDriverKS0108(config);
#endif
#ifdef HAVE_DRIVER_SED1330
        case kDriverSED1330:
            return new cDriverSED1330(config);
#endif
#ifdef HAVE_DRIVER_SED1520
        case kDriverSED1520:
            return new cDriverSED1520(config);
#endif
#ifdef HAVE_DRIVER_T6963C
        case kDriverT6963C:
            return new cDriverT6963C(config);
#endif
#ifdef HAVE_DRIVER_FRAMEBUFFER
        case kDriverFramebuffer:
            return new cDriverFramebuffer(config);
#endif
        case kDriverImage:
            return new cDriverImage(config);
#ifdef HAVE_DRIVER_NORITAKE800
        case kDriverNoritake800:
            return new cDriverNoritake800(config);
#endif
#ifdef HAVE_DRIVER_AVRCTL
        case kDriverAvrCtl:
            return new cDriverAvrCtl(config);
#endif
        case kDriverNetwork:
            return new cDriverNetwork(config);
#ifdef HAVE_DRIVER_GU126X64DK610A4
        case kDriverGU126X64D_K610A4:
            return new cDriverGU126X64D_K610A4(config);
#endif
#ifdef HAVE_DRIVER_DM140GINK
        case kDriverDM140GINK:
            return new cDriverDM140GINK(config);
#endif
        case kDriverUSBserLCD:
            return new cDriverUSBserLCD(config);
#ifdef HAVE_DRIVER_SR7565RREEL
        case kDriverST7565RReel:
            return new cDriverST7565RReel(config);
#endif
#ifdef HAVE_DRIVER_FUTABAMDM166A
        case kDriverFutabaMDM166A:
            return new cDriverFutabaMDM166A(config);
#endif
        case kDriverSerDisp:
            return new cDriverSerDisp(config);
#ifdef HAVE_DRIVER_G15DAEMON
        case kDriverG15daemon:
            return new cDriverG15daemon(config);
#endif
#ifdef HAVE_DRIVER_AX206DPF
        case kDriverAX206DPF:
            return new cDriverAX206DPF(config);
#endif
#ifdef HAVE_DRIVER_PICOLCD256X64
        case kDriverPicoLCD_256x64:
            return new cDriverPicoLCD_256x64(config);
#endif
#ifdef HAVE_DRIVER_VNCSERVER
        case kDriverVncServer:
            return new cDriverVncServer(config);
#endif
#ifdef HAVE_DRIVER_SSD1306
        case kDriverSSD1306:
            return new cDriverSSD1306(config);
#endif
#ifdef HAVE_DRIVER_ILI9341
        case kDriverILI9341:
            return new cDriverILI9341(config);
#endif
#ifdef HAVE_DRIVER_VUPLUS4K
        case kDriverVUPLUS4K:
            return new cDriverVUPLUS4K(config);
#endif
        case kDriverUnknown:
        default:
            return NULL;
    }
}

} // end of namespace
