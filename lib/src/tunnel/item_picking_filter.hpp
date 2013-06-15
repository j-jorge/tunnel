/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief A filter passed to bear::universe::world::pick_items to get only
 *        interesting items.
 * \author Sébastien Angibaud
 */
#ifndef __TUNNEL_ITEM_PICKING_FILTER_HPP__
#define __TUNNEL_ITEM_PICKING_FILTER_HPP__

#include "universe/item_picking_filter.hpp"
#include "universe/shape/shape.hpp"

namespace tunnel
{
  /**
   * \brief A filter passed to bear::universe::world::pick_items to get only
   *        interesting items.
   * \author Sébastien Angibaud
   */
  class item_picking_filter : public bear::universe::item_picking_filter
  {
  public:
    /** \brief The type of the parent class. */
    typedef item_picking_filter super;

  public:
    item_picking_filter(const bear::universe::shape_base * s);
    virtual ~item_picking_filter();
    
  protected:
    virtual bool do_satisfies_condition
    ( const bear::universe::physical_item& item ) const;

  private:
    /** \brief Tell if the "artificial" flag must be checked. */
    const bear::universe::shape_base* m_shape;
  }; // class item_picking_filter

} // namespace tunnel

#endif // __TUNNEL_ITEM_PICKING_FILTER_HPP__
