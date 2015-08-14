/*
  #1: Meet Fishy! Fishy swims back and forth in their Fishtank!
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
  
byte fishDirection = 1;
// 0: UP
// 1: RIGHT
// 2: DOWN
// 3: LEFT

void setup() {
  // put your setup code here, to run once:
   matrix.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

    // Fill screen with white pixels (water!)
    matrix.fillRect(0, 0, 32, 16, matrix.Color333(7, 7, 7));

    // Fishy turns to avoid the wall!
    if ((fishX + fishLength > matrix.width() -2 && fishDirection == 1) || // Right boundary
        (fishX == 1 && fishDirection == 3) // Left boundary
        ) {

        // Turn!
        fishDirection += 2;
        if (fishDirection > 3) {
          fishDirection = 1;
        }
    }

    // Fishy moves in two directions!
    if (fishDirection == 1) { // RIGHT
      fishX += 1;
    }
    if (fishDirection == 3) { // LEFT
      fishX -= 1;
    }

    // Which way is Fishy pointing?
    if (fishDirection == 1 || fishDirection == 3) {
      matrix.fillRect(fishX, fishY, fishLength, fishWidth, matrix.Color333(0, 0, 0));  
    }

    // How fast does Fishy move?
    delay(50); // ms

}
