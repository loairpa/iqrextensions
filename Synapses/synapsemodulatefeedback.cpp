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
 * synapsemodulatefeedback.cpp
 * based on synapseHebbian.cpp
 * Author: LIH
 */

#include "synapsemodulatefeedback.h"
#include <stdlib.h>
#include <stdio.h>




// Interface for dynamic loading is built using a macro.
MAKE_SYNAPSE_DLL_INTERFACE(iqrcommon::ClsSynapseModulateFeedback,
			  "Expontetial Mod")

iqrcommon::ClsSynapseModulateFeedback::ClsSynapseModulateFeedback() : ClsSynapse() {


	// Use base class function to create a parameter object, and store
	// the pointer to its value field (for efficient computation).


  pWeight= addStateVariable("weight", "Synaptic Weight");

    pTau = addDoubleParameter("tau", "Time constant",
		10.0, 1.0, 1000.0, 1,
		"Time constant in "
		"ms.");

    pAlpha_w = addDoubleParameter("lrate",
			     "Learning Rate",
			     .1,
			     0.0,
			     1.0,
			     3,
			     "Learning Rate");



    pAlpha_e = addDoubleParameter("alpha_e",
				 "Eligibility Learning Rate",
				 .1,
				 0.0,
				 1.0,
				 3,
				 "Eligibility Learning Rate",
				 "Eligibiltiy");

    pTau_e= addDoubleParameter("tau_e",
			      "Eligibility Time constant",
			      100.0, 1.0, 10000.0, 1,
		     "Time constant in ms.","Eligibiltiy");

    pOctopamine = addFeedbackInput("modulation", "Octopamine");
    pPostsynapticPotential = addOutputState("psp", "Postsynaptic potential");
    pEligibility = addStateVariable("e","Eligibility");


}

void iqrcommon::ClsSynapseModulateFeedback::update() {


	// For clarity, create a local reference to the state array.  This
	// has the performance advantage that the state array pointer need
	// only be dereferenced once.
	StateArray &synIn = getInputState()->getStateArray();
	StateArray &psp   = pPostsynapticPotential->getStateArray();
	StateArray &dt    = ClsFEComputeEngine::Instance()->getTimeState();
	StateArray &e = pEligibility->getStateArray();
	StateArray &weight = pWeight->getStateArray();
	StateArray &modulation = pOctopamine->getStateArray();

	// Also extract the parameter values for speed and clarity.
	// Again, this ensures that the pointer dereferencing happens only
	// once.

	//double weight = pWeight->getValue();
	double tau_w = pTau->getValue();
	double alpha_w =pAlpha_w->getValue();
	double dtPerTau = (dt[0][0]*1000 ) / tau_w;

	// Eligibility
	double alpha_e=pAlpha_e->getValue();
	double tau_e=pTau_e->getValue();
	double dtPerTaue=(dt[0][0]*1000) / tau_e;

	// Modulation

	double OCT=(modulation[0].sum())?1.0:0.0;

	for(unsigned int i=0; i<synIn[0].size();i++)
	{

		e[0][i]= (synIn[0][i]>0.0)?(e[0][i]+(1-e[0][i])*alpha_e) : (1-dtPerTaue)*e[0][i];

	}


	weight[0]+=(1.0-weight[0])*OCT*e[0]*alpha_w;

	psp[0] -= psp[0] * dtPerTau;
	psp[0] += weight[0] * synIn[0];

       ofstream fout;
       fout.open("weights.log",ios::app);
       fout<<weight[0]<<endl;   //send to file
	    fout.close( );       //close file






}



