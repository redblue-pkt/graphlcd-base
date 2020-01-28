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
  AM_CONDITIONAL([HAVE_DRIVER_AVRCTL], test "$am_driver_avrctl" = "yes")
	
AC_ARG_ENABLE([driver-ax206dpf],
 	AS_HELP_STRING(--enable-driver-ax206dpf,enable driver ax206dpf),
 	[case "${enableval}" in yes | "") am_driver_ax206dpf=yes ;; no) am_driver_ax206dpf=no ;; *) am_driver_ax206dpf=no ;; esac], [am_driver_ax206dpf=no])
  if test "$am_driver_ax206dpf" = "yes"; then
    PKG_CHECK_MODULES([libusb], [libusb], [HAVE_LIBUSB=1])
  fi
  AM_CONDITIONAL([HAVE_DRIVER_AX206DPF], test "$am_driver_ax206dpf" = "yes")

AC_ARG_ENABLE([driver-dm140gink],
	AS_HELP_STRING(--enable-driver-dm140gink,enable driver dm140gink),
	[case "${enableval}" in yes | "") am_driver_dm140gink=yes ;; no) am_driver_dm140gink=no ;; *) am_driver_dm140gink=no ;; esac], [am_driver_dm140gink=no])
  AM_CONDITIONAL([HAVE_DRIVER_DM140GINK], test "$am_driver_dm140gink" = "yes")

AC_ARG_ENABLE([driver-framebuffer],
	AS_HELP_STRING(--enable-driver-framebuffer,enable driver framebuffer),
	[case "${enableval}" in yes | "") am_driver_framebuffer=yes ;; no) am_driver_framebuffer=no ;; *) am_driver_framebuffer=no ;; esac], [am_driver_framebuffer=no])
  AM_CONDITIONAL([HAVE_DRIVER_FRAMEBUFFER], test "$am_driver_framebuffer" = "yes")

AC_ARG_ENABLE([driver-futabamdm166a],
	AS_HELP_STRING(--enable-driver-futabamdm166a,enable driver futabamdm166a),
	[case "${enableval}" in yes | "") am_driver_futabamdm166a=yes ;; no) am_driver_futabamdm166a=no ;; *) am_driver_futabamdm166a=no ;; esac], [am_driver_futabamdm166a=no])
  if test "$am_driver_futabamdm166a" = "yes"; then
    PKG_CHECK_MODULES([libhid], [libhid], [HAVE_LIBHID=1])
  fi
  AM_CONDITIONAL([HAVE_DRIVER_FUTABAMDM166A], test "$am_driver_futabamdm166a" = "yes")

AC_ARG_ENABLE([driver-g15daemon],
	AS_HELP_STRING(--enable-driver-g15daemon,enable driver g15daemon),
	[case "${enableval}" in yes | "") am_driver_g15daemon=yes ;; no) am_driver_g15daemon=no ;; *) am_driver_g15daemon=no ;; esac], [am_driver_g15daemon=no])
  AM_CONDITIONAL([HAVE_DRIVER_G15DAEMON], test "$am_driver_g15daemon" = "yes")

AC_ARG_ENABLE([driver-gu140x32f],
	AS_HELP_STRING(--enable-driver-gu140x32f,enable driver gu140x32f),
	[case "${enableval}" in yes | "") am_driver_gu140x32f=yes ;; no) am_driver_gu140x32f=no ;; *) am_driver_gu140x32f=no ;; esac], [am_driver_gu140x32f=no])
  AM_CONDITIONAL([HAVE_DRIVER_GU140X32F], test "$am_driver_gu140x32f" = "yes")

AC_ARG_ENABLE([driver-gu126x64dk610a4],
	AS_HELP_STRING(--enable-driver-gu126x64dk610a4,enable driver gu126x64dk610a4),
	[case "${enableval}" in yes | "") am_driver_gu126x64dk610a4=yes ;; no) am_driver_gu126x64dk610a4=no ;; *) am_driver_gu126x64dk610a4=no ;; esac], [am_driver_gu126x64dk610a4=no])
  AM_CONDITIONAL([HAVE_DRIVER_GU126X64DK610A4], test "$am_driver_gu126x64dk610a4" = "yes")

AC_ARG_ENABLE([driver-gu256x64372],
	AS_HELP_STRING(--enable-driver-gu256x64372,enable driver gu256x64372),
	[case "${enableval}" in yes | "") am_driver_gu256x64372=yes ;; no) am_driver_gu256x64372=no ;; *) am_driver_gu256x64372=no ;; esac], [am_driver_gu256x64372=no])
  AM_CONDITIONAL([HAVE_DRIVER_GU256X64372], test "$am_driver_gu256x64372" = "yes")

AC_ARG_ENABLE([driver-gu256x643900],
	AS_HELP_STRING(--enable-driver-gu256x643900,enable driver gu256x643900),
	[case "${enableval}" in yes | "") am_driver_gu256x643900=yes ;; no) am_driver_gu256x643900=no ;; *) am_driver_gu256x643900=no ;; esac], [am_driver_gu256x643900=no])
  AM_CONDITIONAL([HAVE_DRIVER_GU256X643900], test "$am_driver_gu256x643900" = "yes")

AC_ARG_ENABLE([driver-hd61830],
	AS_HELP_STRING(--enable-driver-hd61830,enable driver hd61830),
	[case "${enableval}" in yes | "") am_driver_hd61830=yes ;; no) am_driver_hd61830=no ;; *) am_driver_hd61830=no ;; esac], [am_driver_hd61830=no])
  AM_CONDITIONAL([HAVE_DRIVER_HD61830], test "$am_driver_hd61830" = "yes")

AC_ARG_ENABLE([driver-ili9341],
	AS_HELP_STRING(--enable-driver-ili9341,enable driver ili9341),
	[case "${enableval}" in yes | "") am_driver_ili9341=yes ;; no) am_driver_ili9341=no ;; *) am_driver_ili9341=no ;; esac], [am_driver_ili9341=no])
  if test "$am_driver_ili9341" = "yes"; then
    PKG_CHECK_MODULES([libwiringPi], [libwiringPi], [HAVE_LIBWIRINGPI=1])
  fi
  AM_CONDITIONAL([HAVE_DRIVER_ILI9341], test "$am_driver_ili9341" = "yes")

AC_ARG_ENABLE([driver-ks0108],
	AS_HELP_STRING(--enable-driver-ks0108,enable driver ks0108),
	[case "${enableval}" in yes | "") am_driver_ks0108=yes ;; no) am_driver_ks0108=no ;; *) am_driver_ks0108=no ;; esac], [am_driver_ks0108=no])
  AM_CONDITIONAL([HAVE_DRIVER_KS0108], test "$am_driver_ks0108" = "yes")

AC_ARG_ENABLE([driver-noritake800],
	AS_HELP_STRING(--enable-driver-noritake800,enable driver noritake800),
	[case "${enableval}" in yes | "") am_driver_noritake800=yes ;; no) am_driver_noritake800=no ;; *) am_driver_noritake800=no ;; esac], [am_driver_noritake800=no])
  AM_CONDITIONAL([HAVE_DRIVER_NORITAKE800], test "$am_driver_noritake800" = "yes")

AC_ARG_ENABLE([driver-picolcd256x64],
 	AS_HELP_STRING(--enable-driver-picolcd256x64,enable driver picolcd256x64),
 	[case "${enableval}" in yes | "") am_driver_picolcd256x64=yes ;; no) am_driver_picolcd256x64=no ;; *) am_driver_picolcd256x64=no ;; esac], [am_driver_picolcd256x64=no])
  if test "$am_driver_pico256x64" = "yes"; then
    PKG_CHECK_MODULES([libusb], [libusb], [HAVE_LIBUSB=1])
  fi
  AM_CONDITIONAL([HAVE_DRIVER_PICOLCD256X64], test "$am_driver_picolcd256x64" = "yes")

AC_ARG_ENABLE([driver-sed1330],
	AS_HELP_STRING(--enable-driver-sed1330,enable driver sed1330),
	[case "${enableval}" in yes | "") am_driver_sed1330=yes ;; no) am_driver_sed1330=no ;; *) am_driver_sed1330=no ;; esac], [am_driver_sed1330=no])
  AM_CONDITIONAL([HAVE_DRIVER_SED1330], test "$am_driver_sed1330" = "yes")

AC_ARG_ENABLE([driver-sed1520],
	AS_HELP_STRING(--enable-driver-sed1520,enable driver sed1520),
	[case "${enableval}" in yes | "") am_driver_sed1520=yes ;; no) am_driver_sed1520=no ;; *) am_driver_sed1520=no ;; esac], [am_driver_sed1520=no])
  AM_CONDITIONAL([HAVE_DRIVER_SED1520], test "$am_driver_sed1520" = "yes")

AC_ARG_ENABLE([driver-simlcd],
        AS_HELP_STRING(--enable-driver-simlcd,enable driver simlcd),
        [case "${enableval}" in yes | "") am_driver_simlcd=yes ;; no) am_driver_simlcd=no ;; *) am_driver_simlcd=no ;; esac], [am_driver_simlcd=no])
  AM_CONDITIONAL([HAVE_DRIVER_SIMLCD], test "$am_driver_simlcd" = "yes")

AC_ARG_ENABLE([driver-st7565rreel],
	AS_HELP_STRING(--enable-driver-st7565rreel,enable driver st7565rreel),
	[case "${enableval}" in yes | "") am_driver_st7565rreel=yes ;; no) am_driver_st7565rreel=no ;; *) am_driver_st7565rreel=no ;; esac], [am_driver_st7565rreel=no])
  AM_CONDITIONAL([HAVE_DRIVER_ST7565RREEL], test "$am_driver_st7565rreel" = "yes")

AC_ARG_ENABLE([driver-ssd1306],
 	AS_HELP_STRING(--enable-driver-ssd1306,enable driver ssd1306),
 	[case "${enableval}" in yes | "") am_driver_ssd1306=yes ;; no) am_driver_ssd1306=no ;; *) am_driver_ssd1306=no ;; esac], [am_driver_ssd1306=no])
  if test "$am_driver_ssd1306" = "yes"; then
    PKG_CHECK_MODULES([libwiringPi], [libwiringPi], [HAVE_LIBWIRINGPI=1])
  fi
  AM_CONDITIONAL([HAVE_DRIVER_SSD1306], test "$am_driver_ssd1306" = "yes")

AC_ARG_ENABLE([driver-ssd1322ftdi],
 	AS_HELP_STRING(--enable-driver-ssd1322ftdi,enable driver ssd1322ftdi),
 	[case "${enableval}" in yes | "") am_driver_ssd1322ftdi=yes ;; no) am_driver_ssd1322ftdi=no ;; *) am_driver_ssd1322ftdi=yes ;; esac], [am_driver_ssd1322ftdi=no])
  if test "$am_driver_ssd1322ftdi" = "yes"; then
    PKG_CHECK_MODULES([libftdi1], [libftdi1], [HAVE_LIBFTDI=1])
  fi
  AM_CONDITIONAL([HAVE_DRIVER_SSD1322FTDI], test "$am_driver_ssd1322ftdi" = "yes")

AC_ARG_ENABLE([driver-t6963c],
	AS_HELP_STRING(--enable-driver-t6963c,enable driver t6963c),
	[case "${enableval}" in yes | "") am_driver_t6963c=yes ;; no) am_driver_t6963c=no ;; *) am_driver_t6963c=no ;; esac], [am_driver_t6963c=no])
  AM_CONDITIONAL([HAVE_DRIVER_T6963C], test "$am_driver_t6963c" = "yes")

AC_ARG_ENABLE([driver-vuplus4k],
	AS_HELP_STRING(--enable-driver-vuplus4k,enable driver vuplus4k),
	[case "${enableval}" in yes | "") am_driver_vuplus4k=yes ;; no) am_driver_vuplus4k=no ;; *) am_driver_vuplus4k=yes ;; esac], [am_driver_vuplus4k=no])
  AM_CONDITIONAL([HAVE_DRIVER_VUPLUS4K], test "$am_driver_vuplus4k" = "yes")

AC_ARG_ENABLE([driver_vncserver],
	AS_HELP_STRING(--enable-driver-vncserver,enable usage of vncserver),
	[case "${enableval}" in yes | "") am_driver_vncserver=yes ;; no) am_driver_vncserver=no ;; *) am_driver_vncserver=yes ;; esac], [am_driver_vncserver=no])
  if test "$am_driver_vncserver" = "yes"; then
    PKG_CHECK_MODULES([libvncserver], [libvncserver], [HAVE_LIBVNCSERVER=1])
    AS_IF([test "$HAVE_LIBVNCSERVER" = 1], [AC_SUBST(MY_VNCSERVER_CPPFLAGS,-DHAVE_VNCSERVER)])
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


