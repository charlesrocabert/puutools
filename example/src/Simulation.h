
/**
 * \file      Simulation.h
 * \authors   Charles Rocabert
 * \date      20-10-2022
 * \copyright Copyright © 2022-2023 Charles Rocabert. All rights reserved
 * \license   puutools is released under the GNU General Public License
 * \brief     Simulation class declaration
 */

/****************************************************************************
 * puutools
 * ---------
 * Easy-to-use C++ library for the live tracking of lineage and coalescence
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

#ifndef __puutools__Simulation__
#define __puutools__Simulation__

#include <iostream>
#include <cmath>
#include <vector>
#include <tuple>
#include <assert.h>

#include "Prng.h"
#include "Individual.h"


class Simulation
{

public:

  /*----------------------------
   * CONSTRUCTORS
   *----------------------------*/
  Simulation( void ) = delete;
  Simulation( Prng* prng, double initial_trait_value, int population_size, double mutation_rate, double mutation_size );
  Simulation( const Simulation& simulation ) = delete;

  /*----------------------------
   * DESTRUCTORS
   *----------------------------*/
  ~Simulation( void );

  /*----------------------------
   * GETTERS
   *----------------------------*/
  inline Individual*                          get_individual( int position );
  inline Individual*                          get_best_individual( void );
  inline std::tuple<Individual*, Individual*> get_first_parent_descendant_pair( void );
  inline std::tuple<Individual*, Individual*> get_next_parent_descendant_pair( void );

  /*----------------------------
   * SETTERS
   *----------------------------*/
  Simulation& operator=(const Simulation&) = delete;

  /*----------------------------
   * PUBLIC METHODS
   *----------------------------*/
  void initialize_population( void );
  void create_next_generation( void );
  void update_population( void );

  /*----------------------------
   * PUBLIC ATTRIBUTES
   *----------------------------*/

protected:

  /*----------------------------
   * PROTECTED METHODS
   *----------------------------*/

  /*----------------------------
   * PROTECTED ATTRIBUTES
   *----------------------------*/

  /* Parameters */
  Prng*   _prng;                /*!< Pseudo-random numbers generator */
  double  _initial_trait_value; /*!< Initial phenotypic trait value  */
  int     _population_size;     /*!< Population size                 */
  double  _mutation_rate;       /*!< Trait mutation rate             */
  double  _mutation_size;       /*!< Trait mutation size             */

  /* Simulation variables */
  std::vector<Individual*>  _population;         /*!< Population vector        */
  std::vector<double>       _fitness_vector;     /*!< Fitness vector           */
  std::vector<Individual*>  _next_population;    /*!< Next population vector   */
  std::vector<unsigned int> _nb_descendants;     /*!< Number of descendants    */
  int                       _best_individual;    /*!< Best individual position */
  int                       _current_parent;     /*!< Current parent           */
  int                       _current_descendant; /*!< Current descendant       */
  unsigned int              _local_count;        /*!< Local descendant count   */
};

/*----------------------------
 * GETTERS
 *----------------------------*/

/**
 * \brief    Get the individual at position "position"
 * \details  --
 * \param    int position
 * \return   \e Individual*
 */
inline Individual* Simulation::get_individual( int position )
{
  assert(position >= 0);
  assert(position < _population_size);
  return _population[position];
}

/**
 * \brief    Get the best individual
 * \details  --
 * \param    void
 * \return   \e Individual*
 */
inline Individual* Simulation::get_best_individual( void )
{
  return _population[_best_individual];
}

/**
 * \brief    Get the first pair of (parent, descendant)
 * \details  -
 * \param    void
 * \return   \e std::tuple<Individual*, Individual*>
 */
inline std::tuple<Individual*, Individual*> Simulation::get_first_parent_descendant_pair( void )
{
  _current_parent        = 0;
  _current_descendant    = 0;
  _local_count           = 0;
  Individual* parent     = NULL;
  Individual* descendant = NULL;
  while (_nb_descendants[_current_parent] == 0)
  {
    _current_parent++;
    _local_count = 0;
    if (_current_parent >= _population_size)
    {
      return std::make_tuple(parent, descendant);
    }
  }
  parent     = _population[_current_parent];
  descendant = _next_population[_current_descendant];
  //std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
  //std::cout << _current_parent << " " << _current_descendant << "\n";
  _current_descendant++;
  _local_count++;
  return std::make_tuple(parent, descendant);
}

/**
 * \brief    Get the next pair of (parent, descendant)
 * \details  -
 * \param    void
 * \return   \e std::tuple<Individual*, Individual*>
 */
inline std::tuple<Individual*, Individual*> Simulation::get_next_parent_descendant_pair( void )
{
  Individual* parent     = NULL;
  Individual* descendant = NULL;
  if (_local_count >= _nb_descendants[_current_parent])
  {
    _current_parent++;
    _local_count = 0;
    if (_current_parent >= _population_size)
    {
      return std::make_tuple(parent, descendant);
    }
  }
  while (_nb_descendants[_current_parent] == 0)
  {
    _current_parent++;
    _local_count = 0;
    if (_current_parent >= _population_size)
    {
      return std::make_tuple(parent, descendant);
    }
  }
  parent     = _population[_current_parent];
  descendant = _next_population[_current_descendant];
  //std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
  //std::cout << _current_parent << " " << _current_descendant << "\n";
  _current_descendant++;
  _local_count++;
  return std::make_tuple(parent, descendant);
}


#endif /* __puutools__Simulation__ */
