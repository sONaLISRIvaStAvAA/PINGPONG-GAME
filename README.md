# Arduino 2-Player Ping Pong Game

A fun, 2-player reaction game built on an Arduino Uno. This project features an LCD scoreboard, adjustable game speed, and 8-bit sound effects. It was built and simulated entirely in Tinkercad.

<img width="1249" height="518" alt="image" src="https://github.com/user-attachments/assets/0273d177-5c9b-4a6b-8c93-241e79c39139" />

<img width="1180" height="514" alt="image" src="https://github.com/user-attachments/assets/f94b09ba-6b94-426e-b1d0-fc5f15b60cba" />

<img width="699" height="529" alt="image" src="https://github.com/user-attachments/assets/6a8e15f1-1d2e-442a-9912-cec9187a9800" />



## 🚀 Features

* **2-Player Gameplay:** Go head-to-head with a friend.
* **LCD Scoreboard:** Automatically keeps score up to 5 points on a 16x2 LCD.
* **Adjustable Speed:** A potentiometer knob controls the ball's speed, from easy to expert.
* **Sound Effects:** A piezo buzzer provides "soothing" 8-bit sounds for "hit," "miss," and "win."
* **Serve Function:** Player 1 serves the ball to start each round.

## 🛠️ Hardware Components

* 1x Arduino Uno
* 1x 16x2 I2C LCD Screen
* 5x LEDs (for the "ball")
* 2x Pushbuttons (for the "paddles")
* 1x Piezo Buzzer
* 1x 10kohm Potentiometer (for speed control)
* 5x 220ohm Resistors (for the LEDs)
* 1x Breadboard
* Jumper Wires

## 🎮 How to Play

1.  **Set the Speed:** Turn the potentiometer knob to set the game speed for the round.
2.  **Serve:** Player 1 (button on Pin 2) presses their button to serve the ball.
3.  **Rally:** The "ball" (an LED) will move from one side to the other.
4.  **Hit:** Press your button at the *exact* moment the ball reaches your end (the last LED).
5.  **Miss:** If you press too early or too late, the other player gets a point!
6.  **Win:** The first player to 5 points wins the game.

## ⚙️ How to Use

### For Tinkercad

1.  Open the [Tinkercad Project](https) (<- **Suggestion:** Make your Tinkercad project public and paste the link here).
2.  Click the "Start Simulation" button.
    LiquidCrystal_I2C lcd(0x27, 16, 2); 
    ```
4.  **Upload:** Connect your Arduino and upload the sketch.
