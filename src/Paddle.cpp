#include "paddle.h"

// Paddle constructor
Paddle::Paddle(const int16_t &x_pos, const int16_t &y_pos, const int16_t &width, const int16_t &height, const int16_t &speed)
{
    m_x_pos = x_pos;
    m_y_pos = y_pos;
    m_width = width;
    m_height = height;
    m_speed = speed;
}

// Setters and getters
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

// Moves the paddle towards the desired position.
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

// Sets the paddles requested position. Where we want the paddle to move to.
void Paddle::reqYPos(const int16_t &y_pos) 
{
    m_req_y_pos = y_pos;
}

// Checks if the point is inside or touching the paddle.
bool Paddle::checkHit(const int16_t &x_pos, const int16_t &y_pos) {
    int16_t rect_y = m_y_pos - m_height / 2;    // y-coordinant of upper edge of paddle
    if(x_pos >= m_x_pos - 1 && x_pos <= m_x_pos + m_width + 1 && y_pos >= rect_y && y_pos <= rect_y + m_width) {
        return true;
    }
    else {
        return false;
    }
}

// Draws the paddle to the display buffer.
void Paddle::draw(Adafruit_SSD1306 &display)
{
    int16_t rect_y = m_y_pos - m_height / 2;
    if(rect_y < 0) {
        display.fillRect(m_x_pos, 0, m_width, m_height + rect_y, SSD1306_WHITE);
    }
    else {
        display.fillRect(m_x_pos, rect_y, m_width, m_height, SSD1306_WHITE);
    }
}