
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
#include <typeinfo>
#include <assert.h>

#include "../include/puutools.h"
#include "../lib/puutools.cpp"


/**
 * \brief   Basic Individual class
 * \details Declare and defne a very basic Individual class, caryying a single quantitative trait and a fitness value.
 */
class Individual
{
public:
  Individual( void ) = delete;
  Individual( double birth_time, double death_time, double trait, double fitness );
  Individual( const Individual& individual );
  inline double get_birth_time( void ) const;
  inline double get_death_time( void ) const;
  inline double get_trait( void ) const;
  inline double get_fitness( void ) const;
protected:
  double _birth_time;
  double _death_time;
  double _trait;
  double _fitness;
};
Individual::Individual( double birth_time, double death_time, double trait, double fitness )
{
  _birth_time = birth_time;
  _death_time = death_time;
  _trait      = trait;
  _fitness    = fitness;
}
Individual::Individual( const Individual& individual )
{
  _birth_time = individual._birth_time;
  _death_time = individual._death_time;
  _trait      = individual._trait;
  _fitness    = individual._fitness;
}
inline double Individual::get_birth_time( void ) const
{
  return _birth_time;
}
inline double Individual::get_death_time( void ) const
{
  return _death_time;
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
  Individual* my_ind = new Individual(1.0, 3.0, 2.0, 0.1);
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 1) Testing the creation of the default "MASTER_ROOT" node */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  std::cout << "\n>> Testing MASTER ROOT node" << std::endl;
  puu_node<Individual>* my_node = new puu_node<Individual>(0);
  std::cout << "   > Is master root? " << my_node->is_master_root() << std::endl;
  std::cout << "   > Is root?        " << my_node->is_root() << std::endl;
  std::cout << "   > Is normal?      " << my_node->is_normal() << std::endl;
  std::cout << "   > Is active?      " << my_node->is_active() << std::endl;
  std::cout << "   > Is tagged?      " << my_node->is_tagged() << std::endl;
  delete my_node;
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 2) Testing the creation of a normal node                  */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  std::cout << "\n>> Testing NORMAL node" << std::endl;
  my_node = new puu_node<Individual>(1, my_ind->get_birth_time(), my_ind);
  std::cout << "   > Is master root?     " << my_node->is_master_root() << std::endl;
  std::cout << "   > Is root?            " << my_node->is_root() << std::endl;
  std::cout << "   > Is normal?          " << my_node->is_normal() << std::endl;
  std::cout << "   > Is active?          " << my_node->is_active() << std::endl;
  std::cout << "   > Is tagged?          " << my_node->is_tagged() << std::endl;
  std::cout << "   > Individual fitness? " << my_node->get_selection_unit()->get_fitness() << std::endl;
  my_node->tag();
  std::cout << "  >> Tag the node:" << std::endl;
  std::cout << "   > Is tagged?          " << my_node->is_tagged() << std::endl;
  puu_node<Individual>* child1 = new puu_node<Individual>(2, my_ind->get_birth_time(), my_ind);
  puu_node<Individual>* child2 = new puu_node<Individual>(3, my_ind->get_birth_time(), my_ind);
  my_node->add_child(child1);
  my_node->add_child(child2);
  std::cout << "  >> Add two children:" << std::endl;
  std::cout << "   > Nb children?        " << my_node->get_nb_children() << std::endl;
  my_node->inactivate(true);
  std::cout << "  >> Inactivate the node:" << std::endl;
  std::cout << "   > Ind pointer:        " << my_ind << std::endl;
  std::cout << "   > Nod ind pointer:    " << my_node->get_selection_unit() << std::endl;
  
  delete child2;
  child2 = NULL;
  delete child1;
  child1 = NULL;
  delete my_node;
  my_node = NULL;
  delete my_ind;
  my_ind = NULL;
  return EXIT_SUCCESS;
}
