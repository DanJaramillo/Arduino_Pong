#ifndef BALL_H
#define BALL_H
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


class Ball
{
private:
    int m_max_x;
    int m_max_y;
    
    int m_x_pos;
    int m_y_pos;
    
    int m_speed;
    int m_x_vel;
    int m_y_vel;

public:
    Ball(int max_x, int max_y, int speed);
    void setXPos(int x_pos);
    void setYPos(int y_pos);
    void setPos(int x_pos, int y_pos);
    int getXPos();
    int getYPos();
    void update();
    void draw(Adafruit_SSD1306 &display);
};

#endif