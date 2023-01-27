# Arduino_Pong
Pong for an Arduino Uno on a SSD1306 display.

## Purpose
My goal with this project is to experiment with the SSD1306 display drivers and learn Visual Studio Code with PlatformIO.

Previously I had used the official Arduino IDE for all my Arduino and Adafruit MCU projects. While Arduino IDE is easy to use and has most of the features, I wanted to learn something more general purpose and translateable to professional embedded systems programming. This project is to practice 

## Hardware
The processor is an ATmega328P on a Arduino Uno clone board. The paddle positions are controlled by two potentiometers, one for each player. Each player has a dedicated button to release the ball when it is in their possession. The display is a small 128x64 monochome display. All the components were chosen only based on what I had on hand from previous projects.

### Processor
The Arduino Uno clone board used for this project is called the RoboRed and was produced by YourDuino. It has support for both 3.3v and 5v through a toggle switch and allows more current through all the general purpose IO pins. However, any Uno or clone should work as the SSD1306 powered display is 5v compatable.

### Display
The display is a 128 x 64 monochrome OLED display. It is powered by a SSD1306 controller and is communicated with via the serial peripheral interface, SPI. In the current version of the program, it uses a software based SPI and the Adafruit SSD1306 driver. However, I may switch to a hardware SPI and interrupts to allow the next frame calculations to proceed while the previous frame is being drawn.

### Potentiometers
The paddle positions are controlled by two linear, single turn potentiometers. One for each player. They were only chosen as I had them on hand. For each, one side is connected to ground, the other side is connected to 3.3v supply of the Uno board. Each tap is connected to its own analog port on the Uno. The value read at the tap is then translated as the position of the paddle.

### Buttons
The buttons are basic momentary pushbuttons I had available. One side is connected to ground and the other is connected to one of the general purpose IO, GPIO, pins. The GPIO pins are configured as internal pullups. When the button is pressed, it registers low or 0 on the processor.
