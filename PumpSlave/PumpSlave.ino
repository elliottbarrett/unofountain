const int rxEnablePin = 13;
const int rxData0Pin = A5;
const int rxData1Pin = A4;
const int rxData2Pin = A3;
const int rxData3Pin = A2;
const int rxData4Pin = A1;
const int rxData5Pin = A0;
const int rxMode0Pin = 4;
const int rxMode1Pin = 2;
const int txRedPin = 9;
const int txGreenPin = 10;
const int txBluePin = 11;
const int txPumpPin = 6;

enum RxMode {
  MODE_RED,
  MODE_GREEN,
  MODE_BLUE,
  MODE_PUMP,
  MODE_INVALID
};

unsigned int rVal = 0;
unsigned int gVal = 0;
unsigned int bVal = 0;
unsigned int pVal = 0;
RxMode mode = MODE_INVALID;

unsigned int time = 0;
unsigned int lastPrint = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(rxEnablePin, INPUT);
  pinMode(rxData0Pin, INPUT);
  pinMode(rxData1Pin, INPUT);
  pinMode(rxData2Pin, INPUT);
  pinMode(rxData3Pin, INPUT);
  pinMode(rxData4Pin, INPUT);
  pinMode(rxData5Pin, INPUT);
  pinMode(rxMode0Pin, INPUT);
  pinMode(rxMode1Pin, INPUT);
  
  pinMode(txRedPin, OUTPUT);
  pinMode(txGreenPin, OUTPUT);
  pinMode(txBluePin, OUTPUT);
  pinMode(txPumpPin, OUTPUT);
}

void readMode() {
  int val = (digitalRead(rxMode1Pin) == HIGH ? 1 : 0);
  val = (val << 1) | (digitalRead(rxMode0Pin) == HIGH ? 1 : 0);
  mode = (RxMode) val;
}

void readValue() {
  unsigned int val = (digitalRead(rxData5Pin) == HIGH ? 1 : 0);
  val = (val << 1) | (digitalRead(rxData4Pin) == HIGH ? 1 : 0);
  val = (val << 1) | (digitalRead(rxData3Pin) == HIGH ? 1 : 0);
  val = (val << 1) | (digitalRead(rxData2Pin) == HIGH ? 1 : 0);
  val = (val << 1) | (digitalRead(rxData1Pin) == HIGH ? 1 : 0);
  val = (val << 1) | (digitalRead(rxData0Pin) == HIGH ? 1 : 0);
  
  switch (mode) {
    case MODE_RED:
      rVal = val;
      break;
    case MODE_GREEN:
      gVal = val;
      break;
    case MODE_BLUE:
      bVal = val;
      break;
    case MODE_PUMP:
      pVal = val;
      break;
  }
}

void printState() {
  Serial.print("(Slave) R: ");
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
  if (digitalRead(rxEnablePin) == HIGH) {
    readMode();
    readValue();
  }
  analogWrite(txRedPin, rVal);
  analogWrite(txGreenPin, gVal);
  analogWrite(txBluePin, bVal);
  analogWrite(txPumpPin, pVal);
  if (time - lastPrint > 100) {
    lastPrint = time;
    printState();
  }
  delay(30);
}
