/*
 * GraphLCD graphics library
 *
 * extformats.c  -  loading and saving of external formats (via ImageMagick)
 *
 * based on bitmap.[ch] from text2skin: http://projects.vdr-developer.org/projects/show/plg-text2skin
 *
 * This file is released under the GNU General Public License. Refer
 * to the COPYING file distributed with this package.
 *
 * (c) 2011-2013 Wolfgang Astleitner <mrwastl AT users sourceforge net>
 */

#include <stdio.h>
#include <stdint.h>
#include <syslog.h>

#include <cstring>

#include "bitmap.h"
#include "extformats.h"
#include "image.h"

#ifdef HAVE_IMAGEMAGICK
#include <Magick++.h>
//#elif defined(HAVE_IMLIB2)
//#include "quantize.h"
//#include <Imlib2.h>
#endif


namespace GLCD
{

using namespace std;


cExtFormatFile::cExtFormatFile()
{
#ifdef HAVE_IMAGEMAGICK
  Magick::InitializeMagick(NULL);
#endif    
}

cExtFormatFile::~cExtFormatFile()
{
}

bool cExtFormatFile::Load(cImage & image, const string & fileName)
{
    uint16_t scalew = 0;
    uint16_t scaleh = 0;
    return LoadScaled(image, fileName, scalew, scaleh);
}

bool cExtFormatFile::LoadScaled(cImage & image, const string & fileName, uint16_t & scalew, uint16_t & scaleh)
{
#ifdef HAVE_IMAGEMAGICK
  std::vector<Magick::Image> extimages;
  try {
    uint16_t width = 0;
    uint16_t height = 0;
    //uint16_t count;
    uint32_t delay;

    std::vector<Magick::Image>::iterator it;
    readImages(&extimages, fileName);
    if (extimages.size() == 0) {
      syslog(LOG_ERR, "glcdgraphics: Couldn't load '%s' (cExtFormatFile::LoadScaled)", fileName.c_str());
      return false;
    }

    delay = (uint32_t)(extimages[0].animationDelay() * 10);

    image.Clear();
    image.SetDelay(delay);

    bool firstImage = true;

    for (it = extimages.begin(); it != extimages.end(); ++it) {
      bool ignoreImage = false;

      //(*it).quantizeColorSpace( Magick::RGBColorspace );
      //(*it).quantizeColors( 256*256*256 /*colors*/ );
      //(*it).quantize();

      if (firstImage) {
        width = (uint16_t)((*it).columns());
        height = (uint16_t)((*it).rows());
        firstImage = false;

        // one out of scalew/h == 0 ? -> auto aspect ratio
        if (scalew && ! scaleh) {
          scaleh = (uint16_t)( ((uint32_t)scalew * (uint32_t)height) / (uint32_t)width );
        } else if (!scalew && scaleh) {
          scalew = (uint16_t)( ((uint32_t)scaleh * (uint32_t)width) / (uint32_t)height );
        }

        // scale image
        if (scalew && ! (scalew == width && scaleh == height)) {
          (*it).sample(Magick::Geometry(scalew, scaleh));
          width = scalew;
          height = scaleh;
        } else {
          // not scaled => reset to 0
          scalew = 0;
          scaleh = 0;
        }

        image.SetWidth(width);
        image.SetHeight(height);
      } else {
        if (scalew && scaleh) {
          (*it).sample(Magick::Geometry(scalew, scaleh));
        } else 
        if ( (width != (uint16_t)((*it).columns())) || (height != (uint16_t)((*it).rows())) ) {
          ignoreImage = true;
        }
      }

      if (! ignoreImage) {
        /*
        if ((*it).depth() > 8) {
          esyslog("ERROR: text2skin: More than 8bpp images are not supported");
          return false;
        }
        */
        uint32_t * bmpdata = new uint32_t[height * width];
        //Dprintf("this image has %d colors\n", (*it).totalColors());

        bool isMatte = (*it).matte();
        //bool isMonochrome = ((*it).totalColors() <= 2) ? true : false;
        const Magick::PixelPacket *pix = (*it).getConstPixels(0, 0, (int)width, (int)height);

        for (int iy = 0; iy < (int)height; ++iy) {
          for (int ix = 0; ix < (int)width; ++ix) {
            if ( isMatte && Magick::Color::scaleQuantumToDouble(pix->opacity) * 255 == 255 ) {
                bmpdata[iy*width+ix] = cColor::Transparent;
            } else {
                bmpdata[iy*width+ix] = (uint32_t)(
                                        (uint32_t(255 - (Magick::Color::scaleQuantumToDouble(pix->opacity) * 255)) << 24)  |
                                        (uint32_t( Magick::Color::scaleQuantumToDouble(pix->red) * 255) << 16) |
                                        (uint32_t( Magick::Color::scaleQuantumToDouble(pix->green) * 255) << 8) |
                                         uint32_t( Magick::Color::scaleQuantumToDouble(pix->blue) * 255)
                                       );
                //if ( isMonochrome ) {  // if is monochrome: exchange black and white
                //    uint32_t c = bmpdata[iy*width+ix];
                //    switch(c) {
                //        case cColor::White: c = cColor::Black; break;
                //        case cColor::Black: c = cColor::White; break;
                //    }
                //    bmpdata[iy*width+ix] =  c;
                //}
            }
            ++pix;
          }
        }
        cBitmap * b = new cBitmap(width, height, bmpdata);
        //b->SetMonochrome(isMonochrome);
        image.AddBitmap(b);
        delete[] bmpdata;
        bmpdata = NULL;
      }
    }
  } catch (Magick::Exception &e) {
    syslog(LOG_ERR, "glcdgraphics: Couldn't load '%s': %s (cExtFormatFile::LoadScaled)", fileName.c_str(), e.what());
    return false;
  } catch (...) {
    syslog(LOG_ERR, "glcdgraphics: Couldn't load '%s': Unknown exception caught (cExtFormatFile::LoadScaled)", fileName.c_str());
    return false;
  }
  return true;
#else
  return false;
#endif
}

// to be done ...
bool cExtFormatFile::Save(cImage & image, const string & fileName)
{
  return false;
}

} // end of namespace
