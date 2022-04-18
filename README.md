<h1 align="center">puuTools</h1>
<p align="center">
<kbd>
<img src="pic.jpg" width=350>
</kbd>
<br/>
<sup>Helmi Biese - View from Pyynikki Ridge, 1900 (Puu is the Finnish word for tree).</sup>
<br/>
<em>Dynamic tracking of evolutionary events and phylogenetic trees in individual-based simulations of evolution.</em>
<br/><br/>
<a href="https://github.com/charlesrocabert/Evo2Sim/releases/latest"><img src="https://img.shields.io/badge/version- 1.1.0-green.svg" /></a>&nbsp;<a href="https://github.com/charlesrocabert/Evo2Sim/releases/latest"><img src="https://img.shields.io/badge/build-passing-green.svg" /></a>&nbsp;<a href="https://www.gnu.org/licenses/gpl-3.0"><img src="https://img.shields.io/badge/license-GPL v3-blue.svg" /></a>
</p>

# Rationale

<p align="justify">
As the complexity of individual-based evolutionary simulations increases, it becomes crucial to develop tools to efficiently track the phylogeny of <em>in silico</em> populations and access exhaustively to all the events that occured (<em>e.g.</em> genetic mutations) during the simulations.
More and more models simulate complex phenomena such as the evolution of bacterial genomes, phenotypic plasticity, speciation events or even major evolutionary transitions.
</p>

<p align="justify">
As discussed by <a href="https://www.nature.com/articles/nrmicro2750">Hindré et al. (2012)</a> when it comes to complex evolutionary simulations, one solution consists to regularly back up all the information during a simulation, in order to recover the information afterward. However, such an approach usually requires gigabites of storage space, limiting the opportunities to produce light and portable simulation software.
</p>

<p align="justify">
Because computational biologists are usually interested in the evolutionary events that led to the final state of a simulation, it is not necessary to back up everything, but only the lineages that did not went extinct. Another solution thus consists in dynamically tracking the lineage and phylogenetic trees during a simulation, in order to only keep the pertinent information in memory. Moreover, such an approach provides instant access to the history of evolutionary events (<em>e.g.</em> the mutational history of a genome, or the most recent common ancestor age), at any time.
While this approach comes at slightly higher computational and RAM cost (it is necessary to regularly update the structure of the tree, and to maintain in memory the information of approximately 2n-1 individuals), it is much lighter and efficient than backing up everything and running post-treatments afterward.
</p>

<p align="justify">
Re-implementing from scratch this kind of tools each time a new simulation software is developed can be a hassle, as it requires specific algorithms to optimize computational and memory costs. This is where <strong>puuTools</strong> may facilitate this facet of the numerical modeling of evolution.
</p>

# What puuTools does

<p align="justify">
<strong>puuTools</strong> allows to dynamically create, track and manage lineage and phylogenic trees inside forward-in-time, individual-based simulations of evolution.

With <strong>puuTools</strong>, it is possible to update the lineage and/or the phylogenic tree of a population at each generation during a simulation, and to track the evolution of any individual, population or phylogenetic-level property at time resolution. <strong>puuTools</strong> is easy to deploy and is versatile thanks to class inheritance.

<strong>puuTools</strong> is an all-in-one library. It does not depend on third-party packages, and its code is kept simple and light. Learn more about what is under the hood [here](#behind_the_scene).
  
The code of <strong>puuTools</strong> has primarily been implemented during the European project <a href="http://www.evoevo.eu/">EvoEvo</a> (FP7-ICT-610427), as part of the <a href="https://github.com/charlesrocabert/Evo2Sim">Evo2Sim</a> software.
To date, <strong>puuTools</strong> is distributed as a static library for C++ developers. We plan to provide a Python-binding in a future version.
</p>

# Examples

## Wright-Fisher population

<p align="justify">
  
</p>

## Allopatric speciation

<p align="justify">
  
</p>

## A complex scenario where puuTools can be useful

# Behind the scene

Algorithms used
