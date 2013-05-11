/*
arduino.h
Extensions: LIH

based on arduino.h from iqr-duino: https://github.com/debiatan/iqr-duino


*/

#ifndef _ARDUINO_H
#define _ARDUINO_H

#include <string>
#include <vector>
#include "serialstream/SerialStream.h"
using namespace std;
using namespace LibSerial;

typedef enum{INPUT = 0, OUTPUT = 1} Mode;
typedef enum{LOW = 0, HIGH = 1} BinValue;
typedef enum{EXTERNAL = 0, DEFAULT = 1, INTERNAL = 3} ReferenceSource;

class Arduino{
    private:
        string error_message;
        SerialStream serialPort;

        void write_word(int value);
        int read_word();
	int read_analog_value();
	void empty_buffer(int pin);

	vector<int> current_digital_pin_modes;
        vector<int> current_digital_outputs;

	vector<int> current_analog_pin_modes;
	vector<int> current_analog_outputs;

	vector<int>current_PWM_pin_modes;
	vector<int> current_PWM_outputs ;

        void pinMode(int pin, Mode mode);
        int digitalRead(int pin);
        void digitalWrite(int pin, BinValue value);
        void analogReference(ReferenceSource source);
	int analogRead(int pin);
        void analogWrite(int pin, int value);


    public:
        Arduino();
        bool open(const string& device);
        void close();

         vector<float> digitalRead(vector<float> pins);
        void digitalWrite(vector<float> pins, vector<float> values);

	// Analog
	void analogWrite(vector<float> pins, vector<float> values);
	vector<float> analogRead(vector<float> pins,int lightLim);



        string error();
};

#endif // _ARDUINO_H
