<!--<h1 align="center">puuTools</h1>-->

<p align="center">
<img src="./logo/puuTools_logo.png" width=200>
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
- [Algorithm overview](#algorithm)
- [First usage with a walk-through example ](#first_usage)
- [A complex scenario where puuTools can be useful](#complex_scenario)
- [Copyright](#copyright)
- [License](#license)

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
<img src="./doc/backup_vs_live_tracking-crop.jpg">
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
Download the <a href="https://github.com/charlesrocabert/Evo2Sim/releases/latest">latest release</a> of <strong>puutools</strong>, and save it to a directory of your choice. Open a terminal and use the <code>cd</code> command to navigate to this directory. To install <strong>puutools</strong>, simply call <code>install.sh</code> on the command line:
</p>

```
sh install.sh
```

<p align="justify">
The script requires sudo access to install the library in the appropriate folder. <strong>puutools</strong> comes as a single C++ header file, and will be installed in an <code>include</code> directory (usually <code>/usr/local/include</code>).

If you cannot or do not want to use a sudo access, simply <a href="https://github.com/charlesrocabert/puutools/raw/main/puutools/puutools.h">download the source file <code>puutools.h</code></a> and include it directly to your project.
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
<img src="./doc/basic_algorithm-crop.jpg" width=700>
</p>

<!--
<p align="justify">
Figure III.9 – Live update of lineage and phylogenetic trees. At each time-step t, the population state is updated (divisions, deaths, cell updates, ...): (i) at each division, the two daughter cells are added to the trees as leaves, with their parent as a common ancestor, (ii) dead cells are removed from trees. Both lineage and phylogenetic trees are pruned (dead branches are removed), and the phylogenetic tree is shortened (intermediate nodes not being common ancestors are removed). In this example, we start at time t. The common ancestor of the whole population (CA, in red) is the dead cell labelled 0. The most recent common ancestor (MRCA, in blue) is the alive cell 2. Tree leaves are represented in green and all correspond to alive cells (first row). The population state is then updated to time t + 1: the cell 3 dies, and the cell 2 divides in daughter cells 2 and 5 (the cell 2 is still tracked because it divided 4 times and didn’t died yet). These events are added to both trees (second row). Then, pruning and shortening algorithms are applied: the lineage tree looses the branch 3 − 3. The phylogenetic tree looses the leaf 3, and the oldest 2 node. The MRCA is now the node 2, linked to nodes 2 and 4. 
</p>
-->

## First usage with a walk-through example <a name="first_usage"></a>

<p align="justify">
<strong>puutools</strong> is distributed as an external static library. Once installed (see above), the header must be included with the standard <code>#include</code> instruction:
</p>

```c++
#include <puutools.h>
```

<p align="justify">
The main object that will be manipulated by the user is the class <code>puu_tree<selection_unit></code> which instanciates a dynamic representation of a lineage or phylogenetic tree. <code>puu_tree</code> class uses a template: <code>selection_unit</code> can be any class created on your own, with the constraint that the copy contructor must be at least public and not disabled, and preferably fully implemented to avoid errors.
</p>

<p align="justify">
In this example, we will implement a basic algorithm to simulate the evolution of a population of constant size $N$. Individuals are asexual and generations are non-overlapping. Each individual owns a phenotypic trait $x \in \mathcal{R}$ which can mutate with a probability $m$ (per individual per generation) and a size $s$ such that the mutated trait $x' = x + \mathcal{N}(0, s)$. Individual's fitness is calculated with the standard Gaussian fitness function $w = e^{-\frac{x^2}{2}}$. The number of descendants at each generation is fitness proportionate.
</p>

<p align="justify">
We will implement five command line arguments to define each simulation:

- The initial trait value $x_0$;
- The simulation time $T$ (in generations);
- The population size $N$;
- The mutation rate $m$;
- The mutation size $s$;
</p>

<p align="justify">
We will introduce <strong>puutools</strong> code step by step.
</p>

### Pre-processor include directives

<p align="justify">
Let's first include the necessary standard library (<code>std</code>) utilitaries and <strong>puutools</strong> libraries:
</p>

```c++
#include <iostream>
#include <vector>
#include <assert.h>
#include <puutools.h>
```

<p align="justify">
We then include to classes that have been pre-implemented on purpose for this tutorial (see the <code>example</code> folder):
</p>

```c++
#include "Prng.h"
#include "Individual.h"
```

<p align="justify">
The <code>Prng</code> class contains several random functions based on the <a href="https://www.gnu.org/software/gsl/" target="_blank">GNU Scientific Library</a>. The class <code>Individual</code> contains the basic structure of an individual (one phenotypic trait and one fitness value, plus a few methods). This class will be provided to <strong>puutools</strong> to instanciate trees.
</p>

### Read command line parameters

<p align="justify">
Let's implement a basic piece of code to read our parameters from the command line:
</p>

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

### Instanciate the pseudo-random numbers generator (prng)

<p align="justify">
We also instanciate a PRNG object:
</p>

```c++
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 2) Create the prng                    */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  
  Prng prng(time(0));
```

### Initialize the population

<p align="justify">
This step is used to create the initial population and initialize two trees:

- A lineage tree, which will contain parent-children relationships at every generations,
- A phylogenetic tree, which will only contain common ancestors.
</p>

```c++
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 3) Initialize the population          */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  
  puu_tree<Individual>      lineage_tree;
  puu_tree<Individual>      phylogenetic_tree;
  std::vector<Individual*>  population(population_size);
  std::vector<unsigned int> nb_descendants(population_size);
  for (int i = 0; i < population_size; i++)
  {
    population[i] = new Individual(initial_trait_value);
    population[i]->mutate(&prng, mutation_rate, mutation_size);
    lineage_tree.add_root(population[i]);
    phylogenetic_tree.add_root(population[i]);
  }
```

<p align="justify">
Two pieces of code are important here:
</p>

```c++
puu_tree<Individual> lineage_tree;
puu_tree<Individual> phylogenetic_tree;
```

<p align="justify">
We instanciate a tree which will handle the <code>Individual</code> class. Note that we are creating two trees (one for tracking lineages, one for tracking phylogenetic relationships). It is <strong>not mandatory</strong> to name your individual class "Individual". You can use any name.
</p>

```c++
lineage_tree.add_root(population[i]);
phylogenetic_tree.add_root(population[i]);
```

<p align="justify">
Each time a new individual is created, we must add a corresponding <strong>root</strong> in each tree with the function <code>add_root(*individual)</code> (<code>*</code> symbolizing the memory address). To do so, we provide the memory address (through the pointer <code>population[i]</code> to the i<sup>th</sup> individual). If you are not at ease with pointers and memory adresses, consider following an introduction to C/C++ before going further in this example.
</p>

### Evolution algorithm

<p align="justify">
This is the core of our "simple" example. For clarity, each task is uncoupled while it is possible to optimize further the code by merging several loops together.
At each generation:
  
- The vector $w$ of the relative fitnesses is calculated (<strong>step 1</strong>, note that we also detect the best individual of the current generation);
- The number of descendants per individual is drawn from a multinomial distribution (<strong>step 2</strong>);
- The new population is generated from this drawing (<strong>step 3</strong>);
- The population is replaced by the new one (<strong>step 4</strong>);
- Trees structures are updated (<strong>step 5</strong>);
</p>

```c++
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 4) Evolve the population              */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  
  std::vector<double> fitness_vector(population_size);
  double              fitness_sum     = 0.0;
  int                 best_individual = 0;
  double              best_fitness    = 0.0;
  for (int generation = 1; generation <= simulation_time; generation++)
  {
    if (generation%1000==0)
    {
      std::cout << ">> Generation " << generation << "\n";
    }
    
    /* STEP 1 : Update and normalize the fitness vector
       ------------------------------------------------- */
    fitness_sum = 0.0;
    for (int i = 0; i < population_size; i++)
    {
      population[i]->compute_fitness();
      fitness_vector[i]  = population[i]->get_fitness();
      fitness_sum       += population[i]->get_fitness();
    }
    best_individual = 0;
    best_fitness    = 0.0;
    for (int i = 0; i < population_size; i++)
    {
      fitness_vector[i] /= fitness_sum;
      if (best_fitness < fitness_vector[i])
      {
        best_individual = i;
      }
    }
    
    /* STEP 2 : Draw the number of descendants
       ---------------------------------------- */
    prng.multinomial(nb_descendants.data(), fitness_vector.data(), population_size, population_size);
    
    /* STEP 3 : Generate the new population
       ------------------------------------- */
    std::vector<Individual*> new_population(population_size);
    size_t new_individual_pos = 0;
    for (int i = 0; i < population_size; i++)
    {
      for (unsigned int j = 0; j < nb_descendants[i]; j++)
      {
        new_population[new_individual_pos] = new Individual(*population[i]);
        new_population[new_individual_pos]->mutate(&prng, mutation_rate, mutation_size);
        lineage_tree.add_reproduction_event(population[i], new_population[new_individual_pos], (double)generation);
        phylogenetic_tree.add_reproduction_event(population[i], new_population[new_individual_pos], (double)generation);
        new_individual_pos++;
      }
      lineage_tree.inactivate(population[i], true);
      phylogenetic_tree.inactivate(population[i], false);
      delete population[i];
    }
    
    /* STEP 4 : Replace the current population with the new one
       --------------------------------------------------------- */
    for (int i = 0; i < population_size; i++)
    {
      population[i] = new_population[i];
    }
    new_population.clear();
    
    /* STEP 5: Update the lineage and phylogenetic trees
       -------------------------------------------------- */
    if (generation%1000==0)
    {
      lineage_tree.update_as_lineage_tree();
      phylogenetic_tree.update_as_phylogenetic_tree();
    }
  }
```

<p align="justify">
The most import steps for us are <strong>steps 3 and 5</strong>, where trees are manipulated.
</p>

```c++
lineage_tree.add_reproduction_event(population[i], new_population[new_individual_pos], (double)generation);
phylogenetic_tree.add_reproduction_event(population[i], new_population[new_individual_pos], (double)generation);
```

<p align="justify">
Each time a new individual is created from its parent (it is literally a copy of its parent: <code>new Individual(*population[i])</code>), we must create a new relationship in each tree. This is done thought the method <code>add_reproduction_event(*parent, *child, time)</code> (<code>*</code> symbolizing the memory address).
</p>

```c++
lineage_tree.inactivate(population[i], true);
phylogenetic_tree.inactivate(population[i], false);
```

<p align="justify">
Then, we must tell to our trees that the individuals from the previous generation are now dead, with the method <code>inactivate(*individual, copy)</code>. The parameter <code>copy</code> is a boolean (true/false). If true, the tree will copy your individual when inactivated, to save it independently from your population algorithm (this is why it is mandatory to implement a copy constructor with <strong>puutools</strong>). This method must be called by the user. Indeed, depending on the complexity of a simulation, parents and their children can both be alive at the same time (<em>e.g.</em> for a bacterial population). The main reason is tree's structure manipulations can only be done with dead individuals.
</p>

<p align="justify">
Note that here, we copy the dead individuals in the lineage tree, but not in the phylogenetic tree. Indeed, we will recover later the evolution of the phenotypic trait and the fitness from the lineage tree, while we will only extract the structure of the phylogenetic tree.
</p>

```c++
lineage_tree.update_as_lineage_tree();
phylogenetic_tree.update_as_phylogenetic_tree();
```

<p align="justify">
The user will decide with these two methods if a tree is a lineage or a phylogeny. Updating a lineage tree consists in pruning dead branches (branches containing only dead invididuals). Updating a phylogenetic tree consists in pruning the dead branches and shortening the tree, by removing all intermediate nodes to only keep common ancestors.
</p>

<p align="justify">
It is not mandatory to call these methods at each generation. In this example, the methods are called every 1,000 generations. If the trees are updated more often, this will increase the computational load. If the trees are updated less often, this will increase the memory load (trees grow at each generation before being pruned and shortened). The user must decide on the period of trees' updates depending on the performance of its own code.
</p>

<p align="justify">
Remember that the size of a phylogenetic tree is approximately constant over time ($2n-1$ nodes), while a lineage tree will grow slowly over time. Depending on the complexity of your simulation, in can be useful to provide a secondary class saving important information (such that phenotypic trait values, mutational events, etc) instead of the main individual class.
</p>

### Extracting the information from the trees

<p align="justify">
Now that the simulation reached an end, we want to extract some information from the trees.
We first call a last time update functions to ensure a good final structure:
</p>

```c++
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 5) Save lineage and phylogenetic data */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  
  lineage_tree.update_as_lineage_tree();
  phylogenetic_tree.update_as_phylogenetic_tree();
```

<p align="justify">
We then retrieve the lineage of the last best individual. To do so, we first get the tree's node from the memory address of the individual using the method <code>get_node_by_selection_unit(*individual)</code>. We then trace back the lineage of the node using the method <code>get_parent()</code> until the master root of the tree is reached (the master root is not a real root of the tree, but is here to anchor every roots). Doing so, we write statistics in a file:
</p>

```c++
  /* Save the lineage of the last best individual
     --------------------------------------------- */
  std::ofstream file("./output/lineage_best.txt", std::ios::out | std::ios::trunc);
  file << "generation mutation_size trait fitness" << std::endl;
  puu_node<Individual>* best_node = lineage_tree.get_node_by_selection_unit(population[best_individual]);
  while (!best_node->is_master_root())
  {
    file << best_node->get_insertion_time() << " ";
    file << best_node->get_selection_unit()->get_mutation_size() << " ";
    file << best_node->get_selection_unit()->get_trait() << " ";
    file << best_node->get_selection_unit()->get_fitness() << std::endl;
    best_node = best_node->get_parent();
    file.flush();
  }
  file.close();
```

<p align="justify">
We then save the data over the whole lineage tree. To do so, we use standard list exploration methods implemented in <strong>puutools</strong>: <code>get_first()</code> and <code>get_next()</code>. When the last node is reached, the function returns <code>NULL</code>. Note that we carefully check that the node is not the master root:
</p>

```c++
  /* Save the lineage of all alive individuals
     ------------------------------------------ */
  file.open("./output/lineage_all.txt", std::ios::out | std::ios::trunc);
  file << "generation mutation_size trait fitness" << std::endl;
  puu_node<Individual>* node = lineage_tree.get_first();
  while (node != NULL)
  {
    if (!node->is_master_root())
    {
      file << node->get_insertion_time() << " ";
      file << node->get_selection_unit()->get_mutation_size() << " ";
      file << node->get_selection_unit()->get_trait() << " ";
      file << node->get_selection_unit()->get_fitness() << std::endl;
      file.flush();
    }
    node = lineage_tree.get_next();
  }
  file.close();
```

<p align="justify">
Finally, we save the structure of the phylogenetic tree in Newick format (<code>.phb</code> extension):
</p>

```c++
  /* Save the phylogenetic tree
     --------------------------- */
  phylogenetic_tree.write_newick_tree("./output/phylogenetic_tree.phb");
```

<p align="justify">
At the end of the script, the memory must be cleaned from the population:
</p>

```c++
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 6) Free memory                        */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  
  for (int i = 0; i < population_size; i++)
  {
    delete population[i];
    population[i] = NULL;
  }
  return EXIT_SUCCESS;
}
```

### Results

This simulation example is available in the folder <code>example</code> of this repository, and can be compiled with CMake (navigate to the folder <code>example/cmake</code> with a terminal and run the following command:
  
  sh make_release.sh

The binary executable <code>puutools_example</code> is located in the folder <code>example/build/bin</code>.

As an example, we run the simulation by placing an initial population os size $N=200$, away from the fitness optimum (initial trait value = 2). The simulation time is $T=10000$ generations, with a mutation rate $m=0.02$ and a mutation size $s=0.02$.

  ../build/bin/puutools_example 2.0 10000 200 0.02 0.02

Output files are written in the folder <code>example/output</code>, which also contain a Rscript to generate some figures. For example, we can see that the population evolved towards the optimum. As we recover the lineage of the last best individual, we have also access to the size of fixed mutations.
We can also vizualize the phylogenetic tree, as well as the distribution of phenotypic trait values accross the lineage tree.

**Trajectory of the lineage of the last best individual, and phylogenetic tree:**

![image](https://user-images.githubusercontent.com/25666459/191052960-9ec2108c-fb8d-4451-a4ea-46679ed52642.png)

**Repartition of the phenotypic trait in the whole lineage tree:**

![image](https://user-images.githubusercontent.com/25666459/191051967-d0d406ba-0849-478d-853e-247346f51698.png)

## A complex scenario where puutools has been useful <a name="complex_scenario"></a>





