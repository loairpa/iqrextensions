/*This file is part of iqr extensions.

    iqr extensions is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    iqr extensions is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with iqr extensions.  If not, see <http://www.gnu.org/licenses/>.

*/

/*
moduleArduinoAnalog.cpp
Author: LIH

based on moduleArduino.cc from iqr-duino: https://github.com/debiatan/iqr-duino


*/

#include <ctime>
#include <vector>
#include "moduleArduinoAnalog.hpp"
#include <iostream>
#include <ostream>
#include <stdlib.h>
using namespace std;
//#include <ModuleIcon_epuck.h>

MAKE_MODULE_DLL_INTERFACE(iqrcommon::ClsModuleArduino, "ArduinoAnalog")

iqrcommon::ClsModuleArduino::ClsModuleArduino() : ClsThreadModule() {
    /*_strName,_strLabel,_strValue,_bEditable,_bLong,_strDescription,_strCategory*/

	device_name = addStringParameter("device_name", "Device",
				     "/dev/ttyUSB0", true, false,
				     "serial port device name", "General");


    par_cps = addIntParameter("cps", "Cycles/Second", 25, 0, 100000,
			      "arduino evaluations per second", "General");
    var_analog_speed=addIntParameter("speed","Analog write", 150,0,255,"Arduino analog strength", "General");
    var_light_limit=addIntParameter("Light sensitivity", "Light Sensor sensitivity", 50,0,1000,"maximum value for light sensor","General");


    var_digital_command_readout = addInputFromGroup("_digital_command_readout",
						    "Command Digital Readout(10)");

    var_digital_read = addOutputToGroup("_digital_read",
					"Digital readings(10)");

    var_digital_command_writing =
	addInputFromGroup("_digital_command_writing",
			  "Command Digital Writing(11)");
    var_digital_write = addInputFromGroup("_digital_write",
					  "Digital Writings(10)");

    var_analog_command_writing = addInputFromGroup("_analog_command_writing",
			  "Command Analog Writing(PWM pins)");

    var_analog_write = addInputFromGroup("_analog_write",
					  "Analog Writings(PWM pins)");

    var_analog_command_reading = addInputFromGroup("_analog_read", "Command Analog Read (A0 for light, A1 for temp)");
    var_analog_read=addOutputToGroup("_analog_read", "Analog Read (1 light, 2 temp)");;
}

#if 0
moduleIcon iqrcommon::ClsModuleArduino::getIcon() {
    moduleIcon mi(ModuleIcon_epuck_png_data,  ModuleIcon_epuck_png_len, 3 ,5);
    return mi;
}
#endif

void iqrcommon::ClsModuleArduino::checkWidth(StateArray& group, int width,
					   const string& group_name){
    if((int)group.getWidth() != width){
	ostringstream w_int;
	w_int<<width;
	throw ModuleError(string("Module ") + label() + ": " + group_name +
			  " group must be of size " + w_int.str());
    }
}

void iqrcommon::ClsModuleArduino::init(){
    StateArray& digital_command_readout =
	var_digital_command_readout->getTarget()->getStateArray();
    StateArray& digital_read = var_digital_read->getStateArray();

    StateArray& digital_command_writing =
	var_digital_command_writing->getTarget()->getStateArray();
    StateArray& digital_write = var_digital_write->getTarget()->getStateArray();

    StateArray& analog_command_writing =
	var_analog_command_writing->getTarget()->getStateArray();
    StateArray& analog_write = var_analog_write->getTarget()->getStateArray();

    StateArray& analog_command_reading =
	    var_analog_command_reading->getTarget()->getStateArray();
	StateArray& analog_read = var_analog_read->getStateArray();

    checkWidth(digital_command_readout, 10, "Command Digital Readout");
    checkWidth(digital_read, 10, "Digital Readings");
    checkWidth(digital_command_writing, 10, "Command Digital Writing");
    checkWidth(digital_write, 10, "Digital Writings");
    checkWidth(analog_command_writing, 6, "Command Analog Writing");
    checkWidth(analog_write, 6, "Analog Writings");
    checkWidth(analog_command_reading, 2, "Command Analog Reading");
    checkWidth(analog_read, 2, "Analog Read");

    if(!arduino.open(device_name->getValue()))
      throw ModuleError(string("Module ")+label()+string(":")+arduino.error());

    gettimeofday(&time_init, NULL);
    elapsed_cicles = 0;
}

void iqrcommon::ClsModuleArduino::relax(){
    struct timeval time_now;
    double elapsed_time, next_computation_time, delta;
    int cps = par_cps->getValue();
    struct timespec sleep_time;

    if(cps){            // User specified a cycles per second value
	gettimeofday(&time_now, NULL);

	elapsed_time = (time_now.tv_sec - time_init.tv_sec) +
	    (time_now.tv_usec - time_init.tv_usec)/1e6;

	next_computation_time = (double)elapsed_cicles/cps;
	delta = next_computation_time - elapsed_time;

	if(delta > 0){
	    sleep_time.tv_sec = (time_t)floor(delta);
	    delta -= floor(delta);
	    sleep_time.tv_nsec = (long)(delta*1e9);
	    nanosleep(&sleep_time, NULL);
	}
	++elapsed_cicles;
    }
}

void iqrcommon::ClsModuleArduino::vectorToGroup(vector<float> origin,
					      StateArray& destination){
    for(int i = 0; i < (int)origin.size(); ++i)
      destination[0][i] = origin[i];
}

void iqrcommon::ClsModuleArduino::update(){
    relax();
    StateArray& digital_command_readout =
	var_digital_command_readout->getTarget()->getStateArray();
    StateArray& digital_read = var_digital_read->getStateArray();

    StateArray& digital_command_writing =
	var_digital_command_writing->getTarget()->getStateArray();
    StateArray& digital_write = var_digital_write->getTarget()->getStateArray();

    StateArray& analog_command_writing =
	var_analog_command_writing->getTarget()->getStateArray();
    StateArray& analog_write = var_analog_write->getTarget()->getStateArray();


    StateArray& analog_command_reading =
	var_analog_command_reading->getTarget()->getStateArray();
    StateArray& analog_read = var_analog_read->getStateArray();

    int speed = var_analog_speed->getValue();
    int lightSens= var_light_limit->getValue();

    vector<float> v_digital_command_readouts,v_digital_command_writings,
    v_digital_write, v_analog_command_writings, v_analog_write, v_analog_command_readings;

  // Analog WRITE
    for(int i = 0; i < (int)analog_command_writing.getWidth(); ++i){
	v_analog_command_writings.push_back(analog_command_writing[0][i]);
	v_analog_write.push_back(abs(analog_write[0][i]*speed));
    }

    arduino.analogWrite(v_analog_command_writings, v_analog_write);

   // Analog Read
    for(int i=0;i<(int)analog_command_reading.getWidth();++i)
	    v_analog_command_readings.push_back(analog_command_reading[0][i]);
    vectorToGroup(arduino.analogRead( v_analog_command_readings,lightSens),analog_read);


    // DIGITAL WRITE
    for(int i = 0; i < (int)digital_command_writing.getWidth(); ++i){
	v_digital_command_writings.push_back(digital_command_writing[0][i]);
	v_digital_write.push_back(digital_write[0][i]);
    }

    arduino.digitalWrite(v_digital_command_writings, v_digital_write);

    // DIGITAL READ
    for(int i = 0; i < (int)digital_command_readout.getWidth(); ++i)
      v_digital_command_readouts.push_back(digital_command_readout[0][i]);

    vectorToGroup(arduino.digitalRead(v_digital_command_readouts),
		  digital_read);

}

void iqrcommon::ClsModuleArduino::cleanup(){
    // Set all pins to read state
   StateArray& digital_command_readout =
	var_digital_command_readout->getTarget()->getStateArray();
    StateArray& analog_command_reading =
	var_analog_command_reading->getTarget()->getStateArray();

    vector<float> v_digital_command_readouts(digital_command_readout.getWidth(),
					     0.);
    vector<float> v_analog_command_readings(analog_command_reading.getWidth(),
					     0.);
    arduino.digitalRead(v_digital_command_readouts);
    arduino.analogRead(v_analog_command_readings, 0);
    arduino.close();
}





