
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
 * synapsemodulatefeedback.h
 * based on synapseHebbian.h
 * Author: LIH
 */
#ifndef SYNAPSEMODULATEFEEDBACK_H
#define SYNAPSEMODULATEFEEDBACK_H
#define LOGFILE	"weights.log"     //

#include <Common/Item/synapse.hpp>
#include "ClsFEComputeEngine.h"

#include <iostream>
#include <fstream>

namespace iqrcommon {

    class ClsSynapseModulateFeedback : public ClsSynapse
    {



    public:
	ClsSynapseModulateFeedback();

	void update();

    private:
	// Hide copy constructor.
	ClsSynapseModulateFeedback(const ClsSynapseModulateFeedback&);


	ClsDoubleParameter *pAlpha_e;
	ClsDoubleParameter *pTau_e;
	ClsDoubleParameter *pAlpha_w;
	ClsDoubleParameter *pTau;

	// Pointer to output state.
	ClsStateVariable *pPostsynapticPotential, *pWeight,  *pEligibility, *pOctopamine;





    };
}



#endif // SYNAPSEMODULATEFEEDBACK_H
