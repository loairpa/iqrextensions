/****************************************************************************
 ** $Header$
 **
 ** $Author: Jan Meyer
 ** 
 ** $CreateDate: Tue Oct  7 22:28:00 2003
 ** $Date$
 **
 ** $Keywords:
 ** $Description: Implemetation of synapse.
 **
 *****************************************************************************/

#include "synapseExponential.hpp"

// Interface for dynamic loading is built using a macro.
MAKE_SYNAPSE_DLL_INTERFACE(iqrcommon::ClsSynapseExponential, 
			  "Exponential")

iqrcommon::ClsSynapseExponential::ClsSynapseExponential()
    : ClsSynapse()
{    
    // Use base class function to create a parameter object, and store
    // the pointer to its value field (for efficient computation).
    pWeight = addDoubleParameter("weight",
				 "Weight",
				 1.0,
				 -1.0,	// negative weights allow inversion
				 1.0,
				 5,
				 "Uniform synaptic weight.");

    pTau = addDoubleParameter("tau", "Time constant",
		10.0, 1.0, 1000.0, 1,
		"Time constant in "
		"ms.");

    pPostsynapticPotential = addOutputState("psp", "Postsynaptic potential");
}

void
iqrcommon::ClsSynapseExponential::update()
{    

	// For clarity, create a local reference to the state array.  This
	// has the performance advantage that the state array pointer need
	// only be dereferenced once.
	StateArray &synIn = getInputState()->getStateArray();
	StateArray &psp   = pPostsynapticPotential->getStateArray();
	StateArray &dt    = ClsFEComputeEngine::Instance()->getTimeState();
	// Also extract the parameter values for speed and clarity.
	// Again, this ensures that the pointer dereferencing happens only
	// once.
	double weight = pWeight->getValue();
	double tau = pTau->getValue();
	double dtPerTau = (dt[0][0] * 1000) / tau;



	psp[0] -= psp[0] * dtPerTau;
	psp[0] += weight * synIn[0];
}
