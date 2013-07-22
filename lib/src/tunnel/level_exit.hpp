/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief A level_exit.
 * \author Angibaud Sebastien
 */
#ifndef __TUNNEL_LEVEL_EXIT_HPP__
#define __TUNNEL_LEVEL_EXIT_HPP__

#include "tunnel/item_brick/transportable.hpp"
#include "engine/base_item.hpp"
#include "engine/item_brick/basic_renderable_item.hpp"
#include "engine/item_brick/item_with_decoration.hpp"
#include "engine/export.hpp"

namespace tunnel
{
  /**
   * \brief A level_exit.
   *
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class level_exit:
    public bear::engine::item_with_decoration
  < bear::engine::basic_renderable_item< bear::engine::base_item> >,
    public transportable
  {
    DECLARE_BASE_ITEM(level_exit);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::item_with_decoration
    < bear::engine::basic_renderable_item< bear::engine::base_item> > super;

  public:
    level_exit();
    
    bool is_valid() const;
    bool set_string_field( const std::string& name, const std::string& value );
    
    void progress( bear::universe::time_type elapsed_time );
    void collision
    ( bear::engine::base_item& that, bear::universe::collision_info& info );

  private:
    /* \brief Indicates if the level_exit has been opened. */
    bool m_opened;

    /* \brief The filename of the next level. */
    std::string m_level_filename;
  }; // class level_exit
} // namespace tunnel

#endif // __TUNNEL_LEVEL_EXIT_HPP__
