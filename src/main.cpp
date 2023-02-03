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
#define BUTTON_L        2
#define BUTTON_R        3
#define POT_L           A0
#define POT_R           A2

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

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, 
OLED_CS);

int16_t position_l;
int16_t position_r;

enum GAME_STATES{live=0, score_left, score_right, serve_left, serve_right};

bool button_r_prev;
bool button_l_prev;
bool button_r;
bool button_l;

Paddle paddle_l(1, 32, 2, 9, PADDLE_SPEED);
Paddle paddle_r(125, 32, 2, 9, PADDLE_SPEED);
Ball ball(63, 31, BALL_SPEED);

int8_t game_state;


// Setup
void setup() {
    Serial.begin(9600);
    Serial.println("Setup Start");

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }

    // setup buttons
    pinMode(BUTTON_L, INPUT_PULLUP);
    pinMode(BUTTON_R, INPUT_PULLUP);

    button_l_prev = digitalRead(BUTTON_L);
    button_r_prev = digitalRead(BUTTON_R);

    ball.setAngle(20);

    game_state = score_left;
    Serial.println("Setup Finish");
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

    // update objects
    paddle_l.update();
    paddle_r.update();
    ball.update();

    // draw
    display.clearDisplay();
    paddle_l.draw(display);
    paddle_r.draw(display);
    ball.draw(display);

    display.display();

    // temporary code to test IO
    /*
    Serial.println("");
    Serial.print("Button L: ");
    Serial.println(button_l);
    Serial.print("Button R: ");
    Serial.println(button_r);
    Serial.print("Pot L: ");
    Serial.println(position_l);
    Serial.print("Pot R: ");
    Serial.println(position_r);
    delay(500);
    */
}
