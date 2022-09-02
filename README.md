<!--<h1 align="center">puuTools</h1>-->

<p align="center">
<img src="./logo/puuTools_logo_crop.png" width=200>
</p>

<p align="center">
<em>Live tracking of lineage/phylogenetic trees and evolutionary events in individual-based forward-in-time simulations of evolution.</em>
<br/><br/>
<a href="https://github.com/charlesrocabert/Evo2Sim/releases/latest"><img src="https://img.shields.io/badge/version- 1.1.0-green.svg" /></a>&nbsp;<a href="https://github.com/charlesrocabert/Evo2Sim/releases/latest"><img src="https://img.shields.io/badge/build-passing-green.svg" /></a>&nbsp;<a href="https://www.gnu.org/licenses/gpl-3.0"><img src="https://img.shields.io/badge/license-GPL v3-blue.svg" /></a>
</p>

## Content

- [Aim](#aim)
- [What is puuTools](#puutools)
- [First usage with examples](#first_usage)
  - [Wright-Fisher population](#wright_fisher)
  - [Allopatric speciation](#allopatric_speciation)
  - [A complex scenario where puuTools can be useful](#complex_scenario)

## Aim

<p align="center">
<kbd>
<img src="./pic/finnish_landscape.jpg" width=300>
</kbd>
<br/>
<sup>Helmi Biese - View from Pyynikki Ridge, 1900 (Puu is the Finnish word for tree).</sup>
</p>

<p align="justify">
Individual-based forward-in-time evolutionary simulations are more and more common, and have been proven to be useful in many field of biology (ecology and evolution, conservation biology, systems biology, etc).

As the complexity of these tools tends to increase, it becomes crucial to develop tools which efficiently track the phylogeny of <em>in silico</em> populations and unlock our ability to exhaustively access to all the events (<em>e.g.</em> genetic mutations) during a simulation.
<!--
More and more models simulate complex phenomena such as the evolution of bacterial genomes, phenotypic plasticity, speciation events or even major evolutionary transitions.
-->
</p>

<p align="justify">
When dealing with complex evolutionary simulations, one solution consists in producing regular backups during a simulation (<em>e.g.</em> one per generation), in order to recover phylogenetic information in post-processing. However, such an approach usually requires gigabytes of storage, limiting the opportunities to produce light and portable simulation software.
</p>

<p align="justify">
Because computational biologists are usually interested in the evolutionary events that led to the final state, they are usually only interested in the lineages that did not went extinct. Another solution thus consists in dynamically tracking the lineage and phylogenetic trees during a simulation, and only keep the pertinent information in memory. Moreover, such an approach provides live access to the phylogenetic tree, the history of evolutionary events (<em>e.g.</em> the mutational history of a genome, or the most recent common ancestor age - MRCA), at any time during a simulation.
While this approach comes at slightly higher computational and RAM cost (it is necessary to regularly update the structure of the tree, and to maintain in memory the information of approximately 2n-1 individuals), it is much lighter and efficient than backing up everything and running post-treatments.
</p>

<p align="justify">
This functionality is usually re-implemented from scratch in different simulation software, at the cost of re-implementing each time optimized algorithms. The aim of <strong>puuTools</strong> is to help developers by offering an easy-to-use framework to manage lineage and phylogenetic information on the fly during an evolutionary simulation.
</p>

## What is puuTools <a name="puutools"></a>

<p align="justify">
<strong>puuTools</strong> allows to dynamically create, track and manage lineage and phylogenic trees during individual-based forward-in-time simulations of evolution.

With <strong>puuTools</strong>, it is possible to update the lineage and/or the phylogenic tree of a population at each generation during a simulation, and to track and recover any evolutionary events. <strong>puuTools</strong> is easy to deploy and versatile.

<strong>puuTools</strong> is an all-in-one library. It does not depend on third-party packages, and its code is kept simple and light. Learn more about what is under the hood [here](#behind_the_scene).

The code of <strong>puuTools</strong> has primarily been implemented during the European project <a href="http://www.evoevo.eu/">EvoEvo</a> (FP7-ICT-610427), as part of the <a href="https://github.com/charlesrocabert/Evo2Sim">Evo2Sim</a> software.
To date, <strong>puuTools</strong> is distributed as a static library for C++ developers. We plan to provide a Python-binding in a future version.
</p>

## First usage with examples <a name="first_usage"></a>

### Wright-Fisher population <a name="wright_fisher"></a>

<p align="justify">

</p>

### Allopatric speciation <a name="allopatric_speciation"></a>

<p align="justify">

</p>

### A complex scenario where puuTools has been useful <a name="complex_scenario"></a>

## Behind the scene

Algorithms used
