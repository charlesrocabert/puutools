
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
#include <assert.h>

#include "Prng.h"
#include "Individual.h"
#include "puu_enums.h"
#include "puu_node.h"
#include "puu_tree.h"


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
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 1) Define simulation parameters */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  double  initial_trait_value = 0.0;
  int     simulation_time     = 100000;
  int     population_size     = 200;
  double  mutation_rate       = 0.0;
  double  mutation_size       = 0.0;
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 2) Initialize the population    */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  Prng*                 prng              = new Prng();
  Individual**          population        = new Individual*[population_size];
  puu_tree<Individual>* phylogenetic_tree = new puu_tree<Individual>();
  double*               fitness_vector    = new double[population_size];
  double                fitness_sum       = 0.0;
  for (int i = 0; i < population_size; i++)
  {
    population[i] = new Individual(prng, initial_trait_value);
    population[i]->mutate(mutation_rate, mutation_size);
    population[i]->compute_fitness();
    fitness_vector[i]  = population[i]->get_fitness();
    fitness_sum       += population[i]->get_fitness();
    phylogenetic_tree->add_root(population[i]);
  }
  for (int i = 0; i < population_size; i++)
  {
    fitness_vector[i] /= fitness_sum;
  }
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 3) Evolve the population        */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  std::ofstream file("/Users/charlesrocabert/git/puutools/src/example/output/MRCA_age_N200.txt", std::ios::out | std::ios::trunc);
  for (int generation = 1; generation <= simulation_time; generation++)
  {
    if (generation%1000==0)
    {
      std::cout << ">> Generation " << generation << "\n";
    }
    unsigned int* nb_descendants = new unsigned int[population_size];
    Individual**  new_population = new Individual*[population_size];
    size_t        index          = 0;
    fitness_sum                  = 0.0;
    prng->multinomial(nb_descendants, fitness_vector, population_size, population_size);
    
    for (int i = 0; i < population_size; i++)
    {
      for (int j = 0; j < (int)nb_descendants[i]; j++)
      {
        new_population[index] = new Individual(*population[i]);
        new_population[index]->mutate(mutation_rate, mutation_size);
        new_population[index]->compute_fitness();
        fitness_vector[i]  = new_population[index]->get_fitness();
        fitness_sum       += new_population[index]->get_fitness();
        phylogenetic_tree->add_reproduction_event(population[i], new_population[index], (double)generation);
        index++;
      }
      phylogenetic_tree->inactivate(population[i], false);
    }
    for (int i = 0; i < population_size; i++)
    {
      delete population[i];
      population[i] = new_population[i];
    }
    delete[] new_population;
    new_population = NULL;
    delete[] nb_descendants;
    nb_descendants = NULL;
    for (int i = 0; i < population_size; i++)
    {
      fitness_vector[i] /= fitness_sum;
    }
    phylogenetic_tree->prune();
    phylogenetic_tree->shorten();
    file << generation-phylogenetic_tree->get_common_ancestor_age() << "\n";
    file.flush();
  }
  file.close();
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 4) Free memory                  */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  delete[] fitness_vector;
  fitness_vector = NULL;
  delete phylogenetic_tree;
  phylogenetic_tree = NULL;
  for (int i = 0; i < population_size; i++)
  {
    delete population[i];
    population[i] = NULL;
  }
  delete[] population;
  population = NULL;
  delete prng;
  prng = NULL;
  return EXIT_SUCCESS;
}
