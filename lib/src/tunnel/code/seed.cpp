/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the tunnel::seed class.
 * \author Sebastien Angibaud
 */
#include "tunnel/seed.hpp"

BASE_ITEM_EXPORT( seed, tunnel )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
tunnel::seed::seed()
: m_tag(0)
{
} // seed::seed()

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
tunnel::seed::seed(unsigned int tag)
: m_tag(tag)
{
} // seed::seed()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void tunnel::seed::pre_cache()
{
  super::pre_cache();

  get_level_globals().load_model("model/seed.cm");
} // seed::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do post creation actions.
 */
void tunnel::seed::on_enters_layer()
{
  super::on_enters_layer();

  set_model_actor( get_level_globals().get_model("model/seed.cm") );
  start_model_action("idle");  
  set_can_move_items(false);
} // seed::on_enters_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Remove the seed.
 */
void tunnel::seed::remove()
{
  // action dead
  start_model_action("dead");
} // seed::remove()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the tag.
 */
unsigned tunnel::seed::get_tag() const
{
  return m_tag;
} // seed::get_tag()
