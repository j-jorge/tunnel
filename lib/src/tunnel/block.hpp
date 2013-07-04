/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief A block.
 * \author Angibaud Sebastien
 */
#ifndef __TUNNEL_BLOCK_HPP__
#define __TUNNEL_BLOCK_HPP__

#include "tunnel/item_brick/transportable.hpp"
#include "generic_items/block.hpp"
#include "engine/export.hpp"

namespace tunnel
{
  /**
   * \brief A block.
   *
   *  - any field supported by the parent classes.
   *
   * \author Sebastien Angibaud
   */
  class block:
    public bear::block,
    public transportable
  {
    DECLARE_BASE_ITEM(block);

  public:
    /** \brief The type of the parent class. */
    typedef bear::block super;
  }; // class block
} // namespace tunnel

#endif // __TUNNEL_BLOCK_HPP__
