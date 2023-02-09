#include "ball.h"

// Ball constructor
Ball::Ball(const int16_t &x_pos, const int16_t &y_pos, const int16_t &radius) {
    m_x_pos = x_pos;
    m_y_pos = y_pos;
    m_x_vel = 0;
    m_y_vel = 0;
    m_radius = radius;
}

// Setters and getters
int16_t Ball::getXPos() { return m_x_pos; }

int16_t Ball::getYPos() { return m_y_pos; }

float Ball::getXVel() { return m_x_vel; }

float Ball::getYVel() { return m_y_vel; }

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

void Ball::setXVel(const float &x_vel) {
    m_x_vel = x_vel;
}

void Ball::setYVel(const float &y_vel) {
    m_y_vel = y_vel;
}

void Ball::setVel(const float &x_vel, const float &y_vel) {
    m_x_vel = x_vel;
    m_y_vel = y_vel;
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

