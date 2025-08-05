## An Example

Let's look at the fireworks example to demonstrate using the library.

```aiignore
     1	
     2	#define MAXIMUM_NUM_NEOPIXELS 8
     3	
     4	#include <NeoPixelConnect.h>
     5	
     6	// Create an instance of NeoPixelConnect and initialize it
     7	// to use GPIO pin 4 (D12) as the control pin, for a string
     8	// of 8 neopixels. Name the instance p
     9	NeoPixelConnect p(4, MAXIMUM_NUM_NEOPIXELS, pio0, 0);
    10	
    11	// this array will hold a pixel number and the rgb values for the
    12	// randomly generated pixel values
    13	uint8_t random_pixel_setting[4];
    14	
    15	// select a random pixel number in the string
    16	uint8_t get_pixel_number(){
    17	    return((uint16_t)random(0,MAXIMUM_NUM_NEOPIXELS - 1));
    18	}
    19	
    20	// select a random intensity
    21	uint8_t get_pixel_intensity(){
    22	    return((uint8_t)random(0,255));
    23	}
    24	
    25	void get_random_pixel_and_color(){
    26	    random_pixel_setting[0] = get_pixel_number();
    27	    random_pixel_setting[1] = get_pixel_intensity();
    28	    random_pixel_setting[2] = get_pixel_intensity();
    29	    random_pixel_setting[3] = get_pixel_intensity();
    30	}
    31	
    32	void setup(){
    33	    Serial.begin(115200);
    34	    delay(2000);
    35	    Serial.println("In setup");
    36	}
    37	
    38	void loop(){
    39	
    40	    // get a pixel number
    41	    get_random_pixel_and_color();
    42	
    43	    // display the randomly assigned pixel and color
    44	    p.neoPixelSetValue(random_pixel_setting[0], random_pixel_setting[1],
    45	                       random_pixel_setting[2],
    46	                       random_pixel_setting[3], true);
    47	    delay(100);
    48	    // clear all pixels
    49	    p.neoPixelClear();
    50	    delay(100);
    51	}
    52	
    53	

```

The first step in using the library is to create an instance of the NeoPixelConnect class.
Line 9 of the example creates an instance using the constructor that explicitly 
specifies both the PIO and SM. The instance is named _p_.

In addition to having a constructor that requires you to select the PIO and SM explicitly, there are 
two additional constructors. One that will select PIO 0 and SM 0 for you.

```ABAP
NeoPixelConnect(byte pinNumber, uint16_t numberOfPixels);
```

And finally, one where you specify a PIO, and the 
constructor will attempt to find an available SM.

```ABAP
    NeoPixelConnect(byte pinNumber, uint16_t numberOfPixels, PIO pio);

```

Line 13 creates an array that holds a pixel number and its associated RGB values.

Lines 16 and 17 define a function that randomly selects a pixel number.

Lines 21 through 23 select an intensity level randomly.

Lines 25 through 30 randomly select a pixel and then randomly select a color.

Lines 32 through 36 are the _setup_ function. It simply initializes the serial port
speed and prints out a short message.

Lines 38 through 51 are the _loop_ function. A random pixel and color are selected. 
The values for the pixel are entered into the display buffer, and the pixel is then
displayed. 

After 100 milliseconds, all the pixels are 
cleared, and after an additional 100 milliseconds, the loop repeats.

## Additional Methods

There are several additional methods available for pixel control that are
not utilized in this demo.

These methods are described in [NeoPixelConnect.h.](https://github.com/MrYsLab/NeoPixelConnect/blob/master/src/NeoPixelConnect.h)

