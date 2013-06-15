/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the bear::tunnel::item_picking_filter class.
 * \author Sebastien Angibaud
 */
#include "tunnel/item_picking_filter.hpp"
#include "universe/shape/curved_box.hpp"
#include "universe/physical_item.hpp"
#include "generic_items/slope.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param s The shape of the item.
 */
tunnel::item_picking_filter::item_picking_filter
(const bear::universe::shape_base * s)
  : m_shape(s)
{

} // item_picking_filter::item_picking_filter()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
tunnel::item_picking_filter::~item_picking_filter()
{

} // item_picking_filter::~item_picking_filter()

/*----------------------------------------------------------------------------*/
/**
 * \brief Overridden condition checking.
 * \param The item to check
 */
bool tunnel::item_picking_filter::do_satisfies_condition
( const bear::universe::physical_item& item ) const
{
  const bear::slope* const s( dynamic_cast<const bear::slope*>( &item ) );

  if ( s && m_shape )
    {
      const bear::universe::curved_box* const c( s->get_curved_box() );
      
      if ( c == NULL )
        return true;
      else
        c->intersects_strict(*m_shape);
    }
  else
    return true;
} // item_picking_filter::do_satisfies_condition()

