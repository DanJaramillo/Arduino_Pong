#ifndef PADDLE_H
#define PADDLE_H
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/*
Paddle class

Controls position and motion of a paddle for Pong.
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
    // Paddle Constructor - must set initial position, dimensions, and speed of paddle
    Paddle(const int16_t & x_pos, const int16_t & y_pos, const int16_t & width, const int16_t & height, const int16_t & speed);

    // Setters and Getters
    int16_t getSpeed();
    void setSpeed(const int16_t & speed);
    int16_t getXPos();
    int16_t getYPos();
    void setPos(const int16_t & x_pos, const int16_t & y_pos);

    // Updates paddles position based on speed. Paddle will move "speed" pixels until it reaches the requested position
    void update();

    // Sets the position that the paddle should move to.
    void reqYPos(const int16_t & y_pos);

    // Checks if and where the paddle is hit and returns the rebound angle
    int checkHit(const int16_t & x_pos, const int16_t & y_pos);

    // Draws paddle to the display buffer. display.display() call must be made to send buffer to display.
    void draw(Adafruit_SSD1306 & display);
};

#endif