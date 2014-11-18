
#include "Adafruit_ILI9341.h"

#ifndef _ADAFRUIT_ILI9341BUFFEREDH_
#define _ADAFRUIT_ILI9341BUFFEREDH_

class Adafruit_ILI9341Buffered : public Adafruit_ILI9341
{
public:
    Adafruit_ILI9341Buffered(int8_t _CS, int8_t _DC, int8_t _RST = -1);
    
    ~Adafruit_ILI9341Buffered();

    virtual void fillScreen(uint16_t color);
    virtual void drawPixel(int16_t x, int16_t y, uint16_t color);
    virtual void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
    virtual void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
    virtual void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    
    void presentBuffer();

private:
    uint16_t *screen_buffer;
};


#endif
