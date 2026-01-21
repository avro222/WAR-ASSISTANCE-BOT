#include <AFMotor.h>
#include <Servo.h>

AF_DCMotor MotorFR(1); AF_DCMotor MotorFL(2);
AF_DCMotor MotorBL(3); AF_DCMotor MotorBR(4);

Servo spikeServo;   
Servo cannonServo;  

// Speed maximum (255) kore dilam
int valSpeed = 255; 

void setup() {
    Serial.begin(9600); 
    // Sob motor-er speed maximum set kora
    SetSpeed(valSpeed);
    StopMotors();
}

void loop() {
    if (Serial.available() > 0) {
        char command = Serial.read();
        
        switch(command) {
            case 'F': MoveForward(); break;
            case 'B': MoveBackward(); break;
            case 'R': TurnRight(); break;
            case 'L': TurnLeft(); break;
            case 'S': StopMotors(); break;
            
            case 'W': // Spike
                spikeServo.attach(10);
                spikeServo.write(110); 
                delay(800);           
                spikeServo.write(0);   
                delay(150);
                spikeServo.detach();   
                break;

            case 'K': // Cannon
                cannonServo.attach(9);
                cannonServo.write(180); 
                delay(300);             
                cannonServo.write(0);   
                delay(100);
                cannonServo.detach();  
                break;
        }
    }
}

void MoveForward() {
    SetSpeed(255); // Full power
    MotorFL.run(FORWARD); MotorFR.run(FORWARD);
    MotorBL.run(FORWARD); MotorBR.run(FORWARD);
}

void MoveBackward() {
    SetSpeed(255);
    MotorFL.run(BACKWARD); MotorFR.run(BACKWARD);
    MotorBL.run(BACKWARD); MotorBR.run(BACKWARD);
}

void TurnRight() {
    SetSpeed(255);
    MotorFL.run(FORWARD); MotorBL.run(FORWARD);
    MotorFR.run(RELEASE); MotorBR.run(RELEASE);
}

void TurnLeft() {
    SetSpeed(255);
    MotorFR.run(FORWARD); MotorBR.run(FORWARD);
    MotorFL.run(RELEASE); MotorBL.run(RELEASE);
}

void StopMotors() {
    MotorFL.run(RELEASE); MotorFR.run(RELEASE);
    MotorBL.run(RELEASE); MotorBR.run(RELEASE);
}

void SetSpeed(int val) {
    MotorFL.setSpeed(val); MotorFR.setSpeed(val);
    MotorBL.setSpeed(val); MotorBR.setSpeed(val);
}