#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3);        // Initialize UNO RX2 | TX3 connect to combined TX | RX of HC05s

#define STEPPER_PIN_1 9               // Setup UNO pin9 for stepper motor
#define STEPPER_PIN_2 10              // Setup UNO pin10 for stepper motor
#define STEPPER_PIN_3 11              // Setup UNO pin11 for stepper motor
#define STEPPER_PIN_4 12              // Setup UNO pin12 for stepper motor

const byte BTpin = 7;                 // From State pin HC05 to UNO pin7
const byte BT2pin = 5;                // From State pin HC05_2 to UNO pin5
int toWifi = 8;                       // Signal to WiFi Bluetooth 
int toWifi2 = 13;                     // Signal to WiFi Bluetooth
int step_number = 0;                  // Used for opperating the 4 pins
int openStatus = 6;                   // Open state of 
    

<<<<<<< HEAD
String fromPC = ""; // Stores characters sent from APP
int step_number = 0; // 
int rec = 0;
const byte BTpin = 7; // From State pin HC05 to UNO pin7
const byte BT2pin = 5; // From State pin HC05_2 to UNO pin5
int toWifi = 8;
int toWifi2 = 13;
int a = 0;
int i = 0;
int b = 0;
int openStatus = 6; // Open state
bool BTconnected = false;
bool BT6connected = false;
=======
>>>>>>> 7569fe44b8d0091ed938740d19e47abb51406b78

void setup() {
    pinMode(STEPPER_PIN_1, OUTPUT);   // Initialize pin9 UNO - stepper motor IN4
    pinMode(STEPPER_PIN_2, OUTPUT);   // Initialize pin10 UNO - stepper motor IN3
    pinMode(STEPPER_PIN_3, OUTPUT);   // Initialize pin11 on UNO - stepper motor IN2
    pinMode(STEPPER_PIN_4, OUTPUT);   // Initialize pin12 on UNO - stepper motor IN1
    pinMode(BTpin, INPUT);            // Initialize pin7 on UNO
    pinMode(BT2pin, INPUT);           // Initialize pin5 on UNO
    pinMode(toWifi, OUTPUT);          // Initialize pin8 on UNO
    pinMode(toWifi2, OUTPUT);         // Initialize pin13 on UNO
    pinMode(openStatus, OUTPUT);      // Initialize pin6 on UNO output to Wifi 
    BTserial.begin(9600);             // Default communication rate of bluetooth connector
    Serial.begin(115200);             // Hardware serial for USB
    Serial.println("Hello");          // "Hello" output through serial port 
}


void loop() {
    boolean BTconnected = false;
    boolean BT6connected = false;
    int rec = 0;
    int a = 0;
    int i = 0;
    int b = 0;
    String fromPC = "";               // Stores characters sent from APP
    
                                      // look for command in rest mode logic
    digitalWrite(openStatus, HIGH);
    rec = 0;
    if(BTserial.available() > 0) {    // checks if connection to bluetooth
        rec = BTserial.read();        // reads data from bluetooth
        Serial.print((char)BTserial.read()); //send it to the PC
    }
    if (Serial.available()) {
        delay(10);
        fromPC = (char)Serial.read();
        BTserial.print(fromPC);
        Serial.print(fromPC);
    }
    if ( digitalRead(BTpin)==HIGH){  // Tests whether hc05 is connected
        digitalWrite(toWifi, HIGH);
    }
    else {
        digitalWrite(toWifi, LOW);
    }
    if ( digitalRead(BT2pin)==HIGH){ // Tests whether hc05_2 is connected
        digitalWrite(toWifi2, HIGH);
    }
    else {
        digitalWrite(toWifi2, LOW);
    }
    if (rec == 'a') {
        digitalWrite(openStatus, LOW);
        b = 0;
        begin_open:
        rec = 0;
        for(i = b; i < 600; i++) {  //OPEN loop
            OneStep(true);
            delay(2);
        }
        dela:                       // the delay in door loop befor close after open
        rec = 0;
        delay(3000);
        // Dela postion listen logic
        if(BTserial.available() > 0) { // checks if connection to bluetooth
            rec = BTserial.read();  // reads data from bluetooth
        }
        if(rec == 'a') {
            goto dela;
        }    
        rec = 0;    
        for(a = 600; a > 0; a--){   //CLOSE loop
                                    // Closing postion listen loop
            OneStep(false);
            delay(10);
            if(BTserial.available() > 0) { // checks if connection to bluetooth
                rec = BTserial.read(); // reads data from bluetooth
            }
            if(rec == 'a') {
                b = a;
                goto begin_open;
            }    
        }
        digitalWrite(openStatus, HIGH);
        rec = 0;
    }
}
                                   // Below code controls the stepper motor
void OneStep(bool dir) {           //Declares rotation direction
    if(dir) {
        switch(step_number) {
            case 0:
                digitalWrite(STEPPER_PIN_1, HIGH);
                digitalWrite(STEPPER_PIN_2, LOW);
                digitalWrite(STEPPER_PIN_3, LOW);
                digitalWrite(STEPPER_PIN_4, LOW);
            break;
            case 1:
                digitalWrite(STEPPER_PIN_1, LOW);
                digitalWrite(STEPPER_PIN_2, HIGH);
                digitalWrite(STEPPER_PIN_3, LOW);
                digitalWrite(STEPPER_PIN_4, LOW);
            break;
            case 2:
                digitalWrite(STEPPER_PIN_1, LOW);
                digitalWrite(STEPPER_PIN_2, LOW);
                digitalWrite(STEPPER_PIN_3, HIGH);
                digitalWrite(STEPPER_PIN_4, LOW);
            break;
            case 3:
                digitalWrite(STEPPER_PIN_1, LOW);
                digitalWrite(STEPPER_PIN_2, LOW);
                digitalWrite(STEPPER_PIN_3, LOW);
                digitalWrite(STEPPER_PIN_4, HIGH);
            break;
        }
    } else {
        switch(step_number){
            case 0:
                digitalWrite(STEPPER_PIN_1, LOW);
                digitalWrite(STEPPER_PIN_2, LOW);
                digitalWrite(STEPPER_PIN_3, LOW);
                digitalWrite(STEPPER_PIN_4, HIGH);
            break;
            case 1:
                digitalWrite(STEPPER_PIN_1, LOW);
                digitalWrite(STEPPER_PIN_2, LOW);
                digitalWrite(STEPPER_PIN_3, HIGH);
                digitalWrite(STEPPER_PIN_4, LOW);
            break;
            case 2:
                digitalWrite(STEPPER_PIN_1, LOW);
                digitalWrite(STEPPER_PIN_2, HIGH);
                digitalWrite(STEPPER_PIN_3, LOW);
                digitalWrite(STEPPER_PIN_4, LOW);
            break;
            case 3:
                digitalWrite(STEPPER_PIN_1, HIGH);
                digitalWrite(STEPPER_PIN_2, LOW);
                digitalWrite(STEPPER_PIN_3, LOW);
                digitalWrite(STEPPER_PIN_4, LOW);
        }
    }
    step_number++;
    if(step_number > 3) {
        step_number = 0;
    }
}