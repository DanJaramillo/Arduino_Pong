#ifndef BALL_H
#define BALL_H
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/*
    Ball Class

    Controls the basic movement of the ball in Pong Game.
*/

class Ball
{
private:
    int16_t m_max_x;
    int16_t m_max_y;
    
    float m_x_pos;
    float m_y_pos;
    
    int16_t m_speed;
    int16_t m_radius;
    float m_x_vel;
    float m_y_vel;

public:
    // Ball constructor
    Ball(const int16_t &x_pos, const int16_t &y_pos, const int16_t &max_x, const int16_t &max_y, const int16_t &radius, 
    const int16_t &speed);

    // Setters and getters
    int16_t getXPos();
    int16_t getYPos();
    int16_t getXVel();
    int16_t getYVel();

    void setXPos(const int16_t &x_pos);
    void setYPos(const int16_t & y_pos);
    void setPos(const int16_t &x_pos, const int16_t &y_pos);
    void setXVel(const int16_t &x_vel);
    void setYVel(const int16_t &y_vel);
    void setVel(const int16_t &x_vel, const int16_t &y_vel);
    void setAngle(const int16_t &angle);


    /**
     * update()
     * Moves the position of the ball based on the x and y velocities.
    */
    void update();

    /**
     * draw()
     * Draws a filled circle of balls radius at balls current x and y position.
    */
    void draw(Adafruit_SSD1306 &display);
};

#endif