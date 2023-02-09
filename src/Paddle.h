#ifndef PADDLE_H
#define PADDLE_H
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/**
 * Paddle Class
 * Controls position and drawing of paddle for Pong Game.
*/
class Paddle
{
private:
    int16_t m_x_pos;        // current x position of center left side of paddle
    int16_t m_y_pos;        // current y position of center left side of paddle
    int16_t m_req_y_pos;    // requested y position of center left side of paddle. Where paddle will move to.
    int16_t m_speed;        // movement speed of paddle in pixels per frame
    int16_t m_width;        // width of paddle
    int16_t m_height;       // height of paddle

public:
    /**
     * Paddle Constructor
     * Must set initial position, dimensions of paddle, and speed.
    */
    Paddle(const int16_t &x_pos, const int16_t &y_pos, const int16_t &width, const int16_t &height, const int16_t &speed);

    /**
     * Setters and Getters
    */
    int16_t getXPos();
    int16_t getYPos();
    int16_t getSpeed();
    
    void setSpeed(const int16_t &speed);
    void setXPos(const int16_t &x_pos);
    void setYPos(const int16_t &y_pos);
    void setPos(const int16_t &x_pos, const int16_t &y_pos);

    /**
     * update()
     * Moves paddle towards target position by amount specified in speed.
    */
    void update();

    /**
     * reqYPos()
     * Sets a target y position for the paddle to start moving towards.
    */
    void reqYPos(const int16_t &y_pos);

    /**
     * checkHit()
     * Checks if the specified x and y coordinates are inside the paddle.
    */
    bool checkHit(const int16_t &x_pos, const int16_t &y_pos);

    /**
     * draw()
     * Draws a filled rectangle for the current position of the paddle.
    */
    void draw(Adafruit_SSD1306 &display);
};

#endif