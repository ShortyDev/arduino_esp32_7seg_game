#include "seg7.h"

Seg7 seg(15 /* ss pin */, 27 /* pwm pin */);
  
void setup() {
  seg.begin();
  seg.on();
  
  pinMode(32, INPUT); // pin input button 1 - attempt
  pinMode(5, INPUT); // pin input button 3 - reset game
  pinMode(14, INPUT); // pin input button 4 - highscore check
}

bool hold = false;
int counter = 0;
int highscore = 0;

void loop() {
  counter++;
  if (!hold) {
    seg.displayNumber(counter);
    delay(500 - (counter * 5));
  }
  if (counter > 99 && !hold) {
    hold = true;
  }
  bool button1_active = digitalRead(32) > 0;
  bool button2_active = digitalRead(5) > 0;
  bool button4_active = digitalRead(14) > 0;
  if (button1_active && !hold) { // attempt
    hold = true;
    if (highscore < counter && counter < 100) {
     highscore = counter;
     sleep(1);
     seg.displayRaw(0xEA, 0x60);
    }
  } else if (button2_active && hold) { // reset game
    counter = 0;
    hold = false;
  } else if (button4_active) { // display session highscore
    hold = true;
    seg.displayNumber(highscore);
  }
}
