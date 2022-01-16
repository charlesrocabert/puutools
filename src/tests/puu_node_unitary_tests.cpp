
/**
 * \file      puu_node_unitary_tests.cpp
 * \authors   Charles Rocabert
 * \date      16-01-2022
 * \copyright Copyright © 2022 Charles Rocabert. All rights reserved
 * \license   puutools is released under the GNU General Public License
 * \brief     Run unitary tests on the class puu_node
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

#include "../include/puu_enums.h"
#include "../include/puu_node.h"
#include "../lib/puu_node.cpp"

/**
 * \brief   Basic Individual class
 * \details Declare and defne a very basic Individual class, caryying a single quantitative trait and a fitness value.
 */
class Individual
{
public:
  Individual( void ) = delete;
  Individual( double trait, double fitness );
  Individual( const Individual& individual );
  inline double get_trait( void ) const;
  inline double get_fitness( void ) const;
protected:
  double _trait;
  double _fitness;
};
Individual::Individual( double trait, double fitness )
{
  _trait   = trait;
  _fitness = fitness;
}
Individual::Individual( const Individual& individual )
{
  _trait   = individual._trait;
  _fitness = individual._fitness;
}
inline double Individual::get_trait( void ) const
{
  return _trait;
}
inline double Individual::get_fitness( void ) const
{
  return _fitness;
}


/**
 * \brief    Main function
 * \details  --
 * \param    int argc
 * \param    char const** argv
 * \return   \e int
 */
int main( int argc, char const** argv )
{
  Individual* my_ind = new Individual(2.0, 0.1);
  
  puu_node<Individual>* test_node = new puu_node<Individual>(0);
  std::cout << test_node->is_master_root() << std::endl;
  
  return EXIT_SUCCESS;
}
