
/**
 * \file      puutools.h
 * \authors   Charles Rocabert
 * \date      17-01-2022
 * \copyright Copyright © 2022 Charles Rocabert. All rights reserved
 * \license   puutools is released under the GNU General Public License
 * \brief     puutools declarations
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

#ifndef __puutools__
#define __puutools__

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>


/****************************************************************************/

/**
 * \brief   Node class
 * \details Defines the class of a node in the tree (master root, root or normal).
 */
enum puu_node_class
{
  MASTER_ROOT = 0, /*!< The node is the master root */
  ROOT        = 1, /*!< The node is a root          */
  NORMAL      = 2  /*!< The node is normal          */
};

/****************************************************************************/

/**
 * \brief   puu_node class declaration
 * \details The puu_node class manages lineage or phylogenetic tree nodes
 */
template <typename selection_unit>
class puu_node
{
  
public:
  
  /*----------------------------
   * CONSTRUCTORS
   *----------------------------*/
  puu_node( void ) = delete;
  puu_node( unsigned long long int identifier );
  puu_node( unsigned long long int identifier, double time, selection_unit* unit );
  //puu_node( gzFile backup_file );
  puu_node( const puu_node& node ) = delete;
  
  /*----------------------------
   * DESTRUCTORS
   *----------------------------*/
  ~puu_node( void );
  
  /*----------------------------
   * GETTERS
   *----------------------------*/
  inline unsigned long long int get_id( void ) const;
  inline double                 get_insertion_time( void ) const;
  inline selection_unit*        get_selection_unit( void );
  inline puu_node*              get_parent( void );
  inline puu_node*              get_child( size_t pos );
  inline size_t                 get_nb_children( void ) const;
  inline puu_node_class         get_node_class( void ) const;
  inline bool                   is_master_root( void ) const;
  inline bool                   is_root( void ) const;
  inline bool                   is_normal( void ) const;
  inline bool                   is_ancestor( unsigned long long int ancestor_id ) const;
  inline bool                   is_active( void ) const;
  inline bool                   is_tagged( void ) const;
  
  /*----------------------------
   * SETTERS
   *----------------------------*/
  puu_node& operator=(const puu_node&) = delete;
  
  inline void set_parent( puu_node* node );
  inline void as_root( void );
  inline void as_normal( void );
  inline void inactivate( bool copy );
  inline void tag( void );
  inline void untag( void );
  
  /*----------------------------
   * PUBLIC METHODS
   *----------------------------*/
  //void save( gzFile backup_file );
  void add_child( puu_node* node );
  void remove_child( puu_node* node );
  void replace_by_grandchildren( puu_node* child_to_remove );
  void tag_lineage( void );
  void untag_lineage( void );
  
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
  unsigned long long int _identifier;     /*!< Node identifier                          */
  double                 _insertion_time; /*!< Node's insertion time                    */
  selection_unit*        _selection_unit; /*!< Attached selection unit                  */
  puu_node*              _parent;         /*!< Parental node                            */
  std::vector<puu_node*> _children;       /*!< Node's children                          */
  puu_node_class         _node_class;     /*!< Node class (master root, root or normal) */
  bool                   _active;         /*!< Indicates if the node is active          */
  bool                   _tagged;         /*!< Indicates if the node is tagged          */
};

/*----------------------------
 * GETTERS
 *----------------------------*/

/**
 * \brief    Get node's identifier
 * \details  --
 * \param    void
 * \return   \e unsigned long long int
 */
template <typename selection_unit>
inline unsigned long long int puu_node<selection_unit>::get_id( void ) const
{
  return _identifier;
}

/**
 * \brief    Get node's insertion time
 * \details  --
 * \param    void
 * \return   \e double
 */
template <typename selection_unit>
inline double puu_node<selection_unit>::get_insertion_time( void ) const
{
  return _insertion_time;
}

/**
 * \brief    Get the selection unit
 * \details  --
 * \param    void
 * \return   \e selection_unit*
 */
template <typename selection_unit>
inline selection_unit* puu_node<selection_unit>::get_selection_unit( void )
{
  return _selection_unit;
}

/**
 * \brief    Get the parental node
 * \details  --
 * \param    void
 * \return   \e puu_node*
 */
template <typename selection_unit>
inline puu_node<selection_unit>* puu_node<selection_unit>::get_parent( void )
{
  return _parent;
}

/**
 * \brief    Get the child at position 'pos'
 * \details  --
 * \param    void
 * \return   \e puu_node*
 */
template <typename selection_unit>
inline puu_node<selection_unit>* puu_node<selection_unit>::get_child( size_t pos )
{
  assert(pos < _children.size());
  return _children[pos];
}

/**
 * \brief    Get the number of children
 * \details  --
 * \param    void
 * \return   \e puu_node*
 */
template <typename selection_unit>
inline size_t puu_node<selection_unit>::get_nb_children( void ) const
{
  return _children.size();
}

/**
 * \brief    Get the node class
 * \details  --
 * \param    void
 * \return   \e puu_node_class
 */
template <typename selection_unit>
inline puu_node_class puu_node<selection_unit>::get_node_class( void ) const
{
  return _node_class;
}

/**
 * \brief    Check if the node is the master root
 * \details  --
 * \param    void
 * \return   \e bool
 */
template <typename selection_unit>
inline bool puu_node<selection_unit>::is_master_root( void ) const
{
  return (_node_class == MASTER_ROOT);
}

/**
 * \brief    Check if the node is a root
 * \details  --
 * \param    void
 * \return   \e bool
 */
template <typename selection_unit>
inline bool puu_node<selection_unit>::is_root( void ) const
{
  return (_node_class == ROOT);
}

/**
 * \brief    Check if the node is normal
 * \details  --
 * \param    void
 * \return   \e bool
 */
template <typename selection_unit>
inline bool puu_node<selection_unit>::is_normal( void ) const
{
  return (_node_class == NORMAL);
}

/**
 * \brief    Check if the given identifier is an ancestor
 * \details  --
 * \param    unsigned long long int ancestor_id
 * \return   \e bool
 */
template <typename selection_unit>
inline bool puu_node<selection_unit>::is_ancestor( unsigned long long int ancestor_id ) const
{
  puu_node* node = get_parent();
  while (node != NULL)
  {
    if (node->get_id() == ancestor_id)
    {
      return true;
    }
    node = node->get_parent();
  }
  return false;
}

/**
 * \brief    Check if the node is active or inactive
 * \details  --
 * \param    void
 * \return   \e bool
 */
template <typename selection_unit>
inline bool puu_node<selection_unit>::is_active( void ) const
{
  return _active;
}

/**
 * \brief    Check if the node is tagged or not
 * \details  --
 * \param    void
 * \return   \e bool
 */
template <typename selection_unit>
inline bool puu_node<selection_unit>::is_tagged( void ) const
{
  return _tagged;
}

/*----------------------------
 * SETTERS
 *----------------------------*/

/**
 * \brief    Add a parent
 * \details  --
 * \param    puu_node* node
 * \return   \e void
 */
template <typename selection_unit>
inline void puu_node<selection_unit>::set_parent( puu_node* node )
{
  _parent = node;
}

/**
 * \brief    Set the node class as root
 * \details  --
 * \param    void
 * \return   \e void
 */
template <typename selection_unit>
inline void puu_node<selection_unit>::as_root( void )
{
  _node_class = ROOT;
}

/**
 * \brief    Set the node class as normal
 * \details  --
 * \param    void
 * \return   \e void
 */
template <typename selection_unit>
inline void puu_node<selection_unit>::as_normal( void )
{
  _node_class = NORMAL;
}

/** @
 * \brief    Inactivate the node
 * \details  --
 * \param    selection_unit* unit
 * \param    bool copy
 * \return   \e void
 */
template <typename selection_unit>
inline void puu_node<selection_unit>::inactivate( bool copy )
{
  if (copy)
  {
    _selection_unit = new selection_unit(*_selection_unit);
  }
  else
  {
    _selection_unit = NULL;
  }
  _active = false;
}

/**
 * \brief    Tag the node
 * \details  --
 * \param    void
 * \return   \e void
 */
template <typename selection_unit>
inline void puu_node<selection_unit>::tag( void )
{
  _tagged = true;
}

/**
 * \brief    Untag the node
 * \details  --
 * \param    void
 * \return   \e void
 */
template <typename selection_unit>
inline void puu_node<selection_unit>::untag( void )
{
  _tagged = false;
}

/****************************************************************************/

/**
 * \brief   puu_tree class declaration
 * \details The puu_tree class manages lineage or phylogenetic tree
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
 * \brief    Get the number of nodes of the tree
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
 * \details  Return NULL if the node do not exist
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
 * \details  Return NULL if the node do not exist. The node must be active.
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
 * \details  Return NULL if the node map is empty
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
 * \details  Return NULL if the end of the node map is reached
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
 * \brief    Get active node identifiers list
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
 * \details  Return NULL if the population is extincted or if the tree is multirooted
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
 * \details  If the root is multirooted, returns the mean of root ages
 * \param    void
 * \return   \e double
 */
template <typename selection_unit>
inline double puu_tree<selection_unit>::get_common_ancestor_age( void )
{
  puu_node<selection_unit>* master_root = _node_map[0];
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 1) If the population extincted            */
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

/****************************************************************************/


#endif /* defined(__puutools__) */
