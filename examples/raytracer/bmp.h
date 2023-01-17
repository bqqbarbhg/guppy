#pragma once

struct BmpHeaderRgba
{
    char data[122] =
        // magic  size    unused   data offset    DIB size   width  height
        "" "BM"  "????" "\0\0\0\0" "\x7a\0\0\0" "\x6c\0\0\0" "????" "????" 
        // 1-plane 32-bits  bitfields    data-size     print resolution
        "" "\x1\0" "\x20\0" "\x3\0\0\0"   "????"   "\x13\xb\0\0\x13\xb\0\0"
        //   palette counts            channel masks for RGBA            colors
        "" "\0\0\0\0\0\0\0\0" "\xff\0\0\0\0\xff\0\0\0\0\xff\0\0\0\0\xff" "sRGB";
            
    BmpHeaderRgba(size_t width=0, size_t height=0) {
        size_t size = width * height * 4;
        patch(0x02, 122 + size); // total size
        patch(0x12, width);      // width (left-to-right)
        patch(0x16, 0 - height); // height (top-to-bottom)
        patch(0x22, size);       // data size
    }

    void patch(size_t offset, size_t value) {
        data[offset+0] = (char)((value >>  0) & 0xff);
        data[offset+1] = (char)((value >>  8) & 0xff);
        data[offset+2] = (char)((value >> 16) & 0xff);
        data[offset+3] = (char)((value >> 24) & 0xff);
    }
};
