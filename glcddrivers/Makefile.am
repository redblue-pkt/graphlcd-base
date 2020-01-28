AM_CXXFLAGS = -I$(top_srcdir) @MY_DEBUG_CPPFLAGS@

lib_LTLIBRARIES = libglcddrivers.la
libglcddrivers_la_SOURCES = common.cpp config.cpp driver.cpp drivers.cpp port.cpp \
                            image.cpp serdisp.cpp network.cpp usbserlcd.cpp

if HAVE_DRIVER_AVRCTL
libglcddrivers_la_SOURCES += avrctl.cpp
endif

if HAVE_DRIVER_AX206DPF
libglcddrivers_la_SOURCES += ax206dpf.cpp
AM_CXXFLAGS += @libusb_CFLAGS@
endif

if HAVE_DRIVER_DM140GINK
libglcddrivers_la_SOURCES += dm140gink.cpp
endif

if HAVE_DRIVER_FRAMEBUFFER
libglcddrivers_la_SOURCES += framebuffer.cpp
endif

if HAVE_DRIVER_FUTABAMDM166A
libglcddrivers_la_SOURCES += futabaMDM166A.cpp
AM_CXXFLAGS += @libhid_CFLAGS@
endif

if HAVE_DRIVER_G15DAEMON
libglcddrivers_la_SOURCES += g15daemon.cpp
endif

if HAVE_DRIVER_GU140X32F
libglcddrivers_la_SOURCES += gu140x32f.cpp
endif

if HAVE_DRIVER_GU126X64DK610A4
libglcddrivers_la_SOURCES += gu126x64d-K610A4.cpp
endif

if HAVE_DRIVER_GU256X64372
libglcddrivers_la_SOURCES += gu256x64-372.cpp
endif

if HAVE_DRIVER_GU256X643900
libglcddrivers_la_SOURCES += gu256x64-3900.cpp
endif

if HAVE_DRIVER_HD61830
libglcddrivers_la_SOURCES += hd61830.cpp
endif

if HAVE_DRIVER_ILI9341
libglcddrivers_la_SOURCES += ili9341.cpp
endif

if HAVE_DRIVER_KS0108
libglcddrivers_la_SOURCES += ks0108.cpp
endif

if HAVE_DRIVER_NORITAKE800
libglcddrivers_la_SOURCES += noritake800.cpp
endif

if HAVE_DRIVER_PICOLCD256X64
libglcddrivers_la_SOURCES += picoLCD_256x64.cpp
AM_CXXFLAGS += @libusb_CFLAGS@
endif

if HAVE_DRIVER_SED1330
libglcddrivers_la_SOURCES += sed1330.cpp
endif

if HAVE_DRIVER_SED1520
libglcddrivers_la_SOURCES += sed1520.cpp
endif

if HAVE_DRIVER_SIMLCD
libglcddrivers_la_SOURCES += simlcd.cpp
endif

if HAVE_DRIVER_ST7565RREEL
libglcddrivers_la_SOURCES += st7565r-reel.cpp
endif

if HAVE_DRIVER_SSD1306
libglcddrivers_la_SOURCES += ssd1306.cpp
AM_CXXFLAGS += @libwiringPi_CFLAGS@
endif

if HAVE_DRIVER_SSD1322FTDI
libglcddrivers_la_SOURCES += ssd1322ftdi.cpp
AM_CXXFLAGS += @libftdi1_CFLAGS@ 
endif

if HAVE_DRIVER_T6963C
libglcddrivers_la_SOURCES += t6963c.cpp
endif

if HAVE_DRIVER_VUPLUS4K
libglcddrivers_la_SOURCES += vuplus4k.cpp
endif

if HAVE_DRIVER_VNCSERVER
libglcddrivers_la_SOURCES += vncserver.cpp
AM_CXXFLAGS += @MY_VNCSERVER_CPPFLAGS@ @libvncserver_CFLAGS@ 
endif

libglcddrivers_la_LDFLAGS = -version-info @GLCDDRIVERS_MAJOR_VERSION@:@GLCDDRIVERS_MINOR_VERSION@:@GLCDDRIVERS_MICRO_VERSION@ \
                            -lpthread @libftdi1_LIBS@ @libhid_LIBS@ @libusb_LIBS@ @libvncserver_LIBS@ @libwiringPi_LIBS@


pkgincludedir = ${includedir}/glcddrivers
pkginclude_HEADERS = $(srcdir)/config.h $(srcdir)/driver.h $(srcdir)/drivers.h
pkgconfigdir = ${libdir}/pkgconfig
pkgconfig_DATA = libglcddrivers.pc
