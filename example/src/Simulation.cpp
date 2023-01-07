
/**
 * \file      Simulation.cpp
 * \authors   Charles Rocabert
 * \date      20-10-2022
 * \copyright Copyright © 2022-2023 Charles Rocabert. All rights reserved
 * \license   puutools is released under the GNU General Public License
 * \brief     Simulation class definition
 */

/****************************************************************************
 * puutools
 * ---------
 * Easy-to-use C++ library for the live tracking of lineage and phylogenetic
 * trees in individual-based forward-in-time simulations.
 *
 * Copyright © 2022-2023 Charles Rocabert
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

#include "Simulation.h"


/*----------------------------
 * CONSTRUCTORS
 *----------------------------*/

/**
 * \brief    Constructor
 * \details  --
 * \param    Prng* prng
 * \param    double initial_trait_value
 * \param    int population_size
 * \param    double mutation_rate
 * \param    double mutation_size
 * \return   \e void
 */
Simulation::Simulation( Prng* prng, double initial_trait_value, int population_size, double mutation_rate, double mutation_size )
{
  assert(prng != NULL);
  assert(population_size > 0);
  assert(mutation_rate >= 0.0);
  assert(mutation_rate <= 1.0);

  /* Parameters */
  _prng                = prng;
  _initial_trait_value = initial_trait_value;
  _population_size     = population_size;
  _mutation_rate       = mutation_rate;
  _mutation_size       = mutation_size;

  /* Simulation variables */
  _population.reserve(_population_size);
  _fitness_vector.reserve(_population_size);
  _next_population.reserve(_population_size);
  _nb_descendants.reserve(_population_size);
  _best_individual    = 0;
  _current_parent     = 0;
  _current_descendant = 0;
  _local_count        = 0;
}

/*----------------------------
 * DESTRUCTORS
 *----------------------------*/

/**
 * \brief    Destructor
 * \details  --
 * \param    void
 * \return   \e void
 */
Simulation::~Simulation( void )
{
  for (int i = 0; i < _population_size; i++)
  {
    delete _population[i];
    _population[i] = NULL;
  }
  _population.clear();
  _fitness_vector.clear();
  _next_population.clear();
  _nb_descendants.clear();
  _prng = NULL;
}

/*----------------------------
 * PUBLIC METHODS
 *----------------------------*/

/**
 * \brief    Initialize the population
 * \details  --
 * \param    void
 * \return   \e void
 */
void Simulation::initialize_population( void )
{
  for (int i = 0; i < _population_size; i++)
  {
    _population[i] = new Individual(_initial_trait_value);
    _population[i]->mutate(_prng, _mutation_rate, _mutation_size);
  }
}

/**
 * \brief    Create the next generation
 * \details  --
 * \param    void
 * \return   \e void
 */
void Simulation::create_next_generation( void )
{
  /* STEP 1 : Update and normalize the fitness vector
     ------------------------------------------------- */
  double fitness_sum = 0.0;
  for (int i = 0; i < _population_size; i++)
  {
    _population[i]->compute_fitness();
    _fitness_vector[i]  = _population[i]->get_fitness();
    fitness_sum        += _population[i]->get_fitness();
  }
  double best_fitness = 0.0;
  _best_individual    = 0;
  for (int i = 0; i < _population_size; i++)
  {
    _fitness_vector[i] /= fitness_sum;
    if (best_fitness < _fitness_vector[i])
    {
      _best_individual = i;
    }
  }

  /* STEP 2 : Draw the number of descendants
     ---------------------------------------- */
  _prng->multinomial(_nb_descendants.data(), _fitness_vector.data(), _population_size, _population_size);

  /* STEP 3 : Generate the new population
     ------------------------------------- */
  assert(_next_population.size() == 0);
  _next_population.reserve(_population_size);
  int new_individual_pos = 0;
  for (int i = 0; i < _population_size; i++)
  {
    for (unsigned int j = 0; j < _nb_descendants[i]; j++)
    {
      _next_population[new_individual_pos] = new Individual(*_population[i]);
      _next_population[new_individual_pos]->mutate(_prng, _mutation_rate, _mutation_size);
      new_individual_pos++;
    }
  }
}

/**
 * \brief    Update the population with the next generation
 * \details  --
 * \param    void
 * \return   \e void
 */
void Simulation::update_population( void )
{
  for (int i = 0; i < _population_size; i++)
  {
    delete _population[i];
    _population[i] = _next_population[i];
  }
  _next_population.clear();
}


