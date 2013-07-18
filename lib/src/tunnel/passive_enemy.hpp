/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing a passive enemy.
 * \author Sébastien Angibaud
 */
#ifndef __TUNNEL_PASSIVE_ENEMY_HPP__
#define __TUNNEL_PASSIVE_ENEMY_HPP__

#include "generic_items/block.hpp"
#include "engine/export.hpp"

namespace tunnel
{
  /**
   * \brief The class describing a passive enemy.
   *
   * The valid fields for this item are
   *  - \a type_right_side: \c (string) The type of right side
   * possible values: inactive, solid, attack.
   *  - \a type_left_side: \c (string) The type of left side
   * possible values: inactive, solid, attack.
   *  - \a type_bottom_side: \c (string) The type of bottom side
   * possible values: inactive, solid, attack.
   *  - \a type_top_side: \c (string) The type of top side
   * possible values: inactive, solid, attack.
   *
   * \author Sébastien Angibaud
   */
  class passive_enemy:
    public bear::block
  {
    DECLARE_BASE_ITEM(passive_enemy);

  public:
    typedef bear::block super;

  public:
     enum side_type
      {
        inactive_type = 0,
        attack_type
      }; // enum side_type

  public:
    passive_enemy();

    void collision( bear::engine::base_item& that,
        bear::universe::collision_info& info );

    bool set_string_field( const std::string& name, const std::string& value );

  private:
    bool set_side_type(side_type& side, const std::string& value);
    bool collision_and_attack
    ( bear::engine::base_item& that, bear::universe::collision_info& info );
    bool attack( bear::engine::base_item& that );
    bool attack
    ( bear::engine::base_item& that, bear::universe::zone::position side );
    
  private:
    /* \brief The type of the right side. */
    side_type m_right_side_type;

    /* \brief The type of the left side. */
    side_type m_left_side_type;

    /* \brief The type of the top side. */
    side_type m_top_side_type;

    /* \brief The type of the bottom side. */
    side_type m_bottom_side_type;
  }; // class passive_enemy
} // namespace tunnel

#endif // __TUNNEL_PASSIVE_ENEMY_HPP__
