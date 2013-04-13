/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class that helps storing the input configuration.
 * \author Julien Jorge
 */
#ifndef __TUNNEL_CONTROLLER_CONFIG_HPP__
#define __TUNNEL_CONTROLLER_CONFIG_HPP__

#include "tunnel/controller_layout.hpp"

#include <string>

namespace tunnel
{
  /**
   * \brief The class that helps storing the input configuration.
   * \author Julien Jorge
   */
  class controller_config
  {
  public:
    controller_config();

    void load();
    void save() const;

    void save_controller_layout( unsigned int i ) const;
    void load_controller_layout( unsigned int i );

    void set_layout( unsigned int i, const controller_layout& lay );
    controller_layout& get_layout( unsigned int i );
    const controller_layout& get_layout( unsigned int i ) const;

  private:
    void default_controls_for_player_1();

  private:
    /** \brief The base name of the controller files. */
    const std::string m_base_layout_file_name;

    /** \brief The controller layout for the players. */
    static controller_layout s_controller_layout[1];

  }; // class controller_config
} // namespace tunnel

#endif // __TUNNEL_CONTROLLER_CONFIG_HPP__
