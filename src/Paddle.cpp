#include "paddle.h"

/**
 * Paddle Constructor
 * Must set initial position, dimensions of paddle, and speed.
*/
Paddle::Paddle(const int16_t &x_pos, const int16_t &y_pos, const int16_t &width, const int16_t &height, const int16_t &speed)
{
    m_x_pos = x_pos;
    m_y_pos = y_pos;
    m_width = width;
    m_height = height;
    m_speed = speed;
}

/**
 * Setters and Getters
*/
int16_t Paddle::getXPos(){ return m_x_pos; }

int16_t Paddle::getYPos(){ return m_y_pos; }

int16_t Paddle::getSpeed(){ return m_speed; }

void Paddle::setSpeed(const int16_t &speed)
{
    m_speed = speed;
}

void Paddle::setXPos(const int16_t &x_pos) {
    m_x_pos = x_pos;
}

void Paddle::setYPos(const int16_t &y_pos) {
    m_y_pos = y_pos;
}

void Paddle::setPos(const int16_t &x_pos, const int16_t &y_pos)
{
    m_x_pos = x_pos;
    m_y_pos = y_pos;
}

/**
 * update()
 * Moves paddle towards target position by amount specified in speed.
*/
void Paddle::update()
{
    if(m_req_y_pos > m_y_pos + m_speed) {
        m_y_pos = m_y_pos + m_speed;
    }
    else if(m_req_y_pos > m_y_pos) {
        m_y_pos = m_req_y_pos;
    }
    else if(m_req_y_pos < m_y_pos - m_speed) {
        m_y_pos = m_y_pos - m_speed;
    }
    else if(m_req_y_pos < m_y_pos) {
        m_y_pos = m_req_y_pos;
    }
}

/**
 * reqYPos()
 * Sets a target y position for the paddle to start moving towards.
*/
void Paddle::reqYPos(const int16_t &y_pos) 
{
    m_req_y_pos = y_pos;
}

/**
 * checkHit()
 * Checks if the specified x and y coordinates are inside the paddle.
*/
bool Paddle::checkHit(const int16_t &x_pos, const int16_t &y_pos) {
    int16_t rect_y = m_y_pos - m_height / 2;    // y-coordinant of upper edge of paddle
    return x_pos >= m_x_pos - 1 && x_pos <= m_x_pos + m_width && y_pos >= rect_y && y_pos <= rect_y + m_height;
}

/**
 * draw()
 * Draws a filled rectangle for the current position of the paddle.
 * x and y positions specify the middle of the left side of the paddle.
 * (0, 0) specifies upper left corner of the screen with x and y increasing to the right and down respectively.
*/
void Paddle::draw(Adafruit_SSD1306 &display)
{
    int16_t rect_y = m_y_pos - m_height / 2;    // y-coordinant of upper edge of paddle
    display.fillRect(m_x_pos, rect_y, m_width, m_height, SSD1306_WHITE);
}