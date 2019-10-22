#include "playsong.h"

int speakerPin = 11;
int bpm = 60; // beats per minute
int noteBeat = 4; // Song is written in 1/4 notes
String TwoBits= "C4-G3G3A3-G3-..B3-C4----";
String ScaleTest = // A test for every note, including sharps and flats.
"C1C1#D1E1bE1F1G1bG1"
"A1A1#B1C2C2#D2E2bE2F2G2bG2"
"A2A2#B2C3C3#D3E3bE3F3G3bG3"
"A3A3#B3C4C4#D4E4bE4F4G4bG4"
"A4A4#B4C5C5#D5E5bE5F5G5bG5"
"A5A5#B5C6C6#D6E6bE6F6G6bG6"
"A6A6#B6C7C7#D7E7bE7F7G7bG7"
"A7A7#B7C8C8#D8E8bE8F8G8bG8"
"A8A8#B8C9C9#D9E9bE9F9G9bG9";

void setup() {
  Serial.begin(9600);
  Serial.println("Song Player Starting");
  
  playsong(ScaleTest, 360, 1, speakerPin);
  playsong(TwoBits, 60, 4, speakerPin);
}

void loop() {
  delay(1000);
}
