/* 
    Arduino Pong

        by
    Daniel Jaramillo
*/
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "paddle.h"
#include "ball.h"

// Controls
#define BUTTON_L        3
#define BUTTON_R        2
#define POT_L           A2
#define POT_R           A0

// Screen dimensions
#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT   64

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI       9
#define OLED_CLK        10
#define OLED_DC         11
#define OLED_CS         12
#define OLED_RESET      13

// Game info
#define BALL_SPEED      2
#define PADDLE_SPEED    2
#define BALL_RADIUS     2
#define PADDLE_WIDTH    2
#define PADDLE_HEIGHT   9
#define BALL_ANGLE      160     // ball can only be launched left or right in an arc of BALL_ANGLE degrees

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, 
OLED_CS);

int16_t position_l;
int16_t position_r;

enum GAME_STATES{live=0, serve_l, serve_r, start};

bool button_r_prev;
bool button_l_prev;
bool button_r;
bool button_l;

Paddle paddle_l(1, 32, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_SPEED);
Paddle paddle_r(125, 32, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_SPEED);
Ball ball(63, 31, BALL_RADIUS);

int8_t game_state;

// Setup
void setup() {
    Serial.begin(9600);

    if(!display.begin(SSD1306_SWITCHCAPVCC)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }

    // setup buttons
    pinMode(BUTTON_L, INPUT_PULLUP);
    pinMode(BUTTON_R, INPUT_PULLUP);

    button_l_prev = digitalRead(BUTTON_L);
    button_r_prev = digitalRead(BUTTON_R);

    randomSeed(analogRead(POT_L) + analogRead(POT_R));

    game_state = start;
}

// Main Loop
void loop() {
    // read left pot
    position_l = analogRead(POT_L) >> 4;
    paddle_l.reqYPos(position_l);

    // read right pot
    position_r = analogRead(POT_R) >> 4;
    paddle_r.reqYPos(position_r);

    // read left button
    button_l = digitalRead(BUTTON_L);

    // read right button
    button_r = digitalRead(BUTTON_R);

    // update paddles
    paddle_l.update();
    paddle_r.update();

    // update ball
    ball.update();

    switch(game_state) {
        case start:
            if((!button_l && button_l_prev) || (!button_r && button_l_prev)) {
                int angle = random(BALL_ANGLE);
                int dir = random(2);
                if(dir == 0) {
                    angle = angle - BALL_ANGLE / 2;
                }
                else {
                    angle = angle + 180 - BALL_ANGLE / 2;
                }
                ball.setVel(BALL_SPEED * cos(angle * PI / 180), BALL_SPEED * sin(angle * PI / 180));
                game_state = live;
            }
            break;

        case serve_l:
            if(!button_l && button_l_prev) {
                int angle = random(BALL_ANGLE);
                angle = angle - BALL_ANGLE / 2;
                ball.setVel(BALL_SPEED * cos(angle * PI / 180), BALL_SPEED * sin(angle * PI / 180));
                game_state = live;
            }
            else
                ball.setYPos(paddle_l.getYPos());
            break;

        case serve_r:
            if(!button_r && button_r_prev) {
                int angle = random(BALL_ANGLE);
                angle = angle + 180 - BALL_ANGLE / 2;
                ball.setVel(BALL_SPEED * cos(angle * PI / 180), BALL_SPEED * sin(angle * PI / 180));
                game_state = live;
            }
            else
                ball.setYPos(paddle_r.getYPos());
            break;

        case live:
        default:
            // bounce on top and bottom of screen
            if(ball.getYPos() > SCREEN_HEIGHT) {
                ball.setYPos(SCREEN_HEIGHT - (ball.getYPos() - SCREEN_HEIGHT));
                ball.setYVel(-ball.getYVel());
            }
            else if(ball.getYPos() < 0) {
                ball.setYPos(-ball.getYPos());
                ball.setYVel(-ball.getYVel());
            }
            // bounce on left and right paddles
            if(paddle_l.checkHit(ball.getXPos(), ball.getYPos())) {
                ball.setXPos(paddle_l.getXPos() + PADDLE_WIDTH);
                ball.setXVel(-ball.getXVel());
            }
            else if(paddle_r.checkHit(ball.getXPos(), ball.getYPos())) {
                ball.setXPos(paddle_r.getXPos() - 1);
                ball.setXVel(-ball.getXVel());
            }
            // score on left or right walls
            if(ball.getXPos() < 0) {
                ball.setVel(0, 0);
                ball.setXPos(paddle_l.getXPos() + PADDLE_WIDTH + 1);
                game_state = serve_l;
            }
            else if(ball.getXPos() > SCREEN_WIDTH) {
                ball.setVel(0, 0);
                ball.setXPos(paddle_r.getXPos() - 2);
                game_state = serve_r;
            }
            break;
    }

    // store button previous state
    button_l_prev = button_l;
    button_r_prev = button_r;

    // draw
    display.clearDisplay();
    paddle_l.draw(display);
    paddle_r.draw(display);
    ball.draw(display);

    display.display();
}
