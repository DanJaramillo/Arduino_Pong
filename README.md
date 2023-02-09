# Arduino_Pong
Pong for an Arduino Uno and a SSD1306 display.

## Purpose
I started this project to learn the Visual Studio Code and PlatformIO environment. Previous projects used the Arduino IDE. While Arduino IDE is easy and quick for small projects, I wanted to learn something that could be applied to a wider variety of hardware.

## Hardware
The processor is an ATmega328P on a Arduino Uno clone board. The paddle positions are controlled by two potentiometers, one for each player. Each player has a dedicated button to release the ball when it is in their possession. The display is a small 128x64 monochome display. All the components were chosen only based on what I had on hand from previous projects.

### Processor
The Arduino Uno clone board used for this project is called the RoboRed and was produced by YourDuino. Unlike the official Uno, it has support for both 3.3v and 5v through a toggle switch and allows more current through all the general purpose IO pins. However, any Uno or clone should work as the SSD1306 powered display is 5v compatable.

### Display
The display is a 128 x 64 monochrome OLED display. It is powered by a SSD1306 controller and is communicated with via the serial peripheral interface, SPI. In the current version of the program, it uses a software based SPI and the Adafruit SSD1306 driver. However, I may switch to a hardware SPI and interrupts to allow the next frame calculations to proceed while the previous frame is being drawn.

### Potentiometers
The paddle positions are controlled by two linear, single turn potentiometers. One for each player. They were selected as I had them on hand. For each, one side is connected to ground, the other side is connected to 3.3v supply of the Uno board. Each tap is connected to its own analog port on the Uno. The value read at the tap is then translated as the position of the paddle.

### Buttons
The buttons are basic momentary pushbuttons I had available. One side is connected to ground and the other is connected to one of the general purpose IO, GPIO, pins. The GPIO pins are configured as internal pullups. When the button is pressed, it registers low or 0 on the processor.

## Software
The game is controlled by a 4-state state machine. A ball class controls the basic movements of the ball and a paddle class controls the movements of the paddle.

### Ball
The ball class holds the x and y position and velocity, the radius, an update method, and a draw method. The ball constructor sets the size and initial position. The class stores the velocity and position is stored as a float to allow for more precise movement at angles. However, the position is truncated to int16_t's when drawn or requested by the getter methods. The update method moves the ball the distance specified by the velocity. To remove the dependency between the paddles, the game, and the ball, the update method ignores screen boundaries and the paddles. The position of the ball after contact with the wall or the paddle is adjusted by the main method. The draw method truncates the position of the ball and draws the ball using the Adafruit_GFX library fillCircle method.

### Paddle
The paddle class holds the x and y position, the y velocity, the dimensions, a checkHit method, an update method, and a draw method. Unlike the ball, the paddle position and velocity are stored as integers. The position of the paddle is the position of the middle of the left side of the paddle. The paddle constructor sets the intial position, velocity, and dimensions. When the player turns the potentiometer, the position is sampled and set as the target position. The update method then moves the paddle by velocity units each screen refresh towards the target position. This creates smoother on screen motion. The draw method then draws a rectangle using the Adafruit_GFX fillRect method.

### Game
The setup process reads potentiometers to generate a random seed, reads the buttons to get their initial positions, and sets the state machine to the "start position.

The main loop consists of three parts. The read input and update objects phase runs first. Then the state machine logic. Lastly, the update screen logic.

In the first part of the main loop, the buttons and potentiometers are read. The potentiometers position is used to tell the paddles where to move. The button positions are stored for future use by the state machine. Then the paddles and ball are told to move with their update method.

The second part of the main loop is the state machine. The state machine is composed of 4 states: "start", "serve_l", "serve_r", and "live".

After setup, the state machine is in the "start" state. Before moving to the start state, the ball is placed near the middle of the arena and given a velocity of 0. When the state machine detects either of the buttons being pressed and then released the ball will randomly move to the left or the right. The state machine then transitions to the "live" state.

In the "live" state the ball will continue moving around the arena in a straight line until it crosses a screen edge or touches paddle. If the ball hits a paddle or a horizontal edge it follow the same rules as a mirror, the incident angle is equal to the reflection angle. If the ball crosses a vertical edge, it is considered scoring for the player on the opposite side. The ball is then moved to the paddle of the player who was scored on and the state machine moves to the "serve_l" or "serve_r" state.

In the "serve_l" and "serve_r" states, the ball will move as if attached to the corresponding player's paddle. When that player presses and releases the button, the ball will move in a straight line towards the opposite end of the arena at a random angle. On the button press and release, the state machine goes back to the live state.

The final part of the main loop is to store the previous state of the buttons and update the screen. The display buffer is first cleared with the clearDisplay method from the Adafruit_GFX library. The draw methods for each of the paddles and the ball are called to draw to the screen buffer. The display method from Adafruit_GFX library then writes the display buffer to the screen, ending the pass through the main loop.

## Future Improvements
Most of the time


