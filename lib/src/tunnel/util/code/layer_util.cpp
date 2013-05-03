/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the utility functions about the layers.
 * \author Julien Jorge
 */
#include "tunnel/util/layer_util.hpp"

/**
 * Moves all layers having a given tag such that they are processed before all
 * other tagged layers.
 * \param lvl The level from which we move the layers.
 * \param tag The tag of the layers to move.
 */
void tunnel::util::move_tag_after_all_tags
( bear::engine::level& lvl, std::string tag )
{
  bear::engine::level::const_layer_iterator last_not_tagged( lvl.layer_end() );
  bool stop(false);

  while ( !stop && (last_not_tagged != lvl.layer_begin()) )
    {
      bear::engine::level::const_layer_iterator candidate( last_not_tagged );
      --candidate;

      if ( !candidate.get_tag().empty() )
        stop = true;
      else
        last_not_tagged = candidate;
    }

  if ( !stop )
    return;

  bear::engine::level::const_layer_iterator it( last_not_tagged );
  --it;
  std::size_t move_count(0);

  while ( it != lvl.layer_begin() )
    {
      bear::engine::level::const_layer_iterator current( it );
      --it;

      if ( current->get_tag() == tag )
        {
          lvl.move_layer
            ( *current,
              std::distance( current, last_not_tagged ) - 1 - move_count );
          ++move_count;
        }
    }
} // move_tag_after_all_tags()
