/****************************************************************************
 ** $Header$
 **
 ** $Author: Jan Meyer
 ** 
 ** $CreateDate: Tue Oct  7 22:28:00 2003
 ** $Date$
 **
 **
 *****************************************************************************/

#ifndef SYNAPSEEXPONENTIAL_HPP
#define SYNAPSEEXPONENTIAL_HPP

#include "synapse.hpp"
#include "ClsFEComputeEngine.h"

namespace iqrcommon {

    class ClsSynapseExponential : public ClsSynapse
    {
    public:
	ClsSynapseExponential();

	void update();

    private:
	// Hide copy constructor.
	ClsSynapseExponential(const ClsSynapseExponential&);

        ClsDoubleParameter *pWeight, *pTau;

	// Pointers to state variables.
	ClsStateVariable *pPostsynapticPotential;
    };
}

#endif
