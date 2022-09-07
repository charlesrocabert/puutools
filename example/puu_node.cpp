
/**
 * \file      puutools.cpp
 * \authors   Charles Rocabert
 * \date      17-01-2022
 * \copyright Copyright © 2022 Charles Rocabert. All rights reserved
 * \license   puutools is released under the GNU General Public License
 * \brief     puu_node definitions
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

#include "puu_node.h"


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
  //_copy           = false;
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
  //_copy           = false;
  _children.clear();
}

/**
 * \brief    Constructor from backup file
 * \details  Loads a node from a backup file. Nodes' relationships are not loaded.
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
 * \brief    Saves the node in a backup file
 * \details  Nodes' relationships are not saved.
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
    assert(node->get_id() != _children[i]->get_id());
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
    if (node->get_id() == _children[i]->get_id() && pos == -1)
    {
      pos = (int)i;
    }
    else if (node->get_id() == _children[i]->get_id() && pos >= 0)
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
  for (size_t i = 0; i < child_to_remove->get_nb_children(); i++)
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
 * \brief    Untags the lineage of the node
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

