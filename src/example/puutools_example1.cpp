
/**
 * \file      run_simulation.cpp
 * \authors   Charles Rocabert
 * \date      15-01-2022
 * \copyright Copyright © 2022 Charles Rocabert. All rights reserved
 * \license   puutools is released under the GNU General Public License
 * \brief     Individual-based simulation example using puutools
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

#include "./Prng.h"
#include "./Individual.h"
//#include "../include/puutools.h"
#include "../include/puu_node.h"


/**
 * \brief    Main function
 * \details  --
 * \param    int argc
 * \param    char const** argv
 * \return   \e int
 */
int main( int argc, char const** argv )
{
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 1) Define simulation parameters */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  double  initial_trait_value = 2.0;
  int     simulation_time     = 10000;
  int     population_size     = 1000;
  double  mutation_rate       = 0.001;
  double  mutation_size       = 0.1;
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 2) Initialize the population    */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  Prng*        prng              = new Prng();
  Individual** population        = new Individual*[population_size];
  puu_tree*    phylogenetic_tree = new puu_tree();
  double*      fitness_vector    = new double[population_size];
  double       fitness_sum       = 0.0;
  for (int i = 0; i < population_size; i++)
  {
    population[i] = new Individual(initial_trait_value);
    population[i]->mutate(mutation_rate, mutation_size);
    population[i]->compute_fitness();
    fitness_vector[i] = population[i]->get_fitness();
    fitness_sum += population[i]->get_fitness();
    phylogenetic_tree->add_root(population[i]);
  }
  for (int i = 0; i < population_size; i++)
  {
    fitness_vector[i] /= fitness_sum;
  }
  fitness_sum = 0.0;
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 3) Evolve the population        */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  unsigned int* nb_descendants = new unsigned int[population_size];
  prng->multinomial(nb_descendants, fitness_vector, population_size, population_size);
  for (int i = 0; i < population_size; i++)
  {
    
  }
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* ?) Free memory                  */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  for (int i = 0; i < population_size; i++)
  {
    delete population[i];
    population[i] = NULL;
  }
  delete[] population;
  population = NULL;
  delete[] fitness_vector;
  fitness_vector = NULL;
  delete prng;
  prng = NULL;
  return EXIT_SUCCESS;
}
