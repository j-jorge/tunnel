/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief A crystal.
 * \author Angibaud Sebastien
 */
#ifndef __TUNNEL_CRYSTAL_HPP__
#define __TUNNEL_CRYSTAL_HPP__

#include "tunnel/item_brick/transportable.hpp"

#include "engine/base_item.hpp"
#include "engine/item_brick/basic_renderable_item.hpp"
#include "engine/item_brick/item_with_decoration.hpp"
#include "engine/export.hpp"

#include <boost/signals/connection.hpp>

namespace tunnel
{
  /**
   * \brief A crystal.
   *
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class crystal:
    public bear::engine::item_with_decoration
  < bear::engine::basic_renderable_item< bear::engine::base_item> >,
    public transportable
  {
    DECLARE_BASE_ITEM(crystal);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::item_with_decoration
    < bear::engine::basic_renderable_item< bear::engine::base_item> > super;

  public:
    crystal();
    
    void build();
    void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

  private:
    void on_level_started();

  private:
    /* \brief Indicates if the crystal has been given. */
    bool m_given;

    /** \brief The connection to the signal emitted when the level starts. */
    boost::signals::connection m_level_started;  
  }; // class crystal
} // namespace tunnel

#endif // __TUNNEL_CRYSTAL_HPP__
