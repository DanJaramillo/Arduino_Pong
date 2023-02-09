#ifndef BALL_H
#define BALL_H
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/*
    Ball Class

    Controls the basic movement of the ball in Pong Game.
*/

struct Ball
{
private:  
    float m_x_pos;
    float m_y_pos;
    
    int16_t m_speed;
    int16_t m_radius;
    float m_x_vel;
    float m_y_vel;

public:
    // Ball constructor
    Ball(const int16_t &x_pos, const int16_t &y_pos, const int16_t &radius);

    // Setters and getters
    int16_t getXPos();
    int16_t getYPos();
    float getXVel();
    float getYVel();

    void setXPos(const int16_t &x_pos);
    void setYPos(const int16_t & y_pos);
    void setPos(const int16_t &x_pos, const int16_t &y_pos);
    void setXVel(const float &x_vel);
    void setYVel(const float &y_vel);
    void setVel(const float &x_vel, const float &y_vel);

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