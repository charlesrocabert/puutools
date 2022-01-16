
/**
 * \file      puu_node.cpp
 * \authors   Charles Rocabert
 * \date      16-01-2022
 * \copyright Copyright © 2022 Charles Rocabert. All rights reserved
 * \license   puutools is released under the GNU General Public License
 * \brief     puu_node class definition
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

#include "../include/puu_node.h"


/*----------------------------
 * CONSTRUCTORS
 *----------------------------*/

/**
 * \brief    Constructor
 * \details  Create a MASTER_ROOT node
 * \param    unsigned long long int identifier
 * \return   \e void
 */
template <typename individual>
puu_node<individual>::puu_node( unsigned long long int identifier )
{
  _identifier        = identifier;
  _activation_time   = 0.0;
  _inactivation_time = 0.0;
  _score             = 0.0;
  _individual        = NULL;
  _parent            = NULL;
  _node_class        = MASTER_ROOT;
  _active            = false;
  _tagged            = false;
  _children.clear();
}

/**
 * \brief    Active node constructor
 * \details  Create a new active node with its attached individual.
 * \param    unsigned long long int identifier
 * \param    double time
 * \param    double score
 * \param    individual* ind
 * \return   \e void
 */
template <typename individual>
puu_node<individual>::puu_node( unsigned long long int identifier, double time, double score, individual* ind )
{
  assert(time >= 0.0);
  assert(ind != NULL);
  _identifier         = identifier;
  _activation_time    = time;
  _inactivation_time  = 0.0;
  _score              = score;
  _individual         = ind;
  _parent             = NULL;
  _node_class         = NORMAL;
  _active             = true;
  _tagged             = false;
  _children.clear();
}

/**
 * \brief    Constructor from backup file
 * \details  Load Node class from backup file. Relationships are not loaded, but are managed in Tree class
 * \param    gzFile backup_file
 * \return   \e void
 */
/*
template <typename individual>
puu_node<individual>::puu_node( gzFile backup_file )
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
template <typename individual>
puu_node<individual>::~puu_node( void )
{
  _individual = NULL;
  if (!_active)
  {
    delete _individual;
  }
  _individual = NULL;
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
template <typename individual>
void puu_node<individual>::save( gzFile backup_file )
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
template <typename individual>
void puu_node<individual>::add_child( puu_node* node )
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
template <typename individual>
void puu_node<individual>::remove_child( puu_node* node )
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
template <typename individual>
void puu_node<individual>::replace_by_grandchildren( puu_node* child_to_remove )
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
template <typename individual>
void puu_node<individual>::tag_lineage( void )
{
  _tagged = true;
  puu_node* node = _parent;
  while (node != NULL)
  {
    node->tag();
    node = node->get_parent();
    if (node != NULL)
    {
      if (node->isTagged())
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
template <typename individual>
void puu_node<individual>::untag_lineage( void )
{
  _tagged = false;
  puu_node* node = _parent;
  while (node != NULL)
  {
    node->untag();
    node = node->get_parent();
    if (node != NULL)
    {
      if (!node->isTagged())
      {
        node = NULL;
      }
    }
  }
}

/*----------------------------
 * PROTECTED METHODS
 *----------------------------*/

