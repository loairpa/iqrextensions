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
 * neuronAdaptiveIntegrateFire.cpp
 *
 * Author: meyer
 */

#include "neuronAdaptiveIntegrateFire.hpp"
#include <time.h>
#include <valarray>

// Interface for dynamic loading is built using a macro.
MAKE_NEURON_DLL_INTERFACE(iqrcommon::ClsNeuronAdaptiveIntegrateFire,
			  "Adaptive integrate & fire")

iqrcommon::ClsNeuronAdaptiveIntegrateFire::ClsNeuronAdaptiveIntegrateFire()
    : ClsNeuron(),
      pVmembrane(0),
      pActivity(0)
{
    pExcCond = addDoubleParameter("excCond", "Excitatory conductance",
    	3.0, 0.0, 99.99, 3,
		"Excitatory conductance in "
                "mSiemens/cm².",
		"Input");

    pInhCond = addDoubleParameter("inhCond", "Inhibitory conductance",
		1.5, 0.0, 99.99, 3,
		"Inhibitory conductance in "
                "mSiemens/cm².",
		"Input");

    pRm = addDoubleParameter("rm", "Specific membrane resistance",
		1, 0.1, 10, 3,
		"Specific membrane "
                "resistance in MOhmmm².",
		"Membrane");

    pRestPot = addDoubleParameter("restPot", "Resting potential",
		-70.0, -100.0, 100.0, 2,
		"Resting potential in "
		"mV.",
		"Membrane");

    pExcPot = addDoubleParameter("excPot", "Excitatory potential",
		0.0, -20.0, 20.0, 2,
		"Excitatory potential in "
		"mV.",
		"Membrane");

    pInhPot = addDoubleParameter("inhPot", "Inhibitory potential",
		-70.0, -100.0, -50.0, 2,
		"Inhibitory potential in "
		"mV.",
		"Membrane");

    pVmThreshold = addDoubleParameter("threshold", "Threshold potential",
		-50.0, -100.0, 0.0, 2,
		"Membrane potential threshold for "
		"output of a spike in mV.",
		"Membrane");

    pVmReset = addDoubleParameter("vmReset", "Membrane potential reset",
		-70.0, -100.0, 0.0, 2,
		"Membrane potential "
		"after a spike in mV.",
		"Membrane");

    pRefrPeriod = addDoubleParameter("refrPeriod", "Refractory period",
		1.0, 0.0, 10.0, 3,
		"Refractory period in "
		"ms.",
		"Time response");

    pRCm = addDoubleParameter("rcm", "Membrane time constant",
		10.0, 1.0, 100.0, 2,
		"Membrane time constant in "
		"ms.",
		"Time response");

    pAdaptChange = addDoubleParameter("adaptChange", "Increase in adaption conductance",
		0.2, 0.0, 1.0, 4,
		"Spike-triggered increase in conductance in "
                "mSiemens/cm².",
		"Spike-Rate Adaption");

    pAdaptPot = addDoubleParameter("adaptPot", "Spike-rate adaption potential",
   		-70.0, -100.0, -50.0, 2,
		"Spike-rate adaption potential in "
		"mV.",
		"Spike-Rate Adaption");

    pRCsa = addDoubleParameter("rcsa", "Adaption time constant",
		10.0, 1.0, 100000.0, 1,
		"Spike-rate adaption time constant in "
		"ms.",
		"Spike-Rate Adaption");

    pSpikeAmplitude = addDoubleParameter("spkAmpl", "Spike amplitude",
		1.0, 0.0, 1.0, 4,
		"Amplitude of output spikes.",
		"Spike");

    // Add state variables.
    pVmembrane = addStateVariable("vm", "Membrane potential");
    pRefrTime = addStateVariable("tr", "Refractory time");
    pAdaptCond = addStateVariable("adaptCond", "Spike-rate adaption conductance");
    pActivity  = addOutputState("act", "Activity");
}


/**
 * void ClsNeuronAdaptiveIntegrateFire::update()
 *
 * updates the status of the neuron group depending
 * on the actual excitatory and inhibitory inputs
 */
void iqrcommon::ClsNeuronAdaptiveIntegrateFire::update()
{
    // For clarity, create local references to the state arrays.  This
    // has the performance advantage that the state array pointers need
    // only be dereferenced once.
    StateArray &excitation = getExcitatoryInput();
    StateArray &inhibition = getInhibitoryInput();
    StateArray &vm         = pVmembrane->getStateArray();
    StateArray &tr         = pRefrTime->getStateArray();
    StateArray &adaptCond  = pAdaptCond->getStateArray();
    StateArray &activity   = pActivity->getStateArray();
    StateArray &dt         = ClsFEComputeEngine::Instance()->getTimeState();

    // Get parameter values from parameter objects.
    double excCond     = pExcCond->getValue();
    double inhCond     = pInhCond->getValue();
    double rm	       = pRm->getValue();
    double restPot     = pRestPot->getValue();
    double excPot      = pExcPot->getValue();
    double inhPot      = pInhPot->getValue();
    double threshold   = pVmThreshold->getValue();
    double vmReset     = pVmReset->getValue();
    double refrPeriod  = pRefrPeriod->getValue();
    double rcm	       = pRCm->getValue();
    double adaptChange = pAdaptChange->getValue();
    double adaptPot    = pAdaptPot->getValue();
    double rcsa	       = pRCsa->getValue();
    double spikeAmpl   = pSpikeAmplitude->getValue();

    double dtPerRC = (dt[0][0] * 1000) / rcm;

    #ifdef DEBUG_CLSNEURON
        cout << "Neuron interval since last update: "
            << dt[0][0]
            << "s." << endl;
    #endif


	/*cout << "\n inhibiton: "<< inhibition[0][1];
	cout << "\n excitation: "<< excitation[0][1];
	cout << "\n vm: "<< vm[0][1];
	cout << "\n adaptCond: "<< adaptCond[0][1];*/

    for(unsigned int i=0; i<vm[0].size(); i++)
    {
	// Reduce adaptive conductance
        adaptCond[0][i] -= (adaptCond[0][i] * dt[0][0] * 1000) / rcsa;

        // Remember last spike and reset membrane potential.
        // this is done here, so the potential maxima can be plotted
        if(activity[0][i] > 0.0)
        {
            tr[0][i] = refrPeriod ;
            vm[0][i] = vmReset;
            adaptCond[0][i] += adaptChange;
        }

        // Reduce refractory time
	if(tr[0][i] > 0.0)
        {
	    tr[0][i] -= dt[0][0] * 1000;
        }

        // Calculate membrane potential
	vm[0][i] += ((restPot - vm[0][i])
		   +(excCond * excitation[0][i] * (excPot - vm[0][i])
		    +inhCond * inhibition[0][i] * (inhPot-vm[0][i])
		  + adaptCond[0][i] * (adaptPot - vm[0][i])) * rm / 10 ) * dtPerRC;




        // Neurons at threshold or above produce a spike
        // as long they are not in the refractory period
        activity[0][i] = ((tr[0][i] <= 0.0) && (vm[0][i] >= threshold)) ? spikeAmpl : 0.0;

        #ifdef DEBUG_CLSNEURON
            cout << "Neuron vm, thr, refr, act " << endl
                << vm[0][i] << ", "
                << (vm[0][i] >= threshold) << ", "
                << tr[0][i] << ", "
                << activity[0][i] << ":" << ((vm[0][i] >= threshold) && (tr[0][i] <= 0.0))
                << endl;
        #endif
    }
}
