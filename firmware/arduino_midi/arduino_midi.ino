// Lawrence Button Two Arduino GPIO to MIDI code
// Max Hunter, 2024

#define NOTEOFF_MSG 128

#define MIDI_NOTE 84 // C5
#define MIDI_VELOCITY 127
#define SEND_NOTE_OFF 1 // set to 0 to just send noteons
#define DEBOUNCE_DELAY 50 // milliseconds

const int buttonPin = 4;

int midi_state = 0;        // are we currently mid-note?
int button_state = 0;      // the current reading from the input pin
int last_button_state = 0; // the previous reading 

unsigned long last_debounce_time = 0;  // the last time the output pin was toggled

void setup() {
  // Set MIDI baud rate
  Serial.begin(31250);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  int reading = digitalRead(buttonPin);

  if ((reading == 0) && (button_state == 1)) {
    // send MIDI noteon
      MIDImessage(144, MIDI_NOTE, MIDI_VELOCITY);

      button_state = 0;
    // reset the debouncing timer
    // last_debounce_time = millis();
    delay(DEBOUNCE_DELAY);
  }
  else if ((reading == 1) && (button_state == 0)) {
    // send MIDI noteoff
      MIDImessage(128, MIDI_NOTE, MIDI_VELOCITY);

      button_state = 1;
    // reset the debouncing timer
    // last_debounce_time = millis();
      delay(DEBOUNCE_DELAY);

  }
}

//send MIDI message
void MIDImessage(int command, int MIDInote, int MIDIvelocity) {
  Serial.write(command);//send note on or note off command 
  Serial.write(MIDInote);//send pitch data
  Serial.write(MIDIvelocity);//send velocity data
}