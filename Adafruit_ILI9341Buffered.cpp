
#include "Adafruit_ILI9341Buffered.h"
#include <SPI.h>

static uint16_t byteswap(uint16_t w)
{
    return ((w & 0x00ff) << 8) | (w >> 8) & 0x00ff;
}

Adafruit_ILI9341Buffered::Adafruit_ILI9341Buffered(int8_t _CS, int8_t _DC, int8_t _RST) :
    Adafruit_ILI9341(_CS, _DC, _RST)
{
    screen_buffer = (uint16_t *)malloc(ILI9341_TFTWIDTH * ILI9341_TFTHEIGHT * sizeof(uint16_t));
}

Adafruit_ILI9341Buffered::~Adafruit_ILI9341Buffered()
{
    free(screen_buffer);
}

void Adafruit_ILI9341Buffered::drawPixel(int16_t x, int16_t y, uint16_t color)
{
    if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height))
        return;
    
    screen_buffer[y * _width + x] = byteswap(color);
}

void Adafruit_ILI9341Buffered::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{
    if((x >= _width) || (y >= _height))
        return;
    
    if((y+h-1) >= _height)
        h = _height - y;
    
    for (int32_t row = y; row < y + h; ++row)
        screen_buffer[row * _width + x] = byteswap(color);
}

void Adafruit_ILI9341Buffered::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{
    if((x >= _width) || (y >= _height))
        return;
    
    if((x+w-1) >= _width)
        w = _width - x;
    
    for (int32_t col = x; col < x + w; ++col)
        screen_buffer[y * _width + col] = byteswap(color);
}

void Adafruit_ILI9341Buffered::fillScreen(uint16_t color)
{
    for (uint32_t i = 0; i < _width * _height; ++i)
    {
        screen_buffer[i] = byteswap(color);
    }
}

void Adafruit_ILI9341Buffered::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
    if((x >= _width) || (y >= _height))
        return;
    
    if((x + w - 1) >= _width)
        w = _width  - x;
    
    if((y + h - 1) >= _height)
        h = _height - y;
    
    for (int32_t row = y; row < y + h; ++row)
    for (int32_t col = x; col < x + w; ++col)
        screen_buffer[row * _width + col] = byteswap(color);
}

void Adafruit_ILI9341Buffered::presentBuffer()
{
    spi_begin();
    
    setAddrWindow(0, 0, _width - 1, _height - 1);
    
    digitalWrite(_dc, HIGH);
    digitalWrite(_cs, LOW);
    
    for (uint32_t y = 0; y < _height; y += 5)
    {
        SPI.transferBuffer((uint8_t *)&screen_buffer[y * _width], NULL, _width * sizeof(uint16_t) * 5);
    }
    
    digitalWrite(_cs, HIGH);
    
    spi_end();
}
