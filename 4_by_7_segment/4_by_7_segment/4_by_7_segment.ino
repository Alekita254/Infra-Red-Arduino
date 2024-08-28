// Segment pin definitions
int segpin[] = {13, 7, 9, 10, 11, 12, 8}; // A, B, C, D, E, F, G
int dpin[] = {3, 4, 5, 6}; // D1, D2, D3, D4

// Segment table for letters and numbers (A-Z and 0-9)
int segTable[] = {
  0b01110111, // A
  0b01111100, // B
  0b00111001, // C
  0b01011110, // D
  0b01111001, // E
  0b01110001, // F
  0b01101111, // G
  0b01110110, // H
  0b00000110, // I
  0b00001110, // J
  0b01110101, // K
  0b00111000, // L
  0b00010101, // M
  0b01010100, // N
  0b00111111, // O
  0b01110011, // P
  0b01100111, // Q
  0b01010000, // R
  0b01101101, // S
  0b01111000, // T
  0b00111110, // U
  0b00111110, // V
  0b01101110, // W
  0b01110110, // X
  0b01101110, // Y
  0b01011011, // Z
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111  // 9
};

// Message to display
char message[] = "HELLO ITS ALEX LIKE SHARE ADIOS "; // Add spaces at the end for smooth scrolling

void setup() {
  // Set segment pins as output
  for (int i = 0; i < 7; i++) {
    pinMode(segpin[i], OUTPUT);
  }
  // Set digit pins as output
  for (int i = 0; i < 4; i++) {
    pinMode(dpin[i], OUTPUT);
    digitalWrite(dpin[i], HIGH); // Turn off all digits initially
  }
}

void loop() {
  // Scroll through each position in the message
  for (int position = 0; position < strlen(message) - 3; position++) {
    for (int i = 0; i < 80; i++) { // Loop to keep the message visible longer
      for (int digit = 0; digit < 4; digit++) {
        displayChar(digit, message[position + digit]);
        delay(3); // Delay for visibility of each digit
      }
    }
  }
}

void displayChar(int digit, char character) {
  // Turn off all digits
  for (int i = 0; i < 4; i++) {
    digitalWrite(dpin[i], HIGH);
  }
  
  // Activate the selected digit
  digitalWrite(dpin[digit], LOW);

  // Find the index in the segTable corresponding to the character
  int segValue = 0;
  if (character >= 'A' && character <= 'Z') {
    segValue = segTable[character - 'A'];
  } else if (character >= '0' && character <= '9') {
    segValue = segTable[character - '0' + 26];
  } else {
    segValue = 0; // For space or unsupported characters
  }

  // Set the segments for the character
  for (int i = 0; i < 7; i++) {
    digitalWrite(segpin[i], bitRead(segValue, i));
  }
  
  // Small delay to stabilize the display
  delay(1);
  
  // Turn off the current digit
  digitalWrite(dpin[digit], HIGH);
}
