/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
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
#include "visual/shader_program.hpp"

#include <set>
#include <list>

#include <boost/signals2/connection.hpp>
#include <claw/tween/single_tweener.hpp>

namespace tunnel
{
  class state_player;
  class seed;

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

    /** \brief The type of an handle on a base_item. */
    typedef
    bear::universe::derived_item_handle<bear::engine::base_item> handle_type;

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
        injured_state,
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
    void build();
    void on_enters_layer();
 
    bool set_bool_field( const std::string& name, bool value );

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

    bool receive_an_attack(const bear::engine::base_item& attacker);

  public:
    void apply_move_right();
    void apply_move_left();
    void apply_set_impulse_done();
    void apply_impulse_jump();
    void apply_jump();
    void apply_do_jump();
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
    void progress_injure_state( bear::universe::time_type elapsed_time );
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
    bool test_push_state();
    bool test_bottom_contact();
    bool test_in_sky_or_swimm();
    void brake();
    void roar_shake();
    void shake(double force, bear::universe::time_type duration) const;

    void get_visuals_without_invincibility
    ( std::list<bear::engine::scene_visual>& visuals ) const;

    bear::universe::coordinate_type get_move_force_in_walk() const;
   
    void update_layer_visibility();
    void update_layer_activity();
    void search_transportable(std::list<physical_item*>& transportables) const;
    bool check_can_teleport(std::list<const physical_item*>& bad_items) const;
    void init_shaders();
    void remove_shaders();
    void teleport_in_new_layer();
    void finish_teleport();
    void end_fade_effect();
    void finish_abort_tunnel();
    void thwart_gravity();
    void create_hit_star( const bear::universe::position_type& pos );
    void create_camera();
    void injure( const bear::engine::base_item& attacker );
    void finish_injure();

    void create_ground();
    void remove_ground();
    void create_seed();
    void remove_seed();
    void teleport_on_seed();
    void set_on_seed();

    void on_level_progress_done();
    void on_level_started();
    void on_init_shaders();

    static void init_exported_methods();

  private:
    /** \brief Number of actions of the state named "wait". */
    unsigned int m_wait_state_number;

    /** \brief The current state. */
    player_state_name m_current_state;

    /** \brief Indicates the time since player want to run. */
    bear::universe::time_type m_run_time;

    /** \brief The time over which Player can run. */
    static const bear::universe::time_type s_time_to_run;

     /** \brief What Player is doing. */
    player_action::value_type m_current_action;

    /** \brief A copy of initial physical item state. */
    bear::universe::physical_item_state m_initial_state;

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

    /** \brief Indicates the current tag. */
    unsigned int m_initial_tag;    

    /** \brief Indicates the current tag. */
    unsigned int m_current_tag;

    /** \brief Indicates the next tag. */
    unsigned int m_next_tag;

    /** \brief The list of tags. */
    std::vector< std::string > m_tags;

    /** \brief A copy of physical item attributes before teleportation. */
    bear::universe::physical_item_state m_teleport_state_save;

    /** \brief The time last the last teleportation command 
        (open tunnel or abort). */
    bear::universe::time_type m_teleport_time;

    /** \brief Indicates that the tunnel is aborted. */
    bool m_tunnel_aborted;

    /** \brief The tweener for tunnel radius. */
    claw::tween::single_tweener m_radius_tweener;

    /** \brief The tweener for fade effect on target layer. */
    claw::tween::single_tweener m_fade_effect_tweener;

    /** \brief The intensity of fade effect on target layer. */
    double m_fade_effect_intensity;

    /** \brief Indicates that the player is in a state where he can teleport. */
    double m_can_teleport;

    /** \brief The state before the teleportation. */
    std::string m_state_before_teleport;

    /** \brief The connection to the signal emitted by the end of the progress
        of the layer. */
    boost::signals2::connection m_level_progress_done;    

    /** \brief The connection to the signal emitted when the level starts. */
    boost::signals2::connection m_level_started;  

    /** \brief The connection to the signal emitted by the end of the progress
        of the layer. */
    boost::signals2::connection m_init_shaders;

    /** \brief The connection to the signal emitted by the end of the progress
        of the layer. */
    boost::signals2::connection m_remove_shaders;  

    /** \brief The shader for origin layer. */
    bear::visual::shader_program m_origin_shader;

    /** \brief The shader for target layer. */
    bear::visual::shader_program m_target_shader;

    /** \brief The shader for common layer. */
    bear::visual::shader_program m_common_shader;

    /** \brief Indicates that the function on_enters_layer is done. */
    bool m_enters_layer_done;

    /** \brief The radius of teleportation circle. */
    bear::universe::coordinate_type m_teleportation_radius;

    /** \brief Indicates if the player has been created by editor. */
    bool m_editor_player;

    /** \brief Indicates if the player can transport objects. */
    bool m_can_transport; 

    /** \brief Indicates if the monster is injured. */
    bool m_is_injured;

    /** \brief Indicates the time of the attack. */
    bear::universe::time_type m_injured_time;

    /** \brief Transparency of injured frame. */
    double m_opacity_injured;

    /** \brief Increment for the transparency when injured. */
    double m_opacity_inc;

    /** \brief Indicates if the impulse_jump has been done. */
    bool m_impulse_jump_done;

    /** \brief Indicates if we must create a camera. */
    bool m_must_create_camera;

    /** \brief Indicates if we can create a ground. */
    bool m_can_create_ground;

    /** \brief The block that is under the player with bonus. */
    handle_type m_ground;

    /** \brief The seed for teleportation. */
    seed* m_seed;
    
    /** \brief Indicates that there is a teleportation on a seed. */
    bool m_seed_teleportation;

    /** \brief The minimum radius of teleportation circle. */
    static const bear::universe::coordinate_type s_min_teleportation_radius;

    /** \brief The maximum radius of teleportation circle. */
    static const bear::universe::coordinate_type s_max_teleportation_radius;

    /** \brief The time before a teleportation. */
    static const bear::universe::coordinate_type s_time_before_teleportation;

    /** \brief The duration of the tunnel expand after the teleportation. */
    static const bear::universe::coordinate_type s_tunnel_expand_duration;

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

    /** \brief The right force of Player in idle state. */
    static const bear::universe::coordinate_type s_move_force_in_idle;

    /** \brief The right force of Player in jump state. */
    static const bear::universe::coordinate_type s_move_force_in_jump;

    /** \brief The right force of Player in vertical jump state. */
    static const bear::universe::coordinate_type
    s_move_force_in_vertical_jump;

    /** \brief The right force of Player in run state. */
    static const bear::universe::coordinate_type s_move_force_in_run;

    /** \brief The right force of Player in swim state. */
    static const bear::universe::coordinate_type
    s_move_force_in_swimming;

    /** \brief The minimum right force of Player in walk state. */
    static const bear::universe::coordinate_type
    s_move_force_min_in_walk;

    /** \brief The maximum right force of Player in walk state. */
    static const bear::universe::coordinate_type
    s_move_force_max_in_walk;

    /** \brief The impulse force given when Player jumps. */
    static const bear::universe::coordinate_type s_jump_force;

    /** \brief The impulse force given when Player jumps in float state. */
    static const bear::universe::coordinate_type s_jump_force_in_float;

    /** \brief The impulse force given for vertical jumps. */
    static const bear::universe::coordinate_type s_vertical_jump_force;

    /** \brief The speed over which Player is running. */
    static const bear::universe::coordinate_type s_speed_to_run;

    /** \brief The mass of Player. */
    static const double s_mass;

    /** \brief The density of Player. */
    static const double s_density;

    /** \brief The energy of Player. */
    static const unsigned int s_energy; 

    /** \brief Duration of injured state. */
    static const double s_injured_duration;
  }; // class player
} // namespace tunnel

#endif // __TUNNEL_PLAYER_HPP__
