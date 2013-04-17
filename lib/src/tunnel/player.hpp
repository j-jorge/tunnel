/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief The class describing a player.
 * \author Sebastien Angibaud
 */
#ifndef __TUNNEL_PLAYER_HPP__
#define __TUNNEL_PLAYER_HPP__

#include "tunnel/item_brick/item_with_single_player_action_reader.hpp"

#include "engine/model.hpp"
#include "engine/messageable_item.hpp"

#include <set>
#include <list>

#include "engine/export.hpp"

namespace tunnel
{
  class state_player;

  /**
   * \brief The class describing a player.
   * \author Sebastien Angibaud
   */
  class player :
    public item_with_single_player_action_reader
  < bear::engine::model
    < bear::engine::messageable_item
      < bear::engine::base_item > > >
  {
    DECLARE_BASE_ITEM(player);

  public:
    /** \brief The type of the parent class. */
    typedef item_with_single_player_action_reader
    < bear::engine::model
      < bear::engine::messageable_item
        < bear::engine::base_item > > > super;

    TEXT_INTERFACE_DECLARE_METHOD_LIST(super, init_exported_methods)

  protected:
    enum player_state_name
      {
        walk_state = 0,
        idle_state,
        jump_state,
        fall_state,
        dead_state,
        game_over_state,
        roar_state,
        run_state,
        slap_state,
        teleport_state,
        start_jump_state,
        vertical_jump_state,
        look_upward_state,
        crouch_state,
        captive_state,
        wait_state,
        injured_state,
        start_cling_state,
        cling_state,
        clung_jump_state,
        start_hang_state,
        hang_state,
        swimming_state,
        sink_state,
        float_state,
        paralyze_state
      }; // enum player_state_name

  private:
    typedef void (player::*progress_function_type)(bear::universe::time_type);

  public:
    player();
    player(const player& p);
    void init();
    virtual ~player();

    void progress( bear::universe::time_type elapsed_time );
    void get_visual( std::list<bear::engine::scene_visual>& visuals ) const;
    void pre_cache();
    void on_enters_layer();

    bool set_string_list_field
    ( const std::string& name, const std::vector<std::string>& value );
    bool set_string_field( const std::string& name, const std::string& value );
    
    bool is_valid() const;

    void save_position( const bear::universe::position_type& p );
    void save_current_position();

    void start_action( player_action::value_type a );
    void do_action
    ( bear::universe::time_type elapsed_time, player_action::value_type a );
    void stop_action( player_action::value_type a );
    void start_action_model(const std::string& action);

    void set_offensive_phase( bool status );
    void set_authorized_action(player_action::value_type a, bool value);
    void authorize_action( const std::string& a );
    void authorize_all_actions();
    void disable_all_actions();

    double get_jump_time_ratio() const;
    void update_throw_time_ratio();
    void set_throw_down(bool value);
    void set_throw_up(bool value);

    bool is_a_marionette() const;
    void set_marionette( bool b);

    void set_status_look_upward(bool status);
    bool get_status_look_upward() const;
    void set_status_crouch(bool status);
    bool get_status_crouch() const;
    void do_start_look_upward();
    void do_start_crouch();
    void do_start_throw();
    void set_can_cling(bool status);
    bool is_clung() const;
    void set_want_clung_jump(bool status);
    bool want_clung_jump() const;

    bear::universe::position_type hot_spot() const;

    void set_spot_minimum
    ( bear::universe::coordinate_type x, bear::universe::coordinate_type y );
    void set_spot_maximum
    ( bear::universe::coordinate_type x, bear::universe::coordinate_type y );
    void set_spot_balance_move
    ( bear::universe::coordinate_type x, bear::universe::coordinate_type y );

    void add_spot_gap( const bear::universe::position_type& gap );
    void balance_spot( bool x, bool y );
    void stop();

  public:
    void apply_move_right();
    void apply_move_left();
    void apply_impulse_jump();
    void apply_jump();
    void apply_continue_jump();
    void apply_start_jump();
    void apply_vertical_jump();
    void apply_fall();
    void apply_idle();
    void apply_walk();
    void apply_run();
    void apply_slap();
    void apply_open_tunnel();
    void apply_abort_tunnel();
    void apply_teleport();
    void apply_attack();
    void apply_captive();
    void apply_release();
    void apply_injured();
    void apply_paralyze(bear::universe::time_type duration);
    void apply_wait();
    void apply_crouch();
    void apply_look_upward();
    void apply_die();
    void apply_roar();
    void apply_disappear();
    void apply_game_over();
    void apply_start_cling();
    void apply_cling();
    void apply_clung_jump();
    void apply_start_hang();
    void apply_hang();
    void apply_swimming();
    void apply_swim_in_float();
    void apply_swim_up_in_float();
    void apply_sink();
    void apply_swim_up();
    void apply_swim_down();
    void apply_float();
    void apply_swim_jump();
    void apply_dive();

    void choose_wait_state();
    void choose_idle_state();
    void choose_walk_state();
    bear::universe::coordinate_type get_vertical_jump_force() const;

  protected:
    void on_quit_owner();

  private:
    void progress_in_water(bear::universe::time_type elapsed_time);
    void to_string( std::string& str ) const;

    void progress_walk( bear::universe::time_type elapsed_time );
    void progress_idle( bear::universe::time_type elapsed_time );
    void progress_continue_idle( bear::universe::time_type elapsed_time );
    void progress_jump( bear::universe::time_type elapsed_time );
    void progress_fall( bear::universe::time_type elapsed_time );
    void progress_dead( bear::universe::time_type elapsed_time );
    void progress_game_over( bear::universe::time_type elapsed_time );
    void progress_roar( bear::universe::time_type elapsed_time );
    void progress_run( bear::universe::time_type elapsed_time );
    void progress_slap( bear::universe::time_type elapsed_time );
    void progress_teleport( bear::universe::time_type elapsed_time );
    void progress_start_jump( bear::universe::time_type elapsed_time );
    void progress_vertical_jump( bear::universe::time_type elapsed_time );
    void progress_crouch( bear::universe::time_type elapsed_time );
    void progress_look_upward( bear::universe::time_type elapsed_time );
    void progress_captive( bear::universe::time_type elapsed_time );
    void progress_throw( bear::universe::time_type elapsed_time );
    void progress_maintain( bear::universe::time_type elapsed_time );
    void progress_wait( bear::universe::time_type elapsed_time );
    void progress_start_cling( bear::universe::time_type elapsed_time );
    void progress_cling( bear::universe::time_type elapsed_time );
    void progress_clung_jump( bear::universe::time_type elapsed_time );
    void progress_start_hang( bear::universe::time_type elapsed_time );
    void progress_hang( bear::universe::time_type elapsed_time );
    void progress_swimming( bear::universe::time_type elapsed_time );
    void progress_sink( bear::universe::time_type elapsed_time );
    void progress_float( bear::universe::time_type elapsed_time );
    void progress_injured( bear::universe::time_type elapsed_time );
    void progress_paralyze( bear::universe::time_type elapsed_time );

    void set_state(player_state_name state);
    bool is_crushed() const;
    void regenerate();
    bool is_in_floating() const;

    void update_orientation();

    void do_get_camera();
    void do_stop_look_upward();
    void do_stop_crouch();
    void progress_spot( bear::universe::time_type elapsed_time );
    
    bool test_walk();
    bool test_bottom_contact();
    bool test_in_sky_or_swimm();
    void brake();
    void roar_shake();
    void shake(double force, bear::universe::time_type duration) const;

    void render_halos
    ( std::list<bear::engine::scene_visual>& visuals ) const;
    void render_jump_halo
    ( std::list<bear::engine::scene_visual>& visuals ) const;
    void get_visuals_without_invincibility
    ( std::list<bear::engine::scene_visual>& visuals ) const;

    void take_new_hat();
    void start_take_hat();
    void take_out_hat();
    bear::universe::coordinate_type get_move_force_in_walk() const;
   
    void update_layer_visibility();
    void update_layer_activity();

    bool check_can_teleport( unsigned int tag ) const;
    void end_of_progress();
    void update_shaders();
    void teleport_in_new_layer();

    static void init_exported_methods();

  protected:
    /** \brief Number of actions of the state named "wait". */
    unsigned int m_wait_state_number;

    /** \brief The current state. */
    player_state_name m_current_state;

    /** \brief Indicates the time since player want to run. */
    bear::universe::time_type m_run_time;

    /** \brief The time over which Player can run. */
    static const bear::universe::time_type s_time_to_run;

  private:
     /** \brief What Player is doing. */
    player_action::value_type m_current_action;

    /** \brief Last saved position of the center of mass. */
    bear::universe::position_type m_saved_position;

    /** \brief Last bottom_left_position. */
    bear::universe::position_type m_last_bottom_left;

    /** \brief The different states of Player. */
    std::vector<state_player*> m_states;

    /** \brief Indicates if each action is authorized. */
    std::vector<bool> m_authorized_action;

    /** \brief Current progress function. */
    progress_function_type m_progress;

    /** \brief Indicates the time since the last invincibily visual. */
    double m_last_visual_time;

    /** \brief Indicates the ratio of the length of preparation of the jump. */
    double m_jump_time_ratio;

    /** \brief Indicates if Player look up. */
    bool m_status_look_upward;

    /** \brief Indicates the time of the look_upward. */
    bear::universe::time_type m_look_upward_time;

    /** \brief Indicates if Player crouch. */
    bool m_status_crouch;

    /** \brief Indicates if Player can cling. */
    bool m_can_cling;

    /** \brief The orientation of the player in cling state. */
    bool m_cling_orientation;

    /** \brief Indicates if Player want to do a clumb jump. */
    bool m_want_clung_jump;

    /** \brief Indicates the duration of the paralyze state. */
    bear::universe::time_type m_paralyze_duration;

    /** \brief The animation of the halo. */
    bear::visual::animation* m_halo_animation;

    /** \brief The animation of the halo on the hand. */
    bear::visual::animation* m_halo_hand_animation;

    /** \brief The list of last visual when Player is invincible. */
    std::list< std::list<bear::engine::scene_visual> > m_last_visuals;

    /** \brief Indicates the time of the crouch. */
    bear::universe::time_type m_crouch_time;

    /** \brief Indicates the time since the state changement. */
    bear::universe::time_type m_state_time;

    /** \brief Indicates the time since player jump. */
    bear::universe::time_type m_jump_time;

    /** \brief Indicates the time since player is invincible. */
    bool m_offensive_phase;

    /** \brief Indicates if Player is lazy. */
    bool m_lazy;

    /** \brief Indicates if Player wants to move to the right. */
    bool m_move_right;

    /** \brief Indicates if Player wants to move to the left. */
    bool m_move_left;

    /** \brief The current force in x axis when Player moves. */
    bear::universe::coordinate_type m_move_force;

    /** \brief The current force in y axis when Player jumps. */
    bear::universe::coordinate_type m_jump_force;

    /** \brief The number of succesive iteration for which this player
        has a bottom contact. */
    unsigned int m_nb_bottom_contact;

    /** \brief The number of item that controls Player. */
    unsigned int m_controller_number;

    /** \brief Position of the hot spot, relative to the center of mass. */
    bear::universe::position_type m_hot_spot_position;

    /** \brief Minimum acceptable value for the position of the hot spot. */
    bear::universe::position_type m_hot_spot_minimum;

    /** \brief Maximum acceptable value for the position of the hot spot. */
    bear::universe::position_type m_hot_spot_maximum;

    /** \brief Maximum movement allowed when balancing the hot spot. */
    bear::universe::position_type m_hot_spot_balance_move;

    /** \brief Indicates if Plee has his main hat. */
    bool m_has_main_hat;

    /** \brief Indicates if Plee has a hat. */
    bool m_has_hat;

    /** \brief Indicates the current tag. */
    unsigned int m_initial_tag;    

    /** \brief Indicates the current tag. */
    unsigned int m_current_tag;

    /** \brief Indicates the next tag. */
    unsigned int m_next_tag;

    /** \brief The list of tags. */
    std::vector< std::string > m_tags;

    /** \brief Indicates if the player want to teleport. */
    bool m_want_teleport;

    /** \brief A pointer on the camera. */
    bear::engine::base_item* m_camera;

    /** \brief A pointer on the next layer for teleportation. */
    bear::engine::layer* m_next_layer;

    /** \brief A copy of physical item attributes before teleportation. */
    bear::universe::physical_item_state m_teleport_state_save;

    /** \brief The maximum halo height. */
    static const bear::universe::size_type s_max_halo_height;

    /** \brief  The time to crouch. */
    static const bear::universe::time_type s_time_to_crouch;

    /** \brief  The time to look_upward. */
    static const bear::universe::time_type s_time_to_look_upward;

    /** \brief The time after which Player is waiting. */
    static const bear::universe::time_type s_time_to_wait;

    /** \brief The time over which Player jump automatically. */
    static const bear::universe::time_type s_time_to_jump;

    /** \brief The time over which Player cannot cling. */
    static const bear::universe::time_type s_max_time_to_cling;

    /** \brief The time over which Player cannot hang. */
    static const bear::universe::time_type s_max_time_to_hang;

    /** \brief How long do we allow to add a force when jumping */
    static const bear::universe::time_type s_max_time_continue_jump;

    /** \brief The right force of Plee in idle state. */
    static const bear::universe::coordinate_type s_move_force_in_idle;

    /** \brief The right force of Plee in jump state. */
    static const bear::universe::coordinate_type s_move_force_in_jump;

    /** \brief The right force of Plee in vertical jump state. */
    static const bear::universe::coordinate_type
    s_move_force_in_vertical_jump;

    /** \brief The right force of Plee in run state. */
    static const bear::universe::coordinate_type s_move_force_in_run;

    /** \brief The right force of Plee in swim state. */
    static const bear::universe::coordinate_type
    s_move_force_in_swimming;

    /** \brief The minimum right force of Plee in walk state. */
    static const bear::universe::coordinate_type
    s_move_force_min_in_walk;

    /** \brief The maximum right force of Plee in walk state. */
    static const bear::universe::coordinate_type
    s_move_force_max_in_walk;

    /** \brief The impulse force given when Plee jumps. */
    static const bear::universe::coordinate_type s_jump_force;

    /** \brief The impulse force given when Plee jumps in float state. */
    static const bear::universe::coordinate_type s_jump_force_in_float;

    /** \brief The impulse force given for vertical jumps. */
    static const bear::universe::coordinate_type s_vertical_jump_force;

    /** \brief The speed over which Plee is running. */
    static const bear::universe::coordinate_type s_speed_to_run;

    /** \brief The mass of Plee. */
    static const double s_mass;

    /** \brief The density of Plee. */
    static const double s_density;
  }; // class player
} // namespace tunnel

#endif // __TUNNEL_PLAYER_HPP__
