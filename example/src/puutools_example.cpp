
/**
 * \file      puutools_example.cpp
 * \authors   Charles Rocabert
 * \date      15-01-2022
 * \copyright Copyright © 2022 Charles Rocabert. All rights reserved
 * \license   puutools is released under the GNU General Public License
 * \brief     Simulation example using puutools
 */

/****************************************************************************
 * puutools
 * ---------
 * Easy-to-use C++ library for the live tracking of lineage and phylogenetic
 * trees in individual-based forward-in-time simulations of evolution.
 *
 * Copyright © 2022 Charles Rocabert
 * Web: https://github.com/charlesrocabert/puutools/
 *
 * puutools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * puutools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/

#include <iostream>
#include <vector>
#include <tuple>
#include <assert.h>
#include <puutools.h>

#include "Prng.h"
#include "Individual.h"
#include "Simulation.h"


/**
 * \brief    Main function
 * \details  --
 * \param    int argc
 * \param    char const** argv
 * \return   \e int
 */
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
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 2) Create the prng                    */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  
  Prng prng(time(0));
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 3) Create the simulation              */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  
  Simulation simulation(&prng, initial_trait_value, population_size, mutation_rate, mutation_size);
  simulation.initialize_population();
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 4) Create trees and add roots         */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  
  puu_tree<Individual> lineage_tree;
  puu_tree<Individual> phylogenetic_tree;
  
  for (int i = 0; i < population_size; i++)
  {
    lineage_tree.add_root(simulation.get_individual(i));
    phylogenetic_tree.add_root(simulation.get_individual(i));
  }
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 5) Evolve the population              */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  
  for (int generation = 1; generation <= simulation_time; generation++)
  {
    if (generation%1000==0)
    {
      std::cout << ">> Generation " << generation << "\n";
    }
    
    /* STEP 1 : Create the next generation
       ------------------------------------ */
    simulation.create_next_generation();
    
    /* STEP 2 : Add reproduction events
       --------------------------------- */
    Individual* parent;
    Individual* descendant;
    std::tie(parent, descendant) = simulation.get_first_parent_descendant_pair();
    while (parent != NULL)
    {
      lineage_tree.add_reproduction_event(parent, descendant, (double)generation);
      phylogenetic_tree.add_reproduction_event(parent, descendant, (double)generation);
      std::tie(parent, descendant) = simulation.get_next_parent_descendant_pair();
    }
    
    /* STEP 3 : Inactivate parents
       ---------------------------- */
    for (int i = 0; i < population_size; i++)
    {
      lineage_tree.inactivate(simulation.get_individual(i), true);
      phylogenetic_tree.inactivate(simulation.get_individual(i), false);
    }
    
    /* STEP 4 : Replace the current population with the new one
       --------------------------------------------------------- */
    simulation.update_population();
    
    /* STEP 5: Update the lineage and phylogenetic trees
       -------------------------------------------------- */
    if (generation%100==0)
    {
      lineage_tree.update_as_lineage_tree();
      phylogenetic_tree.update_as_phylogenetic_tree();
    }
    
  }
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 6) Save lineage and phylogenetic data */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  
  lineage_tree.update_as_lineage_tree();
  phylogenetic_tree.update_as_phylogenetic_tree();
  
  /* Save the lineage of the last best individual
     --------------------------------------------- */
  std::ofstream file("./output/lineage_best.txt", std::ios::out | std::ios::trunc);
  file << "generation mutation_size trait fitness" << std::endl;
  puu_node<Individual>* best_node = lineage_tree.get_node_by_selection_unit(simulation.get_best_individual());
  while (best_node != NULL)
  {
    file << best_node->get_insertion_time() << " ";
    file << best_node->get_selection_unit()->get_mutation_size() << " ";
    file << best_node->get_selection_unit()->get_trait() << " ";
    file << best_node->get_selection_unit()->get_fitness() << std::endl;
    best_node = best_node->get_parent();
    file.flush();
  }
  file.close();
  
  /* Save the lineage of all alive individuals
     ------------------------------------------ */
  file.open("./output/lineage_all.txt", std::ios::out | std::ios::trunc);
  file << "generation mutation_size trait fitness" << std::endl;
  puu_node<Individual>* node = lineage_tree.get_first();
  while (node != NULL)
  {
    file << node->get_insertion_time() << " ";
    file << node->get_selection_unit()->get_mutation_size() << " ";
    file << node->get_selection_unit()->get_trait() << " ";
    file << node->get_selection_unit()->get_fitness() << std::endl;
    file.flush();
    node = lineage_tree.get_next();
  }
  file.close();
  
  /* Save the phylogenetic tree
     --------------------------- */
  phylogenetic_tree.write_newick_tree("./output/phylogenetic_tree.phb");
  
  return EXIT_SUCCESS;
}
