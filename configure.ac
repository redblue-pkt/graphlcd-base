AC_INIT(graphlcd-base,0.0.1,,graphlcd-base)
AM_INIT_AUTOMAKE([1.12 gnits dist-bzip2 no-dist-gzip -Wall no-define])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])

AM_PROG_AR
AC_PROG_CXX
PKG_PROG_PKG_CONFIG

LT_INIT([disable-static])

m4_define([libglcddrivers_major_version], [2])
GLCDDRIVERS_MAJOR_VERSION=libglcddrivers_major_version
AC_SUBST(GLCDDRIVERS_MAJOR_VERSION)
m4_define([libglcddrivers_minor_version], [1])
GLCDDRIVERS_MINOR_VERSION=libglcddrivers_minor_version
AC_SUBST(GLCDDRIVERS_MINOR_VERSION)
m4_define([libglcddrivers_micro_version], [0])
GLCDDRIVERS_MICRO_VERSION=libglcddrivers_micro_version
AC_SUBST(GLCDDRIVERS_MICRO_VERSION)

m4_define([libglcdgraphics_major_version], [2])
GLCDGRAPHICS_MAJOR_VERSION=libglcdgraphics_major_version
AC_SUBST(GLCDGRAPHICS_MAJOR_VERSION)
m4_define([libglcdgraphics_minor_version], [1])
GLCDGRAPHICS_MINOR_VERSION=libglcdgraphics_minor_version
AC_SUBST(GLCDGRAPHICS_MINOR_VERSION)
m4_define([libglcdgraphics_micro_version], [0])
GLCDGRAPHICS_MICRO_VERSION=libglcdgraphics_micro_version
AC_SUBST(GLCDGRAPHICS_MICRO_VERSION)

m4_define([libglcdskin_major_version], [2])
GLCDSKIN_MAJOR_VERSION=libglcdskin_major_version
AC_SUBST(GLCDSKIN_MAJOR_VERSION)
m4_define([libglcdskin_minor_version], [1])
GLCDSKIN_MINOR_VERSION=libglcdskin_minor_version
AC_SUBST(GLCDSKIN_MINOR_VERSION)
m4_define([libglcdskin_micro_version], [0])
GLCDSKIN_MICRO_VERSION=libglcdskin_micro_version
AC_SUBST(GLCDSKIN_MICRO_VERSION)

AC_ARG_ENABLE([plugins],
[  --enable-plugins        linker plugins],
[case "${enableval}" in
  yes | "") plugins=yes ;;
  no) plugins=no ;;
  *) plugins=yes ;;
 esac],
[plugins=no])
if test "$plugins" = "yes"; then
  AC_DEFINE(ENABLE_PLUGINS, 1,
	    [Define to enable linker plugins])
fi
AM_CONDITIONAL(PLUGINS, test "$plugins" = "yes") 


AC_ARG_ENABLE([freetype2],
 	AS_HELP_STRING(--disable-freetype2,disable usage of freetype2),
 	[case "${enableval}" in yes | "") am_freetype2=yes ;; no) am_freetype2=no ;; *) am_freetype2=yes ;; esac], [am_freetype2=yes])
	if test "$am_freetype2" = "yes"; then
		PKG_CHECK_MODULES([libfreetype2], [freetype2], [HAVE_FREETYPE2=1])
		AS_IF([test "$HAVE_FREETYPE2" = 1], [AC_SUBST(MY_LIBFREETYPE2_CPPFLAGS,-DHAVE_FREETYPE2)])
	fi

AC_SUBST(MY_IMAGEMAGICK_CPPFLAGS,[])
AC_SUBST(imagemagick_CFLAGS,[])
AC_SUBST(imagemagick_LIBS,[])
AC_ARG_WITH([imagemagick],
 	AS_HELP_STRING(--with-imagemagick,use imagemagick) )
	if test "x$with_gtk" = "xyes"; then
		PKG_CHECK_MODULES([ImageMagick], [ImageMagick++], [HAVE_IMAGEMAGICK=1])
		AS_IF([test "$HAVE_IMAGEMAGICK" = 1], [AC_SUBST(MY_IMAGEMAGICK_CPPFLAGS,-DHAVE_IMAGEMAGICK)])
	fi

AC_ARG_ENABLE([fontconfig],
 	AS_HELP_STRING(--disable-fontconfig,disable support for fontconfig),
 	[case "${enableval}" in yes | "") am_fontconfig=yes ;; no) am_fontconfig=no ;; *) am_fontconfig=yes ;; esac], [am_fontconfig=yes])
	if test "$am_fontconfig" = "yes"; then
		AC_CHECK_LIB([fontconfig], [FcNameParse])
		AS_IF([test "$ac_cv_lib_fontconfig_FcNameParse" = yes], [AC_SUBST(LIBFONTCONFIG_CPPFLAGS,-DHAVE_FONTCONFIG) AC_SUBST(LIBFONTCONFIG_LDFLAGS,-lfontconfig)])
	fi

AC_ARG_ENABLE([debug],
 	AS_HELP_STRING(--disable-debug,disable debug output),
 	[case "${enableval}" in yes | "") am_debug=yes ;; no) am_debug=no ;; *) am_debug=yes ;; esac], [am_debug=yes])
	if test "$am_debug" = "yes"; then
		AC_DEFINE(HAVE_DEBUG, 1, [Define to enable debug output])
		AC_SUBST(MY_DEBUG_CPPFLAGS,-DHAVE_DEBUG)
	fi

AC_ARG_ENABLE([driver-avrctl],
	AS_HELP_STRING(--enable-driver-avrctl,enable driver avrctl),
	[case "${enableval}" in yes | "") am_driver_avrctl=yes ;; no) am_driver_avrctl=no ;; *) am_driver_avrctl=no ;; esac], [am_driver_avrctl=no])
	if test "$am_driver_avrctl" = "yes"; then
		AC_DEFINE(HAVE_DRIVER_AVRCTL, 1, [Define avrctl driver])
		AC_SUBST(MY_AVRCTL_CPPFLAGS,-DHAVE_DRIVER_AVRCTL)
	fi
	AM_CONDITIONAL([HAVE_DRIVER_AVRCTL], test "$am_driver_avrctl" = "yes")
	
AC_ARG_ENABLE([driver-ax206dpf],
 	AS_HELP_STRING(--enable-driver-ax206dpf,enable driver ax206dpf),
 	[case "${enableval}" in yes | "") am_driver_ax206dpf=yes ;; no) am_driver_ax206dpf=no ;; *) am_driver_ax206dpf=no ;; esac], [am_driver_ax206dpf=no])
	if test "$am_driver_ax206dpf" = "yes"; then
		PKG_CHECK_MODULES([libusb], [libusb], [HAVE_LIBUSB=1])
		AC_DEFINE(HAVE_DRIVER_AX206DPF, 1, [Define ax206dpf driver])
		AC_SUBST(MY_AX206DPF_CPPFLAGS,-DHAVE_DRIVER_AX206DPF)
	fi
	AM_CONDITIONAL([HAVE_DRIVER_AX206DPF], test "$am_driver_ax206dpf" = "yes")

AC_ARG_ENABLE([driver-dm140gink],
	AS_HELP_STRING(--enable-driver-dm140gink,enable driver dm140gink),
	[case "${enableval}" in yes | "") am_driver_dm140gink=yes ;; no) am_driver_dm140gink=no ;; *) am_driver_dm140gink=no ;; esac], [am_driver_dm140gink=no])
	if test "$am_driver_dm140gink" = "yes"; then
		AC_DEFINE(HAVE_DRIVER_DM140GINK, 1, [Define dm140gink driver])
		AC_SUBST(MY_DM140GINK_CPPFLAGS,-DHAVE_DRIVER_DM140GINK)
	fi
	AM_CONDITIONAL([HAVE_DRIVER_DM140GINK], test "$am_driver_dm140gink" = "yes")

AC_ARG_ENABLE([driver-framebuffer],
	AS_HELP_STRING(--enable-driver-framebuffer,enable driver framebuffer),
	[case "${enableval}" in yes | "") am_driver_framebuffer=yes ;; no) am_driver_framebuffer=no ;; *) am_driver_framebuffer=no ;; esac], [am_driver_framebuffer=no])
	if test "$am_driver_framebuffer" = "yes"; then
		AC_DEFINE(HAVE_DRIVER_FRAMEBUFFER, 1, [Define framebuffer driver])
		AC_SUBST(MY_FRAMEBUFFER_CPPFLAGS,-DHAVE_DRIVER_FRAMEBUFFER)
	fi
	AM_CONDITIONAL([HAVE_DRIVER_FRAMEBUFFER], test "$am_driver_framebuffer" = "yes")

AC_ARG_ENABLE([driver-futabamdm166a],
	AS_HELP_STRING(--enable-driver-futabamdm166a,enable driver futabamdm166a),
	[case "${enableval}" in yes | "") am_driver_futabamdm166a=yes ;; no) am_driver_futabamdm166a=no ;; *) am_driver_futabamdm166a=no ;; esac], [am_driver_futabamdm166a=no])
	if test "$am_driver_futabamdm166a" = "yes"; then
		PKG_CHECK_MODULES([libhid], [libhid], [HAVE_LIBHID=1])
		AC_DEFINE(HAVE_DRIVER_FUTABAMDM166A, 1, [Define futabamdm166a driver])
		AC_SUBST(MY_FUTABAMDM166A_CPPFLAGS,-DHAVE_DRIVER_FUTABAMDM166A)
	fi
	AM_CONDITIONAL([HAVE_DRIVER_FUTABAMDM166A], test "$am_driver_futabamdm166a" = "yes")

AC_ARG_ENABLE([driver-g15daemon],
	AS_HELP_STRING(--enable-driver-g15daemon,enable driver g15daemon),
	[case "${enableval}" in yes | "") am_driver_g15daemon=yes ;; no) am_driver_g15daemon=no ;; *) am_driver_g15daemon=no ;; esac], [am_driver_g15daemon=no])
	if test "$am_driver_g15daemon" = "yes"; then
		AC_DEFINE(HAVE_DRIVER_G15DAEMON, 1, [Define g15daemon driver])
		AC_SUBST(MY_G15DAEMON_CPPFLAGS,-DHAVE_DRIVER_G15DAEMON)
	fi
	AM_CONDITIONAL([HAVE_DRIVER_G15DAEMON], test "$am_driver_g15daemon" = "yes")

AC_ARG_ENABLE([driver-gu140x32f],
	AS_HELP_STRING(--enable-driver-gu140x32f,enable driver gu140x32f),
	[case "${enableval}" in yes | "") am_driver_gu140x32f=yes ;; no) am_driver_gu140x32f=no ;; *) am_driver_gu140x32f=no ;; esac], [am_driver_gu140x32f=no])
	if test "$am_driver_gu140x32f" = "yes"; then
		AC_DEFINE(HAVE_DRIVER_GU140X32F, 1, [Define gu140x32f driver])
		AC_SUBST(MY_GU140X32F_CPPFLAGS,-DHAVE_DRIVER_GU140X32F)
	fi
	AM_CONDITIONAL([HAVE_DRIVER_GU140X32F], test "$am_driver_gu140x32f" = "yes")

AC_ARG_ENABLE([driver-gu126x64dk610a4],
	AS_HELP_STRING(--enable-driver-gu126x64dk610a4,enable driver gu126x64dk610a4),
	[case "${enableval}" in yes | "") am_driver_gu126x64dk610a4=yes ;; no) am_driver_gu126x64dk610a4=no ;; *) am_driver_gu126x64dk610a4=no ;; esac], [am_driver_gu126x64dk610a4=no])
	if test "$am_driver_gu126x64dk610a4" = "yes"; then
		AC_DEFINE(HAVE_DRIVER_GU126X64DK610A4, 1, [Define gu126x64dk610a4 driver])
		AC_SUBST(MY_GU126X64DK610A4_CPPFLAGS,-DHAVE_DRIVER_GU126X64DK610A4)
	fi
	AM_CONDITIONAL([HAVE_DRIVER_GU126X64DK610A4], test "$am_driver_gu126x64dk610a4" = "yes")

AC_ARG_ENABLE([driver-gu256x64372],
	AS_HELP_STRING(--enable-driver-gu256x64372,enable driver gu256x64372),
	[case "${enableval}" in yes | "") am_driver_gu256x64372=yes ;; no) am_driver_gu256x64372=no ;; *) am_driver_gu256x64372=no ;; esac], [am_driver_gu256x64372=no])
	if test "$am_driver_gu256x64372" = "yes"; then
		AC_DEFINE(HAVE_DRIVER_GU256X64372, 1, [Define gu256x64372 driver])
		AC_SUBST(MY_GU256X64372_CPPFLAGS,-DHAVE_DRIVER_GU256X64372)
	fi
	AM_CONDITIONAL([HAVE_DRIVER_GU256X64372], test "$am_driver_gu256x64372" = "yes")

AC_ARG_ENABLE([driver-gu256x643900],
	AS_HELP_STRING(--enable-driver-gu256x643900,enable driver gu256x643900),
	[case "${enableval}" in yes | "") am_driver_gu256x643900=yes ;; no) am_driver_gu256x643900=no ;; *) am_driver_gu256x643900=no ;; esac], [am_driver_gu256x643900=no])
	if test "$am_driver_gu256x643900" = "yes"; then
		AC_DEFINE(HAVE_DRIVER_GU256X643900, 1, [Define gu256x643900 driver])
		AC_SUBST(MY_GU256X643900_CPPFLAGS,-DHAVE_DRIVER_GU256X643900)
	fi
	AM_CONDITIONAL([HAVE_DRIVER_GU256X643900], test "$am_driver_gu256x643900" = "yes")

AC_ARG_ENABLE([driver-hd61830],
	AS_HELP_STRING(--enable-driver-hd61830,enable driver hd61830),
	[case "${enableval}" in yes | "") am_driver_hd61830=yes ;; no) am_driver_hd61830=no ;; *) am_driver_hd61830=no ;; esac], [am_driver_hd61830=no])
	if test "$am_driver_hd61830" = "yes"; then
		AC_DEFINE(HAVE_DRIVER_HD61830, 1, [Define hd61830 driver])
		AC_SUBST(MY_HD61830_CPPFLAGS,-DHAVE_DRIVER_HD61830)
	fi
	AM_CONDITIONAL([HAVE_DRIVER_HD61830], test "$am_driver_hd61830" = "yes")

AC_ARG_ENABLE([driver-ili9341],
	AS_HELP_STRING(--enable-driver-ili9341,enable driver ili9341),
	[case "${enableval}" in yes | "") am_driver_ili9341=yes ;; no) am_driver_ili9341=no ;; *) am_driver_ili9341=no ;; esac], [am_driver_ili9341=no])
	if test "$am_driver_ili9341" = "yes"; then
		PKG_CHECK_MODULES([libwiringPi], [libwiringPi], [HAVE_LIBWIRINGPI=1])
		AC_DEFINE(HAVE_DRIVER_ILI9341, 1, [Define ili9341 driver])
		AC_SUBST(MY_ILI9341_CPPFLAGS,-DHAVE_DRIVER_ILI9341)
	fi
	AM_CONDITIONAL([HAVE_DRIVER_ILI9341], test "$am_driver_ili9341" = "yes")

AC_ARG_ENABLE([driver-ks0108],
	AS_HELP_STRING(--enable-driver-ks0108,enable driver ks0108),
	[case "${enableval}" in yes | "") am_driver_ks0108=yes ;; no) am_driver_ks0108=no ;; *) am_driver_ks0108=no ;; esac], [am_driver_ks0108=no])
	if test "$am_driver_ks0108" = "yes"; then
		AC_DEFINE(HAVE_DRIVER_KS0108, 1, [Define ks0108 driver])
		AC_SUBST(MY_KS0108_CPPFLAGS,-DHAVE_DRIVER_KS0108)
	fi
	AM_CONDITIONAL([HAVE_DRIVER_KS0108], test "$am_driver_ks0108" = "yes")

AC_ARG_ENABLE([driver-noritake800],
	AS_HELP_STRING(--enable-driver-noritake800,enable driver noritake800),
	[case "${enableval}" in yes | "") am_driver_noritake800=yes ;; no) am_driver_noritake800=no ;; *) am_driver_noritake800=no ;; esac], [am_driver_noritake800=no])
	if test "$am_driver_noritake800" = "yes"; then
		AC_DEFINE(HAVE_DRIVER_NORITAKE800, 1, [Define noritake800 driver])
		AC_SUBST(MY_NORITAKE800_CPPFLAGS,-DHAVE_DRIVER_NORITAKE800)
	fi
	AM_CONDITIONAL([HAVE_DRIVER_NORITAKE800], test "$am_driver_noritake800" = "yes")

AC_ARG_ENABLE([driver-picolcd256x64],
 	AS_HELP_STRING(--enable-driver-picolcd256x64,enable driver picolcd256x64),
 	[case "${enableval}" in yes | "") am_driver_picolcd256x64=yes ;; no) am_driver_picolcd256x64=no ;; *) am_driver_picolcd256x64=no ;; esac], [am_driver_picolcd256x64=no])
	if test "$am_driver_picolcd256x64" = "yes"; then
		PKG_CHECK_MODULES([libusb], [libusb], [HAVE_LIBUSB=1])
		AC_DEFINE(HAVE_DRIVER_PICOLCD256X64, 1, [Define picolcd256x64 driver])
		AC_SUBST(MY_PICOLCD256X64_CPPFLAGS,-DHAVE_DRIVER_PICOLCD256X64)
	fi
	AM_CONDITIONAL([HAVE_DRIVER_PICOLCD256X64], test "$am_driver_picolcd256x64" = "yes")

AC_ARG_ENABLE([driver-sed1330],
	AS_HELP_STRING(--enable-driver-sed1330,enable driver sed1330),
	[case "${enableval}" in yes | "") am_driver_sed1330=yes ;; no) am_driver_sed1330=no ;; *) am_driver_sed1330=no ;; esac], [am_driver_sed1330=no])
	if test "$am_driver_sed1330" = "yes"; then
		AC_DEFINE(HAVE_DRIVER_SED1330, 1, [Define sed1330 driver])
		AC_SUBST(MY_SED1330_CPPFLAGS,-DHAVE_DRIVER_SED1330)
	fi
	AM_CONDITIONAL([HAVE_DRIVER_SED1330], test "$am_driver_sed1330" = "yes")

AC_ARG_ENABLE([driver-sed1520],
	AS_HELP_STRING(--enable-driver-sed1520,enable driver sed1520),
	[case "${enableval}" in yes | "") am_driver_sed1520=yes ;; no) am_driver_sed1520=no ;; *) am_driver_sed1520=no ;; esac], [am_driver_sed1520=no])
	if test "$am_driver_sed1520" = "yes"; then
		AC_DEFINE(HAVE_DRIVER_SED1520, 1, [Define sed1520 driver])
		AC_SUBST(MY_SED1520_CPPFLAGS,-DHAVE_DRIVER_SED1520)
	fi
	AM_CONDITIONAL([HAVE_DRIVER_SED1520], test "$am_driver_sed1520" = "yes")

AC_ARG_ENABLE([driver-simlcd],
        AS_HELP_STRING(--enable-driver-simlcd,enable driver simlcd),
        [case "${enableval}" in yes | "") am_driver_simlcd=yes ;; no) am_driver_simlcd=no ;; *) am_driver_simlcd=no ;; esac], [am_driver_simlcd=no])
	if test "$am_driver_simlcd" = "yes"; then
		AC_DEFINE(HAVE_DRIVER_SIMLCD, 1, [Define simlcd driver])
		AC_SUBST(MY_SIMLCD_CPPFLAGS,-DHAVE_DRIVER_SIMLCD)
	fi
	AM_CONDITIONAL([HAVE_DRIVER_SIMLCD], test "$am_driver_simlcd" = "yes")

AC_ARG_ENABLE([driver-st7565rreel],
	AS_HELP_STRING(--enable-driver-st7565rreel,enable driver st7565rreel),
	[case "${enableval}" in yes | "") am_driver_st7565rreel=yes ;; no) am_driver_st7565rreel=no ;; *) am_driver_st7565rreel=no ;; esac], [am_driver_st7565rreel=no])
	if test "$am_driver_st7565rreel" = "yes"; then
		AC_DEFINE(HAVE_DRIVER_ST7565RREEL, 1, [Define st7565rreel driver])
		AC_SUBST(MY_ST7565RREEL_CPPFLAGS,-DHAVE_DRIVER_ST7565RREEL)
	fi
	AM_CONDITIONAL([HAVE_DRIVER_ST7565RREEL], test "$am_driver_st7565rreel" = "yes")

AC_ARG_ENABLE([driver-ssd1306],
 	AS_HELP_STRING(--enable-driver-ssd1306,enable driver ssd1306),
 	[case "${enableval}" in yes | "") am_driver_ssd1306=yes ;; no) am_driver_ssd1306=no ;; *) am_driver_ssd1306=no ;; esac], [am_driver_ssd1306=no])
	if test "$am_driver_ssd1306" = "yes"; then
		PKG_CHECK_MODULES([libwiringPi], [libwiringPi], [HAVE_LIBWIRINGPI=1])
		AC_DEFINE(HAVE_DRIVER_SSD1306, 1, [Define ssd1306 driver])
		AC_SUBST(MY_SSD1306_CPPFLAGS,-DHAVE_DRIVER_SSD1306)
	fi
	AM_CONDITIONAL([HAVE_DRIVER_SSD1306], test "$am_driver_ssd1306" = "yes")

AC_ARG_ENABLE([driver-ssd1322ftdi],
 	AS_HELP_STRING(--enable-driver-ssd1322ftdi,enable driver ssd1322ftdi),
 	[case "${enableval}" in yes | "") am_driver_ssd1322ftdi=yes ;; no) am_driver_ssd1322ftdi=no ;; *) am_driver_ssd1322ftdi=yes ;; esac], [am_driver_ssd1322ftdi=no])
	if test "$am_driver_ssd1322ftdi" = "yes"; then
		PKG_CHECK_MODULES([libftdi1], [libftdi1], [HAVE_LIBFTDI=1])
		AC_DEFINE(HAVE_DRIVER_SSD1322FTDI, 1, [Define ssd1322ftdi driver])
		AC_SUBST(MY_SSD1322FTDI_CPPFLAGS,-DHAVE_DRIVER_SSD1322FTDI)
	fi
	AM_CONDITIONAL([HAVE_DRIVER_SSD1322FTDI], test "$am_driver_ssd1322ftdi" = "yes")

AC_ARG_ENABLE([driver-t6963c],
	AS_HELP_STRING(--enable-driver-t6963c,enable driver t6963c),
	[case "${enableval}" in yes | "") am_driver_t6963c=yes ;; no) am_driver_t6963c=no ;; *) am_driver_t6963c=no ;; esac], [am_driver_t6963c=no])
	if test "$am_driver_t6963c" = "yes"; then
		AC_DEFINE(HAVE_DRIVER_T6963C, 1, [Define t6963c driver])
		AC_SUBST(MY_T6963C_CPPFLAGS,-DHAVE_DRIVER_T6963C)
	fi
	AM_CONDITIONAL([HAVE_DRIVER_T6963C], test "$am_driver_t6963c" = "yes")

AC_ARG_ENABLE([driver-vuplus4k],
	AS_HELP_STRING(--enable-driver-vuplus4k,enable driver vuplus4k),
	[case "${enableval}" in yes | "") am_driver_vuplus4k=yes ;; no) am_driver_vuplus4k=no ;; *) am_driver_vuplus4k=yes ;; esac], [am_driver_vuplus4k=no])
	if test "$am_driver_vuplus4k" = "yes"; then
		AC_DEFINE(HAVE_DRIVER_VUPLUS4K, 1, [Define vuplus4k driver])
		AC_SUBST(MY_VUPLUS4K_CPPFLAGS,-DHAVE_DRIVER_VUPLUS4K)
	fi
	AM_CONDITIONAL([HAVE_DRIVER_VUPLUS4K], test "$am_driver_vuplus4k" = "yes")

AC_ARG_ENABLE([driver_vncserver],
	AS_HELP_STRING(--enable-driver-vncserver,enable usage of vncserver),
	[case "${enableval}" in yes | "") am_driver_vncserver=yes ;; no) am_driver_vncserver=no ;; *) am_driver_vncserver=yes ;; esac], [am_driver_vncserver=no])
	if test "$am_driver_vncserver" = "yes"; then
		PKG_CHECK_MODULES([libvncserver], [libvncserver], [HAVE_LIBVNCSERVER=1])
		AC_DEFINE(HAVE_DRIVER_VNCSERVER, 1, [Define vncserver driver])
		AC_SUBST(MY_VNCSERVER_CPPFLAGS,-DHAVE_DRIVER_VNCSERVER)
	fi
	AM_CONDITIONAL([HAVE_DRIVER_VNCSERVER], test "$am_driver_vncserver" = "yes")

CXXFLAGS="$CXXFLAGS -Wall -Woverloaded-virtual -fPIC -D_GNU_SOURCE"
dnl CXXFLAGS="$CXXFLAGS -MMD"


AC_OUTPUT([
Makefile \
glcdgraphics/Makefile \
glcdgraphics/libglcdgraphics.pc \
glcddrivers/Makefile \
glcddrivers/libglcddrivers.pc \
glcdskin/Makefile \
glcdskin/libglcdskin.pc \
tools/Makefile \
tools/convpic/Makefile \
tools/crtfont/Makefile \
tools/genfont/Makefile \
tools/lcdtestpattern/Makefile \
tools/showpic/Makefile \
tools/showtext/Makefile \
tools/skintest/Makefile \
])


