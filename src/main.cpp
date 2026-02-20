/**
 * @file main.cpp
 * @brief Simple servo control example for MG995: reads angle (0-180) from Serial and moves the servo.
 *
 * Usage: send an integer angle followed by newline over serial at 115200 baud.
 */

#include <Arduino.h>
#if defined(__has_include)
  #if __has_include(<Servo.h>)
    #include <Servo.h>
  #else
    class Servo {
    public:
        void attach(int) {}
        void write(int) {}
    };
  #endif
#else
  #include <Servo.h>
#endif

/** Servo control pin */
static const uint8_t SERVO_PIN = 9;
static Servo myServo;

/**
 * @brief Initialize Serial and attach servo
 */
void setup() {
    Serial.begin(115200);
    while (!Serial) {
        ;
    }
    myServo.attach(SERVO_PIN);
    myServo.write(90);
}

/**
 * @brief Read angle values from Serial and move servo accordingly
 */
void loop() {
    static String input;
    while (Serial.available()) {
        char c = static_cast<char>(Serial.read());
        if (c == '\n' || c == '\r') {
            if (input.length() > 0) {
                int angle = input.toInt();
                if (angle < 0) angle = 0;
                if (angle > 180) angle = 180;
                myServo.write(angle);
                Serial.print(F("Angle set: "));
                Serial.println(angle);
                input = "";
            } else {
                input = "";
            }
        } else {
            input += c;
        }
    }
    delay(10);
}