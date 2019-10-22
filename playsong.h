// How to write a melody string for for void playsong(melody, bpm, noteBeat, speakerPin)
// ---
// playsong() takes a string with a song in it and plays it from beginning to end.
// To start, define the bpm of the compoition (determining how fast or slow the piece is)
// and then define the noteBeat which determines how playsong will interpret each note
// in the string. So if you pass in a noteBeat of 1, then all notes will be whole notes,
// 4 will be all notes being quarter notes (common), 8 will be 8th notes, etc.
// 
// To begin writing the melod string string simply start with the note you want to play,
// followed by the octive of that note, followed by the optional modifier:
// # for sharp, and b for flat.
//
// So "C4" would play a middle C. "B3" is the note below middle C and 
// "D4" is the note above it. "F4#" would play a F# in the middle C octive.
// "G3b" would be G-flat below middle C. Etc.
//
// After the note you can add hold marks '-' or rest marks '.' to rest for one noteBeat.
// So if you were writing your string in quarter notes and wanted to start with a 
// middle C, but hold it to a whole note, you would write: "C4---"
//
// Example: For shave and a hair cut, you can call:
//    playsong( "C4-G3G3A3-G3-..B3-C4----", 60, 4, [speakerPin]);


#ifndef debug
#define debug true
#endif

String noteNames = "A.BC.D.EF.G.";
float NOTE_A4 = 440.0;
float a = 0;

int pitches_setup() {
  a = pow(2.0, 1.0/12.0);
  
  Serial.println("pitches_setup() Debug Info");
  Serial.print("a = ");
  Serial.println(a);
}

int getWaveLenth(char note, int octive, int sharpflat) {
  // note is letter of note in common notation
  // octive is octive of note
  // sharpflat is 0 if natural, -1 if flat, +1 if sharp
  
  // From https://pages.mtu.edu/~suits/NoteFreqCalcs.html
  // The basic formula for the frequencies of the notes of the equal tempered scale
  // is given by:
  // fn = f0 * (a)n
  // where
  // f0 = the frequency of one fixed note which must be defined. A common choice is 
  //     setting the A above middle C (A4) at f0 = 440 Hz.
  // n = the number of half steps away from the fixed note you are. If you are at a 
  //     higher note, n is positive. If you are on a lower note, n is negative.
  // fn = the frequency of the note n half steps away.
  // a = (2)1/12 = the twelth root of 2 = the number which when multiplied by itself 
  //      12 times equals 2 = 1.059463094359...
  if (a == 0) {
    pitches_setup();
  }

  int noteindex = noteNames.indexOf(note& ~(0x20));

  if (noteindex == -1) {
    Serial.print("getWavelength(): ERROR in note name \"");
    Serial.print(note);
    Serial.println("\"");
    return -1;
  }

  if (noteindex >= 3) {
    octive--; // Correct for the fact that the octive actually starts on C.
  }
  if (sharpflat > 1) { // Just some type checking.
    sharpflat = 1;
  } else if (sharpflat < -1) {
    sharpflat = -1;
  }

  noteindex += 12 * (octive - 4) + sharpflat;
  Serial.print("noteindex = ");
  Serial.println(noteindex);
  
  return NOTE_A4 * pow(a, noteindex);
}

void playsong(String melody, int bpm, int noteBeat, int speakerPin) {
  // Interpret the melodystring and play it.
  // melody = A string with the song notes, holds, and rests defined in it.
  // bpm = the number of beats per minute of the composition
  // noteBeat = the base note used in the string. 
  //   So 1 would mean every note is a whole note. 
  //      4 would mean every note is 1/4 note.
  //      8 would be 1/8 notes, etc.
  // There is very little type checking. User be warned.
  
  int melodyBeat = 0;
  int noteBeatPause = (60000 / bpm) / noteBeat;
  
  while (melodyBeat < melody.length()) {
    char note = melody[melodyBeat];
    int octive = melody[++melodyBeat] - '0'; // Technically we can only do 8 octives, but that's more than a piano
    int modifier = 0; // Search for a sharp or flat
    if (melody[melodyBeat+1] == '#') {
      melodyBeat++;
      modifier = 1;
    } else if (melody[melodyBeat+1] == 'b') {
      melodyBeat++;
      modifier = -1;
    }
    int wavelength = getWaveLenth(note, octive, modifier);
    if (debug) {
      Serial.print("note = ");
      Serial.println(note);
      Serial.print("octive: ");
      Serial.println(octive);
      Serial.print("modifier = ");
      Serial.println(modifier);
      Serial.print("wavelength = ");
      Serial.println(wavelength);
    }
    
    tone(speakerPin, wavelength);
    
    do {
      delay(noteBeatPause);
      melodyBeat++;
      if (debug) {
        Serial.print("Hold ");
        Serial.println(noteBeatPause);
      }
    } while (melody[melodyBeat] == '-');
    
    noTone(speakerPin);
    
    while (melody[melodyBeat] == '.') {
      delay(noteBeatPause);
      melodyBeat++;
      if (debug) {
        Serial.print("Rest ");
        Serial.println(noteBeatPause);
      }
    }
  }
}
