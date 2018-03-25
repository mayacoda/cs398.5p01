#ifndef __bmp_h__
#define __bmp_h__


#ifdef _WIN32
#include <gl/glut.h>

#include <windows.h> //the windows include file, required by all windows applications
// Bitmap file data structures are defined in <wingdi.h> under Windows
#include <wingdi.h>

#elif __APPLE__

#include <GLUT/glut.h>

// The following may not be defined in your compiler includes if you are not on Windows

#define BI_RGB 0
#define BI_RLE8 1
#define BI_RLE4 2
#define BI_BITFIELDS 3

inline unsigned short FlipWORD(unsigned short in) {
    return ((in >> 8) | (in << 8));
}

inline unsigned int FlipDWORD(unsigned int in) {
    return (((in & 0xFF000000) >> 24) | ((in & 0x000000FF) << 24) |
            ((in & 0x00FF0000) >> 8) | ((in & 0x0000FF00) << 8));
}

class BITMAPFILEHEADER {
public:
    unsigned short bfType;
    unsigned int   bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int   bfOffBits;

    void SwitchEndianess() {
        bfType      = FlipWORD(bfType);
        bfSize      = FlipDWORD(bfSize);
        bfReserved1 = FlipWORD(bfReserved1);
        bfReserved2 = FlipWORD(bfReserved2);
        bfOffBits   = FlipDWORD(bfOffBits);
        return;
    }

    BITMAPFILEHEADER() {}
};


class BITMAPINFOHEADER {
public:
    unsigned int   biSize;
    unsigned int   biWidth;
    unsigned int   biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int   biCompression;
    unsigned int   biSizeImage;
    unsigned int   biXPelsPerMeter;
    unsigned int   biYPelsPerMeter;
    unsigned int   biClrUsed;
    unsigned int   biClrImportant;

    void SwitchEndianess() {
        biSize          = FlipDWORD(biSize);
        biWidth         = FlipDWORD(biWidth);
        biHeight        = FlipDWORD(biHeight);
        biPlanes        = FlipWORD(biPlanes);
        biBitCount      = FlipWORD(biBitCount);
        biCompression   = FlipDWORD(biCompression);
        biSizeImage     = FlipDWORD(biSizeImage);
        biXPelsPerMeter = FlipDWORD(biXPelsPerMeter);
        biYPelsPerMeter = FlipDWORD(biYPelsPerMeter);
        biClrUsed       = FlipDWORD(biClrUsed);
        biClrImportant  = FlipDWORD(biClrImportant);
    }

    BITMAPINFOHEADER() {

    }
};

struct tRGBQUAD {
    unsigned char rgbBlue;
    unsigned char rgbGreen;
    unsigned char rgbRed;
    unsigned char rgbReserved;
};

struct BITMAPINFO {
    BITMAPINFOHEADER bmiHeader;
    tRGBQUAD         bmiColors[1];
};

typedef unsigned char  ebmpBYTE;
typedef unsigned short ebmpWORD;
typedef unsigned int   ebmpDWORD;


/**
 * Checks the endianness of the machine
 * @return bool
 */
inline bool IsBigEndian() {
    short word = 0x0001;
    return (*(char*) &word) != 0x01;
}


#endif


extern GLubyte* ReadBitmap(const char* filename, BITMAPINFO** info);

#endif