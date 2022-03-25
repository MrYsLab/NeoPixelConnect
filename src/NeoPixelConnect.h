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
    /// @brief Constructor
    /// @param pinNumber: GPIO pin that controls the NeoPixel string.
    /// @param numberOfPixels: Number of pixels in the string
    /// @param pio: pio selected - default = pio0. pio1 may be specified
    /// @param sm: state machine selected. Default = 0
    NeoPixelConnect(byte pinNumber, byte numberOfPixels, PIO pio, uint sm);

    /// @brief Constructor
    /// @param pinNumber: GPIO pin that controls the NeoPixel string.
    /// @param numberOfPixels: Number of pixels in the string
    /// This construcor sets pio=pio0 and sm to 0
    NeoPixelConnect(byte pinNumber, byte numberOfPixels);

    /// @brief Destructor
    virtual ~NeoPixelConnect(){};

    ///@brief Initialize the class instance after calling constructor
    /// @param pinNumber: GPIO pin that controls the NeoPixel string.
    /// @param numberOfPixels: Number of pixels in the string
    void neoPixelInit(byte pinNumber, byte numberOfPixels);

    /// @brief Set a NeoPixel to a given color. By setting autoShow to true, change is
    /// displayed immediately.
    /// @param pixelNumber: set a color for a specific neopixel in the string
    /// @param r: red value (0-255)
    /// @param g: green value(0-255)
    /// @param b: blue value (0-255)
    /// @param autoShow: If true, show the change immediately.
    void neoPixelSetValue(uint8_t pixel_number, uint8_t r=0, uint8_t g=0, uint8_t b=0, bool autoShow=false);

    /// @brief Set all the pixels to "off".
    /// @param autoShow: If true, show the change immediately
    // set all pixels to 0
    void neoPixelClear(bool autoShow=true);

    /// @brief Fill all the pixels with same value
    /// @param r: red value (0-255)
    /// @param g: green value(0-255)
    /// @param b: blue value (0-255)
    /// @param autoShow: If true, show the change immediately.
    void neoPixelFill(uint8_t r=0, uint8_t g=0, uint8_t b=0, bool autoShow=true);

    /// @brief Display all the pixels in the buffer
    void neoPixelShow(void);

private:
    // pio - 0 or 1
    PIO pixelPio = pio0;

    // calculated program offset in memory
    uint pixelOffset;

    // pio state machine to use
    uint pixelSm = 0;

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
