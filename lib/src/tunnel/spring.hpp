/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief A spring.
 * \author Angibaud Sebastien
 */
#ifndef __TUNNEL_SPRING_HPP__
#define __TUNNEL_SPRING_HPP__

#include "tunnel/item_brick/transportable.hpp"
#include "generic_items/spring.hpp"
#include "engine/export.hpp"

namespace tunnel
{
  /**
   * \brief A spring.
   *
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class spring:
    public bear::spring,
    public transportable
  {
    DECLARE_BASE_ITEM(spring);

  public:
    /** \brief The type of the parent class. */
    typedef bear::spring super;

  public:
    void pre_cache();

    void build();

  }; // class spring
} // namespace tunnel

#endif // __TUNNEL_SPRING_HPP__
