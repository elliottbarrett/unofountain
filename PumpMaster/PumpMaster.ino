const int txEnablePin = 13;
const int txData0Pin = 2;
const int txData1Pin = 3;
const int txData2Pin = 4;
const int txData3Pin = 5;
const int txData4Pin = 6;
const int txData5Pin = 7;
const int txMode0Pin = 22;
const int txMode1Pin = 23;
const int holdTime = 15; // ms

enum txMode {
  MODE_RED,
  MODE_GREEN,
  MODE_BLUE,
  MODE_PUMP,
  MODE_INVALID
};

int rVal;
int gVal;
int bVal;
int pVal;
unsigned int time = 0;
unsigned int lastPrint = 0;

void setup() {
  Serial.begin(9600);
  rVal = 16;
  gVal = 32;
  bVal = 48;
  pVal = 0;
  time = 0;
  
  pinMode(txEnablePin, OUTPUT);
  pinMode(txData0Pin, OUTPUT);
  pinMode(txData1Pin, OUTPUT);
  pinMode(txData2Pin, OUTPUT);
  pinMode(txData3Pin, OUTPUT);
  pinMode(txData4Pin, OUTPUT);
  pinMode(txData5Pin, OUTPUT);
  pinMode(txMode0Pin, OUTPUT);
  pinMode(txMode1Pin, OUTPUT);
}

void writeValue(txMode mode, int val) {
  digitalWrite(txEnablePin, LOW);
  digitalWrite(txMode0Pin, (int)mode & 0x01 ? HIGH : LOW);
  digitalWrite(txMode1Pin, (int)mode & 0x02 ? HIGH : LOW);
  digitalWrite(txData0Pin, val >> 0 & 0x01 ? HIGH : LOW);
  digitalWrite(txData1Pin, val >> 1 & 0x01 ? HIGH : LOW);
  digitalWrite(txData2Pin, val >> 2 & 0x01 ? HIGH : LOW);
  digitalWrite(txData3Pin, val >> 3 & 0x01 ? HIGH : LOW);
  digitalWrite(txData4Pin, val >> 4 & 0x01 ? HIGH : LOW);
  digitalWrite(txData5Pin, val >> 5 & 0x01 ? HIGH : LOW);
  digitalWrite(txEnablePin, HIGH);
}

void printState() {
  Serial.print("(Master) R: ");
  Serial.print(rVal);
  Serial.print(", G: ");
  Serial.print(gVal);
  Serial.print(", B: ");
  Serial.print(bVal);
  Serial.print(", P: ");
  Serial.print(pVal);
  Serial.print('\n');
}

void loop() {
  time = millis();
  writeValue(MODE_RED, rVal);
  delay(holdTime);
  writeValue(MODE_GREEN, gVal);
  delay(holdTime);
  writeValue(MODE_BLUE, bVal);
  delay(holdTime);
  writeValue(MODE_PUMP, pVal);
  delay(holdTime);
  digitalWrite(txEnablePin, LOW);
  delay(100 - holdTime * 4);
  rVal = (rVal + 1) % 64;
  gVal = (gVal + 1) % 64;
  bVal = (bVal + 1) % 64;
  pVal = (pVal + 1) % 64;
  if (time - lastPrint > 100) {
    printState();
    lastPrint = time;
  }
}
