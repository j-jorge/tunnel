/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief A door switch.
 * \author Angibaud Sebastien
 */
#ifndef __TUNNEL_SWITCH_HPP__
#define __TUNNEL_SWITCH_HPP__

#include "tunnel/item_brick/transportable.hpp"

#include "engine/base_item.hpp"
#include "engine/model.hpp"
#include "engine/export.hpp"

namespace tunnel
{
  /**
   * \brief A door switch.
   *
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class door_switch:
    public bear::engine::model< bear::engine::base_item>,
    public transportable
  {
    DECLARE_BASE_ITEM(door_switch);

  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::model< bear::engine::base_item > super;

  public:
    door_switch();

    void pre_cache();
    void on_enters_layer();
    bool is_valid() const;

    bool set_string_field( const std::string& name, const std::string& value );

  private:
    /* \brief The tag of the switch. */
    std::string m_tag;
  }; // class door_switch
} // namespace tunnel

#endif // __TUNNEL_SWITCH_HPP__
