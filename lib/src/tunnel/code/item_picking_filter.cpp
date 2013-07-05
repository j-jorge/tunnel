/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the bear::tunnel::item_picking_filter class.
 * \author Sebastien Angibaud
 */
#include "tunnel/item_picking_filter.hpp"

#include "universe/shape/curved_box.hpp"
#include "universe/physical_item.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param s The shape of the item.
 */
tunnel::item_picking_filter::item_picking_filter
( const bear::universe::shape& s )
  : m_shape(s)
{

} // item_picking_filter::item_picking_filter()

/*----------------------------------------------------------------------------*/
/**
 * \brief Overridden condition checking.
 * \param The item to check
 */
bool tunnel::item_picking_filter::do_satisfies_condition
( const bear::universe::physical_item& item ) const
{
  bool result = false;

  if ( super::do_satisfies_condition( item ) && 
       item.get_height() != 0 && item.get_width() != 0 )
    {
      bear::universe::shape_base* const item_shape
        ( item.get_shape().clone_impl() );
      bear::universe::curved_box* const curve
        ( dynamic_cast<bear::universe::curved_box*>( item_shape ) );

      if ( curve == NULL )
        result = true;
      else
        {
          bear::universe::shape_base* const local_shape( m_shape.clone_impl() );
          result = curve->intersects_strict( *local_shape );
          delete local_shape;
        }

      delete item_shape;
    }

  return result;
} // item_picking_filter::do_satisfies_condition()

