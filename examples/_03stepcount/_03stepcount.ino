/*
  #3: Fishy turns on prime-numbered steps, and their swim speed is now a variable.
*/

#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

// How big is Fishy?
byte fishLength = 5;
byte fishWidth = 2;
  
uint8_t fishX = 1; // Where is Fishy's head?
uint8_t fishY = 8;

uint8_t fishSpeed = 50; // How fast does Fishy move? (ms until next frame of animation, higher is slower)

uint8_t stepCount = 0; // How many "steps" has Fishy taken?
  
byte fishDirection = 1;
// 0: UP
// 1: RIGHT
// 2: DOWN
// 3: LEFT

void setup() {
  // put your setup code here, to run once:
   matrix.begin();

  // Examples
}

void loop() {
  // put your main code here, to run repeatedly:

    // Fill screen with white pixels (water!)
    matrix.fillRect(0, 0, 32, 16, matrix.Color333(7, 7, 7));

    // Fishy turns to avoid the wall!
    if ((fishX + fishLength > matrix.width() -2 && fishDirection == 1) || // Right boundary
        (fishX == 0 && fishDirection == 3) || // Left boundary
        (fishY + fishLength > matrix.height() -2 && fishDirection == 2) || // Down boundary
        (fishY == 0 && fishDirection == 0) // Up boundary
        ) {

        // Smooth out Fishy's turns on the right and down boundaries
        if (fishDirection == 1) {
          fishX = matrix.width() - fishWidth;
        }
        if (fishDirection == 2) {
          fishY = matrix.height() - fishWidth;
        }

        // Turn!
        fishDirection += 1;
    }

    // Fishy moves in four directions!
    if (fishDirection == 0) { // UP
      fishY -= 1;
    }
    if (fishDirection == 1) { // RIGHT
      fishX += 1;
    }
    if (fishDirection == 2) { // DOWN
      fishY += 1;
    }
    if (fishDirection == 3) { // LEFT
      fishX -= 1;
    }

    // Which way is Fishy pointing?
    if (fishDirection == 1 || fishDirection == 3) {
      matrix.fillRect(fishX, fishY, fishLength, fishWidth, matrix.Color333(0, 0, 0));  
    } else if (fishDirection == 2 || fishDirection == 0) {
      matrix.fillRect(fishX, fishY, fishWidth, fishLength, matrix.Color333(0, 0, 0));
    }

    // How fast does Fishy move?
    delay(fishSpeed); // ms

// [1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97]

    // Fishy changes their movement pattern based on how many steps they have taken
    stepCount++;

    // Fishy makes a turn on prime-numbered steps!
    if (stepCount == 7 || stepCount == 11 || stepCount == 13 || stepCount == 17 || stepCount == 19 || stepCount == 23 || stepCount == 29 || stepCount == 31 || stepCount == 37 || 
    stepCount == 41 || stepCount == 43 || stepCount == 47 || stepCount == 53 || stepCount == 59 || stepCount == 61 || stepCount == 67 || stepCount == 71 || stepCount == 73 ||
    stepCount == 79 || stepCount == 83 || stepCount == 89 || stepCount == 97) {
      fishDirection += 1;
    } else if (stepCount >= 150) {
      stepCount = 0;
    }

    // Fishy can only turn up/down/left/right
    if (fishDirection > 3 || fishDirection < 0) {
      fishDirection = 0;
    }

}
