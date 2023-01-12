/* 
    Arduino Pong

        by
    Daniel Jaramillo
*/

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "Paddle.h"

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

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, 
OLED_CS);

int position_l;
int position_r;

enum GAME_STATES{live=0, score_left, score_right, serve_left, serve_right};

bool button_r_prev;
bool button_l_prev;
bool button_r;
bool button_l;

Paddle paddle_l(2, 32, 2, 5);
Paddle paddle_r(124, 32, 2, 5);

int game_state;


// Setup
void setup() {
    Serial.begin(9600);

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

    game_state = score_left;
}

// Main Loop
void loop() {
    // read left pot
    position_l = analogRead(POT_L) >> 3;

    // read right pot
    position_r = analogRead(POT_R) >> 3;

    // read left button
    button_l = digitalRead(BUTTON_L);

    // read right button
    button_r = digitalRead(BUTTON_R);

    // draw
    display.clearDisplay();
    paddle_l.draw(display);
    paddle_r.draw(display);

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
