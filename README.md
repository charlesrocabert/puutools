<p align="center">
<img src="./logo/puuTools_logo.png" width=250>
</p>

<p align="center">
<em>Easy-to-use C++ library for the live tracking of lineage and phylogenetic trees in individual-based forward-in-time simulations of evolution.</em>
<br/>
<em><sup>(Puu is the Finnish word for tree)</sup></em>
<br/><br/>
<a href="https://github.com/charlesrocabert/puutools/releases/latest"><img src="https://img.shields.io/github/release/charlesrocabert/puutools/all.svg" /></a>&nbsp;<a href="https://github.com/charlesrocabert/Evo2Sim/releases/latest"><img src="https://img.shields.io/badge/build-passing-green.svg" /></a>&nbsp;<a href="https://www.gnu.org/licenses/gpl-3.0"><img src="https://img.shields.io/badge/license-GPL v3-blue.svg" /></a>
</p>

## Content

- [Aim](#aim)
- [What is puuTools](#puutools)
- [Installation instructions](#installation)
- [CMake find module](#findmodule)
- [Copyright](#copyright)
- [License](#license)
- [Algorithm overview](#algorithm)
- [First usage with a walk-through example ](#first_usage)
- [A complex scenario where puuTools can be useful](#complex_scenario)

## Aim

<p align="center">
<kbd>
<img src="./pic/finnish_landscape.jpg" width=400>
</kbd>
<br/>
<sup>Helmi Biese - View from Pyynikki Ridge, 1900.</sup>
</p>

<p align="justify">
Individual-based forward-in-time evolutionary simulations are more and more common, and have been proven useful in many fields (ecology and evolution, conservation biology, systems biology, etc).

Precisely recovering the evolutionary and mutational events that led to the final state of a population is one major interest of evolutionary simulations. It is then important to develop tools which efficiently track the lineages of <em>in silico</em> populations and provide exhaustive access to all the events that occured during a simulation.
</p>

<p align="justify">
One solution consists in producing full backups at regular intervals during a simulation, in order to recover lineage information in post-processing. However, such an approach usually requires gigabytes of storage, as it saves more information than strictly necessary to recover lineages, and limits the opportunities to produce light and portable simulation software.
</p>

<p align="justify">
Another solution consists in dynamically tracking the lineage and/or phylogenetic trees during a simulation, in order to only keep the pertinent information in live memory. Such an approach provides live access to ancestor relationships, including tracing back evolutionary events, at any time during a simulation.
While this approach comes at slightly higher computational and live memory costs (it is necessary to maintain in memory and regularly update the structure of the trees), it is much lighter and efficient than backing up everything and running post-treatments.
</p>

<p align="justify">
This functionality is usually re-implemented from scratch in different simulation software, at the cost of re-investing time to optimize the algorithms. The aim of <strong>puutools</strong> is to help developers by offering an <strong>easy-to-use</strong> and <strong>light</strong> framework to manage lineage and phylogenetic information on the fly during an evolutionary simulation.
</p>

<p align="center">
<img src="./doc/backup_vs_live_tracking.jpg">
</p>

## What is puutools <a name="puutools"></a>

<p align="justify">
While tree-like data-structures are standard knowledge in computer science, the C++ standard library does not provide tree-like containers, and a straightforward tool to specifically manipulate ancestral relationships in individual-based simulations is still missing.
<strong>puutools</strong> allows to dynamically create, track and manage lineage and/or phylogenic trees during individual-based forward-in-time simulations of evolution.
</p>

<p align="justify">
With <strong>puutools</strong>, it is possible to update the lineage and/or the phylogenic tree of a population at each generation during a simulation, and to track and recover evolutionary events at any time. <strong>puutools</strong> is easy to deploy and versatile, providing the user with a small set of integrated functions.
</p>

<p align="justify">
<strong>puutools</strong> is an all-in-one library. It does not depend on third-party packages, and its code is kept simple and light. By the way, <strong>puutools</strong> comes as and header-only library, so compilation is not needed.
</p>

<p align="justify">
The code of <strong>puutools</strong> has primarily been implemented and optimized during the European project <a href="http://www.evoevo.eu/">EvoEvo</a> (FP7-ICT-610427), as part of the <a href="https://github.com/charlesrocabert/Evo2Sim">Evo<sup>2</sup>Sim</a> software (see <a href="https://doi.org/10.1371/journal.pcbi.1005459">Rocabert et al. 2017</a>). The code has also been used in <a href="https://github.com/charlesrocabert/SigmaFGM">&sigma;FGM</a> framework (see <a href="https://doi.org/10.1111/evo.14083">Rocabert et al. 2020</a>).
To date, <strong>puutools</strong> is distributed as a static library for C++ developers. We plan to provide a Python-binding in a future version.
</p>

## Installation instructions <a name="installation"></a>

### Supported platforms

<p align="justify">
<strong>puutools</strong> library has been developed for Unix/Linux and macOS systems.
</p>

### Required dependencies

- A C++11 compiler (GCC, LLVM, ...);
- CMake >= 3.19 (command line version);

**Additional dependencies for the example code:**

- Gnu Scientific Library (GSL);
- CBLAS;
- R >= 4.0.0;
- Rpackage ape;

### Installation

<p align="justify">
Download the <a href="https://github.com/charlesrocabert/puutools/releases/latest">latest release</a> of <strong>puutools</strong>, and save it to a directory of your choice. Open a terminal and use the <code>cd</code> command to navigate to this directory. To install <strong>puutools</strong>, simply call <code>install.sh</code> on the command line:
</p>

```
sh install.sh
```

<p align="justify">
The script requires sudo access to install the library in the appropriate folder. <strong>puutools</strong> comes as a single C++ header file, and will be installed in an <code>include</code> directory (usually <code>/usr/local/include</code>).

:warning: If you cannot or do not want to use a sudo access, simply <a href="https://github.com/charlesrocabert/puutools/raw/main/puutools/puutools.h">download the source file <code>puutools.h</code></a> and include it directly to your project.
</p>

## CMake find module <a name="findmodule"></a>

<p align="justify">
A find module is useful to determine whether a package is available during the compilation of a project with CMake.
It has also the advantage to determine the paths with no need to provide them explicitely in the <code>CMakeLists.txt</code> file.
</p>

<p align="justify">
You can download here the CMake find module of <strong>puutools</strong>: <a href="https://github.com/charlesrocabert/puutools/raw/main/cmake_find_module/FindPuuTools.cmake" target="_blank">CMake Find Module</a>
</p>

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

## Algorithm overview <a name="algorithm"></a>

<p align="center">
<img src="./doc/basic_algorithm.jpg" width=700 />
</p>

## First usage with a walk-through example <a name="first_usage"></a>

<p align="justify">
You will find a <a href="https://github.com/charlesrocabert/puutools/tree/main/example" target="_blank">complete walk-through example</a> to get used to the main functionalities of <strong>puutools</strong>.
</p>

## A complex scenario where puutools has been useful <a name="complex_scenario"></a>

<p align="center">
  <img src="https://user-images.githubusercontent.com/25666459/196973050-579efd60-4e72-436c-bd07-9298d31ddd37.png" width=600 />  
</p>
  
<p align="justify">
The original code of <strong>puutools</strong> has been used for research purpose as part of the bacterial evolution simulator <a href="https://github.com/charlesrocabert/Evo2Sim">Evo<sup>2</sup>Sim</a>. The software has for example been used to study bacterial diversification events in batch culture setups, due to stable cross-feeding (see <a href="https://doi.org/10.1371/journal.pcbi.1005459">Rocabert et al. 2017</a>). Tracking lineages and phylogenetic trees was an essential step in this scientific work. An example of simulation output is available here: https://charlesrocabert.github.io/doc/evo2sim_simulation_example/viewer/viewer.html.
</p>


