# Arduino_Pong
Pong for an Arduino Uno and a SSD1306 display.

## Purpose
I started this project to learn the Visual Studio Code with PlatformIO. Previous projects used the Arduino IDE. While Arduino IDE is easy and quick for small projects, I wanted to learn something that could be applied to a wider variety of hardware.

While I experimented with many different designs, I settled on the most straight forward design as I wanted to move to other projects.

## Hardware
The processor is an ATmega328P on a Arduino Uno clone board. Paddle positions are controlled by two rotary potentiometers, one for each player. Each player has a dedicated button to release the ball when it is in their possession. The display is a small 128x64 monochome oled display. Components were chosen as they were the best of what I already had on hand.

### Processor
The Arduino Uno clone board used for this project is called the RoboRed and was produced by YourDuino. Unlike the official Uno, it has support for both 3.3v and 5v through a toggle switch and allows more current through all the general purpose IO. However, any Uno or clone should work as the display controller, SSD1306, is both 5v and 3.3v compatible.

### Display
The display is a 128 x 64 monochrome OLED display. It is controlled by a SSD1306 driver chip through the serial peripheral interface, SPI. In the current version of the program, it uses a software based SPI and the Adafruit SSD1306 driver. However, I may switch to a hardware SPI and interrupts to allow the next frame calculations to proceed while the previous frame is being drawn.

### Potentiometers
The paddle positions are controlled by two linear, single turn potentiometers. One for each player. For each, one side is connected to ground, the other side is connected to 3.3v supply of the Uno board. Each tap is connected to its own analog port on the Uno. The value read at the tap is then translated as the position of the paddle. If using the board in 5v mode or an official Arduino Uno, the high side should be connected to 5v.

### Buttons
The buttons are basic momentary pushbuttons. One side is connected to ground and the other is connected to one of the general purpose IO, GPIO, pins. The GPIO pins are configured as internal pullups. Pressing the button will pull the pin from high to low or 3.3v to ground with the current configuration.

## Software
The game is designed as a 4-state state machine. The main file has the intialization routine and the game logic. A ball class controls the basic movements of the ball and a paddle class controls the movements of the paddle.

### Ball
The ball class holds the position, velocity, and radius of the ball. The class contains a constructor and basic setters/getters. An update method controls basic movement and a draw method will update the display buffer. The ball class stores the position and velocity as floats to allow for more precise movement at angles. However, the position is truncated to int16_t's when drawn or retrieved by the getter methods. The update method moves the ball the distance specified by the velocity. To remove the dependency between the paddles, the game, and the ball, the update method does not calculate collisions. Instead, the collision detection was moved to the main game loop. The draw method takes the Adafruit_SSD1306 object as a paramater and draws the ball using the Adafruit_GFX library fillCircle method.

### Paddle
The paddle class stores the position, velocity, and dimensions of the paddle. It has a constructor, basic setters/getters, a checkHit method, an update method, and a draw method. Unlike the ball, the paddle position and velocity are stored as integers. The position of the paddle is the position of the middle of the left side of the paddle. When the player turns the potentiometer, the position is sampled and set as the target position. The update method then moves the paddle by velocity units each screen refresh towards the target position. The draw method takes a Adafruit_SSD1306 object and draws the paddle using the Adafruit_GFX fillRect method.

### Game
The setup process reads potentiometers to seed the random number generator and set the initial paddle positions, reads the intial position of the buttons, moves the ball to its initial position, and then sets the state machine to the "start" state.

The main loop consists of four parts: read inputs, update objects, run state machine, and lastly, draw to the screen.

The read inputs section of the main loop involves reading the potentiometers and pushbuttons and storing them for use later in the main loop. Then the update objects section runs to move the ball and paddles if required.

The third part of the main loop is the state machine. The state machine is composed of 4 states: "start", "serve_l", "serve_r", and "live".

The state machine is put in the "start" state on initial startup or reset. The start state waits for a press and then release of either of the player buttons. When this is detected, the ball is given a random start angle and a speed of 2. The possible start angles are restricted to a 160 degree arc centered towards either the left or the right sides of the screen. Then the state machine is set to the "live" state.

In the "live" state the ball will continue moving around the arena in a straight line until it crosses a screen edge or touches paddle. If the ball hits a paddle or a horizontal edge it will bounce as a ray of light off a mirror. If the ball crosses a vertical edge without hitting a paddle, it is considered scoring for the player on the opposite side. The ball is then moved to the paddle of the player who was scored on and the state machine moves to the "serve_l" or "serve_r" state, corresponding to the player who was scored against.

In the "serve_l" and "serve_r" states, the ball will move as if attached to the corresponding player's paddle. When the serving player presses and releases the button, the ball will move in a straight line towards the opposite end of the arena at a random angle chosen from a 160 degree arc centered towards the opposite side of the screen. The state machine will then switch to the live state.

After the main game logic in the state machine is run, the final part of the main loop will store the previous state of the buttons and update the screen. The display buffer is first cleared with the clearDisplay method from the Adafruit_GFX library. Then the draw methods for each of the paddles and the ball are called to update the screen buffer. Finally, the display method from Adafruit_GFX library then writes the display buffer to the screen, ending the pass through the main loop.

## Possible Improvements
I experimented with using fixed point arithmetic for the ball's movement as a way to eliminate floating point calculations. Then I would use a compiler calculated trig table for my movement at an angle. I decided to leave it with the more straightforward approach as it takes less programming time.

I might change the ball and paddle collision logic at some point. The current way just checks if the ball would be inside the paddle. However, if the ball is too fast, it can pass through the paddle without registering a bounce. A better way would be to check if a line from the previous position to the current position of the ball intersects with the line of the face of the paddle.

Score tracking and a max score to win could be added but I just had no interest in it.

The ball and paddle collsion could be changed to make the ball bounce at different angles depending on where it hit the paddle. Hitting with the middle of the paddle would make the ball bounce like normal. Hitting with the edges would make the ball bounce at an angle more in that direction.

The ball could be made to accelerate over time and reset when someone scores. This would require changing the ball and paddle collision logic.
