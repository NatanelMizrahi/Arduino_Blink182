#include "pitches.h"

int digit_1_ctrl_pin = 8;
int digit_8_ctrl_pin = 7;
int digit_2_ctrl_pin = 4;
int speaker_pin = 12;

const int BPM = 100;
const int OFF_DELTA = 50;

typedef enum { ONE, TWO, EIGHT} digit_t;
typedef enum { A,B,C,D,E,F,G  } note_t;

int song_notes[] = { C, C, D, D, E, G, G, D, D, E, A, A, D, D, E, F, F, E, E, D };

int note_to_pitch(note_t note) {
  switch (note) {
      case F: return NOTE_F3; 
      case G: return NOTE_G3; 
      case A: return NOTE_A3; 
      case B: return NOTE_B3; 
      case C: return NOTE_C4; 
      case D: return NOTE_D4; 
      case E: return NOTE_E4; 
  }
}

int get_note_duration_ms(int n_16ths){
  double BPS = BPM/60.0;
  double BPS_16th = BPS*4.0;
  double duartion_16th_ms = 1000.0/BPS_16th;
  int duration = (int)(duartion_16th_ms * n_16ths) - OFF_DELTA;
//  printf("%d, %f, %f, %f, %d",BPM, BPS, BPS_16th, duartion_16th_ms, duration);
  return duration;
}

void setup() {
  pinMode(digit_1_ctrl_pin, OUTPUT);
  pinMode(digit_8_ctrl_pin, OUTPUT);
  pinMode(digit_2_ctrl_pin, OUTPUT);
  pinMode(speaker_pin, OUTPUT);
}
int get_ctrl_pin_by_digit(digit_t digit) {
  switch (digit) {
      case ONE: return digit_1_ctrl_pin;
      case TWO: return digit_2_ctrl_pin;
      case EIGHT: return digit_8_ctrl_pin;
  }
}
void play_note(digit_t digit, note_t note, int n_16ths) {
  int digit_ctrl_pin = get_ctrl_pin_by_digit(digit);
  int duration_ms = get_note_duration_ms(n_16ths);
  int note_pitch = note_to_pitch(note);
  
  digitalWrite(digit_ctrl_pin, HIGH);
  tone(speaker_pin, note_pitch, duration_ms);
  delay(duration_ms);
  digitalWrite(digit_ctrl_pin, LOW);
  noTone(speaker_pin);
  delay(OFF_DELTA);
}


void song_loop() {
  int len = sizeof(song_notes)/sizeof(int);
  digit_t digits [] = { ONE, ONE, EIGHT, EIGHT, TWO };
  int tempo []      = { 2, 1, 2, 1, 2 };
  for (int i = 0; i < len; i++) {
    play_note(digits[i%5], song_notes[i], tempo[i%5]);  
  }
}
void loop() {
  song_loop();
}
