const int rxPumpPin = A0;
const int rxRedPin = A1;
const int rxGreenPin = A2;
const int rxBluePin = A3;

const int txPumpPin = 10;
const int txRedPin = 6;
const int txGreenPin = 5;
const int txBluePin = 3;
const int readEnablePin = 2;

// Constrained to [0,255]
int pumpVal = 0;
int redVal = 0;
int greenVal = 0;
int blueVal = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(txPumpPin, OUTPUT);
  pinMode(txRedPin, OUTPUT);
  pinMode(txGreenPin, OUTPUT);
  pinMode(txBluePin, OUTPUT);
  
  pinMode(rxPumpPin, INPUT);
  pinMode(rxRedPin, INPUT);
  pinMode(rxGreenPin, INPUT);
  pinMode(rxBluePin, INPUT);
  pinMode(readEnablePin, INPUT);
}

void loop() {
  if (digitalRead(readEnablePin) == HIGH) {
    // analogRead returns 0..1023, need to shift to translate to 0..255 range
    pumpVal = analogRead(rxPumpPin) >> 2;
    redVal = analogRead(rxRedPin) >> 2;
    greenVal = analogRead(rxGreenPin) >> 2;
    blueVal = analogRead(rxBluePin) >> 2; 
  }

  analogWrite(txPumpPin, pumpVal);
  analogWrite(txRedPin, redVal);
  analogWrite(txGreenPin, greenVal);
  analogWrite(txBluePin, blueVal);

  Serial.print(pumpVal);
  Serial.print("\n");
}
