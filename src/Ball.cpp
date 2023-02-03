#include "ball.h"

// Ball constructor
Ball::Ball(int16_t max_x, int16_t max_y, int16_t radius, int16_t speed) {
    m_max_x = max_x;
    m_max_y = max_y;
    m_radius = radius;
    m_speed = speed;
}

// Setters and getters
void Ball::setXPos(int16_t x_pos) {
    m_x_pos = x_pos;
}

void Ball::setYPos(int16_t y_pos) {
    m_y_pos = y_pos;
}

void Ball::setPos(int16_t x_pos, int16_t y_pos) {
    m_x_pos = x_pos;
    m_y_pos = y_pos;
}
void Ball::setAngle(int16_t angle) {
    m_angle = angle;
    m_x_vel = cos(angle * PI / 180);
    m_y_vel = sin(angle * PI / 180);
}

int16_t Ball::getXPos() {
    return m_x_pos;
}
int16_t Ball::getYPos() {
    return m_y_pos;
}

// Update position of the ball
void Ball::update() {
    m_x_pos += m_x_vel;
    m_y_pos += m_y_vel;

    if(m_x_pos < 0) {
        m_x_pos = -m_x_pos;
        m_x_vel = -m_x_vel;
    }
    else if(m_x_pos >= m_max_x) {
        m_x_pos -= m_x_pos - m_max_x;
        m_x_vel = -m_x_vel;
    }
    if(m_y_pos < 0) {
        m_y_pos = -m_y_pos;
        m_y_vel = -m_y_vel;
    }
    else if(m_y_pos > m_max_y) {
        m_y_pos -= m_y_pos - m_max_y;
        m_y_vel = -m_y_vel;
    }
}

// Draw ball to screen
void Ball::draw(Adafruit_SSD1306 &display) {
    display.fillCircle(m_x_pos, m_y_pos, m_radius, SSD1306_WHITE);
}

