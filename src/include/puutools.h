
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
 * Web: https://github.com/charlesrocabert/puutools
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
 * \brief   Node state
 * \details Defines the state of a node in the tree (active or inactive).
 */
enum puu_node_state
{
  ACTIVE   = 0, /*!< The node is active   */
  INACTIVE = 1  /*!< The node is inactive */
};

/******************************************************************************/

/**
 * \brief   Node class definition
 * \details TODO.
 */
template <class individual>
class puu_node
{
  
public:
  
  /*----------------------------
   * CONSTRUCTORS
   *----------------------------*/
  puu_node( void ) = delete;
  puu_node( unsigned long long int identifier );
  puu_node( unsigned long long int identifier, individual* ind );
  puu_node( gzFile backup_file );
  puu_node( const puu_node& node ) = delete;
  
  /*----------------------------
   * DESTRUCTORS
   *----------------------------*/
  ~puu_node( void );
  
  /*----------------------------
   * GETTERS
   *----------------------------*/
  inline unsigned long long int get_id( void ) const;
  inline individual*            get_individual( void );
  inline puu_node*              get_parent( void );
  inline puu_node*              get_child( size_t pos );
  inline size_t                 get_nb_children( void ) const;
  inline puu_node_class         get_node_class( void ) const;
  inline puu_node_state         get_node_state( void ) const;
  inline bool                   isTagged( void ) const;
  inline bool                   isMasterRoot( void ) const;
  inline bool                   isRoot( void ) const;
  inline bool                   isNormal( void ) const;
  inline bool                   isActive( void ) const;
  inline bool                   isInactive( void ) const;
  inline bool                   isAncestor( unsigned long long int ancestor_id );
  
  /*----------------------------
   * SETTERS
   *----------------------------*/
  puu_node& operator=(const puu_node&) = delete;
  
  inline void set_individual( individual* ind );
  inline void set_parent( puu_node* node );
  inline void tag( void );
  inline void untag( void );
  inline void set_master_root( void ); /* as */
  inline void set_root( void ); /* as */
  inline void set_normal( void ); /* as */
  inline void set_dead( void ); /* as */
  inline void set_alive( void ); /* as */
  
  /*----------------------------
   * PUBLIC METHODS
   *----------------------------*/
  void save( gzFile backup_file );
  void add_child( puu_node* node );
  void remove_child( puu_node* node );
  void replace_children( puu_node* child_to_remove );
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
  unsigned long long int _identifier; /*!< Node identifier                          */
  individual*            _individual; /*!< Attached individual                      */
  puu_node*              _parent;     /*!< Parent of the node                       */
  std::vector<puu_node*> _children;   /*!< Children of the node                     */
  puu_node_class         _node_class; /*!< Node class (master root, root or normal) */
  puu_node_state         _node_state; /*!< Node state (active or inactive)          */
  bool                   _tagged;     /*!< Indicates if the node is tagged          */
};


/*----------------------------
 * GETTERS
 *----------------------------*/

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
 * \brief    Get the individual
 * \details  --
 * \param    void
 * \return   \e Cell*
 */
inline individual* puu_node::get_individual( void )
{
  return _individual;
}

/**
 * \brief    Get the replication report linked to the node
 * \details  --
 * \param    void
 * \return   \e ReplicationReport*
 */
inline ReplicationReport* Node::get_replication_report( void )
{
  return _replication_report;
}

/**
 * \brief    Get the parent node
 * \details  --
 * \param    void
 * \return   \e Node*
 */
inline Node* Node::get_parent( void )
{
  return _parent;
}

/**
 * \brief    Get the child at position 'pos'
 * \details  --
 * \param    void
 * \return   \e Node*
 */
inline Node* Node::get_child( size_t pos )
{
  assert(pos < _children.size());
  return _children[pos];
}

/**
 * \brief    Get the number of children
 * \details  --
 * \param    void
 * \return   \e Node*
 */
inline size_t Node::get_number_of_children( void ) const
{
  return _children.size();
}

/**
 * \brief    Get the node class
 * \details  --
 * \param    void
 * \return   \e node_class
 */
inline node_class Node::get_node_class( void ) const
{
  return _node_class;
}

/**
 * \brief    Get the node state
 * \details  --
 * \param    void
 * \return   \e node_state
 */
inline node_state Node::get_node_state( void ) const
{
  return _node_state;
}

/**
 * \brief    Check if the node is tagged or not
 * \details  --
 * \param    void
 * \return   \e bool
 */
inline bool Node::isTagged( void ) const
{
  return _tagged;
}

/**
 * \brief    Check if the node is the master root
 * \details  --
 * \param    void
 * \return   \e bool
 */
inline bool Node::isMasterRoot( void ) const
{
  return (_node_class == MASTER_ROOT);
}

/**
 * \brief    Check if the node is a root or not
 * \details  --
 * \param    void
 * \return   \e bool
 */
inline bool Node::isRoot( void ) const
{
  return (_node_class == ROOT);
}

/**
 * \brief    Check if the node is normal or not
 * \details  --
 * \param    void
 * \return   \e bool
 */
inline bool Node::isNormal( void ) const
{
  return (_node_class == NORMAL);
}

/**
 * \brief    Check if the node is dead
 * \details  --
 * \param    void
 * \return   \e bool
 */
inline bool Node::isDead( void ) const
{
  return (_node_state == DEAD);
}

/**
 * \brief    Check if the node is alive
 * \details  --
 * \param    void
 * \return   \e bool
 */
inline bool Node::isAlive( void ) const
{
  return (_node_state == ALIVE);
}

/**
 * \brief    Check if the given identifier is an ancestor
 * \details  --
 * \param    unsigned long long int ancestor_id
 * \return   \e bool
 */
inline bool Node::isAncestor( unsigned long long int ancestor_id )
{
  Node* node = get_parent();
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

/*----------------------------
 * SETTERS
 *----------------------------*/

/**
 * \brief    Set the alive cell's pointer (and its replication report pointer)
 * \details  --
 * \param    Cell* cell
 * \return   \e void
 */
inline void Node::set_alive_cell( Cell* cell )
{
  assert(_node_state == ALIVE);
  _alive_cell         = cell;
  _replication_report = cell->get_replication_report();
}

/**
 * \brief    Set the replication report pointer
 * \details  Only alive node should be modified
 * \param    ReplicationReport* replication_report
 * \return   \e void
 */
inline void Node::set_replication_report( ReplicationReport* replication_report )
{
  assert(_node_state == ALIVE);
  _replication_report = replication_report;
}

/**
 * \brief    Add a parent
 * \details  --
 * \param    Node* node
 * \return   \e void
 */
inline void Node::set_parent( Node* node )
{
  _parent = node;
}

/**
 * \brief    Tag the node
 * \details  --
 * \param    void
 * \return   \e void
 */
inline void Node::tag( void )
{
  _tagged = true;
}

/**
 * \brief    Untag the node
 * \details  --
 * \param    void
 * \return   \e void
 */
inline void Node::untag( void )
{
  _tagged = false;
}

/**
 * \brief    Set the node class as master root
 * \details  --
 * \param    void
 * \return   \e void
 */
inline void Node::set_master_root( void )
{
  _identifier         = 0;
  _alive_cell         = NULL;
  _replication_report = NULL;
  _parent             = NULL;
  _children.clear();
  _node_class = MASTER_ROOT;
  _node_state = DEAD;
  _tagged     = false;
}

/**
 * \brief    Set the node class as root
 * \details  --
 * \param    void
 * \return   \e void
 */
inline void Node::set_root( void )
{
  _node_class = ROOT;
}

/**
 * \brief    Set the node class as normal
 * \details  --
 * \param    void
 * \return   \e void
 */
inline void Node::set_normal( void )
{
  _node_class = NORMAL;
}

/**
 * \brief    Set the node state dead
 * \details  --
 * \param    size_t death_time
 * \return   \e void
 */
inline void Node::set_dead( size_t death_time )
{
  /*----------------------------------------*/
  /* 1) Copy and set the replication report */
  /*----------------------------------------*/
  _replication_report = new ReplicationReport(*_replication_report);
  _replication_report->set_death_time(death_time);
  
  /*----------------------------------------*/
  /* 2) Set the alive cell pointer to NULL  */
  /*----------------------------------------*/
  _alive_cell = NULL;
  
  /*----------------------------------------*/
  /* 3) set the new node state              */
  /*----------------------------------------*/
  _node_state = DEAD;
}

/******************************************************************************/

class puu_tree
{
  
public:
  
  /*----------------------------
   * CONSTRUCTORS
   *----------------------------*/
  Tree( void ) = delete;
  Tree( Parameters* parameters );
  Tree( Parameters* parameters, Population* population, gzFile backup_file );
  Tree( const Tree& tree ) = delete;
  
  /*----------------------------
   * DESTRUCTORS
   *----------------------------*/
  ~Tree( void );
  
  /*----------------------------
   * GETTERS
   *----------------------------*/
  inline unsigned long long int get_current_id( void ) const;
  inline size_t get_number_of_nodes( void ) const;
  inline Node*  get_node( unsigned long long int identifier );
  inline Node*  get_first_node( void );
  inline Node*  get_next_node( void );
  inline void   get_alive_nodes( std::vector<unsigned long long int>* alive_nodes );
  inline Node*  get_best_alive_node( void );
  inline Node*  get_common_ancestor( void );
  inline double get_common_ancestor_age( void );
  inline unsigned long long int get_node_id_by_alive_cell_id( unsigned long long int alive_cell_identifier );
  
  /*----------------------------
   * SETTERS
   *----------------------------*/
  Tree& operator=(const Tree&) = delete;
  
  /*----------------------------
   * PUBLIC METHODS
   *----------------------------*/
  void save( gzFile backup_file );
  void add_root( Cell* cell );
  void add_division( Cell* parent, Cell* child1, Cell* child2 );
  void freeze_node( unsigned long long int cell_identifier, size_t death_time );
  void delete_node( unsigned long long int node_identifier );
  void clean_cell_map( void );
  void prune();
  void shorten();
  
  void write_tree( std::string filename );
  void write_newick_tree( std::string filename );
  
  void write_lineage_statistics( std::string filename, unsigned long long int identifier );
  void write_phylogeny_statistics( std::string filename );
  void write_trophic_data( std::string filename );
  
  void compute_AI_score_on_SL( size_t backup_time );
  void compute_common_ancestor_SL_repartition( double& Sp_A, double& Sp_B );
  
  /*----------------------------
   * PUBLIC ATTRIBUTES
   *----------------------------*/
  
protected:
  
  /*----------------------------
   * PROTECTED METHODS
   *----------------------------*/
  void inOrderNewick( Node* node, size_t parent_time, std::stringstream& output );
  void tag_tree();
  void untag_tree();
  void tag_offspring( Node* node, std::vector<Node*>* tagged_nodes );
  
  /*----------------------------
   * PROTECTED ATTRIBUTES
   *----------------------------*/
  Parameters*                                                 _parameters; /*!< Simulation parameters */
  unsigned long long int                                      _current_id; /*!< Current node id       */
  std::unordered_map<unsigned long long int, Node*>           _node_map;   /*!< Tree nodes map        */
  std::unordered_map<unsigned long long int, Node*>           _cell_map;   /*!< Cells map             */
  std::unordered_map<unsigned long long int, Node*>::iterator _iterator;   /*!< Tree map iterator     */
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

