#include "application.h"

Servo wings;

#include "neopixel.h"

#define PIN_SERVO   D0
#define PIN_SPEAKER D7

#define PIXEL_COUNT 12
#define PIXEL_PIN   D2
#define PIXEL_TYPE  SK6812RGBW

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

String play_song = "";

int gamma[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
    10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
    17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
    25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
    37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
    51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
    69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
    90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
    115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
    144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
    177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
    215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255
};

void setup() {
    strip.setBrightness(127);
    strip.begin();
    strip.show();

    pinMode(PIN_SPEAKER, OUTPUT);
    digitalWrite(PIN_SPEAKER, LOW);

    wings.attach(PIN_SERVO);

    Particle.function("wings", doWings);
    Particle.function("song", doSong);
}


void loop() {
    // whiteOverRainbow(20, 75, 5);
    whiteOverRainbow(80, 150, 6);

    checkSong();
}


// void playOther() {
//     int length = 15; // the number of notes
//     char notes[] = "ccggaagffeeddc "; // a space represents a rest
//     int beats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
//     int tempo = 300;

//     for (int i = 0; i < length; i++) {
//         if (notes[i] == ' ') {
//             delay(beats[i] * tempo); // rest
//         } else {
//             playNote(notes[i], beats[i] * tempo);
//         }

//         // pause between notes
//         delay(tempo / 2);
//     }
// }


int doWings(String cmd) {
    int angle = cmd.toInt();

    if(angle==20) {
        wings.write(20);
        delay(100);
        wings.write(18);
    }

    else if(angle==0) {
        wings.write(0);
        delay(100);
        wings.write(2);
    }

    return angle;
}


int doSong(String song) {
    play_song = song;

    return 1;
}


void checkSong() {
    if(play_song=="")
        return;

    wings.write(20);
    delay(250);
    wings.write(18);

    if(play_song=="hark")
        HarkTheHerald();

    else if(play_song=="godrest")
        GodRestYeMerryGentlemen();

    else if(play_song=="ohcome")
        OhComeAllYeFaithful();

    else if(play_song=="jingle")
        JingleBells();

    wings.write(0);
    delay(250);
    wings.write(2);

    play_song = "";
}


void playTone(int tone, int duration) {
    for (long i = 0; i < duration * 1000L; i += tone * 2) {
        digitalWrite(PIN_SPEAKER, HIGH);
        delayMicroseconds(tone);
        digitalWrite(PIN_SPEAKER, LOW);
        delayMicroseconds(tone);
    }
}


void playNote(char note, int duration) {
    char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
    int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

    // play the tone corresponding to the note name
    for (int i = 0; i < 8; i++) {
        if (names[i] == note) {
            playTone(tones[i], duration);
        }
    }

    Particle.process();
}


void HarkTheHerald() {
    int length = 77;
    char notes[] = "cffefaagCCCvagacffefaagCffeedcCCCfvaagCCCfvaagDDDCvavgavCffgaDDDCvavgavCffgf ";
    int beats[] = {2,2,3,1,2,2,2,2,2,2,3,1,2,2,4,2,2,3,1,2,2,2,2,2,2,3,1,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,1,1,3,1,2,2,4,3,1,2,2,2,2,4,2,1,1,3,1,2,2,4,8};
    int tempo = 250;

    for (int i = 0; i < length; i++) {
        if (notes[i] == ' ') {
            delay(beats[i] * tempo); // rest
        } else {
            playNote(notes[i], beats[i] * tempo);
        }

        // pause between notes
        delay(tempo / 2);
    }
}


void GodRestYeMerryGentlemen() {
    int length = 69;
    char notes[] = "ddaagfedcdefga ddaagfedcdefga avgavCDagfdefgfgavaagfedfedgfgavCDagfed";
    int beats[] = { 2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,2,4,2,2,2,2,2,2,4,1,1,2,4,2,2,2,2,2,2,2,2,2,2,8 };
    int tempo = 250;

    for (int i = 0; i < length; i++) {
        if (notes[i] == ' ') {
            delay(beats[i] * tempo); // rest
        } else {
            playNote(notes[i], beats[i] * tempo);
        }

        // pause between notes
        delay(tempo / 2);
    }
}


void OhComeAllYeFaithful() {
    int length = 64;
    char notes[] = "ggdgadbabCbaggsesgabsedd DCbCbabgasedggsgagdbbabCbabCbagsgCbagg ";
    int beats[] = { 2,4,2,2,4,4,2,2,2,2,4,2,2,4,2,2,2,2,2,2,4,3,1,6,2,4,2,2,4,4,2,2,2,2,3,1,2,2,2,2,2,2,4,2,2,2,2,2,2,4,2,2,2,2,2,2,4,2,2,4,3,1,6,8 };
    int tempo = 250;

    for (int i = 0; i < length; i++) {
        if (notes[i] == ' ') {
            delay(beats[i] * tempo); // rest
        } else {
            playNote(notes[i], beats[i] * tempo);
        }

        // pause between notes
        delay(tempo / 2);
    }
}


void JingleBells() {
    int length = 26;
    int tempo = 200;
    char notes[] = "eeeeeeegcde fffffeeeeddedg";
    int beats[] = {1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2};

    for (int i = 0; i < length; i++) {
        if (notes[i] == ' ') {
            delay(beats[i] * tempo); // rest
        } else {
            playNote(notes[i], beats[i] * tempo);
        }

        // pause between notes
        delay(tempo / 2);
    }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
    WheelPos = 255 - WheelPos;

    if(WheelPos < 85) {
        return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3,0);
    }

    if(WheelPos < 170) {
        WheelPos -= 85;
        return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3,0);
    }

    WheelPos -= 170;
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0,0);
}


void whiteOverRainbow(uint8_t wait, uint8_t whiteSpeed, uint8_t whiteLength ) {
    if(whiteLength >= strip.numPixels())
        whiteLength = strip.numPixels() - 1;

    int head = whiteLength - 1;
    int tail = 0;
    int loops = 3;
    int loopNum = 0;
    static unsigned long lastTime = 0;

    while(true) {
        for(int j=0; j<256; j++) {
            for(uint16_t i=0; i<strip.numPixels(); i++) {
                if( (i >= tail && i <= head)
                    || (tail > head && i >= tail)
                    || (tail > head && i <= head) ) {
                    strip.setPixelColor(i, strip.Color(0,0,0, 255 ) );
                } else {
                    strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
                }
            }

            if(millis() - lastTime > whiteSpeed) {
                head++;
                tail++;

                if(head == strip.numPixels()) {
                    loopNum++;
                }

                lastTime = millis();
            }

            if(loopNum == loops)
                return;

            head %= strip.numPixels();
            tail %= strip.numPixels();

            strip.show();
            Particle.process();
            delay(wait);
        }
    }
}

