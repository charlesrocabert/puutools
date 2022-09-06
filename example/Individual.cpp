
/**
 * \file      Individual.cpp
 * \authors   Charles Rocabert
 * \date      16-01-2022
 * \copyright Copyright © 2022 Charles Rocabert. All rights reserved
 * \license   puutools is released under the GNU General Public License
 * \brief     Individual class definition
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

#include "Individual.h"


/*----------------------------
 * CONSTRUCTORS
 *----------------------------*/

/**
 * \brief    Constructor
 * \details  --
 * \param    Prng* prng
 * \param    double initial_trait_value
 * \return   \e void
 */
Individual::Individual( Prng* prng, double initial_trait_value )
{
  _prng    = prng;
  _trait   = initial_trait_value;
  _fitness = 0.0;
}

/**
 * \brief    Copy constructor
 * \details  --
 * \param    const Individual& individual
 * \return   \e void
 */
Individual::Individual( const Individual& individual )
{
  _prng    = individual._prng;
  _trait   = individual._trait;
  _fitness = individual._fitness;
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
Individual::~Individual( void )
{
  /* Nothing to do */
}

/*----------------------------
 * PUBLIC METHODS
 *----------------------------*/

/**
 * \brief    Mutate the individual
 * \details  --
 * \param    double mutation_rate
 * \param    double mutation_size
 * \return   \e void
 */
void Individual::mutate( double mutation_rate, double mutation_size )
{
  if (_prng->uniform() < mutation_rate)
  {
    _trait += _prng->gaussian(0.0, mutation_size);
  }
}

/**
 * \brief    Compute the fitness
 * \details  --
 * \param    void
 * \return   \e void
 */
void Individual::compute_fitness( void )
{
  _fitness = exp(-_trait*_trait);
}

