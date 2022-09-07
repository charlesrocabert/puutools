<!--<h1 align="center">puuTools</h1>-->

<p align="center">
<img src="./logo/puuTools_logo.png" width=250>
</p>

<p align="center">
<em>Live tracking of lineage/phylogenetic trees and evolutionary events in individual-based forward-in-time simulations of evolution.</em>
<br/>
<em><sup>(Puu is the Finnish word for tree)</sup></em>
<br/><br/>
<a href="https://github.com/charlesrocabert/Evo2Sim/releases/latest"><img src="https://img.shields.io/badge/version- 1.1.0-green.svg" /></a>&nbsp;<a href="https://github.com/charlesrocabert/Evo2Sim/releases/latest"><img src="https://img.shields.io/badge/build-passing-green.svg" /></a>&nbsp;<a href="https://www.gnu.org/licenses/gpl-3.0"><img src="https://img.shields.io/badge/license-GPL v3-blue.svg" /></a>
</p>

## Content

- [Aim](#aim)
- [What is puuTools](#puutools)
- [Installation instructions](#installation)
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
<sup>Helmi Biese - View from Pyynikki Ridge, 1900.</sup>
</p>

<p align="justify">
Individual-based forward-in-time evolutionary simulations are more and more common, and have been proven useful in many fields (ecology and evolution, conservation biology, systems biology, etc).

As models' complexity tends to increase, it becomes crucial to develop tools which efficiently track the lineages of <em>in silico</em> populations and provide exhaustive access to all evolutionary events during a simulation.
</p>

<p align="justify">
When dealing with complex evolutionary simulations, one solution consists in producing full simulation backups at regular intervals during a simulation, in order to recover lineage information in post-processing. However, such an approach usually requires gigabytes of storage, as it saves more information than strictly necessary to recover lineages, limiting the opportunities to produce light and portable simulation software.
</p>

<p align="justify">
Because computational biologists are usually interested in the evolutionary events that led to the final state of a simulation, they are interested in the lineages that did not went extinct. Thus, another solution consists in dynamically tracking the lineage trees during a simulation, in order to only keep the pertinent information in memory. Moreover, such an approach provides live access to the lineage and phylogenetic relationships, including tracing back evolutionary events, at any time during a simulation.
While this approach comes at slightly higher computational and live memory cost (it is necessary to regularly update the structure of the tree, and to maintain in memory the information of approximately 2n-1 individuals), it is much lighter and efficient than backing up everything and running post-treatments.
</p>

<p align="justify">
This functionality is usually re-implemented from scratch in different simulation software, at the cost of re-investing time and energy to optimize the algorithms. The aim of <strong>puuTools</strong> is to help developers win development time by offering an easy-to-use and light framework to manage lineage and phylogenetic information on the fly during an evolutionary simulation.
</p>

<p align="center">
<img src="./doc/backup_vs_live_tracking-crop.jpg" width=800>
</p>

## What is puuTools <a name="puutools"></a>

<p align="justify">
<strong>puuTools</strong> allows to dynamically create, track and manage lineage and phylogenic trees during individual-based forward-in-time simulations of evolution.

With <strong>puuTools</strong>, it is possible to update the lineage and/or the phylogenic tree of a population at each generation during a simulation, and to track and recover any evolutionary events. <strong>puuTools</strong> is easy to deploy and versatile.

<strong>puuTools</strong> is an all-in-one library. It does not depend on third-party packages, and its code is kept simple and light. Learn more about what is under the hood [here](#behind_the_scene).

The code of <strong>puuTools</strong> has primarily been implemented during the European project <a href="http://www.evoevo.eu/">EvoEvo</a> (FP7-ICT-610427), as part of the <a href="https://github.com/charlesrocabert/Evo2Sim">Evo<sup>2</sup>Sim</a> software (see https://doi.org/10.1371/journal.pcbi.1005459). The code has also been used in <a href="https://github.com/charlesrocabert/SigmaFGM">&sigma;FGM</a> framework (see https://doi.org/10.1111/evo.14083).
To date, <strong>puuTools</strong> is distributed as a static library for C++ developers. We plan to provide a Python-binding in a future version.
</p>

## Installation instructions <a name="installation"></a>

### Supported platforms

<strong>puuTools</strong> library has been successfully tested on Ubuntu and MacOS.

### Required dependencies

- A C++11 compiler (GCC, LLVM, ...);
- zlib;

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
