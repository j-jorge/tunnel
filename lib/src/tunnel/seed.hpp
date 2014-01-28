/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class describing a seed.
 * \author Sebastien Angibaud
 */
#ifndef __TUNNEL_SEED_HPP__
#define __TUNNEL_SEED_HPP__

#include "engine/base_item.hpp"
#include "engine/model.hpp"
#include "engine/export.hpp"

namespace tunnel
{
  /**
   * \brief The class describing a seed for teleportation.
   * \author Sebastien Angibaud
   */
  class seed :
    public bear::engine::model< bear::engine::base_item>
  {
    DECLARE_BASE_ITEM(seed);
    
  public:
    /** \brief The type of the parent class. */
    typedef bear::engine::model< bear::engine::base_item > super;
  
  public:
    seed();
    seed(unsigned int tag);
    
    void pre_cache();
    void on_enters_layer();

    void remove();
    unsigned int get_tag() const;

  private:
    /* The tag of the layer. */
    unsigned int m_tag;
  }; // class seed
}

#endif // __TUNNEL_SEED_HPP__
