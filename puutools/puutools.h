
/**
 * \file      puutools.h
 * \authors   Charles Rocabert
 * \date      17-01-2022
 * \copyright Copyright © 2022-2023 Charles Rocabert. All rights reserved
 * \license   puutools is released under the GNU General Public License
 * \brief     puutools declarations and definitions
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

#ifndef __puutools__
#define __puutools__

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Node class enumeration                                                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* puu_node class declarations and definitions                                */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/**
 * \brief   puu_node class declaration
 * \details The puu_node class manages a lineage or coalescence node
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
  puu_node( const puu_node& node ) = delete;

  /*----------------------------
   * DESTRUCTORS
   *----------------------------*/
  ~puu_node( void );

  /*----------------------------
   * GETTERS
   *----------------------------*/
  inline unsigned long long int get_identifier( void ) const;
  inline double                 get_insertion_time( void ) const;
  inline selection_unit*        get_selection_unit( void );
  inline puu_node*              get_previous( void );
  inline puu_node*              get_parent( void );
  inline puu_node*              get_child( size_t pos );
  inline size_t                 get_number_of_children( void ) const;
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
  unsigned long long int _identifier;     /*!< Node identifier                                 */
  double                 _insertion_time; /*!< Node's insertion time                           */
  selection_unit*        _selection_unit; /*!< Attached selection unit                         */
  puu_node*              _parent;         /*!< Parental node                                   */
  std::vector<puu_node*> _children;       /*!< Node's children                                 */
  puu_node_class         _node_class;     /*!< Node class (master root, root or normal)        */
  bool                   _active;         /*!< Indicates if the node is active                 */
  bool                   _tagged;         /*!< Indicates if the node is tagged                 */
  bool                   _copy;           /*!< Indicates if the selection unit has been copied */
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
inline unsigned long long int puu_node<selection_unit>::get_identifier( void ) const
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
 * \brief    Get the previous node
 * \details  --
 * \param    void
 * \return   \e puu_node*
 */
template <typename selection_unit>
inline puu_node<selection_unit>* puu_node<selection_unit>::get_previous( void )
{
  return _parent;
}

/**
 * \brief    Get the parental node
 * \details  Returns also NULL if the parent is the master root
 * \param    void
 * \return   \e puu_node*
 */
template <typename selection_unit>
inline puu_node<selection_unit>* puu_node<selection_unit>::get_parent( void )
{
  if (_parent != NULL && _parent->is_master_root())
  {
    return NULL;
  }
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
inline size_t puu_node<selection_unit>::get_number_of_children( void ) const
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
  puu_node* node = get_previous();
  while (node != NULL)
  {
    if (node->get_id() == ancestor_id)
    {
      return true;
    }
    node = node->get_previous();
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
  _copy   = copy;
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

/*----------------------------
 * CONSTRUCTORS
 *----------------------------*/

/**
 * \brief    Constructor
 * \details  Creates a MASTER_ROOT node
 * \param    unsigned long long int identifier
 * \return   \e void
 */
template <typename selection_unit>
puu_node<selection_unit>::puu_node( unsigned long long int identifier )
{
  _identifier     = identifier;
  _insertion_time = 0.0;
  _selection_unit = NULL;
  _parent         = NULL;
  _node_class     = MASTER_ROOT;
  _active         = false;
  _tagged         = false;
  _copy           = false;
  _children.clear();
}

/**
 * \brief    Active node constructor
 * \details  Creates a new active node with its attached selection unit.
 * \param    unsigned long long int identifier
 * \param    double time
 * \param    selection_unit* unit
 * \return   \e void
 */
template <typename selection_unit>
puu_node<selection_unit>::puu_node( unsigned long long int identifier, double time, selection_unit* unit )
{
  assert(time >= 0.0);
  assert(unit != NULL);
  _identifier     = identifier;
  _insertion_time = time;
  _selection_unit = unit;
  _parent         = NULL;
  _node_class     = NORMAL;
  _active         = true;
  _tagged         = false;
  _copy           = false;
  _children.clear();
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
template <typename selection_unit>
puu_node<selection_unit>::~puu_node( void )
{
  if (_copy)
  {
    delete _selection_unit;
  }
  _selection_unit = NULL;
  _children.clear();
}

/*----------------------------
 * PUBLIC METHODS
 *----------------------------*/

/**
 * \brief    Adds a child
 * \details  --
 * \param    puu_node* node
 * \return   \e void
 */
template <typename selection_unit>
void puu_node<selection_unit>::add_child( puu_node* node )
{
  for (size_t i = 0; i < _children.size(); i++)
  {
    assert(node->get_identifier() != _children[i]->get_identifier());
  }
  _children.push_back(node);
}

/**
 * \brief    Removes a child
 * \details  --
 * \param    puu_node* node
 * \return   \e void
 */
template <typename selection_unit>
void puu_node<selection_unit>::remove_child( puu_node* node )
{
  int pos = -1;
  for (size_t i = 0; i < _children.size(); i++)
  {
    if (node->get_identifier() == _children[i]->get_identifier() && pos == -1)
    {
      pos = (int)i;
    }
    else if (node->get_identifier() == _children[i]->get_identifier() && pos >= 0)
    {
      printf("Error in Node::remove_child(): multiple occurences of a node in the list of children. Exit.\n");
      exit(EXIT_FAILURE);
    }
  }
  if (pos == -1)
  {
    printf("Error in Node::remove_child(): the node to remove does not exist. Exit.\n");
    exit(EXIT_FAILURE);
  }
  else
  {
    _children.erase(_children.begin()+pos);
  }
}

/**
 * \brief    Replaces the given child by its own children
 * \details  --
 * \param    puu_node* child_to_remove
 * \return   \e void
 */
template <typename selection_unit>
void puu_node<selection_unit>::replace_by_grandchildren( puu_node* child_to_remove )
{
  remove_child(child_to_remove);
  for (size_t i = 0; i < child_to_remove->get_number_of_children(); i++)
  {
    add_child(child_to_remove->get_child(i));
  }
}

/**
 * \brief    Tags the lineage of the node
 * \details  --
 * \param    void
 * \return   \e void
 */
template <typename selection_unit>
void puu_node<selection_unit>::tag_lineage( void )
{
  _tagged        = true;
  puu_node* node = _parent;
  while (node != NULL)
  {
    node->tag();
    node = node->get_previous();
    if (node != NULL)
    {
      if (node->is_tagged())
      {
        node = NULL;
      }
    }
  }
}

/**
 * \brief    Untags the lineage of the node
 * \details  --
 * \param    void
 * \return   \e void
 */
template <typename selection_unit>
void puu_node<selection_unit>::untag_lineage( void )
{
  _tagged        = false;
  puu_node* node = _parent;
  while (node != NULL)
  {
    node->untag();
    node = node->get_previous();
    if (node != NULL)
    {
      if (!node->is_tagged())
      {
        node = NULL;
      }
    }
  }
}

/*----------------------------
 * PROTECTED METHODS
 *----------------------------*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* puu_tree class declarations and definitions                                */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/**
 * \brief   puu_tree class declaration
 * \details The puu_tree class manages a lineage or coalescence tree
 */
template <typename selection_unit>
class puu_tree
{

public:

  /*----------------------------
   * CONSTRUCTORS
   *----------------------------*/
  puu_tree( void );
  puu_tree( const puu_tree& tree ) = delete;

  /*----------------------------
   * DESTRUCTORS
   *----------------------------*/
  ~puu_tree( void );

  /*----------------------------
   * GETTERS
   *----------------------------*/
  inline size_t                    get_number_of_nodes( void ) const;
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
  void add_root( selection_unit* unit );
  void add_reproduction_event( selection_unit* parent, selection_unit* child, double time );
  void inactivate( selection_unit* unit, bool copy_unit );
  void update_as_lineage_tree( void );
  void update_as_coalescence_tree( void );
  void write_tree( std::string filename );
  void write_newick_tree( std::string filename );

  /*----------------------------
   * PUBLIC ATTRIBUTES
   *----------------------------*/

protected:

  /*----------------------------
   * PROTECTED METHODS
   *----------------------------*/
  void prune( void );
  void shorten( void );
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
inline size_t puu_tree<selection_unit>::get_number_of_nodes( void ) const
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
  if (_iterator == _node_map.end())
  {
    return NULL;
  }
  if (_iterator->second->is_master_root())
  {
    _iterator++;
  }
  if (_iterator == _node_map.end())
  {
    return NULL;;
  }
  return _iterator->second;
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
  if (_iterator == _node_map.end())
  {
    return NULL;
  }
  if (_iterator->second->is_master_root())
  {
    _iterator++;
  }
  if (_iterator == _node_map.end())
  {
    return NULL;
  }
  return _iterator->second;
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
      active_node_identifiers->push_back(_iterator->second->get_identifier());
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
  if(master_root->get_number_of_children() == 0)
  {
    return 0.0;
  }

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 2) If there is a unique common ancestor   */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  else if (master_root->get_number_of_children() == 1)
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
    for (size_t i = 0; i < master_root->get_number_of_children(); i++)
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
    return mean/master_root->get_number_of_children();
  }
}

/*----------------------------
 * SETTERS
 *----------------------------*/

/*----------------------------
 * CONSTRUCTORS
 *----------------------------*/

/**
 * \brief    Default constructor
 * \details  The tree is initialized with one node called the master root
 * \param    void
 * \return   \e void
 */
template <typename selection_unit>
puu_tree<selection_unit>::puu_tree( void )
{
  _current_id = 0;
  _node_map.clear();
  _iterator = _node_map.begin();
  puu_node<selection_unit>* master_root = new puu_node<selection_unit>(_current_id);
  _node_map[_current_id] = master_root;
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
template <typename selection_unit>
puu_tree<selection_unit>::~puu_tree( void )
{
  _iterator = _node_map.begin();
  for (_iterator = _node_map.begin(); _iterator != _node_map.end(); ++_iterator)
  {
    delete _iterator->second;
    _iterator->second = NULL;
  }
  _node_map.clear();
  _unit_map.clear();
}

/*----------------------------
 * PUBLIC METHODS
 *----------------------------*/

/**
 * \brief    Adds a root to the tree
 * \details  --
 * \param    selection_unit* unit
 * \return   \e void
 */
template <typename selection_unit>
void puu_tree<selection_unit>::add_root( selection_unit* unit )
{
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 1) Get the master root          */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  puu_node<selection_unit>* master_root = _node_map[0];

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 2) Create the root              */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  _current_id++;
  puu_node<selection_unit>* root = new puu_node<selection_unit>(_current_id, 0.0, unit);

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 3) Connect nodes                */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  root->as_root();
  root->set_parent(master_root);
  master_root->add_child(root);

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 4) Add the root to the node map */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  assert(_node_map.find(root->get_identifier()) == _node_map.end());
  _node_map[root->get_identifier()] = root;

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 5) Add the root to the unit map */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  assert(_unit_map.find(unit) == _unit_map.end());
  _unit_map[unit] = root;
}

/**
 * \brief    Adds a reproduction event to the tree
 * \details  --
 * \param    selection_unit* parent
 * \param    selection_unit* child
 * \param    double time
 * \return   \e void
 */
template <typename selection_unit>
void puu_tree<selection_unit>::add_reproduction_event( selection_unit* parent, selection_unit* child, double time )
{
  assert(time >= 0.0);

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 1) Get parental node              */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  assert(_unit_map.find(parent) != _unit_map.end());
  puu_node<selection_unit>* parent_node = _unit_map[parent];

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 2) Create child node              */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  _current_id++;
  puu_node<selection_unit>* child_node = new puu_node<selection_unit>(_current_id, time, child);

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 3) Update child node attributes   */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  child_node->set_parent(parent_node);
  parent_node->add_child(child_node);

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 4) Add child node to the node map */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  assert(_node_map.find(_current_id) == _node_map.end());
  _node_map[child_node->get_identifier()] = child_node;

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 5) Add child node to the unit map */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  assert(_unit_map.find(child) == _unit_map.end());
  _unit_map[child] = child_node;
}

/**
 * \brief    Inactivates the node belonging to the provided selection unit
 * \details  If copy_unit is set to true, a local copy of the selection unit is made
 * \param    selection_unit* unit
 * \param    bool copy_unit
 * \return   \e void
 */
template <typename selection_unit>
void puu_tree<selection_unit>::inactivate( selection_unit* unit, bool copy_unit )
{
  assert(_unit_map.find(unit) != _unit_map.end());
  puu_node<selection_unit>* node = _unit_map[unit];
  _unit_map.erase(unit);
  node->inactivate(copy_unit);
}

/**
 * \brief    Update the tree as a lineage tree
 * \details  Prune dead branches.
 * \param    void
 * \return   \e void
 */
template <typename selection_unit>
void puu_tree<selection_unit>::update_as_lineage_tree( void )
{
  prune();
}

/**
 * \brief    Update the tree as a coalescence tree
 * \details  Prune dead branches and shorten the tree.
 * \param    void
 * \return   \e void
 */
template <typename selection_unit>
void puu_tree<selection_unit>::update_as_coalescence_tree( void )
{
  prune();
  shorten();
}

/**
 * \brief    Writes tree in a text file
 * \details  Writes adjacency list in a file (.txt).
 * \param    std::string filename
 * \return   \e void
 */
template <typename selection_unit>
void puu_tree<selection_unit>::write_tree( std::string filename )
{
  std::ofstream file(filename.c_str(), std::ios::out | std::ios::trunc);
  for (_iterator = _node_map.begin(); _iterator != _node_map.end(); ++_iterator)
  {
    for (size_t i = 0; i < _iterator->second->get_number_of_children(); i++)
    {
      file << _iterator->second->get_id() << " " << _iterator->second->get_child(i)->get_id() << "\n";
    }
  }
  file.close();
}

/**
 * \brief    Writes Newick tree
 * \details  Writes tree in Newick format in a file (.phb)
 * \param    std::string filename
 * \return   \e void
 */
template <typename selection_unit>
void puu_tree<selection_unit>::write_newick_tree( std::string filename )
{
  std::ofstream file(filename.c_str(), std::ios::out | std::ios::trunc);

  for (size_t i = 0; i < _node_map[0]->get_number_of_children(); i++)
  {
    std::stringstream newick_tree;
    inOrderNewick(_node_map[0]->get_child(i), 0, newick_tree);
    newick_tree << ";\n";
    file << newick_tree.str();
  }
  file.close();
}

/*----------------------------
 * PROTECTED METHODS
 *----------------------------*/

/**
 * \brief    Prunes the tree
 * \details  Removes all dead branches.
 * \param    void
 * \return   \e void
 */
template <typename selection_unit>
void puu_tree<selection_unit>::prune()
{
  untag_tree();

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 1) Tag alive cells lineage          */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  for (_iterator = _node_map.begin(); _iterator != _node_map.end(); ++_iterator)
  {
    assert(_iterator->first == _iterator->second->get_identifier());
    if (_iterator->second->is_active())
    {
      _iterator->second->tag_lineage();
    }
  }

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 2) Build the list of untagged nodes */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  std::vector<unsigned long long int> remove_list;
  for (_iterator = _node_map.begin(); _iterator != _node_map.end(); ++_iterator)
  {
    if (!_iterator->second->is_tagged() && !_iterator->second->is_master_root())
    {
      remove_list.push_back(_iterator->first);
    }
  }

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 3) Delete untagged nodes            */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  for (size_t i = 0; i < remove_list.size(); i++)
  {
    delete_node(remove_list[i]);
  }
  remove_list.clear();

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 4) Set master root children as root */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  puu_node<selection_unit>* master_root = _node_map[0];
  for (size_t i = 0; i < master_root->get_number_of_children(); i++)
  {
    master_root->get_child(i)->as_root();
  }
}

/**
 * \brief    Shortens the tree
 * \details  Removes all the dead nodes that are not common ancestors
 * \param    void
 * \return   \e void
 */
template <typename selection_unit>
void puu_tree<selection_unit>::shorten()
{
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 1) Select all intermediate nodes:   */
  /*    - not master root                */
  /*    - not alive                      */
  /*    - possessing exactly one child   */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  std::vector<unsigned long long int> remove_list;
  remove_list.clear();
  for (_iterator = _node_map.begin(); _iterator != _node_map.end(); ++_iterator)
  {
    assert(_iterator->first == _iterator->second->get_identifier());
    if (!_iterator->second->is_master_root() && !_iterator->second->is_active() && _iterator->second->get_number_of_children() == 1)
    {
      remove_list.push_back(_iterator->first);
    }
  }

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 2) Delete nodes                     */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  for (size_t i = 0; i < remove_list.size(); i++)
  {
    delete_node(remove_list[i]);
  }
  remove_list.clear();

#if DEBUG
  for (_iterator = _node_map.begin(); _iterator != _node_map.end(); ++_iterator)
  {
    if (!_iterator->second->is_master_root() && !_iterator->second->is_active())
    {
      assert(_iterator->second->get_number_of_children() >= 2);
    }
  }
#endif

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 3) Set master root children as root */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  puu_node<selection_unit>* master_root = _node_map[0];
  for (size_t i = 0; i < master_root->get_number_of_children(); i++)
  {
    master_root->get_child(i)->as_root();
  }
}

/**
 * \brief    Deletes a node and removes all node's relationships
 * \details  --
 * \param    unsigned long long int node_identifier
 * \return   \e void
 */
template <typename selection_unit>
void puu_tree<selection_unit>::delete_node( unsigned long long int node_identifier )
{
  assert(_node_map.find(node_identifier) != _node_map.end());
  puu_node<selection_unit>* node = _node_map[node_identifier];
  assert(node->get_identifier() == node_identifier);
  assert(!node->is_active());

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 1) Update parental children list  */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  node->get_previous()->replace_by_grandchildren(node);

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 2) Set the new parent of children */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  for (size_t i = 0; i < node->get_previous()->get_number_of_children(); i++)
  {
    node->get_previous()->get_child(i)->set_parent(node->get_previous());
  }

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 3) Delete node in the node map    */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  delete _node_map[node_identifier];
  _node_map[node_identifier] = NULL;
  _node_map.erase(node_identifier);
}

/**
 * \brief    Recursive method used to build the Newick format file
 * \details  --
 * \param    puu_node* node
 * \param    double parent_time
 * \param    std::stringstream& output
 * \return   \e void
 */
template <typename selection_unit>
void puu_tree<selection_unit>::inOrderNewick( puu_node<selection_unit>* node, double parent_time, std::stringstream& output )
{
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 1) If node is a leaf                 */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  if (node->is_active() || node->get_number_of_children() < 2)
  {
    output << node->get_identifier() << ":" << node->get_insertion_time()-parent_time;
  }

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 2) Else if node has several children */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  else
  {
    output << "(";
    for (size_t i = 0; i < node->get_number_of_children(); i++)
    {
      inOrderNewick(node->get_child(i), node->get_insertion_time(), output);
      if (i < node->get_number_of_children()-1)
      {
        output << ", ";
      }
    }
    output << ")";
    output << node->get_identifier() << ":" << node->get_insertion_time()-parent_time;
  }
}

/**
 * \brief    Tags all the nodes
 * \details  --
 * \param    void
 * \return   \e void
 */
template <typename selection_unit>
void puu_tree<selection_unit>::tag_tree()
{
  for (_iterator = _node_map.begin(); _iterator != _node_map.end(); ++_iterator)
  {
    _iterator->second->tag();
  }
}

/**
 * \brief    Untags all the nodes
 * \details  --
 * \param    void
 * \return   \e void
 */
template <typename selection_unit>
void puu_tree<selection_unit>::untag_tree()
{
  for (_iterator = _node_map.begin(); _iterator != _node_map.end(); ++_iterator)
  {
    _iterator->second->untag();
  }
}

/**
 * \brief    Tags all the offspring of the given node
 * \details  --
 * \param    puu_node* node
 * \param    std::vector<puu_node*>* tagged_nodes
 * \return   \e void
 */
template <typename selection_unit>
void puu_tree<selection_unit>::tag_offspring( puu_node<selection_unit>* node, std::vector<puu_node<selection_unit>*>* tagged_nodes )
{
  untag_tree();
  tagged_nodes->clear();
  tagged_nodes->push_back(node);
  bool end = false;
  while (!end)
  {
    end = true;
    for (size_t i = 0; i < tagged_nodes->size(); i++)
    {
      for (size_t j = 0; j < tagged_nodes->at(i)->get_number_of_children(); j++)
      {
        if (!tagged_nodes->at(i)->get_child(j)->is_tagged())
        {
          end = false;
          tagged_nodes->at(i)->get_child(j)->tag();
          tagged_nodes->push_back(tagged_nodes->at(i)->get_child(j));
        }
      }
    }
  }
}


#endif /* defined(__puutools__) */

