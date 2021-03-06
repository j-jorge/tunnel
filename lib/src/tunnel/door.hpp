/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief A door.
 * \author Angibaud Sebastien
 */
#ifndef __TUNNEL_DOOR_HPP__
#define __TUNNEL_DOOR_HPP__

#include "engine/base_item.hpp"
#include "engine/model.hpp"
#include "engine/export.hpp"

#include <set>

namespace tunnel
{
  /**
   * \brief A door.
   *
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class door:
    public bear::engine::model< bear::engine::base_item>
  {
    DECLARE_BASE_ITEM(door);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::model< bear::engine::base_item > super;

    TEXT_INTERFACE_DECLARE_METHOD_LIST(super, init_exported_methods);

  public:
    door();

    void pre_cache();
    void on_enters_layer();
    bool is_valid() const;

    bool set_bool_field( const std::string& name, bool value );
    bool set_string_list_field
    ( const std::string& name, const std::vector<std::string>& value );

    bool has_tag( const std::string& tag ) const;
    void switch_door();

  private:
    void on_door_collision
    ( bear::engine::base_item& mark, bear::engine::base_item& that,
      bear::universe::collision_info& info );
    
  private:
    static void init_exported_methods();
    
  private:
    /* \brief The tags of the door. */
    std::set< std::string > m_tags;

    /* \brief Indicates if the door is opened. */
    bool m_opened;
  }; // class door
} // namespace tunnel

#endif // __TUNNEL_DOOR_HPP__
