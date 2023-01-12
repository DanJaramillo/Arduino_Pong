#include <Paddle.h>

Paddle::Paddle(int x_pos, int y_pos, int width, int height, int speed=2)
{
    m_x_pos = x_pos;
    m_y_pos = y_pos;
    m_width = width;
    m_height = height;
    m_speed = speed;
}
int Paddle::getSpeed(){ return m_speed; }

void Paddle::setSpeed(int speed)
{
    m_speed = speed;
}

int Paddle::getXPos(){ return m_x_pos; }
int Paddle::getYPos(){ return m_y_pos; }
void Paddle::setPos(int x_pos, int y_pos)
{
    m_x_pos = x_pos;
    m_y_pos = y_pos;
}

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

void Paddle::reqYPos(int y_pos) 
{
    m_req_y_pos = y_pos;
}

void Paddle::draw(Adafruit_SSD1306 &display)
{
    int rect_y = m_y_pos - m_height / 2;
    if(rect_y < 0) {
        display.fillRect(m_x_pos, 0, m_width, m_height + rect_y, SSD1306_WHITE);
    }
    else {
        display.fillRect(m_x_pos, rect_y, m_width, m_height, SSD1306_WHITE);
    }
}