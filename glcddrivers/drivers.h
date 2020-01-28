/*
 * GraphLCD driver library
 *
 * drivers.h  -  global driver constants and functions
 *
 * This file is released under the GNU General Public License. Refer
 * to the COPYING file distributed with this package.
 *
 * (c) 2004 Andreas Regel <andreas.regel AT powarman.de>
 */

#ifndef _GLCDDRIVERS_DRIVERS_H_
#define _GLCDDRIVERS_DRIVERS_H_

#include <string>


namespace GLCD
{

class cDriverConfig;
class cDriver;

enum eDriver
{
    kDriverUnknown       = 0,
#ifdef HAVE_DRIVER_SIMLCD
    kDriverSimLCD        = 1,
#endif
#ifdef HAVE_DRIVER_GU140X32F
    kDriverGU140X32F     = 2,
#endif
#ifdef HAVE_DRIVER_GU256X64372
    kDriverGU256X64_372  = 3,
#endif
#ifdef HAVE_DRIVER_GU256X643900
    kDriverGU256X64_3900 = 4,
#endif
#ifdef HAVE_DRIVER_HD61830
    kDriverHD61830       = 5,
#endif
#ifdef HAVE_DRIVER_KS0108
    kDriverKS0108        = 6,
#endif
#ifdef HAVE_DRIVER_SED1330
    kDriverSED1330       = 7,
#endif
#ifdef HAVE_DRIVER_SED1520
    kDriverSED1520       = 8,
#endif
#ifdef HAVE_DRIVER_T6963C
    kDriverT6963C        = 9,
#endif
#ifdef HAVE_DRIVER_FRAMEBUFFER
    kDriverFramebuffer   = 10,
#endif
    kDriverImage         = 11,
#ifdef HAVE_DRIVER_NORITAKE800
    kDriverNoritake800   = 12,
#endif
#ifdef HAVE_DRIVER_AVRCTL
    kDriverAvrCtl        = 13,
#endif
    kDriverNetwork       = 14,
#ifdef HAVE_DRIVER_GU126X64DK610A4
    kDriverGU126X64D_K610A4 = 15,
#endif
#ifdef HAVE_DRIVER_DM140GINK
    kDriverDM140GINK     = 16,
#endif
#ifdef HAVE_DRIVER_FUTABAMDM166A
    kDriverFutabaMDM166A = 17,
#endif
#ifdef HAVE_DRIVER_AX206DPF
    kDriverAX206DPF      = 18,
#endif
#ifdef HAVE_DRIVER_PICOLCD256X64
    kDriverPicoLCD_256x64 = 19,
#endif
#ifdef HAVE_DRIVER_VNCSERVER
    kDriverVncServer     = 20,
#endif
#ifdef HAVE_DRIVER_SSD1306
    kDriverSSD1306       = 21,
#endif
#ifdef HAVE_DRIVER_ILI9341
    kDriverILI9341       = 22,
#endif
#ifdef HAVE_DRIVER_VUPLUS4K
    kDriverVUPLUS4K      = 23,
#endif
    kDriverUSBserLCD     = 24,
#ifdef HAVE_DRIVER_ST7565REEL
    kDriverST7565RReel   = 25,
#endif
    kDriverSerDisp       = 100,
#ifdef HAVE_DRIVER_G15DAEMON
    kDriverG15daemon     = 200
#endif
};

struct tDriver
{
    std::string name;
    eDriver id;
};

tDriver * GetAvailableDrivers(int & count);
int GetDriverID(const std::string & driver);
cDriver * CreateDriver(int driverID, cDriverConfig * config);

} // end of namespace

#endif
