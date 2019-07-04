const int txEnable0Pin = 13;
const int txEnable1Pin = 12;
const int txData0Pin = 2;
const int txData1Pin = 3;
const int txData2Pin = 4;
const int txData3Pin = 5;
const int txData4Pin = 6;
const int txData5Pin = 7;
const int txMode0Pin = 22;
const int txMode1Pin = 23;
const int holdTime = 20; // ms

enum txMode {
  MODE_RED,
  MODE_GREEN,
  MODE_BLUE,
  MODE_PUMP,
  MODE_INVALID
};

struct PumpState
{
  int r;
  int g;
  int b;
  int p;

  void increment() {
    r = (r + 1) % 64;
    g = (g + 1) % 64;
    b = (b + 1) % 64;
    p = (p + 1) % 64;
  }
};

unsigned int time = 0;
unsigned int lastPrint = 0;

PumpState ps0;
PumpState ps1;

void setup() {
  Serial.begin(9600);
  ps0.r = 16;
  ps0.g = 32;
  ps0.b = 48;
  ps0.p = 0;
  ps1.r = 48;
  ps1.g = 0;
  ps1.b = 16;
  ps1.p = 32;
  time = 0;
  
  pinMode(txEnable0Pin, OUTPUT);
  pinMode(txEnable1Pin, OUTPUT);
  pinMode(txData0Pin, OUTPUT);
  pinMode(txData1Pin, OUTPUT);
  pinMode(txData2Pin, OUTPUT);
  pinMode(txData3Pin, OUTPUT);
  pinMode(txData4Pin, OUTPUT);
  pinMode(txData5Pin, OUTPUT);
  pinMode(txMode0Pin, OUTPUT);
  pinMode(txMode1Pin, OUTPUT);
}

void writeValue(int addressPin, txMode mode, int val) {
  digitalWrite(addressPin, LOW);
  digitalWrite(txMode0Pin, (int)mode & 0x01 ? HIGH : LOW);
  digitalWrite(txMode1Pin, (int)mode & 0x02 ? HIGH : LOW);
  digitalWrite(txData0Pin, val >> 0 & 0x01 ? HIGH : LOW);
  digitalWrite(txData1Pin, val >> 1 & 0x01 ? HIGH : LOW);
  digitalWrite(txData2Pin, val >> 2 & 0x01 ? HIGH : LOW);
  digitalWrite(txData3Pin, val >> 3 & 0x01 ? HIGH : LOW);
  digitalWrite(txData4Pin, val >> 4 & 0x01 ? HIGH : LOW);
  digitalWrite(txData5Pin, val >> 5 & 0x01 ? HIGH : LOW);
  digitalWrite(addressPin, HIGH);
}

void printState() {
  Serial.print("(Master) R0: ");
  Serial.print(ps0.r);
  Serial.print(", G0: ");
  Serial.print(ps0.g);
  Serial.print(", B0: ");
  Serial.print(ps0.b);
  Serial.print(", P0: ");
  Serial.print(ps0.p);
  Serial.print(" || R1: ");
  Serial.print(ps0.r);
  Serial.print(", G1: ");
  Serial.print(ps0.g);
  Serial.print(", B1: ");
  Serial.print(ps0.b);
  Serial.print(", P1: ");
  Serial.print(ps0.p);
  Serial.print('\n');
}

void loop() {
  time = millis();
  writeValue(txEnable0Pin, MODE_RED, ps0.r);
  delay(holdTime);
  writeValue(txEnable0Pin, MODE_GREEN, ps0.g);
  delay(holdTime);
  writeValue(txEnable0Pin, MODE_BLUE, ps0.b);
  delay(holdTime);
  writeValue(txEnable0Pin, MODE_PUMP, ps0.p);
  delay(holdTime);
//  
//  writeValue(txEnable1Pin, MODE_RED, ps1.r);
//  delay(holdTime);
//  writeValue(txEnable1Pin, MODE_GREEN, ps1.g);
//  delay(holdTime);
//  writeValue(txEnable1Pin, MODE_BLUE, ps1.b);
//  delay(holdTime);
//  writeValue(txEnable1Pin, MODE_PUMP, ps1.p);
//  delay(holdTime);

  if (time - lastPrint > 100) {
    printState();
    lastPrint = time;
  }
  
  ps0.increment();
  ps1.increment();
}
