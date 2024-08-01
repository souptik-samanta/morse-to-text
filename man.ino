#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD, change the address if needed (e.g., 0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Pins for the switches
const int dotPin = A1;
const int dashPin = A0;

char letter[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
                  'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
                  'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };
String code[] = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
                  "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
                  "..-", "...-", ".--", "-..-", "-.--", "--..", "|" };

// Variables to store Morse code input
String morseInput = "";
String decodedMessage = "";

//setup
void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(dotPin, INPUT_PULLUP);
  pinMode(dashPin, INPUT_PULLUP);

  lcd.setCursor(0, 0);
  lcd.print("Morse Code Decoder");
}



//fumction
String morseToEnglish(String morseCode) {
  for (int j = 0; j < sizeof(code) / sizeof(code[0]); j++) {
    if (morseCode == code[j]) {
      return String((char)(j + 'a'));
    }
  }
  return ""; // Return empty string if no match found
}
