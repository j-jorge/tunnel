/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief The class that helps accessing to the game variables.
 * \author Julien Jorge
 */
#ifndef __TUNNEL_GAME_VARIABLES_HPP__
#define __TUNNEL_GAME_VARIABLES_HPP__

#include <string>

namespace tunnel
{
  /**
   * \brief The class that helps accessing to the game variables.
   * \author Julien Jorge
   */
  class game_variables
  {
  public:
    static unsigned int get_port();
    static void set_port(unsigned int port);
    
    static std::string get_ip(unsigned int p);
    static void set_ip(unsigned int p, const std::string& ip);

    static bool is_local_player(unsigned int p);
    static void set_local_player(unsigned int p, bool value);

    static bool is_editor_running();
    static void set_editor_running(bool value);

    static bool is_level_finished();
    static void set_level_is_finished(bool value);

    static std::string get_next_level_name();
    static void set_next_level_name( const std::string& n );

    static std::string get_level_name( const std::string& filename);
    static void set_level_name
    ( const std::string& filename, const std::string& name );

    static void set_level_precedence
    ( const std::string& prec, const std::string& next );
    static void set_finished_level( const std::string& lvl, bool b);
    static bool level_is_finished(const std::string& lvl);

    static std::string get_main_level_name();
    static void set_main_level_name( const std::string& n );

    static std::string get_lives_count_variable_name();
    static unsigned int get_lives_count();
    static void set_lives_count(unsigned int c );
    static unsigned int get_persistent_lives_count();
    static void set_persistent_lives_count( unsigned int c );

    static std::string get_energy_variable_name();
    static unsigned int get_energy();
    static void set_energy( unsigned int e );

    static std::string get_crystal_count_variable_name();
    static unsigned int get_crystal_count();
    static void set_crystal_count( unsigned int nb );

    static std::string get_founded_crystal_count_variable_name();
    static unsigned int get_founded_crystal_count();
    static void set_founded_crystal_count( unsigned int nb );

    static std::string get_score_variable_name();
    static unsigned int get_score();
    static unsigned int get_persistent_score();
    static void set_score( unsigned int c );
    static void set_persistent_score( unsigned int c );
    static void add_score( unsigned int c );
    static void sub_score( unsigned int c );

    static std::string get_string_default( const std::string& n );

    static std::string
    make_player_specific_variable_name( unsigned int p, const std::string& n );

    static std::string make_persistent_variable_name( const std::string& n );
    static std::string make_persistent_level_variable_name
    ( const std::string& n );

    static void load_player_variables();
    static void load_player_variables(unsigned int p);
    static void save_player_variables();
    static void save_player_variables(unsigned int p);
  }; // class game_variables
} // namespace tunnel

#endif // __TUNNEL_GAME_VARIABLES_HPP__
