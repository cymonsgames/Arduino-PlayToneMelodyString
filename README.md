# Arduino-PlayToneMelodyString
Make music with an arduino and speaker. These functions turn a string into a song. Great for kids, schools, and makerspace activities.

My son salvaged a junk speaker and wanted to learn how to make it play a song. So I copied the code from theToneMelody example on Arduino.cc (https://www.arduino.cc/en/Tutorial/toneMelody), and let him play around with it. Watching him struggle, I quickly realized it's method of having and maintaining 2 parallel arrays was incredibly inefficient. So while he managed to get a few bars of dual of the fates into the arduino, I decided to make a better way. The result is before you.

I wrote a library that would take a string that you define the notes you want to play, as well as add holds or pauses where appropriate, and it walks through the string playing your song. So instead of the data for shave and a hair cut looking like this:

  int melody[] = {   NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4  };
  int noteDurations[] = { 4, 8, 8, 4, 4, 4, 4, 4 };

It looks like this:

  String TwoBits= "C4-G3G3A3-G3-..B3-C4----";

I added a longer pause on the last note.

Also, my code calculates the wavelengths of the notes instead of using a big look up table. Maybe a little slower since it involves the pow function, but I don't know, I kinda like doing it that way better.

To make a melodystring,  begin writing the melod string string simply start with the note you want to play, followed by the octive of that note, followed by the optional modifier: # for sharp, and b for flat.

So "C4" would play a middle C. "B3" is the note below middle C and "D4" is the note above it. "F4#" would play a F# in the middle C octive. "G3b" would be G-flat below middle C. Etc.

After the note you can add hold marks '-' or rest marks '.' to rest for one noteBeat. So if you were writing your string in quarter notes (noteBeat = 4) and wanted to start with a middle C, but hold it to a whole note, you would write: "C4---"

playsong() also needs the bpm of the compoition (determining how fast or slow the piece is, 60 is common) and a variable I called noteBeat which determines how playsong will interpret each note in the string. So if you pass in a noteBeat of 1, then all notes will be whole notes, 4 will be all notes being quarter notes (common), 8 will be 8th notes, etc.

Example: For shave and a hair cut, you can call:
   playsong( "C4-G3G3A3-G3-..B3-C4----", 60, 4, [speakerPin]);

It's just that simple. playsong() will play short or long compositions, as long as you fit them in a string. You only need to add playsong.h to your project to use playsong(). Song_Player.ino contains example code that plays 2 tunes, a test one, and shave and a hair cut. Feel free to modify or use it however you see fit. I've done my best to comment the code for you.


