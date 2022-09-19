
/**
 * \file      puutools_wright_fisher_example.cpp
 * \authors   Charles Rocabert
 * \date      15-01-2022
 * \copyright Copyright © 2022 Charles Rocabert. All rights reserved
 * \license   puutools is released under the GNU General Public License
 * \brief     Wright-Fisher simulation example using puutools
 */

/****************************************************************************
 * puutools
 * ---------
 * Lineage and phylogenetic tree toolbox for individual-based simulations.
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
#include <assert.h>
#include <puutools.h>

#include "Prng.h"
#include "Individual.h"
//#include "../puutools/puutools.h"

/**
 * \brief    Main function
 * \details  --
 * \param    int argc
 * \param    char const** argv
 * \return   \e int
 */
int main( int argc, char const** argv )
{
  (void)argc;
  (void)argv;
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 1) Define simulation parameters       */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  
  double  initial_trait_value = 2.0;
  int     simulation_time     = 10000;
  int     population_size     = 1000;
  double  mutation_rate       = 1.0/200.0;
  double  mutation_size       = 0.02;
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 2) Create the prng                    */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  
  Prng prng(time(0));
  
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
    lineage_tree.update_as_lineage_tree();
    phylogenetic_tree.update_as_phylogenetic_tree();
  }
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 5) Save lineage and phylogenetic data */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  
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
  
  /* Save the phylogenetic tree
     --------------------------- */
  phylogenetic_tree.write_newick_tree("./output/phylogenetic_tree.phb");
  
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
