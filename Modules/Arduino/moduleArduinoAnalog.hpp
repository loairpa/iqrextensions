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
moduleArduinoAnalog.hpp
Author: LIH

based on moduleArduino.cc from iqr-duino: https://github.com/debiatan/iqr-duino


*/

#ifndef MODULEARDUINOANALOG_HPP


#define MODULEARDUINOANALOG_HPP


#include <Common/Item/threadModule.hpp>
#include <sys/time.h>
#include "arduino.h"

using namespace std;
namespace iqrcommon{
	class ClsModuleArduino : public ClsThreadModule{
		public:
			ClsModuleArduino();
			void init();
			void update();
			void cleanup();


		private:
			ClsModuleArduino(const ClsModuleArduino&);

	    StateVariablePtr* var_digital_command_readout;
	    ClsStateVariable* var_digital_read;
	    StateVariablePtr* var_digital_command_writing;
	    StateVariablePtr* var_digital_write;
	    StateVariablePtr* var_analog_command_writing;
	    StateVariablePtr* var_analog_write;
	    StateVariablePtr* var_analog_command_reading;
	    ClsStateVariable* var_analog_read;


	    Arduino arduino;

	    ClsStringParameter *device_name;

	    struct timeval time_init;
	    int elapsed_cicles;
	    ClsIntParameter *par_cps,*var_analog_speed, *var_light_limit;

	    void checkWidth(StateArray& group, int width,
			    const string& group_name);

	    void relax();

	    void vectorToGroup(vector<float> origin, StateArray& destination);


	};
}


#endif // MODULEARDUINONEW_HPP
