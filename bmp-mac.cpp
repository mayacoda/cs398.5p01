
#include "bmp-mac.h"

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>

/**
 * Reads the given number of bytes from the istream into the buffer
 *
 * @param buffer, to store the read bytes
 * @param size, size in bytes of each chunk
 * @param number, number of chunks to read
 * @param in, istream from which to read the bytes
 * @return bool, true if read correctly, false if there was a problem
 */
bool SafeFread(char* buffer, int size, int number, std::istream &in) {
    if (in.eof()) return false;
    std::streamsize bytesRequested = size * number;
    in.read(buffer, bytesRequested);

    return in.gcount() == bytesRequested;
}

/**
 * Reads bitmap data from the file into the BITMAPINFO**
 *
 * @param filename
 * @param info
 * @return
 */
GLubyte* ReadBitmap(const char* filename, BITMAPINFO** info) {
    std::ifstream fileStream;

    fileStream.open(filename, std::ios_base::binary);

    if (!fileStream.is_open()) {
        std::cout << "ReadBitmap: file cannot be opened: " << filename << std::endl;
        return nullptr;
    }

    bool NotCorrupted = true;
    BITMAPFILEHEADER header;


    NotCorrupted &= SafeFread((char*) &(header.bfType), sizeof(ebmpWORD), 1, fileStream);

    bool IsBitmap = false;

    if (IsBigEndian() and header.bfType == 16973) IsBitmap     = true;
    if (not IsBigEndian() and header.bfType == 19778) IsBitmap = true;

    if (!IsBitmap) {
        fileStream.close();
        std::cout << "ReadBitmap: not a bitmap" << std::endl;
        return nullptr;
    }

    NotCorrupted &= SafeFread((char*) &(header.bfSize), sizeof(ebmpDWORD), 1, fileStream);
    NotCorrupted &= SafeFread((char*) &(header.bfReserved1), sizeof(ebmpWORD), 1, fileStream);
    NotCorrupted &= SafeFread((char*) &(header.bfReserved2), sizeof(ebmpWORD), 1, fileStream);
    NotCorrupted &= SafeFread((char*) &(header.bfOffBits), sizeof(ebmpDWORD), 1, fileStream);

    if (IsBigEndian()) header.SwitchEndianess();

    // read the info header

    BITMAPINFOHEADER infoHeader;

    NotCorrupted &= SafeFread((char*) &(infoHeader.biSize), sizeof(ebmpDWORD), 1, fileStream);
    NotCorrupted &= SafeFread((char*) &(infoHeader.biWidth), sizeof(ebmpDWORD), 1, fileStream);
    NotCorrupted &= SafeFread((char*) &(infoHeader.biHeight), sizeof(ebmpDWORD), 1, fileStream);
    NotCorrupted &= SafeFread((char*) &(infoHeader.biPlanes), sizeof(ebmpWORD), 1, fileStream);
    NotCorrupted &= SafeFread((char*) &(infoHeader.biBitCount), sizeof(ebmpWORD), 1, fileStream);

    NotCorrupted &= SafeFread((char*) &(infoHeader.biCompression), sizeof(ebmpDWORD), 1, fileStream);
    NotCorrupted &= SafeFread((char*) &(infoHeader.biSizeImage), sizeof(ebmpDWORD), 1, fileStream);
    NotCorrupted &= SafeFread((char*) &(infoHeader.biXPelsPerMeter), sizeof(ebmpDWORD), 1, fileStream);
    NotCorrupted &= SafeFread((char*) &(infoHeader.biYPelsPerMeter), sizeof(ebmpDWORD), 1, fileStream);
    NotCorrupted &= SafeFread((char*) &(infoHeader.biClrUsed), sizeof(ebmpDWORD), 1, fileStream);
    NotCorrupted &= SafeFread((char*) &(infoHeader.biClrImportant), sizeof(ebmpDWORD), 1, fileStream);

    if (IsBigEndian()) infoHeader.SwitchEndianess();

    if (!NotCorrupted) {
        std::cout << "ReadBitmap: file is corrupted" << std::endl;
        return nullptr;
    }


    if ((*info = (BITMAPINFO*) malloc(sizeof(BITMAPINFO))) == nullptr) {
        fileStream.close();
        std::cout << "ReadBitmap: could not allocate memory for file info" << std::endl;
        return nullptr;
    }

    (*info)->bmiHeader = infoHeader;

    /* Now that we have all the header info read fileStream, allocate memory for *
     * the bitmap and read it fileStream...
     */
    int imgsize     = (*info)->bmiHeader.biSizeImage;
    // sometimes imagesize is not set fileStream files
    if (imgsize == 0)
        imgsize = static_cast<int>(((*info)->bmiHeader.biWidth *
                                    (*info)->bmiHeader.biBitCount + 7) / 8 *
                                   fabs((*info)->bmiHeader.biHeight));

    char* pixels;
    if ((pixels = (char*) malloc(imgsize)) == nullptr) {
        free(*info);
        fileStream.close();
        std::cout << "ReadBitmap: could not allocate memory for pixels" << std::endl;
        return nullptr;
    }

    int infosize = header.bfOffBits - 54;
    ebmpBYTE* TempSkipBYTE = new ebmpBYTE[infosize];

    if (!SafeFread((char*) TempSkipBYTE, infosize, 1, fileStream)) {
        fileStream.close();
        std::cout << "ReadBitmap: could not skip bfOffBits" << std::endl;
        return nullptr;
    }

    delete[] TempSkipBYTE;

    if (!SafeFread(pixels, 1, imgsize, fileStream)) {
        free(*info);
        free(pixels);
        fileStream.close();
        std::cout << "ReadBitmap: could not read pixel data from file" << std::endl;
        return nullptr;
    }

    fileStream.close();
    return reinterpret_cast<GLubyte*>(pixels);
}
