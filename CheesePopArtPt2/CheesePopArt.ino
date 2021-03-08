#include <Adafruit_NeoPixel.h>

#include "frames.h"

#include <Bounce2.h>

Bounce button = Bounce();

Adafruit_NeoPixel strip(24, 0);

int switchVal = 0;

int whichFrame = 0;

boolean blankslate = true;

//last time it was moldy
long moldTime = 0;

long moldInterval = 500;

int numberofblue = 12;
int currentblue = 0;

//timer for mapped
long mappedTime = 0;

long mappedInterval = 500;



char colors[8][3] {
  //black                 0
  {0, 0, 0},
  //darkest orange        1
  {249, 91, 12},
  //second darkest orange 2
  {246, 129, 71},
  //first yellow          3
  {243, 180, 85},
  //second yellow         4
  {229, 197, 39},
  //third yellow          5
  {245, 229, 151},
  //fourth yellow         6
  {250, 240, 191},
  //white                 7
  {250, 250, 250}
};

void setup() {
  // put your setup code here, to run once:
  button.attach(1, INPUT);
  button.interval(5);

  strip.begin();
  strip.clear();
  strip.setBrightness(30);

  randomSeed(analogRead(2));
}

void loop() {
  // put your main code here, to run repeatedly:
  button.update();

  if (button.rose()) {
    switchVal = (switchVal + 1) % 4;
  }

  switch (switchVal) {

    case 0: off();
      break;

    case 1: staticstate();
      break;

    case 2: sanimation();
      break;

    case 3: mapped();
      break;
  }
}

void off() {
  strip.clear();
  strip.show();
}

void staticstate() {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 229, 197, 39);
  }
  strip.show();
}

void sanimation() {
  if (blankslate) {
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, 246, 129, 71);
    }
    strip.show();
    blankslate = false;
  } else {
    if (millis() - moldTime > moldInterval) {
      int j = random(0, strip.numPixels());
      strip.setPixelColor(j, 0, 0, 255);
      strip.show();
      moldTime = millis();
      currentblue++;
      if (currentblue == numberofblue) {
        blankslate = true;
        currentblue = 0;
      }
    }
  }
}

void mapped() {
  if (millis() - mappedTime > mappedInterval) {
    for (int i = 0; i < strip.numPixels(); i++) {
      int whichColor = animation[whichFrame][i];

      int whichPixel = PixelMap[i];

      int red = colors[whichColor][0];
      int green = colors[whichColor][1];
      int blue = colors[whichColor][2];

      strip.setPixelColor(whichPixel, red, green, blue);
    }
    strip.show();
    whichFrame = (whichFrame + 1) % 6;
    //delay(500);
    mappedTime = millis();
  }
}
