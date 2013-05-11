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
 * neuronAdaptiveIntegrateFire.hpp
 *
 * Author: meyer
 */

#ifndef NEURONADAPTIVEINTEGRATEFIRE_HPP
#define NNEURONADAPTIVEINTEGRATEFIRE_HPP

#include "neuron.hpp"
#include "ClsFEComputeEngine.h"

namespace iqrcommon {

    class ClsNeuronAdaptiveIntegrateFire : public ClsNeuron
    {
    public:	
	ClsNeuronAdaptiveIntegrateFire();
	void update();

    private:
	// Hide copy constructor.
	ClsNeuronAdaptiveIntegrateFire(const ClsNeuronAdaptiveIntegrateFire&);

	// Pointers to parameter objects.  The objects are managed by
	// the base class, the pointers are only needed to provide
	// rapid access to these objects during the performance
	// critical update function.
	ClsDoubleParameter *pExcCond, *pInhCond, *pRm;
	ClsDoubleParameter *pRestPot, *pExcPot, *pInhPot;
	ClsDoubleParameter *pVmThreshold, *pVmReset;
	ClsDoubleParameter *pRefrPeriod, *pRCm;
	ClsDoubleParameter *pAdaptChange, *pAdaptPot, *pRCsa;
	ClsDoubleParameter *pSpikeAmplitude;

	// Pointers to state variables.	
	ClsStateVariable *pVmembrane, *pRefrTime, *pAdaptCond, *pActivity;


    };
}
#endif
