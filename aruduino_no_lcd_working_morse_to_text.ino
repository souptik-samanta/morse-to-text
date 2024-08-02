String m = "";
boolean toread = true;

const int dotPin = 10;
const int dashPin = 6;
const int spacePin = 11;
const int submitPin = 9;
const int resetPin = 5;

void setup() {
   Serial.begin(9600);
   pinMode(LED_BUILTIN, OUTPUT);
   pinMode(dotPin, INPUT_PULLUP);
   pinMode(dashPin, INPUT_PULLUP);
   pinMode(spacePin, INPUT_PULLUP);
   pinMode(submitPin, INPUT_PULLUP);
   pinMode(resetPin, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(resetPin) == LOW) {
    m = "";
    toread = true;
    delay(500); // Debounce delay
  }

  if (toread) {
    if (digitalRead(spacePin) == LOW) {
      m += " ";
      delay(500); // Debounce delay
    }

    if (digitalRead(dotPin) == LOW) {
      m += ".";
      delay(500); // Debounce delay
    }

    if (digitalRead(dashPin) == LOW) {
      m += "-";
      delay(500); // Debounce delay
    }

    if (digitalRead(submitPin) == LOW) {
      toread = false;
      String translatedText = posofdatatoeng(m);
      Serial.println(translatedText);
      delay(500); // Debounce delay
    }
  }
}

String posofdatatoeng(String s) {
  String translatedText = "";
  String morseLetter = "";
  s.trim(); // Remove any leading or trailing spaces

  for (int i = 0; i < s.length(); i++) {
    char c = s.charAt(i);

    if (c == ' ') {
      if (morseLetter.length() > 0) {
        translatedText += data(morseLetter);
        morseLetter = "";
      }
    } else {
      morseLetter += c;
    }
  }

  // Translate the last Morse code letter if any
  if (morseLetter.length() > 0) {
    translatedText += data(morseLetter);
  }

  return translatedText;
}

String data(String nw) {
  char letters[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
                  'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
                  'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };

  String codes[] = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
                  "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
                  "..-", "...-", ".--", "-..-", "-.--", "--..", ".----", "..---", "...--",
                  "....-", ".....", "-....", "--...", "---..", "----.", "-----" };

  for (int i = 0; i < 36; i++) {
    if (nw == codes[i]) {
      return String(letters[i]);
    }
  }
  return ""; // Return empty string if no match found
}
