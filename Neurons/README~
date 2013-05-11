These are neural extensions of iqr. 

Included are neuronAdaptiveIntegrateFire.cpp, neuronAdaptiveIntegrateFire.hpp,neuronAdaptiveIntegrateFireMod.cpp,neuronAdaptiveIntegrateFireMod.hpp

To use store the .so files in the ~/iqr/lib/Neurons/ directory.

neuronAdaptiveIntegrateFire is based on equation:


$\tau_m \frac{dV}{dt}=E_L-V-r_mg_{sra}(V-E_{sra})+R_m I_e$

where $V$ is the membrane potential, $E_L$ is the reversal potential, $\tau_m$ is the membrane time constant, $R_m$ is the membrane resistance and $I_e$ is the stimulating current. To generate spikes, the membrane potential $V$ must reach a predetermined threshold $V_{th}$. Then a spike is fired and the membrane potential is reset. When a constant current is injected into the neuron, most real-neurons exhibit spike-rate adaptation, i.e. the inter-spike interval lengthens with time, before settling to a steady state value.  $g_{sra}$ is the spike-rate adaptation conductance that increases with every spike the neuron fires, introducing a current that drives the membrane potential towards the reversal potential $E_{sra}$, causing the firing rate to adapt. When no spikes are fired, the conductance decreases exponentially to 0. $r_m$ is the specific membrane resistance

From Peter Dayan and L.F. Abbotts:
Theoretical Neuroscience: Computational and Mathematical Modeling of Neural Systems.

neuronAdaptiveIntegrateFireMod is the same, only it holds on to a modulatory parameter.


