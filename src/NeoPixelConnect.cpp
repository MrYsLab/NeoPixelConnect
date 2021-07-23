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

#include <NeoPixelConnect.h>

/// @brief Constructor
/// @param pinNumber: GPIO pin that controls the NeoPixel string.
/// @param numberOfPixels: Number of pixels in the string
NeoPixelConnect::NeoPixelConnect(byte pinNumber, byte numberOfPixels){
    uint offset = pio_add_program(pixelPio, &ws2812_program);
    ws2812_program_init(pixelPio, 0, offset, pinNumber, 800000,
                false);

    // save the number of pixels in use
    this->actual_number_of_pixels = numberOfPixels;

    // set the pixels to the fill color
    for (int i = 0; i < this->actual_number_of_pixels; i++) {
        this->pixelBuffer[i][RED] = 0;
        this->pixelBuffer[i][GREEN] = 0;
        this->pixelBuffer[i][BLUE] = 0;
    }

    // show the pixels
    this->neoPixelShow();
    delay(1);

}

/// @brief Set a NeoPixel to a given color. By setting autoShow to true, change is
/// displayed immediately.
/// @param pixelNumber: set a color for a specific neopixel in the string
/// @param r: red value (0-255)
/// @param g: green value(0-255)
/// @param b: blue value (0-255)
/// @param autoShow: If true, show the change immediately.
void NeoPixelConnect::neoPixelSetValue(uint8_t pixelNumber, uint8_t r, uint8_t g, uint8_t b, bool autoShow){
    this->pixelBuffer[pixelNumber][RED] = r;
    this->pixelBuffer[pixelNumber][GREEN] = g;
    this->pixelBuffer[pixelNumber][BLUE] = b;
    if (autoShow) {
        this->neoPixelShow();
    }
}

/// @brief Set all the pixels to "off".
/// @param autoShow: If true, show the change immeditelty
void NeoPixelConnect::neoPixelClear(bool autoShow){
    // set all the neopixels in the buffer to all zeroes
    for (int i = 0; i < this->actual_number_of_pixels; i++) {
        this->pixelBuffer[i][RED] = 0;
        this->pixelBuffer[i][GREEN] = 0;
        this->pixelBuffer[i][BLUE] = 0;
    }
    if (autoShow) {
        this->neoPixelShow();
    }

}

/// @brief Fill all the pixels with same value
/// @param r: red value (0-255)
/// @param g: green value(0-255)
/// @param b: blue value (0-255)
/// @param autoShow: If true, show the change immediately.
void NeoPixelConnect::neoPixelFill(uint8_t r, uint8_t g, uint8_t b, bool autoShow){
    // fill all the neopixels in the buffer with the
    // specified rgb values.
    for (int i = 0; i < this->actual_number_of_pixels; i++) {
        this->pixelBuffer[i][RED] = r;
        this->pixelBuffer[i][GREEN] = g;
        this->pixelBuffer[i][BLUE] = b;
    }
    if (autoShow) {
        this->neoPixelShow();
    }

}

/// @brief Display all the pixels in the buffer
void NeoPixelConnect::neoPixelShow(void){
    // show the neopixels in the buffer
    for (int i = 0; i < this->actual_number_of_pixels; i++) {
        this->putPixel(urgb_u32(pixelBuffer[i][RED],
                           pixelBuffer[i][GREEN],
                           pixelBuffer[i][BLUE]));
    }
}