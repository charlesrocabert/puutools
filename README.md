<!--<h1 align="center">puuTools</h1>-->

<p align="center">
<img src="./logo/puuTools_logo.png" width=200>
</p>

<p align="center">
<em>Easy-to-use and versatile framework for the live tracking of lineage/phylogenetic trees and evolutionary events in individual-based forward-in-time simulations of evolution.</em>
<br/>
<em><sup>(Puu is the Finnish word for tree)</sup></em>
<br/><br/>
<a href="https://github.com/charlesrocabert/Evo2Sim/releases/latest"><img src="https://img.shields.io/badge/version- 1.1.0-green.svg" /></a>&nbsp;<a href="https://github.com/charlesrocabert/Evo2Sim/releases/latest"><img src="https://img.shields.io/badge/build-passing-green.svg" /></a>&nbsp;<a href="https://www.gnu.org/licenses/gpl-3.0"><img src="https://img.shields.io/badge/license-GPL v3-blue.svg" /></a>
</p>

## Content

- [Aim](#aim)
- [What is puuTools](#puutools)
- [Installation instructions](#installation)
- [First usage with a walk-through example ](#first_usage)
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
This functionality is usually re-implemented from scratch in different simulation software, at the cost of re-investing time to optimize the algorithms. The aim of <strong>puutools</strong> is to help developers by offering an <strong>easy-to-use</strong> and <strong>light</strong> framework to manage lineage and phylogenetic information on the fly during an evolutionary simulation.
</p>

<p align="center">
<img src="./doc/backup_vs_live_tracking-crop.jpg">
</p>

## What is puutools <a name="puutools"></a>

<p align="justify">
While tree's data-structures are standard in computer science, a straightforward tool to specifically manipulate ancestral relationships in individual-based simulations is still missing.
<strong>puutools</strong> allows to dynamically create, track and manage lineage and/or phylogenic trees during individual-based forward-in-time simulations of evolution.

With <strong>puutools</strong>, it is possible to update the lineage and/or the phylogenic tree of a population at each generation during a simulation, and to track and recover any evolutionary events. <strong>puutools</strong> is easy to deploy and versatile, providing the user with a small set of easy-to-use functions.

<strong>puutools</strong> is an all-in-one library. It does not depend on third-party packages, and its code is kept simple and light. <!--Learn more about what is under the hood [here](#behind_the_scene).-->

The code of <strong>puutools</strong> has primarily been implemented and optimized during the European project <a href="http://www.evoevo.eu/">EvoEvo</a> (FP7-ICT-610427), as patt of the <a href="https://github.com/charlesrocabert/Evo2Sim">Evo<sup>2</sup>Sim</a> software (see https://doi.org/10.1371/journal.pcbi.1005459). The code has also been used in <a href="https://github.com/charlesrocabert/SigmaFGM">&sigma;FGM</a> framework (see https://doi.org/10.1111/evo.14083).
To date, <strong>puutools</strong> is distributed as a static library for C++ developers. We plan to provide a Python-binding in a future version.
</p>

## Installation instructions <a name="installation"></a>

### Supported platforms

<strong>puutools</strong> library has been developed for Unix/Linux and macOS systems.

### Required dependencies

- A C++11 compiler (GCC, LLVM, ...);
- CMake >= 3.19 (command line version);

### Installation

<p align="justify">
Download the <a href="https://github.com/charlesrocabert/Evo2Sim/releases/latest">latest release</a> of <strong>puutools</strong>, and save it to a directory of your choice. Open a terminal and use the <code>cd</code> command to navigate to this directory. To install <strong>puutools</strong>, simply call <code>install.sh</code> on the command line:

    sh install.sh

The script requires sudo access to install the library in the appropriate folder. <strong>puutools</strong> comes as a single C++ header file, and will then be installed in an <code>include</code> directory (usually <code>/usr/local/include</code>).
</p>

## First usage with a walk-through example <a name="first_usage"></a>

<p align="justify">
<strong>puutools</strong> is distributed as an external static library. Once installed (see above), the header must be included with the standard <code>#include</code> instruction:

```c++
#include <puutools.h>
```

The main object that will be manipulated by the user is the class <code>puu_tree<selection_unit></code> which instanciates a dynamic representation of a lineage or phylogenetic tree. <code>puu_tree</code> class uses a template: <code>selection_unit</code> can be any class created on your own, with the constraint that the copy contructor must be at least public and not disabled, and preferably fully implemented to avoid errors.
</p>

### A simple model to implement
<p align="justify">
In this example, we will implement a basic algorithm to simulate the evolution of a population of constant size $N$. Individuals are asexual and generations are non-overlapping. Each individual owns a phenotypic trait $x \in \mathcal{R}$ which can mutate with a probability $m$ (per individual per generation) and a size $s$ such that the mutated trait $x' = x + \mathcal{N}(0, s)$. Individual's fitness is calculated with the standard Gaussian fitness function $w = e^{-\frac{x^2}{2}}$. The number of descendants at each generation is fitness proportionate.

We will implement five command line arguments to define each simulation:
- The initial trait value $x_0$;
- The simulation time $T$ (in generations);
- The population size $N$;
- The mutation rate $m$;
- The mutation size $s$;

We will introduce <strong>puutools</strong> code step by step.
</p>

## Pre-processor include directives
<p align="justify">
Let's first include the necessary standard library (<code>std</code>) utilitaries and <strong>puutools</strong> libraries:

```c++
#include <iostream>
#include <vector>
#include <assert.h>
#include <puutools.h>
```

We then include to classes that are pre-implemented (see <code>example</code> folder):
    
```c++
#include "Prng.h"
#include "Individual.h"
```

The <code>Prng</code> class implements many random functions based on the <a href="https://www.gnu.org/software/gsl/" target="_blank">GNU Scientific Library</a>. The class <code>Individual</code> implements the functions described above (one phenotypic trait and a fitness value, plus a few methods). This class will be provided to <strong>puutools</strong> to instanciate trees.

## Read command line parameters
Let's implement a basic piece of code to read our parameters from the command line:

```c++
int main( int argc, char const** argv )
{
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 1) Read simulation parameters         */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  
  assert(argc==6);
  (void)argc;
  double  initial_trait_value = atof(argv[1]);
  int     simulation_time     = atoi(argv[2]);
  int     population_size     = atoi(argv[3]);
  double  mutation_rate       = atof(argv[4]);
  double  mutation_size       = atof(argv[5]);
  std::cout << "> Running a simulation with the following parameters:" << std::endl;
  std::cout << "  • Initial trait value: " << initial_trait_value << std::endl;
  std::cout << "  • Simulation time    : " << simulation_time << std::endl;
  std::cout << "  • Population size    : " << population_size << std::endl;
  std::cout << "  • Mutation rate      : " << mutation_rate << std::endl;
  std::cout << "  • Mutation size      : " << mutation_size << std::endl;
```

</p>

## A complex scenario where puutools has been useful <a name="complex_scenario"></a>

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


