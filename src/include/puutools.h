
/**
 * \file      puutools.h
 * \authors   Charles Rocabert
 * \date      14-01-2022
 * \copyright Copyright © 2022 Charles Rocabert. All rights reserved
 * \license   puutools is released under the GNU General Public License
 * \brief     puutools classes declaration
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
#include <vector>
#include <unordered_map>
#include <string>
#include <cstring>
#include <cmath>
#include <zlib.h>

/******************************************************************************/

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

/******************************************************************************/

/**
 * \brief   Node class definition
 * \details TODO.
 */
template <typename individual>
class puu_node
{
  
public:
  
  /*---------------------------------------------
   * CONSTRUCTORS DECLARATION (puu_node)
   *---------------------------------------------*/
  puu_node( void ) = delete;
  puu_node( unsigned long long int identifier, double score );
  puu_node( unsigned long long int identifier, double score, individual* ind );
  puu_node( gzFile backup_file );
  puu_node( const puu_node& node ) = delete;
  
  /*---------------------------------------------
   * DESTRUCTORS DECLARATION (puu_node)
   *---------------------------------------------*/
  ~puu_node( void );
  
  /*---------------------------------------------
   * GETTERS DECLARATION (puu_node)
   *---------------------------------------------*/
  inline unsigned long long int get_id( void ) const;
  inline double                 get_score( void );
  inline individual*            get_individual( void );
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
  
  /*---------------------------------------------
   * SETTERS DECLARATION (puu_node)
   *---------------------------------------------*/
  puu_node& operator=(const puu_node&) = delete;
  
  inline void set_score( double score );
  inline void set_parent( puu_node* node );
  inline void as_master_root( void );
  inline void as_root( void );
  inline void as_normal( void );
  inline void as_inactive( void );
  inline void tag( void );
  inline void untag( void );
  
  /*---------------------------------------------
   * PUBLIC METHODS DECLARATION (puu_node)
   *---------------------------------------------*/
  void save( gzFile backup_file );
  void add_child( puu_node* node );
  void remove_child( puu_node* node );
  void replace_by_grandchildren( puu_node* child_to_remove );
  void tag_lineage( void );
  void untag_lineage( void );
  
  /*---------------------------------------------
   * PUBLIC ATTRIBUTES DECLARATION (puu_node)
   *---------------------------------------------*/
  
protected:
  
  /*---------------------------------------------
   * PROTECTED METHODS DECLARATION (puu_node)
   *---------------------------------------------*/
  
  /*---------------------------------------------
   * PROTECTED ATTRIBUTES DECLARATION (puu_node)
   *---------------------------------------------*/
  unsigned long long int _identifier; /*!< Node identifier                          */
  double                 _score;      /*!< Node score                               */
  individual*            _individual; /*!< Attached individual                      */
  puu_node*              _parent;     /*!< Parent of the node                       */
  std::vector<puu_node*> _children;   /*!< Children of the node                     */
  puu_node_class         _node_class; /*!< Node class (master root, root or normal) */
  bool                   _active;     /*!< Indicates if the node is active          */
  bool                   _tagged;     /*!< Indicates if the node is tagged          */
};

/*---------------------------------------------
 * GETTERS DEFINITION (puu_node)
 *---------------------------------------------*/

/**
 * \brief    Get node identifier
 * \details  --
 * \param    void
 * \return   \e unsigned long long int
 */
inline unsigned long long int puu_node::get_id( void ) const
{
  return _identifier;
}

/**
 * \brief    Get node score
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double puu_node::get_score( void ) const
{
  return _score;
}

/**
 * \brief    Get the individual
 * \details  --
 * \param    void
 * \return   \e individual*
 */
inline individual* puu_node::get_individual( void )
{
  return _individual;
}

/**
 * \brief    Get the parental node
 * \details  --
 * \param    void
 * \return   \e puu_node*
 */
inline puu_node* puu_node::get_parent( void )
{
  return _parent;
}

/**
 * \brief    Get the child at position 'pos'
 * \details  --
 * \param    void
 * \return   \e puu_node*
 */
inline puu_node* puu_node::get_child( size_t pos )
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
inline size_t puu_node::get_nb_children( void ) const
{
  return _children.size();
}

/**
 * \brief    Get the node class
 * \details  --
 * \param    void
 * \return   \e puu_node_class
 */
inline puu_node_class puu_node::get_node_class( void ) const
{
  return _node_class;
}

/**
 * \brief    Check if the node is the master root
 * \details  --
 * \param    void
 * \return   \e bool
 */
inline bool puu_node::is_master_root( void ) const
{
  return (_node_class == MASTER_ROOT);
}

/**
 * \brief    Check if the node is a root
 * \details  --
 * \param    void
 * \return   \e bool
 */
inline bool puu_node::is_root( void ) const
{
  return (_node_class == ROOT);
}

/**
 * \brief    Check if the node is normal
 * \details  --
 * \param    void
 * \return   \e bool
 */
inline bool puu_node::is_normal( void ) const
{
  return (_node_class == NORMAL);
}

/**
 * \brief    Check if the given identifier is an ancestor
 * \details  --
 * \param    unsigned long long int ancestor_id
 * \return   \e bool
 */
inline bool puu_node::is_ancestor( unsigned long long int ancestor_id )
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
inline bool puu_node::is_active( void ) const
{
  return _active;
}

/**
 * \brief    Check if the node is tagged or not
 * \details  --
 * \param    void
 * \return   \e bool
 */
inline bool puu_node::is_tagged( void ) const
{
  return _tagged;
}

/*---------------------------------------------
 * SETTERS DEFINITION (puu_node)
 *---------------------------------------------*/

/**
 * \brief    Add a parent
 * \details  --
 * \param    puu_node* node
 * \return   \e void
 */
inline void puu_node::set_parent( puu_node* node )
{
  _parent = node;
}

/**
 * \brief    Set the node class as master root
 * \details  --
 * \param    void
 * \return   \e void
 */
inline void puu_node::as_master_root( void )
{
  _identifier = 0;
  _individual = NULL;
  _parent     = NULL;
  _node_class = MASTER_ROOT;
  _active     = false;
  _tagged     = false;
  _children.clear();
}

/**
 * \brief    Set the node class as root
 * \details  --
 * \param    void
 * \return   \e void
 */
inline void puu_node::as_root( void )
{
  _node_class = ROOT;
}

/**
 * \brief    Set the node class as normal
 * \details  --
 * \param    void
 * \return   \e void
 */
inline void puu_node::as_normal( void )
{
  _node_class = NORMAL;
}

/**
 * \brief    Set the node state as inactive
 * \details  --
 * \param    void
 * \return   \e void
 */
inline void Node::as_inactive( void )
{
  _active = false;
}

/**
 * \brief    Tag the node
 * \details  --
 * \param    void
 * \return   \e void
 */
inline void puu_node::tag( void )
{
  _tagged = true;
}

/**
 * \brief    Untag the node
 * \details  --
 * \param    void
 * \return   \e void
 */
inline void puu_node::untag( void )
{
  _tagged = false;
}

/******************************************************************************/

/**
 * \brief   Tree class definition
 * \details TODO.
 */
template <typename individual>
class puu_tree
{
  
public:
  
  /*---------------------------------------------
   * CONSTRUCTORS DECLARATION (puu_tree)
   *---------------------------------------------*/
  puu_tree( void );
  puu_tree( gzFile backup_file );
  puu_tree( const puu_tree& tree ) = delete;
  
  /*---------------------------------------------
   * DESTRUCTORS DECLARATION (puu_tree)
   *---------------------------------------------*/
  ~puu_tree( void );
  
  /*---------------------------------------------
   * GETTERS DECLARATION (puu_tree)
   *---------------------------------------------*/
  inline unsigned long long int get_current_id( void ) const;
  inline size_t                 get_nb_nodes( void ) const;
  inline puu_node*              get_node( unsigned long long int identifier );
  inline puu_node*              get_first( void );
  inline puu_node*              get_next( void );
  inline void                   get_active_node_identifiers( std::vector<unsigned long long int>* active_node_identifiers );
  inline puu_node*              get_best_active_node( void );
  inline puu_node*              get_common_ancestor( void );
  inline double                 get_common_ancestor_age( void );
  inline unsigned long long int get_node_id_by_active_individual_identifiers( unsigned long long int active_individual_identifiers );
  
  /*---------------------------------------------
   * SETTERS DECLARATION (puu_tree)
   *---------------------------------------------*/
  puu_tree& operator=(const puu_tree&) = delete;
  
  /*---------------------------------------------
   * PUBLIC METHODS DECLARATION (puu_tree)
   *---------------------------------------------*/
  void save( gzFile backup_file );
  void add_root( individual* ind );
  void add_reproduction_event( individual* parent, individual* child );
  void delete_node( unsigned long long int node_identifier );
  void prune();
  void shorten();
  
  void write_tree( std::string filename );
  void write_newick_tree( std::string filename );
  
  void write_lineage_statistics( std::string filename, unsigned long long int identifier );
  void write_phylogeny_statistics( std::string filename );
  
  /*---------------------------------------------
   * PUBLIC ATTRIBUTES DECLARATION (puu_tree)
   *---------------------------------------------*/
  
protected:
  
  /*---------------------------------------------
   * PROTECTED METHODS DECLARATION (puu_tree)
   *---------------------------------------------*/
  void inOrderNewick( puu_node* node, size_t parent_time, std::stringstream& output );
  void tag_tree();
  void untag_tree();
  void tag_offspring( puu_node* node, std::vector<puu_node*>* tagged_nodes );
  
  /*---------------------------------------------
   * PROTECTED ATTRIBUTES DECLARATION (puu_tree)
   *---------------------------------------------*/
  unsigned long long int                                      _current_id; /*!< Current node id       */
  std::unordered_map<unsigned long long int, puu_node*>       _node_map;   /*!< Tree nodes map        */
  std::unordered_map<unsigned long long int, puu_node*>::iterator _iterator;   /*!< Tree map iterator     */
};

/*----------------------------
 * GETTERS
 *----------------------------*/

/**
 * \brief    Get current node identifier
 * \details  --
 * \param    void
 * \return   \e unsigned long long int
 */
inline unsigned long long int Tree::get_current_id( void ) const
{
  return _current_id;
}

/**
 * \brief    Get the number of nodes of the tree
 * \details  --
 * \param    void
 * \return   \e size_t
 */
inline size_t Tree::get_number_of_nodes( void ) const
{
  return _node_map.size();
}

/**
 * \brief    Get the node by its identifier
 * \details  Return NULL if the node do not exist
 * \param    unsigned long long int identifier
 * \return   \e Node*
 */
inline Node* Tree::get_node( unsigned long long int identifier )
{
  if (_node_map.find(identifier) != _node_map.end())
  {
    return _node_map[identifier];
  }
  return NULL;
}

/**
 * \brief    Get the first node of the map
 * \details  Return NULL if the tree is empty
 * \param    void
 * \return   \e Node*
 */
inline Node* Tree::get_first_node( void )
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
 * \details  Return NULL if the end of the tree is reached
 * \param    void
 * \return   \e Node*
 */
inline Node* Tree::get_next_node( void )
{
  _iterator++;
  if (_iterator != _node_map.end())
  {
    return _iterator->second;
  }
  return NULL;
}

/**
 * \brief    Get alive node identifiers list
 * \details  --
 * \param    std::vector<unsigned long long int>* alive_nodes
 * \return   \e void
 */
inline void Tree::get_alive_nodes( std::vector<unsigned long long int>* alive_nodes )
{
  alive_nodes->clear();
  for (_iterator = _cell_map.begin(); _iterator != _cell_map.end(); ++_iterator)
  {
    alive_nodes->push_back(_iterator->second->get_id());
  }
}

/**
 * \brief    Get best alive node
 * \details  --
 * \param    void
 * \return   \e Node*
 */
inline Node* Tree::get_best_alive_node( void )
{
  double best_score = 0.0;
  Node*  best_node  = NULL;
  for (_iterator = _node_map.begin(); _iterator != _node_map.end(); ++_iterator)
  {
    if (_iterator->second->isAlive())
    {
      if (best_score < _iterator->second->get_alive_cell()->get_score())
      {
        best_score = _iterator->second->get_alive_cell()->get_score();
        best_node  = _iterator->second;
      }
    }
  }
  return best_node;
}

/**
 * \brief    Get the common ancestor
 * \details  Return NULL if the population is extincted or if the tree is multirooted
 * \param    void
 * \return   \e Node*
 */
inline Node* Tree::get_common_ancestor( void )
{
  Node* master_root = _node_map[0];
  if (master_root->get_number_of_children() == 1)
  {
    return master_root->get_child(0);
  }
  return NULL;
}

/**
 * \brief    Get the common ancestor age
 * \details  --
 * \param    void
 * \return   \e double
 */
inline double Tree::get_common_ancestor_age( void )
{
  Node* master_root = _node_map[0];
  
  /*-----------------------------------------*/
  /* 1) If the population extincted          */
  /*-----------------------------------------*/
  if(master_root->get_number_of_children() == 0)
  {
    return 0.0;
  }
  
  /*-----------------------------------------*/
  /* 2) If there is a unique common ancestor */
  /*-----------------------------------------*/
  else if (master_root->get_number_of_children() == 1)
  {
    if (master_root->get_child(0)->isAlive())
    {
      return (double)master_root->get_child(0)->get_alive_cell()->get_birth_time();
    }
    else
    {
      return (double)master_root->get_child(0)->get_replication_report()->get_birth_time();
    }
  }
  
  /*-------------------------------------------*/
  /* 3) If there are multiple common ancestors */
  /*-------------------------------------------*/
  else
  {
    double mean = 0.0;
    for (size_t i = 0; i < master_root->get_number_of_children(); i++)
    {
      if (master_root->get_child(0)->isAlive())
      {
        mean += (double)master_root->get_child(0)->get_alive_cell()->get_birth_time();
      }
      else
      {
        mean += (double)master_root->get_child(0)->get_replication_report()->get_birth_time();
      }
    }
    return mean/master_root->get_number_of_children();
  }
}

/**
 * \brief    Get an alive node identifier by its linked alive cell identifier
 * \details  --
 * \param    void
 * \return   \e double
 */
inline unsigned long long int Tree::get_node_id_by_alive_cell_id( unsigned long long int alive_cell_identifier )
{
  for (_iterator = _node_map.begin(); _iterator != _node_map.end(); ++_iterator)
  {
    if (_iterator->second->isAlive())
    {
      if (_iterator->second->get_alive_cell()->get_id() == alive_cell_identifier)
      {
        return _iterator->first;
      }
    }
  }
  return 0;
}

/*----------------------------
 * SETTERS
 *----------------------------*/


#endif /* defined(__puutools__) */
