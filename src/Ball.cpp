#include "ball.h"

// Ball constructor
Ball::Ball(const int16_t &x_pos, const int16_t &y_pos, const int16_t &max_x, const int16_t &max_y, const int16_t &radius, 
const int16_t & speed) {
    m_x_pos = x_pos;
    m_y_pos = y_pos;
    m_max_x = max_x;
    m_max_y = max_y;
    m_radius = radius;
    m_speed = speed;
}

// Setters and getters
int16_t Ball::getXPos() { return m_x_pos; }

int16_t Ball::getYPos() { return m_y_pos; }

int16_t Ball::getXVel() { return m_x_vel; }

int16_t Ball::getYVel() { return m_y_vel; }

void Ball::setXPos(const int16_t &x_pos) {
    m_x_pos = x_pos;
}

void Ball::setYPos(const int16_t &y_pos) {
    m_y_pos = y_pos;
}

void Ball::setPos(const int16_t &x_pos, const int16_t &y_pos) {
    m_x_pos = x_pos;
    m_y_pos = y_pos;
}

void Ball::setXVel(const int16_t &x_vel) {
    m_x_vel = x_vel;
}

void Ball::setYVel(const int16_t &y_vel) {
    m_y_vel = y_vel;
}

void Ball::setVel(const int16_t &x_vel, const int16_t &y_vel) {
    m_x_vel = x_vel;
    m_y_vel = y_vel;
}

void Ball::setAngle(const int16_t &angle) {
    m_x_vel = cos(angle * PI / 180);
    m_y_vel = sin(angle * PI / 180);
}

// Update position of the ball
void Ball::update() {
    m_x_pos += m_x_vel;
    m_y_pos += m_y_vel;
}

// Draw ball to screen
void Ball::draw(Adafruit_SSD1306 &display) {
    display.fillCircle(m_x_pos, m_y_pos, m_radius, SSD1306_WHITE);
}

