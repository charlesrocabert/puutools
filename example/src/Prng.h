
/**
 * \file      Prng.h
 * \authors   Charles Rocabert
 * \date      16-01-2022
 * \copyright Copyright © 2022 Charles Rocabert. All rights reserved
 * \license   puutools is released under the GNU General Public License
 * \brief     Prng class declaration
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

#ifndef __puutools__Prng__
#define __puutools__Prng__


#include <iostream>
#include <cmath>
#include <assert.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>


class Prng
{
  
public:
  
  /*----------------------------
   * CONSTRUCTORS
   *----------------------------*/
  Prng( void );
  Prng( unsigned long int seed );
  Prng( const Prng& prng );
  
  /*----------------------------
   * DESTRUCTORS
   *----------------------------*/
  ~Prng( void );
  
  /*----------------------------
   * GETTERS
   *----------------------------*/
  
  /*----------------------------
   * SETTERS
   *----------------------------*/
  Prng& operator=(const Prng&) = delete;
  
  inline void set_seed( unsigned long int seed );
  
  /*----------------------------
   * PUBLIC METHODS
   *----------------------------*/
  double uniform( void );
  int    uniform( int min, int max );
  int    bernouilli( double p );
  int    binomial( int n, double p );
  void   multinomial( unsigned int* draws, double* probas, int N, int K );
  double gaussian( double mu, double sigma );
  double lognormal( double mu, double sigma );
  int    exponential( double mu );
  int    poisson( double lambda );
  int    roulette_wheel( double* probas, double sum, int N );
  
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
  gsl_rng* _prng; /*!< Pseudorandom numbers generator */
  
};


/*----------------------------
 * GETTERS
 *----------------------------*/

/*----------------------------
 * SETTERS
 *----------------------------*/

/**
 * \brief    Set prng seed
 * \details  --
 * \param    unsigned long int seed
 * \return   \e void
 */
inline void Prng::set_seed( unsigned long int seed )
{
  gsl_rng_set(_prng, seed);
}


#endif /* defined(__puutools__Prng__) */
