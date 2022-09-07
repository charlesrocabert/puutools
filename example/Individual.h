
/**
 * \file      Individual.h
 * \authors   Charles Rocabert
 * \date      16-01-2022
 * \copyright Copyright © 2022 Charles Rocabert. All rights reserved
 * \license   puutools is released under the GNU General Public License
 * \brief     Individual class declaration
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

#ifndef __puutools__Individual__
#define __puutools__Individual__


#include "Prng.h"


class Individual
{
  
public:
  
  /*----------------------------
   * CONSTRUCTORS
   *----------------------------*/
  Individual( void ) = delete;
  Individual( Prng* prng, double initial_trait_value );
  Individual( const Individual& individual );
  
  /*----------------------------
   * DESTRUCTORS
   *----------------------------*/
  ~Individual( void );
  
  /*----------------------------
   * GETTERS
   *----------------------------*/
  inline double get_trait( void ) const;
  inline double get_fitness( void ) const;
  
  /*----------------------------
   * SETTERS
   *----------------------------*/
  Individual& operator=(const Individual&) = delete;
  
  /*----------------------------
   * PUBLIC METHODS
   *----------------------------*/
  void mutate( double mutation_rate, double mutation_size );
  void compute_fitness( void );
  
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
  Prng*  _prng;    /*!< Prng        */
  double _trait;   /*!< Trait value */
  double _fitness; /*!< Fitness     */
};

/*----------------------------
 * GETTERS
 *----------------------------*/

/**
 * \brief    Get the trait value
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Individual::get_trait( void ) const
{
  return _trait;
}

/**
 * \brief    Get the fitness value
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Individual::get_fitness( void ) const
{
  return _fitness;
}


#endif /* __puutools__Individual__ */