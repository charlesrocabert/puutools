
/**
 * \file      puu_node.h
 * \authors   Charles Rocabert
 * \date      16-01-2022
 * \copyright Copyright © 2022 Charles Rocabert. All rights reserved
 * \license   puutools is released under the GNU General Public License
 * \brief     puu_node class declaration
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

#ifndef __puutools__puu_node__
#define __puutools__puu_node__

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cstring>
#include <cmath>
#include <zlib.h>

#include "puu_enums.h"


/**
 * \brief   Node class definition
 * \details TODO.
 */
template <typename individual>
class puu_node
{
  
public:
  
  /*----------------------------
   * CONSTRUCTORS
   *----------------------------*/
  puu_node( void ) = delete;
  puu_node( unsigned long long int identifier );
  puu_node( unsigned long long int identifier, double time, double score, individual* ind );
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
  inline double                 get_score( void ) const;
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
  
  /*----------------------------
   * SETTERS
   *----------------------------*/
  puu_node& operator=(const puu_node&) = delete;
  
  inline void set_score( double score );
  inline void set_parent( puu_node* node );
  inline void as_master_root( void );
  inline void as_root( void );
  inline void as_normal( void );
  inline void as_inactive( void );
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
  unsigned long long int _identifier;        /*!< Node identifier                          */
  double                 _activation_time;   /*!< Node's activation time                   */
  double                 _inactivation_time; /*!< Node's inactivation time                 */
  double                 _score;             /*!< Node's score                             */
  individual*            _individual;        /*!< Attached individual                      */
  puu_node*              _parent;            /*!< Parental node                            */
  std::vector<puu_node*> _children;          /*!< Node's children                          */
  puu_node_class         _node_class;        /*!< Node class (master root, root or normal) */
  bool                   _active;            /*!< Indicates if the node is active          */
  bool                   _tagged;            /*!< Indicates if the node is tagged          */
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
template <typename individual>
inline unsigned long long int puu_node<individual>::get_id( void ) const
{
  return _identifier;
}

/**
 * \brief    Get node score
 * \details  --
 * \param    void
 * \return   \e double
 */
template <typename individual>
inline double puu_node<individual>::get_score( void ) const
{
  return _score;
}

/**
 * \brief    Get the individual
 * \details  --
 * \param    void
 * \return   \e individual*
 */
template <typename individual>
inline individual* puu_node<individual>::get_individual( void )
{
  return _individual;
}

/**
 * \brief    Get the parental node
 * \details  --
 * \param    void
 * \return   \e puu_node*
 */
template <typename individual>
inline puu_node<individual>* puu_node<individual>::get_parent( void )
{
  return _parent;
}

/**
 * \brief    Get the child at position 'pos'
 * \details  --
 * \param    void
 * \return   \e puu_node*
 */
template <typename individual>
inline puu_node<individual>* puu_node<individual>::get_child( size_t pos )
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
template <typename individual>
inline size_t puu_node<individual>::get_nb_children( void ) const
{
  return _children.size();
}

/**
 * \brief    Get the node class
 * \details  --
 * \param    void
 * \return   \e puu_node_class
 */
template <typename individual>
inline puu_node_class puu_node<individual>::get_node_class( void ) const
{
  return _node_class;
}

/**
 * \brief    Check if the node is the master root
 * \details  --
 * \param    void
 * \return   \e bool
 */
template <typename individual>
inline bool puu_node<individual>::is_master_root( void ) const
{
  return (_node_class == MASTER_ROOT);
}

/**
 * \brief    Check if the node is a root
 * \details  --
 * \param    void
 * \return   \e bool
 */
template <typename individual>
inline bool puu_node<individual>::is_root( void ) const
{
  return (_node_class == ROOT);
}

/**
 * \brief    Check if the node is normal
 * \details  --
 * \param    void
 * \return   \e bool
 */
template <typename individual>
inline bool puu_node<individual>::is_normal( void ) const
{
  return (_node_class == NORMAL);
}

/**
 * \brief    Check if the given identifier is an ancestor
 * \details  --
 * \param    unsigned long long int ancestor_id
 * \return   \e bool
 */
template <typename individual>
inline bool puu_node<individual>::is_ancestor( unsigned long long int ancestor_id ) const
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
template <typename individual>
inline bool puu_node<individual>::is_active( void ) const
{
  return _active;
}

/**
 * \brief    Check if the node is tagged or not
 * \details  --
 * \param    void
 * \return   \e bool
 */
template <typename individual>
inline bool puu_node<individual>::is_tagged( void ) const
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
template <typename individual>
inline void puu_node<individual>::set_parent( puu_node* node )
{
  _parent = node;
}

/**
 * \brief    Set the node class as master root
 * \details  --
 * \param    void
 * \return   \e void
 */
template <typename individual>
inline void puu_node<individual>::as_master_root( void )
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
template <typename individual>
inline void puu_node<individual>::as_root( void )
{
  _node_class = ROOT;
}

/**
 * \brief    Set the node class as normal
 * \details  --
 * \param    void
 * \return   \e void
 */
template <typename individual>
inline void puu_node<individual>::as_normal( void )
{
  _node_class = NORMAL;
}

/**
 * \brief    Set the node state as inactive
 * \details  --
 * \param    void
 * \return   \e void
 */
template <typename individual>
inline void puu_node<individual>::as_inactive( void )
{
  _active = false;
}

/**
 * \brief    Tag the node
 * \details  --
 * \param    void
 * \return   \e void
 */
template <typename individual>
inline void puu_node<individual>::tag( void )
{
  _tagged = true;
}

/**
 * \brief    Untag the node
 * \details  --
 * \param    void
 * \return   \e void
 */
template <typename individual>
inline void puu_node<individual>::untag( void )
{
  _tagged = false;
}


#endif /* defined(__puutools__puu_node__) */

