These are synapse extensions of iqr. 

Included files are: synapseExpotnetial.h,synapseExpotnetial.cpp,synapsemodulatefeedback.cpp, synapsemodulatefeedback.h

To use store the .so files in the ~/iqr/lib/Synapses/ directory.

Synapsemodulate feedback are conditionally modulatory synapses, whose weights only change when a reward is present (OCT). 


$\Delta w=e(t)\cdot OCT \cdot \alpha$

$w(t+1)=w(t)+(1-w(t)) \cdot \Delta w$


Here, $OCT$ is the octopaminergic signal, that is either 0 or 1, depending on whether the reward is presented or not, and $\alpha$ is the learning rate. The eligibility trace $e(t)$ serves as a memory state variable. It increases with each spike by:


$e(t+1)=e(t)+(1-e(t))\cdot \alpha_e$

 but decreases exponentially when no spikes are fired:

 $e(t+1)=e(t)\cdot exp(\frac{-\Delta t}{\tau_e})$

The eligibility increases with each spike by $\alpha_e$, and $\tau_e$ is the eligibility time constant, which determines how fast it decreases when no spikes are fired.

Based on the work of  Wessnitzer et al 2012 and Cassenaer et al. 2012
