<h1 align="center">puuTools</h1>
<p align="center">
<kbd>
<img src="pic.jpg" width=350>
</kbd>
<br/>
<sup>(Helmi Biese) - View from Pyynikki Ridge, 1900.</sup>
<br/>
<em>Live-management toolbox for lineage and phylogenetic trees in individual-based simulations</em>
<br/><br/>
<a href="https://github.com/charlesrocabert/Evo2Sim/releases/latest"><img src="https://img.shields.io/badge/version- 1.1.0-green.svg" /></a>&nbsp;<a href="https://github.com/charlesrocabert/Evo2Sim/releases/latest"><img src="https://img.shields.io/badge/build-passing-green.svg" /></a>&nbsp;<a href="https://www.gnu.org/licenses/gpl-3.0"><img src="https://img.shields.io/badge/license-GPL v3-blue.svg" /></a>
</p>

<p align="justify">
As the complexity of numerical, individual-based evolutionary simulations increases, it becomes important to be able to efficiently track the evolution of a population at the lineage and phylogenetic level. For example, trace back the mutational history of a genome, the evolution of a complex phenotypic trait such as plasticity or non-genetic variability, that are not easily detectable by only looking at the mean or the best. or detect a speciation event.  more and more models simulate emergent properties such as speciation or major transitions, where it is essential to access to the phylogeny and trace back

As re-implementing each time the tools to trace back evolution at the level of the lineages and the phylogeny can be a hassle, we decided to implement and distribute an open-source tool to facilitate this aspect of the numerical modeling evolution.
  
<strong>puuTools</strong> allows to easily create, track and manage lineage and phylogenic trees inside forward-in-time, individual-based simulations of evolution.

With <strong>puuTools</strong>, it is possible to update the lineage and/or the phylogenic tree of a population at each generation or time-step of a simulation, to track the evolution of any individual or population-level property at the resolution of the lineage or phylogenetic level. <strong>puuTools</strong> is easy to deploy in one's simulation framework and is versatile thanks to class inheritance.

To date, <strong>puuTools</strong> is distributed as a static library for C++ developers. We plan to provide a Python-binding in a future version.


</p>
