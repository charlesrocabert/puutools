
/**
 * \file      puutools.cpp
 * \authors   Charles Rocabert
 * \date      17-01-2022
 * \copyright Copyright © 2022 Charles Rocabert. All rights reserved
 * \license   puutools is released under the GNU General Public License
 * \brief     puutools definitions
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

#include "../include/puutools.h"


/****************************************************************************/

/*----------------------------
 * CONSTRUCTORS
 *----------------------------*/

/**
 * \brief    Constructor
 * \details  Create a MASTER_ROOT node
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
  _children.clear();
}

/**
 * \brief    Active node constructor
 * \details  Create a new active node with its attached selection unit.
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
  _children.clear();
}

/**
 * \brief    Constructor from backup file
 * \details  Load Node class from backup file. Relationships are not loaded, but are managed in Tree class
 * \param    gzFile backup_file
 * \return   \e void
 */
/*
template <typename selection_unit>
puu_node<selection_unit>::puu_node( gzFile backup_file )
{
 TODO
}
*/

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
  if (!_active && _selection_unit != NULL)
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
 * \brief    Save in backup file
 * \details  Relationships are not saved, but are managed in Tree class
 * \param    gzFile backup_file
 * \return   \e void
 */
/*
template <typename selection_unit>
void puu_node<selection_unit>::save( gzFile backup_file )
{
  TODO
}
*/

/**
 * \brief    Add a child
 * \details  --
 * \param    puu_node* node
 * \return   \e void
 */
template <typename selection_unit>
void puu_node<selection_unit>::add_child( puu_node* node )
{
  for (size_t i = 0; i < _children.size(); i++)
  {
    assert(node->get_id() != _children[i]->get_id());
  }
  _children.push_back(node);
}

/**
 * \brief    Remove a child
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
    if (node->get_id() == _children[i]->get_id() && pos == -1)
    {
      pos = (int)i;
    }
    else if (node->get_id() == _children[i]->get_id() && pos >= 0)
    {
      printf("Error in Node::remove_child(): multiple occurences of a node in the children list. Exit.\n");
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
 * \brief    Replace this child by its own children
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
 * \brief    Tag the lineage of this node
 * \details  --
 * \param    void
 * \return   \e void
 */
template <typename selection_unit>
void puu_node<selection_unit>::tag_lineage( void )
{
  _tagged = true;
  puu_node* node = _parent;
  while (node != NULL)
  {
    node->tag();
    node = node->get_parent();
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
 * \brief    Untag the lineage of this node
 * \details  --
 * \param    void
 * \return   \e void
 */
template <typename selection_unit>
void puu_node<selection_unit>::untag_lineage( void )
{
  _tagged = false;
  puu_node* node = _parent;
  while (node != NULL)
  {
    node->untag();
    node = node->get_parent();
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

/****************************************************************************/

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

/**
 * \brief    Constructor from backup file
 * \details  Load Tree class from backup file. First, load nodes. Then, load tree relationships (parent and children information), and load selection units.
 * \param    gzFile backup_file
 * \return   \e void
 */
/*
template <typename selection_unit>
puu_tree<selection_unit>::puu_tree( gzFile backup_file )
{
  TODO
}
*/

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
 * \brief    Save in backup file
 * \details  --
 * \param    gzFile backup_file
 * \return   \e void
 */
/*
template <typename selection_unit>
void puu_tree<selection_unit>::save( gzFile backup_file )
{
  TODO
}
*/

/**
 * \brief    Add a root to the tree
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
  assert(_node_map.find(root->get_id()) == _node_map.end());
  _node_map[root->get_id()] = root;
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 5) Add the root to the unit map */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  assert(_unit_map.find(unit) == _unit_map.end());
  _unit_map[unit] = root;
}

/**
 * \brief    Add a reproduction event to the tree
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
  //_unit_map.erase(parent);
  //parent_node->inactivate(copy_parent);

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
  assert(_node_map.find(_current_id) != _node_map.end());
  _node_map[child_node->get_identifier()] = child_node;
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 5) Add child node to the unit map */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  assert(_unit_map.find(child) != _unit_map.end());
  _unit_map[child] = child_node;
}

/**
 * \brief    Inactivate the node related to this selection unit
 * \details  If copy_unit is true, a local copy of the selection unit is made
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
 * \brief    Delete a node and remove all links
 * \details  --
 * \param    unsigned long long int node_identifier
 * \return   \e void
 */
template <typename selection_unit>
void puu_tree<selection_unit>::delete_node( unsigned long long int node_identifier )
{
  assert(_node_map.find(node_identifier) != _node_map.end());
  puu_node<selection_unit>* node = _node_map[node_identifier];
  assert(node->get_id() == node_identifier);
  assert(!node->is_active());
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 1) Update parental children list  */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  node->get_parent()->replace_children(node);
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 2) Set the new parent of children */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  for (size_t i = 0; i < node->get_parent()->get_number_of_children(); i++)
  {
    node->get_parent()->get_child(i)->set_parent(node->get_parent());
  }
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 3) Delete node in the node map    */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  delete _node_map[node_identifier];
  _node_map[node_identifier] = NULL;
  _node_map.erase(node_identifier);
}

/**
 * \brief    Prune the tree
 * \details  Remove all dead branches
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
    assert(_iterator->first == _iterator->second->get_id());
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
 * \brief    Shorten the tree
 * \details  Remove all the dead nodes that are not common ancestors
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
    assert(_iterator->first == _iterator->second->get_id());
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
    if (!_iterator->second->isMasterRoot() && !_iterator->second->isAlive())
    {
      assert(_iterator->second->get_number_of_children() == 2);
    }
  }
#endif
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 3) Set master root children as root */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  puu_node<selection_unit>* master_root = _node_map[0];
  for (size_t i = 0; i < master_root->get_number_of_children(); i++)
  {
    master_root->get_child(i)->set_root();
  }
}

/**
 * \brief    Write tree
 * \details  Write adjacency list in a file (.txt)
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
 * \brief    Write Newick tree
 * \details  Write tree in Newick format in a file (.phb)
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
 * \brief    Recursive method used to build Newick format file
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
    output << node->get_id() << ":" << node->get_insertion_time()-parent_time;
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
    output << node->get_id() << ":" << node->get_insertion_time()-parent_time;
  }
}

/**
 * \brief    Tag all the nodes
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
 * \brief    Untag all the nodes
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
 * \brief    Tag all the offspring of this node
 * \details  --
 * \param    puu_node* node
 * \param    std::vector<Node*>* tagged_nodes
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

