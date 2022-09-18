<!--<h1 align="center">puuTools</h1>-->

<p align="center">
<img src="./logo/puuTools_logo.png" width=200>
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
- [Copyright](#copyright)
- [License](#license)

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
When dealing with complex evolutionary simulations, one solution consists in producing full simulation backups at regular intervals during a simulation, in order to recover lineage information in post-processing. However, such an approach usually requires gigabytes of storage, as it saves more information than strictly necessary to recover lineages, limiting the opportunities to produce light and portable simulation software (Fig. 1).
</p>

<p align="justify">
Because precisely recovering the evolutionary events that led to the final state of a population is one major interest of evolutionary simulations, keeping trace of the lineages that did not went extinct is relevant. Thus, another solution consists in dynamically tracking the lineage trees during a simulation, in order to only keep the pertinent information in memory. Moreover, such an approach provides live access to the lineage and phylogenetic relationships, including tracing back evolutionary events, at any time during a simulation.
While this approach comes at slightly higher computational and live memory cost (it is necessary to maintain in memory and regularly update the structure of the tree), it is much lighter and efficient than backing up everything and running post-treatments.
</p>

<p align="justify">
This functionality is usually re-implemented from scratch in different simulation software, at the cost of re-investing time to optimize the algorithms. The aim of <strong>puuTools</strong> is to help developers by offering an easy-to-use and light framework to manage lineage and phylogenetic information on the fly during an evolutionary simulation.
</p>

<p align="center">
<img src="./doc/backup_vs_live_tracking-crop.jpg">
</p>

## What is puuTools <a name="puutools"></a>

<p align="justify">
<strong>puutools</strong> allows to dynamically create, track and manage lineage and/or phylogenic trees during individual-based forward-in-time simulations of evolution.

With <strong>puutools</strong>, it is possible to update the lineage and/or the phylogenic tree of a population at each generation during a simulation, and to track and recover any evolutionary events. <strong>puutools</strong> is easy to deploy and versatile.

<strong>puutools</strong> is an all-in-one library. It does not depend on third-party packages, and its code is kept simple and light. <!--Learn more about what is under the hood [here](#behind_the_scene).-->

The code of <strong>puutools</strong> has primarily been implemented and optimized during the European project <a href="http://www.evoevo.eu/">EvoEvo</a> (FP7-ICT-610427), as patt of the <a href="https://github.com/charlesrocabert/Evo2Sim">Evo<sup>2</sup>Sim</a> software (see https://doi.org/10.1371/journal.pcbi.1005459). The code has also been used in <a href="https://github.com/charlesrocabert/SigmaFGM">&sigma;FGM</a> framework (see https://doi.org/10.1111/evo.14083).
To date, <strong>puutools</strong> is distributed as a static library for C++ developers. We plan to provide a Python-binding in a future version.
</p>

## Installation instructions <a name="installation"></a>

### Supported platforms

<strong>puutools</strong> library has been successfully tested on Ubuntu and MacOS.

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

### A complex scenario where puutools has been useful <a name="complex_scenario"></a>

## Behind the scene

Algorithms used

## Copyright <a name="copyright"></a>
Copyright &copy; 2022 Charles Rocabert.
All rights reserved.

## License <a name="license"></a>
<p align="justify">
This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
</p>

<p align="justify">
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
</p>

<p align="justify">
You should have received a copy of the GNU General Public License along with this program. If not, see http://www.gnu.org/licenses/.
</p>


