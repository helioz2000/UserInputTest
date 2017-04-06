#define SERIAL_BAUDRATE 19200

#define UI_INTERVAL 200
#define UI_H 712
#define UI_HH UI_H + UI_INTERVAL
//#define ai_HHH ai_HH + ai_INTERVAL
#define UI_L 312
#define UI_LL UI_L - UI_INTERVAL
//#define ai_LLL ai_LL - ai_INTERVAL

enum userinput {
  LowLow,
  Low,
  Middle,
  High,
  HighHigh,
};

int sensorPin = A7;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

int value = 0;

userinput inputState = Middle;

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
    Serial.begin(SERIAL_BAUDRATE);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void inputRead() {
  int  sensorValue = analogRead(sensorPin);
  //Serial.println(sensorValue);

  if ( sensorValue > UI_H ) {
    if ( sensorValue > UI_HH ) {
      inputState = HighHigh;
      //Serial.println("++");
    } else {
      inputState = High;
      //Serial.println("+");
    }
  } else {
    if ( sensorValue < UI_L ) {
      if ( sensorValue < UI_LL ) {
        inputState = LowLow;
        //Serial.println("--");
      } else {
        inputState = Low;
        //Serial.println("-");
      }
    } else {
      inputState = Middle;
    }
  }
}

void loop() {
  inputRead();

  switch (inputState) {
    case Low:
    case LowLow:
      value--;
      break;
    case High:
    case HighHigh:
      value++;
      break;
    default:
      break;
  }
    
  Serial.println(value);
  
  // delay
  switch (inputState) {
    case Low:
    case High:
      delay(600);
      break;
    case LowLow:
    case HighHigh:
      delay(200);
      break;
    default:
      break;
  }
}
