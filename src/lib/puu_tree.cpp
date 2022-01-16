
/**
 * \file      puu_tree.cpp
 * \authors   Charles Rocabert
 * \date      16-01-2022
 * \copyright Copyright © 2022 Charles Rocabert. All rights reserved
 * \license   puutools is released under the GNU General Public License
 * \brief     puu_tree class definition
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

#include "../include/puu_tree.h"


/*----------------------------
 * CONSTRUCTORS
 *----------------------------*/

/**
 * \brief    Default onstructor
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
  /* 2) Create the node              */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  _current_id++;
  puu_node<selection_unit>* node = new puu_node<selection_unit>(_current_id, unit);
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 3) Connect nodes                */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  node->as_root();
  node->set_parent(master_root);
  master_root->add_child(node);
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 4) Add the node to the node map */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  assert(_node_map.find(node->get_id()) == _node_map.end());
  _node_map[node->get_id()] = node;
  
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 5) Add the node to the unit map */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  assert(_unit_map.find(unit) == _unit_map.end());
  _unit_map[unit] = node;
}

/**
 * \brief    Add a division to the tree
 * \details  --
 * \param    selection_unit* parent
 * \param    selection_unit* child
 * \return   \e void
 */
template <typename selection_unit>
void puu_tree<selection_unit>::add_reproduction_event( selection_unit* parent, selection_unit* child )
{
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 1) Get parental node              */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  assert(_unit_map.find(parent) != _unit_map.end());
  puu_node<selection_unit>* parent_node = _unit_map[parent];
  parent_node->set_dead();

  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  /* 2) Create child node              */
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  _current_id++;
  puu_node<selection_unit>* child_node = new puu_node<selection_unit>(_current_id, child);

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
  /*--------------------------------------*/
  /* 1) If node is a leaf                 */
  /*--------------------------------------*/
  if (node->is_active() || node->get_number_of_children() < 2)
  {
    output << node->get_id() << ":" << node->get_insertion_time()-parent_time;
  }
  
  /*--------------------------------------*/
  /* 2) Else if node has several children */
  /*--------------------------------------*/
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

