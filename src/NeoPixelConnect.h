/*
 Copyright (c) 2020-2021 Alan Yorinks All rights reserved.

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU AFFERO GENERAL PUBLIC LICENSE
 Version 3 as published by the Free Software Foundation; either
 or (at your option) any later version.
 This library is distributed in the hope that it will be useful,f
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 General Public License for more details.

 You should have received a copy of the GNU AFFERO GENERAL PUBLIC LICENSE
 along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef NEOPIXEL_CONNECT_NEOPIXELCONNECT_H
#define NEOPIXEL_CONNECT_NEOPIXELCONNECT_H

#include <Arduino.h>
#include"stdio.h"
#include <stdlib.h>

#include "hardware/pio.h"
#include "hardware/dma.h"
#include "hardware/clocks.h"
#include "hardware/gpio.h"

#include "ws2812.pio.h"

#define MAXIMUM_NUM_NEOPIXELS 150

// Pixel buffer array offsets
#define RED 0
#define GREEN 1
#define BLUE 2


class NeoPixelConnect
{
public:
    // Constructor
    NeoPixelConnect(byte pinNumber, byte numberOfPixels);

    // Destructor
    virtual ~NeoPixelConnect(){};

    // set a pixel to a specified color
    void neoPixelSetValue(uint8_t pixel_number, uint8_t r=0, uint8_t g=0, uint8_t b=0, bool autoShow=false);

    // set all pixels to 0
    void neoPixelClear(bool autoShow=true);

    // fill all pixels with a specific color
    void neoPixelFill(uint8_t r=0, uint8_t g=0, uint8_t b=0, bool autoShow=true);

    // show all the pixels
    void neoPixelShow(void);

private:
    // pio - 0 or 1
    PIO pixelPio = pio0;

    // calculated program offset in memory
    uint pixelOffset;

    // pio state machine to use
    uint pixlSm = 0;

    // number of pixels in the strip
    int actual_number_of_pixels;

    // a buffer that holds the color for each pixel
    uint8_t pixelBuffer[MAXIMUM_NUM_NEOPIXELS][3];

    // write a color to a pixel
    static inline void putPixel(uint32_t pixel_grb) {
        pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
    }

    // create a 32 bit value combining the 3 colors
    static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
        return
                ((uint32_t) (r) << 8) |
                ((uint32_t) (g) << 16) |
                (uint32_t) (b);
    }

};


#endif //NEOPIXEL_CONNECT_NEOPIXELCONNECT_H
