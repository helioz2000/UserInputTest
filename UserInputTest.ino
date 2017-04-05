#define SERIAL_BAUDRATE 19200

#define UI_INTERVAL 206
#define UI_H 612
#define UI_HH UI_H + UI_INTERVAL
//#define ai_HHH ai_HH + ai_INTERVAL
#define UI_L 412
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
  delay(300);
  switch(inputState) {
    
    case LowLow:
      value -= 3 ;
      break;
    case Low:
      value-- ;
      break;
    case High:
      value++ ;
      break;
    case HighHigh:
      value += 3 ;
      break;
    default:
    break;
  }

  Serial.println(value);

}
