
/**
 * \file      puutools.h
 * \authors   Charles Rocabert
 * \date      17-01-2022
 * \copyright Copyright © 2022 Charles Rocabert. All rights reserved
 * \license   puutools is released under the GNU General Public License
 * \brief     puu_tree declarations
 */

/****************************************************************************
 * puutools
 * ---------
 * Live tracking of lineage/phylogenetic trees and evolutionary events in
 * individual-based forward-in-time simulations of evolution.
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

#ifndef __puutools__puu_tree__
#define __puutools__puu_tree__

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
//#include <zlib.h>

#include "puu_enums.h"
#include "puu_node.h"


/**
 * \brief   puu_tree class declaration
 * \details The puu_tree class manages a lineage or phylogenetic tree
 */
template <typename selection_unit>
class puu_tree
{
  
public:
  
  /*----------------------------
   * CONSTRUCTORS
   *----------------------------*/
  puu_tree( void );
  //puu_tree( gzFile backup_file );
  puu_tree( const puu_tree& tree ) = delete;
  
  /*----------------------------
   * DESTRUCTORS
   *----------------------------*/
  ~puu_tree( void );
  
  /*----------------------------
   * GETTERS
   *----------------------------*/
  inline size_t                    get_nb_nodes( void ) const;
  inline puu_node<selection_unit>* get_node_by_identifier( unsigned long long int identifier );
  inline puu_node<selection_unit>* get_node_by_selection_unit( selection_unit* unit );
  inline puu_node<selection_unit>* get_first( void );
  inline puu_node<selection_unit>* get_next( void );
  inline void                      get_active_node_identifiers( std::vector<unsigned long long int>* active_node_identifiers );
  inline puu_node<selection_unit>* get_common_ancestor( void );
  inline double                    get_common_ancestor_age( void );
  
  /*----------------------------
   * SETTERS
   *----------------------------*/
  puu_tree& operator=(const puu_tree&) = delete;
  
  /*----------------------------
   * PUBLIC METHODS
   *----------------------------*/
  //void save( gzFile backup_file );
  void add_root( selection_unit* unit );
  void add_reproduction_event( selection_unit* parent, selection_unit* child, double time );
  void inactivate( selection_unit* unit, bool copy_unit );
  void prune();
  void shorten();
  void write_tree( std::string filename );
  void write_newick_tree( std::string filename );
  
  /*----------------------------
   * PUBLIC ATTRIBUTES
   *----------------------------*/
  
protected:
  
  /*----------------------------
   * PROTECTED METHODS
   *----------------------------*/
  void delete_node( unsigned long long int node_identifier );
  void inOrderNewick( puu_node<selection_unit>* node, double parent_time, std::stringstream& output );
  void tag_tree();
  void untag_tree();
  void tag_offspring( puu_node<selection_unit>* node, std::vector<puu_node<selection_unit>*>* tagged_nodes );
  
  /*----------------------------
   * PROTECTED ATTRIBUTES
   *----------------------------*/
  unsigned long long int                                                                   _current_id; /*!< Current node id     */
  std::unordered_map<unsigned long long int, puu_node<selection_unit>*>                    _node_map;   /*!< Tree nodes map      */
  std::unordered_map<selection_unit*, puu_node<selection_unit>*>                           _unit_map;   /*!< Selection units map */
  typename std::unordered_map<unsigned long long int, puu_node<selection_unit>*>::iterator _iterator;   /*!< Tree map iterator   */
};

/*----------------------------
 * GETTERS
 *----------------------------*/

/**
 * \brief    Get the number of nodes in the tree
 * \details  --
 * \param    void
 * \return   \e size_t
 */
template <typename selection_unit>
inline size_t puu_tree<selection_unit>::get_nb_nodes( void ) const
{
  return _node_map.size();
}

/**
 * \brief    Get the node by its identifier
 * \details  Returns NULL if the node does not exist
 * \param    unsigned long long int identifier
 * \return   \e Node*
 */
template <typename selection_unit>
inline puu_node<selection_unit>* puu_tree<selection_unit>::get_node_by_identifier( unsigned long long int identifier )
{
  if (_node_map.find(identifier) != _node_map.end())
  {
    return _node_map[identifier];
  }
  return NULL;
}

/**
 * \brief    Get the node by selection unit
 * \details  Returns NULL if the node does not exist. The node must be active.
 * \param    selection_unit* unit
 * \return   \e puu_node*
 */
template <typename selection_unit>
inline puu_node<selection_unit>* puu_tree<selection_unit>::get_node_by_selection_unit( selection_unit* unit )
{
  if (_unit_map.find(unit) != _unit_map.end())
  {
    assert(_unit_map[unit]->is_active());
    return _unit_map[unit];
  }
  return NULL;
}

/**
 * \brief    Get the first node of the map
 * \details  Returns NULL if the node map is empty
 * \param    void
 * \return   \e puu_node*
 */
template <typename selection_unit>
inline puu_node<selection_unit>* puu_tree<selection_unit>::get_first( void )
{
  _iterator = _node_map.begin();
  if (_iterator != _node_map.end())
  {
    return _iterator->second;
  }
  return NULL;
}

/**
 * \brief    Get the next node
 * \details  Returns NULL if the end of the node map is reached
 * \param    void
 * \return   \e puu_node*
 */
template <typename selection_unit>
inline puu_node<selection_unit>* puu_tree<selection_unit>::get_next( void )
{
  _iterator++;
  if (_iterator != _node_map.end())
  {
    return _iterator->second;
  }
  return NULL;
}

/**
 * \brief    Get the list of active node identifiers
 * \details  --
 * \param    std::vector<unsigned long long int>* active_node_identifiers
 * \return   \e void
 */
template <typename selection_unit>
inline void puu_tree<selection_unit>::get_active_node_identifiers( std::vector<unsigned long long int>* active_node_identifiers )
{
  active_node_identifiers->clear();
  for (_iterator = _node_map.begin(); _iterator != _node_map.end(); ++_iterator)
  {
    if (_iterator->second->is_active())
    {
      active_node_identifiers->push_back(_iterator->second->get_id());
    }
    
  }
}

/**
 * \brief    Get the common ancestor
 * \details  Returns NULL if the population is extincted or if the tree is multi-rooted
 * \param    void
 * \return   \e puu_node*
 */
template <typename selection_unit>
inline puu_node<selection_unit>* puu_tree<selection_unit>::get_common_ancestor( void )
{
  puu_node<selection_unit>* master_root = _node_map[0];
  if (master_root->get_number_of_children() == 1)
  {
    return master_root->get_child(0);
  }
  return NULL;
}

/**
 * \brief    Get the common ancestor age
 * \details  If the root is multi-rooted, returns the mean of root ages
 * \param    void
 * \return   \e double
 */
template <typename selection_unit>
inline double puu_tree<selection_unit>::get_common_ancestor_age( void )
{
  puu_node<selection_unit>* master_root = _node_map[0];
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 1) If the population went extincte        */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  if(master_root->get_nb_children() == 0)
  {
    return 0.0;
  }
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 2) If there is a unique common ancestor   */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  else if (master_root->get_nb_children() == 1)
  {
    if (master_root->get_child(0)->is_active())
    {
      return (double)master_root->get_child(0)->get_insertion_time();
    }
    else
    {
      return (double)master_root->get_child(0)->get_insertion_time();
    }
  }
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 3) If there are multiple common ancestors */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  else
  {
    double mean = 0.0;
    for (size_t i = 0; i < master_root->get_nb_children(); i++)
    {
      if (master_root->get_child(0)->is_active())
      {
        mean += (double)master_root->get_child(0)->get_insertion_time();
      }
      else
      {
        mean += (double)master_root->get_child(0)->get_insertion_time();
      }
    }
    return mean/master_root->get_nb_children();
  }
}

/*----------------------------
 * SETTERS
 *----------------------------*/

#include "puu_tree.cpp"


#endif /* defined(__puutools__puu_tree__) */
