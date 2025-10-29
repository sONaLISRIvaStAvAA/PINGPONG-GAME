/*
  Arduino 2-Player Ping Pong Game - FINAL VERSION
  
  Features:
  - 5 LEDs: Pins 4, 5, 6, 7, 8
  - Button 1: Pin 2 (wired to GND, using INPUT_PULLUP)
  - Button 2: Pin 3 (wired to GND, using INPUT_PULLUP)
  - I2C LCD: Pins A4 (SDA), A5 (SCL) (Address 0x27)
  - Buzzer: Pin 9 (with new soothing sounds)
  - Speed Knob: Pin A0
*/

// --- Include Libraries ---
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 

// --- Pin Definitions ---
const int p1ButtonPin = 2;
const int p2ButtonPin = 3;
const int buzzerPin = 9;
const int speedKnobPin = A0;

const int ledPins[] = {4, 5, 6, 7, 8}; // 5 "ball" LEDs
const int ledCount = 5;

// --- Game Variables ---
int ballPosition = 2;   // Start in the middle
int ballDirection = 1;    // 1 = move right, -1 = move left
int gameSpeed = 150;    // Will be set by the knob
int p1Score = 0;
int p2Score = 0;
const int maxScore = 5; 

// --- LCD Setup ---
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Using the known-good 0x27 address

// --- Setup Function (runs once) ---
void setup() {
  // Set up all the LED pins as OUTPUTs
  for (int i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  // Set up the button pins using the internal pull-up resistor
  pinMode(p1ButtonPin, INPUT_PULLUP);
  pinMode(p2ButtonPin, INPUT_PULLUP);
  
  // Buzzer pin is an output
  pinMode(buzzerPin, OUTPUT);

  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("Ping Pong Game!");
  lcd.setCursor(0, 1);
  lcd.print("Set Speed...");
  delay(2000);

  // Show the initial score
  updateScoreboard();
  
  // Read the difficulty knob (0-1023)
  int speedReading = analogRead(speedKnobPin);
  // Convert 0-1023 to 200ms (slow) - 50ms (fast)
  gameSpeed = map(speedReading, 0, 1023, 200, 50);

  // Turn on the starting LED
  digitalWrite(ledPins[ballPosition], HIGH);

  // Wait for Player 1 to serve
  lcd.setCursor(0, 1);
  lcd.print("P1 to serve...");
  while( digitalRead(p1ButtonPin) == HIGH ) {
    // Wait here until the button is pressed (goes LOW)
  }
  
  // "Serve" sound (soothing C5 note)
  tone(buzzerPin, 523, 75);
  
  lcd.setCursor(0, 1);
  lcd.print("               "); // Clear bottom row
}

// --- Main Loop (runs forever) ---
void loop() {
  // 1. Move the ball
  digitalWrite(ledPins[ballPosition], LOW);   
  ballPosition = ballPosition + ballDirection;  
  digitalWrite(ledPins[ballPosition], HIGH);  

  // 2. Check for a hit or a miss
  checkGameLogic();

  // 3. Wait (speed is set by the knob)
  delay(gameSpeed);
}

// --- Function to check game logic ---
void checkGameLogic() {
  
  // Check Player 1's side (leftmost LED, index 0)
  if (ballPosition == 0) {
    if (digitalRead(p1ButtonPin) == LOW) { // LOW means pressed
      // HIT!
      ballDirection = 1;
      // New "soothing" hit sound (C5)
      tone(buzzerPin, 523, 75);
      
    } else {
      // MISS! Player 2 scores
      p2Score++;
      updateScoreboard();
      checkWin(); 
      resetBall();
    }
  }
  
  // Check Player 2's side (rightmost LED, index 4)
  else if (ballPosition == ledCount - 1) { 
    if (digitalRead(p2ButtonPin) == LOW) {
      // HIT!
      ballDirection = -1;
      // New "soothing" hit sound (C5)
      tone(buzzerPin, 523, 75);
      
    } else {
      // MISS! Player 1 scores
      p1Score++;
      updateScoreboard();
      checkWin(); 
      resetBall();
    }
  }
}

// --- Function to update the LCD Score ---
void updateScoreboard() {
  lcd.clear();
  lcd.setCursor(0, 0); // Top row
  lcd.print("P1: ");
  lcd.print(p1Score);
  
  lcd.setCursor(9, 0); // Top row, 9th character
  lcd.print("P2: ");
  lcd.print(p2Score);
}

// --- Function to reset the ball after a score ---
void resetBall() {
  
  // New "miss" sound (lower note, E4)
  tone(buzzerPin, 330, 150);
  
  // Turn off all LEDs
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  
  lcd.setCursor(0, 1); // Bottom row
  lcd.print("Score! Set Speed");
  delay(1500);

  // Read the difficulty knob for the next round
  int speedReading = analogRead(speedKnobPin);
  gameSpeed = map(speedReading, 0, 1023, 200, 50);

  // Reset ball to the middle
  ballPosition = 2; 
  digitalWrite(ledPins[ballPosition], HIGH);
  
  // Randomly choose next direction
  if (random(2) == 0) {
    ballDirection = 1;
  } else {
    ballDirection = -1;
  }
  
  // Wait for Player 1 to serve
  lcd.setCursor(0, 1);
  lcd.print("P1 to serve...");
  while( digitalRead(p1ButtonPin) == HIGH ) {
    // Wait here until the button is pressed (goes LOW)
  }
  
  // "Serve" sound (same as "hit" sound)
  tone(buzzerPin, 523, 75);
  
  lcd.setCursor(0, 1);
  lcd.print("               "); // Clear bottom row
}

// --- Function to check for a winner ---
void checkWin() {
  if (p1Score >= maxScore) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Player 1 WINS!");
    endGame();
  } else if (p2Score >= maxScore) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Player 2 WINS!");
    endGame();
  }
}

// --- Function to stop the game and celebrate ---
void endGame() {
  
  // Play a new "soothing" jingle (C-E-G)
  tone(buzzerPin, 523, 150); // C5
  delay(160);
  tone(buzzerPin, 659, 150); // E5
  delay(160);
  tone(buzzerPin, 784, 200); // G5
  delay(200);
  
  // Flash all LEDs
  for (int j = 0; j < 5; j++) {
    for (int i = 0; i < ledCount; i++) {
      digitalWrite(ledPins[i], HIGH);
    }
    delay(200);
    for (int i = 0; i < ledCount; i++) {
      digitalWrite(ledPins[i], LOW);
    }
    delay(200);
  }

  // Reset scores and wait
  p1Score = 0;
  p2Score = 0;
  lcd.setCursor(0, 1);
  lcd.print("Restarting...");
  delay(4000);
  updateScoreboard();
}