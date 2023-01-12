#ifndef PADDLE_H
#define PADDLE_H
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


class Paddle
{
private:
    int m_x_pos;
    int m_y_pos;
    int m_req_y_pos;
    int m_speed;
    int m_width;
    int m_height;

public:
    Paddle(int x_pos, int y_pos, int width, int height, int speed);
    int getSpeed();
    void setSpeed(int speed);
    int getXPos();
    int getYPos();
    void setPos(int x_pos, int y_pos);
    void update();
    void reqYPos(int y_pos);
    void draw(Adafruit_SSD1306 &display);
};

#endif