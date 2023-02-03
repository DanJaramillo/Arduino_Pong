#ifndef BALL_H
#define BALL_H
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <math.h>

#define BALL_RAD    1


class Ball
{
private:
    int16_t m_max_x;
    int16_t m_max_y;
    
    float m_x_pos;
    float m_y_pos;
    
    int16_t m_speed;
    float m_x_vel;
    float m_y_vel;
    int16_t m_angle;

public:
    // Ball constructor
    Ball(int16_t max_x, int16_t max_y, int16_t speed);

    // Setters and getters
    void setXPos(int16_t x_pos);
    void setYPos(int16_t y_pos);
    void setPos(int16_t x_pos, int16_t y_pos);
    void setAngle(int16_t angle);
    int16_t getXPos();
    int16_t getYPos();

    // Update position of the ball
    void update();

    // Draw ball to screen
    void draw(Adafruit_SSD1306 &display);
};

#endif