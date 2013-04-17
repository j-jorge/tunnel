/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the tunnel::player class.
 * \author Sebastien Angibaud
 */
#include "tunnel/player.hpp"
#include <sstream>

#include "engine/game.hpp"
#include "engine/level.hpp"
#include "engine/world.hpp"

#include "generic_items/decorative_item.hpp"
#include "generic_items/tweener_item.hpp"
#include "generic_items/camera_shaker.hpp"
#include "generic_items/decorative_effect.hpp"
#include "generic_items/shader/layer_shader.hpp"
#include "universe/forced_movement/forced_tracking.hpp"

#include "tunnel/camera_on_player.hpp"
#include "tunnel/defines.hpp"
#include "tunnel/player_action.hpp"

#include "tunnel/player_state/state_player.hpp"
#include "tunnel/player_state/state_roar.hpp"
#include "tunnel/player_state/state_walk.hpp"
#include "tunnel/player_state/state_idle.hpp"
#include "tunnel/player_state/state_jump.hpp"
#include "tunnel/player_state/state_fall.hpp"
#include "tunnel/player_state/state_dead.hpp"
#include "tunnel/player_state/state_game_over.hpp"
#include "tunnel/player_state/state_run.hpp"
#include "tunnel/player_state/state_slap.hpp"
#include "tunnel/player_state/state_teleport.hpp"
#include "tunnel/player_state/state_start_jump.hpp"
#include "tunnel/player_state/state_vertical_jump.hpp"
#include "tunnel/player_state/state_look_upward.hpp"
#include "tunnel/player_state/state_crouch.hpp"
#include "tunnel/player_state/state_captive.hpp"
#include "tunnel/player_state/state_wait.hpp"
#include "tunnel/player_state/state_start_cling.hpp"
#include "tunnel/player_state/state_cling.hpp"
#include "tunnel/player_state/state_clung_jump.hpp"
#include "tunnel/player_state/state_start_hang.hpp"
#include "tunnel/player_state/state_hang.hpp"
#include "tunnel/player_state/state_sink.hpp"
#include "tunnel/player_state/state_swimming.hpp"
#include "tunnel/player_state/state_float.hpp"
#include "tunnel/player_state/state_paralyze.hpp"

#include "tunnel/util/player_util.hpp"

#include <claw/tween/easing/easing_linear.hpp>

const bear::universe::size_type tunnel::player::s_max_halo_height = 64;
const bear::universe::time_type tunnel::player::s_time_to_crouch = 0.5;
const bear::universe::time_type tunnel::player::s_time_to_look_upward = 0.5;
const bear::universe::time_type tunnel::player::s_time_to_wait = 3;
const bear::universe::time_type tunnel::player::s_time_to_jump = 1;
const bear::universe::time_type tunnel::player::s_time_to_run = 2.5; // 1.2;
const bear::universe::time_type tunnel::player::s_max_time_to_cling = 0.3;
const bear::universe::time_type tunnel::player::s_max_time_to_hang = 1;
const bear::universe::time_type tunnel::player::s_max_time_continue_jump = 0.26;

const bear::universe::coordinate_type
tunnel::player::s_move_force_in_idle = 200000;

const bear::universe::coordinate_type
tunnel::player::s_move_force_in_jump = 100000;

const bear::universe::coordinate_type
tunnel::player::s_move_force_in_vertical_jump = 50000;

const bear::universe::coordinate_type
tunnel::player::s_move_force_in_run = 350000; // 450000;

const bear::universe::coordinate_type
tunnel::player::s_move_force_in_swimming = 80000;

const bear::universe::coordinate_type
tunnel::player::s_move_force_min_in_walk = 50000; // 50000 

const bear::universe::coordinate_type
tunnel::player::s_move_force_max_in_walk = 300000; // 300000

const bear::universe::coordinate_type tunnel::player::s_jump_force = 2600000;

const bear::universe::coordinate_type
tunnel::player::s_jump_force_in_float = 11500000;

const bear::universe::coordinate_type
tunnel::player::s_vertical_jump_force = 8500000;

const bear::universe::coordinate_type tunnel::player::s_speed_to_run = 580; // 580 

const double tunnel::player::s_mass = 100;
const double tunnel::player::s_density = 1.5;

BASE_ITEM_EXPORT( player, tunnel )

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
tunnel::player::player()
: m_current_state(roar_state), m_last_visual_time(0),
  m_status_look_upward(false),
  m_status_crouch(false), m_can_cling(false),
  m_cling_orientation(false), m_halo_animation(NULL),
  m_halo_hand_animation(NULL), m_move_right(false), m_move_left(false),
  m_move_force(0), m_nb_bottom_contact(0),
  m_controller_number(0),
  m_hot_spot_position(0, 0),
  m_hot_spot_minimum(0, 0), m_hot_spot_maximum(0, 0),
  m_hot_spot_balance_move(0, 0), m_initial_tag(0), m_current_tag(0),
  m_next_tag(0)
{
  set_mass(s_mass);
  set_density(s_density);
  set_size( 50, 110 );

  init();
} // player::player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
tunnel::player::player( const player& p )
  : super(p),
    m_current_state(p.roar_state), m_last_visual_time(0),
    m_status_look_upward(p. m_status_look_upward),
    m_status_crouch(p.m_status_crouch), m_can_cling(p. m_can_cling),
    m_cling_orientation(p.m_cling_orientation),
    m_halo_animation(NULL), m_halo_hand_animation(NULL),
    m_move_right(p. m_move_right), m_move_left(p.m_move_left), m_move_force(0),
    m_nb_bottom_contact(0), m_controller_number(0),
    m_hot_spot_position(0, 0),
    m_hot_spot_minimum(0, 0), m_hot_spot_maximum(0, 0),
    m_hot_spot_balance_move(0, 0), m_initial_tag(p.m_initial_tag),
    m_current_tag(p.m_current_tag), m_next_tag(p.m_next_tag), m_tags(p.m_tags)
{
  init();
} // player::player()

/*----------------------------------------------------------------------------*/
/**
 * \brief Init member variables.
 */
void tunnel::player::init()
{
  set_name( util::get_player_name(1) );

  set_z_fixed(false);
  set_weak_collisions(false);
  m_offensive_phase = false;

  set_spot_minimum(-200, -250);
  set_spot_maximum(200, 220);
  set_spot_balance_move(3, 15);

  save_current_position();
  m_last_bottom_left = bear::universe::position_type(0, 0);
  m_run_time = 0;

  m_states.resize(28);
  m_states[walk_state] = new state_walk(this);
  m_states[idle_state] = new state_idle(this);
  m_states[jump_state] = new state_jump(this);
  m_states[fall_state] = new state_fall(this);
  m_states[dead_state] = new state_dead(this);
  m_states[game_over_state] = new state_game_over(this);
  m_states[roar_state] = new state_roar(this);
  m_states[run_state] = new state_run(this);
  m_states[slap_state] = new state_slap(this);
  m_states[teleport_state] = new state_teleport(this);
  m_states[start_jump_state] = new state_start_jump(this);
  m_states[vertical_jump_state] = new state_vertical_jump(this);
  m_states[look_upward_state] = new state_look_upward(this);
  m_states[crouch_state] = new state_crouch(this);
  m_states[captive_state] = new state_captive(this);
  m_states[wait_state] = new state_wait(this);
  m_states[start_cling_state] = new state_start_cling(this);
  m_states[cling_state] = new state_cling(this);
  m_states[clung_jump_state] = new state_clung_jump(this);
  m_states[start_hang_state] = new state_start_hang(this);
  m_states[hang_state] = new state_hang(this);
  m_states[swimming_state] = new state_swimming(this);
  m_states[sink_state] = new state_sink(this);
  m_states[float_state] = new state_float(this);
  m_states[paralyze_state] = new state_paralyze(this);

  m_progress = &player::progress_roar;
} // player::init()

/*----------------------------------------------------------------------------*/
/**
 * \brief Destructor.
 */
tunnel::player::~player()
{
  unsigned int i;

  for (i=0; i!=m_states.size(); ++i)
    delete m_states[i];

  if ( m_halo_animation )
    delete m_halo_animation;

  if ( m_halo_hand_animation )
    delete m_halo_hand_animation;

  m_level_progress_done.disconnect();
} // player::~player()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the progression of the item.
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::player::progress( bear::universe::time_type elapsed_time )
{
  // THIS CONDITION MUST BE CHECKED FIRST
  if ( !is_a_marionette() )
    progress_input_actions(elapsed_time);
  else
    dummy_progress_input_actions(elapsed_time);

  super::progress(elapsed_time);
  
  m_state_time += elapsed_time;
  m_run_time += elapsed_time;
  m_jump_time += elapsed_time;

  m_jump_force = get_mass() * 7500 *
    (1 - (m_jump_time / s_max_time_continue_jump)
     * (m_jump_time / s_max_time_continue_jump) );

  if (m_jump_force <= 0)
    m_jump_force = 0;

  if ( is_crushed() && (m_current_state != player::dead_state) )
    apply_die();
  else
    {
      if ( m_progress != NULL )
        (this->*m_progress)(elapsed_time);
      
      if ( is_only_in_environment(bear::universe::water_environment) )
        progress_in_water(elapsed_time);

      progress_spot( elapsed_time );
      update_orientation();
      m_can_cling = false;
    }

  m_last_bottom_left = get_bottom_left();
} // player::progress()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the sprite representing the item.
 * \param visuals (out) The sprites of the item, and their positions.
 */
void tunnel::player::get_visual
( std::list<bear::engine::scene_visual>& visuals ) const
{
  super::get_visual(visuals);

  render_halos(visuals);

  std::list< std::list<bear::engine::scene_visual> >::const_iterator it;

  for ( it = m_last_visuals.begin(); it != m_last_visuals.end(); ++it )
    {
      std::list<bear::engine::scene_visual>::const_iterator it2;
      for (it2 = it->begin(); it2 != it->end(); ++it2 )
        visuals.push_front(*it2);
    }
} // player::get_visual()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
void tunnel::player::pre_cache()
{
  super::pre_cache();

  // player
  get_level_globals().load_model("model/player/plee.cm");
  
  // halo for soul
  get_level_globals().load_image("gfx/plee/misc.png");

  // Bath cap
  get_level_globals().load_animation("animation/plee/bath-cap.canim");

  // halo for vertical jump
  get_level_globals().load_animation("animation/plee/halo.canim");

  // sounds
  get_level_globals().load_sound("sound/plee/grr.wav");
  get_level_globals().load_sound("sound/plee/snore.ogg");
} // player::pre_cache()

/*----------------------------------------------------------------------------*/
/**
 * \brief Do post creation actions.
 */
void tunnel::player::on_enters_layer()
{
  super::on_enters_layer();

  m_authorized_action.resize(player_action::max_value + 1);
  for ( unsigned int i=0; i <= player_action::max_value; ++i)
    m_authorized_action[i] = true;

  save_current_position();

  m_wait_state_number = 0;
  m_want_clung_jump = false;
  bear::engine::level_globals& glob = get_level_globals();

  m_halo_animation = new bear::visual::animation
    ( glob.get_animation("animation/plee/halo.canim") );

  m_halo_hand_animation = new bear::visual::animation
    ( glob.get_animation("animation/plee/halo_hand.canim") );

  get_level().add_interest_around(this);

  set_model_actor( get_level_globals().get_model("model/player/plee.cm") );
  start_action_model("idle");

  m_wait_state_number = 3;
  m_has_main_hat = true;
  m_has_hat = true;
  save_position(get_center_of_mass());

  update_layer_visibility();
  update_layer_activity();
} // player::on_enters_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type list of <std::string>.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool tunnel::player::set_string_list_field
( const std::string& name, const std::vector<std::string>& value )
{
  bool result = false;

  if ( name == "player.tags" )
    {
      m_tags.resize(value.size());

      for (std::size_t i=0; i!=value.size(); ++i)
        m_tags[i] = value[i].c_str();

      result = true;
    }
  else
    result = super::set_string_list_field( name, value );

  return result;
} // player::set_string_list_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set a field of type string.
 * \param name The name of the field.
 * \param value The new value of the field.
 * \return false if the field "name" is unknow, true otherwise.
 */
bool tunnel::player::set_string_field
( const std::string& name, const std::string& value )
{
  bool result = true;

  if (name == "player.initial_tag")
    {
      m_current_tag = m_tags.size();
      
      for ( unsigned int i = 0; i != m_tags.size(); ++i )
        if ( m_tags[i] == value )
          m_current_tag = i;
    
      m_initial_tag = m_current_tag;
    }
  else
    result = super::set_string_field(name, value);

  return result;
} // player::set_string_field()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell if the item is correctly initialized.
 */
bool tunnel::player::is_valid() const
{
  return ! m_tags.empty() && ( m_current_tag < m_tags.size() ) 
    && super::is_valid();
} // player::is_valid()

/*----------------------------------------------------------------------------*/
/**
 * \brief Save the position of the player.
 * \param p The center of mass to remember.
 */
void tunnel::player::save_position( const bear::universe::position_type& p )
{
  m_saved_position = p;
} // player::save_position()

/*----------------------------------------------------------------------------*/
/**
 * \brief Save the current position of the player.
 */
void tunnel::player::save_current_position()
{
  save_position( get_center_of_mass() );
} // player::save_current_position()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell to Player to start an action.
 * \param a The action to start.
 */
void tunnel::player::start_action( player_action::value_type a )
{
  if ( m_authorized_action[a] )
    switch( a )
      {
      case player_action::idle : break;
      case player_action::move_left : break;
      case player_action::move_right : break;
      case player_action::jump :
        m_states[m_current_state]->do_jump(); break;
      case player_action::slap :
        m_states[m_current_state]->do_slap(); break;
      case player_action::teleport :
        m_states[m_current_state]->do_teleport(); break;
      case player_action::look_upward : do_start_look_upward(); break;
      case player_action::crouch : do_start_crouch(); break;
      case player_action::captive : break;
      case player_action::release : break;
      case player_action::die : apply_die(); break;
      case player_action::roar : start_action_model("roar"); break;
      case player_action::disappear : start_action_model("disappear"); break;
      case player_action::action_null: break;
      default:
        claw::logger << claw::log_warning << "Action ignored (start): " << a
                     << std::endl;;
      }
} // player::start_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell to the player to do an action.
 * \param elapsed_time How long the action is done.
 * \param a The action to do.
 */
void tunnel::player::do_action
( bear::universe::time_type elapsed_time, player_action::value_type a )
{
  switch( a )
      {
      case player_action::move_left :
        m_states[m_current_state]->do_move_left(); break;
      case player_action::move_right :
        m_states[m_current_state]->do_move_right(); break;

      default:

        if ( m_authorized_action[a] )
          switch( a )
            {
            case player_action::idle : choose_idle_state(); break;
            case player_action::jump :
              m_states[m_current_state]->do_continue_jump(); break;
            case player_action::slap : break;
            case player_action::teleport : break;
            case player_action::look_upward :
              m_states[m_current_state]->do_continue_look_upward(); break;
            case player_action::crouch :
              m_states[m_current_state]->do_continue_crouch(); break;
            case player_action::captive :
              m_states[m_current_state]->captive(); break;
            case player_action::release :
              m_states[m_current_state]->release(); break;
            case player_action::die : break;
            case player_action::action_null: break;
            default:
              claw::logger << claw::log_warning << "Action ignored: " << a
                           << std::endl;
            }
      }
} // player::do_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell to player to stop an action.
 * \param a The action to stop.
 */
void tunnel::player::stop_action( player_action::value_type a )
{
  if ( m_authorized_action[a] )
    switch( a )
      {
      case player_action::idle : break;
      case player_action::move_left :
        m_want_clung_jump = false; break;
      case player_action::move_right :
        m_want_clung_jump = false; break;
      case player_action::jump :
        m_states[m_current_state]->do_stop_vertical_jump(); break;
      case player_action::slap : break;
      case player_action::teleport : 
        m_states[m_current_state]->do_stop_teleport(); break;
      case player_action::look_upward : do_stop_look_upward(); break;
      case player_action::crouch :
        do_stop_crouch(); break;
      case player_action::captive : break;
      case player_action::release : break;
      case player_action::die : break;
      case player_action::action_null: break;
      default:
        claw::logger << claw::log_warning << "Action ignored (stop): " << a
                     << std::endl;
      }
} // player::stop_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start a new action of model.
 * \param action The action to start.
 */
void tunnel::player::start_action_model(const std::string& action)
{
  start_model_action(action);
} // player::start_action_model()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set offensive phase.
 * \param status The new status.
*/
void tunnel::player::set_offensive_phase( bool status )
{
  m_offensive_phase = status;
} // player::set_offensive_phase()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if a given action is authorized.
 * \param a Tha action to set.
 * \param value The new state of the action (true if authorized).
*/
void tunnel::player::set_authorized_action(player_action::value_type a, bool value)
{
  m_authorized_action[a] = value;
} // player::set_authorized_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Authorize a given action.
 * \param a The name of the action to authorize.
 */
void tunnel::player::authorize_action( const std::string& a )
{
  const player_action::value_type c = player_action::from_string(a);

  if ( c != player_action::action_null )
    m_authorized_action[c] = true;
} // player::authorize_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Authorize all the actions.
 */
void tunnel::player::authorize_all_actions()
{
  for ( std::size_t i=0; i!=m_authorized_action.size(); ++i )
    m_authorized_action[i] = true;
} // player::authorize_all_actions()

/*----------------------------------------------------------------------------*/
/**
 * \brief Disable all the actions.
 */
void tunnel::player::disable_all_actions()
{
  for ( std::size_t i=0; i!=m_authorized_action.size(); ++i )
    m_authorized_action[i] = false;
} // player::disable_all_actions()

/*----------------------------------------------------------------------------*/
/**
 * \brief Give the ratio of the length of preparation of the jump.
 */
bear::universe::time_type tunnel::player::get_jump_time_ratio() const
{
  return m_jump_time_ratio;
} // player::get_jump_time_ratio()

/*----------------------------------------------------------------------------*/
/**
 * \brief Indicates if Player is a marionette.
 */
bool tunnel::player::is_a_marionette() const
{
  return (m_controller_number != 0);
} // player::is_a_marionette()

/*----------------------------------------------------------------------------*/
/**
 * \brief Turn on/off the marionette state of Player.
 * \param b The new value of the state.
 */
void tunnel::player::set_marionette( bool b )
{
  if ( b )
    ++m_controller_number;
  else
    {
      CLAW_PRECOND( m_controller_number >= 1 );
      --m_controller_number;
    }
} // player::set_marionette()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the look up status.
 */
void tunnel::player::set_status_look_upward(bool status)
{
  m_status_look_upward = status;
} // player::set_status_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Give the look up status.
 */
bool tunnel::player::get_status_look_upward() const
{
  return m_status_look_upward;
} // player::get_status_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the crouch status.
 */
void tunnel::player::set_status_crouch(bool status)
{
  m_status_crouch = status;
} // player::set_status_crouch()

/*----------------------------------------------------------------------------*/
/**
 * \brief Give the crouch status.
 */
bool tunnel::player::get_status_crouch() const
{
  return m_status_crouch;
} // player::get_status_crouch()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player start to look up.
 */
void tunnel::player::do_start_look_upward()
{
  m_status_look_upward = true;
  m_look_upward_time = 0;
  m_states[m_current_state]->do_look_upward();
} // player::do_start_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Make the player start to crouch.
 */
void tunnel::player::do_start_crouch()
{
  m_status_crouch = true;
  m_crouch_time = 0;
  m_states[m_current_state]->do_crouch();
} // player::do_start_crouch()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if Player can cling.
 * \param status The new status.
 */
void tunnel::player::set_can_cling(bool status)
{
  m_can_cling = status;
} // player::set_can_cling()

/*----------------------------------------------------------------------------*/
/**
 * \brief Indicates if the player is clung.
 */
bool tunnel::player::is_clung() const
{
  return ( m_current_state == cling_state );
} // player::is_clung()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set if Player want to do a clumb jump.
 * \param status The new status.
 */
void tunnel::player::set_want_clung_jump(bool status)
{
  m_want_clung_jump = status;
} // player::set_want_clung_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Indicates if the player want to do a clung jump.
 */
bool tunnel::player::want_clung_jump() const
{
  return m_want_clung_jump;
} // player::want_clung_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the coordinates of the point to target to (for camera or active
 *        region).
 */
bear::universe::position_type tunnel::player::hot_spot() const
{
  bear::universe::position_type p;

  bear::universe::size_type w, h;
  get_action("idle")->get_max_size(w, h);
  const bear::universe::size_box_type half_player( w / 2, h / 2 );

  if ( get_rendering_attributes().is_mirrored() )
    {
      p = get_bottom_right();
      p.x -= half_player.x;
    }
  else
    {
      p = get_bottom_left();
      p.x += half_player.x;
    }

  p.y += half_player.y;

  return p + m_hot_spot_position;
} // player::hot_spot()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the minimum acceptable value for the position of the hot spot.
 * \param x Minimum value on the X-axis.
 * \param y Minimum value on the Y-axis.
 */
void tunnel::player::set_spot_minimum
( bear::universe::coordinate_type x, bear::universe::coordinate_type y )
{
  m_hot_spot_minimum.set
    ( std::min(x, m_hot_spot_maximum.x), std::min(y, m_hot_spot_maximum.y) );
} // player::set_spot_minimum()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the maximum acceptable value for the position of the hot spot.
 * \param x Maximum value on the X-axis.
 * \param y Maximum value on the Y-axis.
 */
void tunnel::player::set_spot_maximum
( bear::universe::coordinate_type x, bear::universe::coordinate_type y )
{
  m_hot_spot_maximum.set
    ( std::max(x, m_hot_spot_minimum.x), std::max(y, m_hot_spot_minimum.y) );
} // player::set_spot_maximum()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the maximum movement allowed when balancing the hot spot.
 * \param x Maximum movement on the X-axis.
 * \param y Maximum movement on the Y-axis.
 */
void tunnel::player::set_spot_balance_move
( bear::universe::coordinate_type x, bear::universe::coordinate_type y )
{
  m_hot_spot_balance_move.set(std::abs(x), std::abs(y));
} // player::set_spot_balance_move()

/*----------------------------------------------------------------------------*/
/**
 * \brief Change the gap of the spot.
 * \param gap The vector of gap.
 */
void tunnel::player::add_spot_gap( const bear::universe::position_type& gap )
{
  m_hot_spot_position += gap;

  if ( m_hot_spot_position.x > m_hot_spot_maximum.x )
    m_hot_spot_position.x -= std::abs(gap.x);
  else if ( m_hot_spot_position.x < m_hot_spot_minimum.x )
    m_hot_spot_position.x += std::abs(gap.x);

  if ( m_hot_spot_position.y > m_hot_spot_maximum.y )
    m_hot_spot_position.y -= std::abs(gap.y);
  else if ( m_hot_spot_position.y < m_hot_spot_minimum.y )
    m_hot_spot_position.y += std::abs(gap.y);
} // player::add_spot_gap()

/*----------------------------------------------------------------------------*/
/**
 * \brief Balance the gap of the spot.
 * \param x Tell if we balance on the X-axis.
 * \param y Tell if we balance on the Y-axis.
 */
void tunnel::player::balance_spot(bool x, bool y)
{
  if ( x )
    {
      if ( m_hot_spot_position.x > m_hot_spot_balance_move.x )
        m_hot_spot_position.x -= m_hot_spot_balance_move.x;
      else if ( m_hot_spot_position.x < -m_hot_spot_balance_move.x)
        m_hot_spot_position.x += m_hot_spot_balance_move.x;
      else
        m_hot_spot_position.x = 0;
    }

  if ( y )
    {
      if ( m_hot_spot_position.y > m_hot_spot_balance_move.y )
        m_hot_spot_position.y -= m_hot_spot_balance_move.y;
      else if ( m_hot_spot_position.y < -m_hot_spot_balance_move.y)
        m_hot_spot_position.y += m_hot_spot_balance_move.y;
      else
        m_hot_spot_position.y = 0;
    }
} // player::balance_spot()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action move_right.
 */
void tunnel::player::apply_move_right()
{
  if ( m_authorized_action[player_action::move_right]  )
    {
      m_move_right = true;
      add_internal_force( bear::universe::force_type(m_move_force, 0) );
    }
  if ( get_speed().x == 0 )
    get_rendering_attributes().mirror(false);
} // player::apply_move_right()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action move_left.
 */
void tunnel::player::apply_move_left()
{
  if ( m_authorized_action[player_action::move_left]  )
    {
      m_move_left = true;
      add_internal_force( bear::universe::force_type(-m_move_force, 0) );
    }
  else if ( get_speed().x == 0 )
    get_rendering_attributes().mirror(true);
} // player::apply_move_left()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply impulsion of a jump.
 */
void tunnel::player::apply_impulse_jump()
{
  if ( m_current_state == float_state )
    {
      add_internal_force
        ( bear::universe::force_type(0, s_jump_force_in_float) );
      start_action_model("jump");
    }
  else
    {
      m_jump_time = 0;
      add_external_force( bear::universe::force_type(0, 2*s_jump_force ) );
    }
} // player::apply_impulse_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action jump.
 */
void tunnel::player::apply_jump()
{
  m_move_force = s_move_force_in_jump;
  set_state(player::jump_state);
  m_progress = &player::progress_jump;
} // player::apply_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action continue_jump.
 */
void tunnel::player::apply_continue_jump()
{
  if ( m_jump_time <= s_max_time_continue_jump )
    add_external_force( bear::universe::force_type(0, m_jump_force) );
} // player::apply_continue_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action start_jump.
 */
void tunnel::player::apply_start_jump()
{
  set_state(player::start_jump_state);
  m_progress = &player::progress_start_jump;
  m_halo_animation->reset();
} // player::apply_start_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action vertical_jump.
 *
 */
void tunnel::player::apply_vertical_jump()
{
  m_move_force = s_move_force_in_vertical_jump;
  m_run_time = 0;

  if ( m_state_time >= s_time_to_jump )
    m_jump_time_ratio = 1;
  else
    m_jump_time_ratio = m_state_time / s_time_to_jump;

  set_state(player::vertical_jump_state);
  m_progress = &player::progress_vertical_jump;
} // player::apply_vertical_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action fall.
 *
 */
void tunnel::player::apply_fall()
{
  m_move_force = s_move_force_in_jump;
  set_state(player::fall_state);
  m_progress = &player::progress_fall;
} // player::apply_fall()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action idle.
 *
 */
void tunnel::player::apply_idle()
{
  m_move_force = s_move_force_in_idle;
  set_state(player::idle_state);
  m_progress = &player::progress_idle;
} // player::apply_idle()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action walk.
 *
 */
void tunnel::player::apply_walk()
{
  m_move_force = s_move_force_in_idle;
  set_state(player::walk_state);
  m_progress = &player::progress_walk;
} // player::apply_walk()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action run.
 */
void tunnel::player::apply_run()
{
  m_move_force = s_move_force_in_run;
  set_state(player::run_state);
  m_progress = &player::progress_run;
} // player::apply_run()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action slap.
 */
void tunnel::player::apply_slap()
{
  m_move_force = s_move_force_in_idle;
  set_state(player::slap_state);
  m_progress = &player::progress_slap;
  apply_attack();
} // player::apply_slap()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action open tunnel.
 */
void tunnel::player::apply_open_tunnel()
{
  m_teleport_state_save = *this;

  m_move_force = s_move_force_in_idle;
  set_state(player::teleport_state);
  m_progress = &player::progress_teleport;

  unsigned int next = ( m_current_tag + 1 ) % m_tags.size();

  bear::engine::level::layer_iterator it = get_level().layer_begin();

  for ( ; it != get_level().layer_end(); ++it )
    if ( it->get_tag() == m_tags[next] )
      {
        it->set_visible(true);
        it->set_active(true);
      }
} // player::apply_onpen_tunnel()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action abort tunnel.
 */
void tunnel::player::apply_abort_tunnel()
{
  start_action_model("idle");

  unsigned int next = (m_current_tag + 1) % m_tags.size();

  bear::engine::level::layer_iterator it = get_level().layer_begin();
  for ( ; it != get_level().layer_end(); ++it )
    if ( it->get_tag() == m_tags[next] )
      {
        it->set_visible(false);
        it->set_active(false);
      }
} // player::apply_abort_tunnel()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action teleport.
 */
void tunnel::player::apply_teleport()
{
  unsigned int next = (m_current_tag + 1) % m_tags.size();

  if ( check_can_teleport(next) )
    {
      start_action_model("idle");
      m_next_tag = next;

      m_level_progress_done =
        get_level().on_progress_done
        ( boost::bind( &player::on_level_progress_done, this ) );
    }
  //else
  //  abort_teleport();
} // player::apply_end_teleport()

/*----------------------------------------------------------------------------*/
/**
 * \brief Turn the attack mode.
 */
void tunnel::player::apply_attack()
{
  m_offensive_phase = true;
} // player::apply_attack()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action captive.
 *
 */
void tunnel::player::apply_captive()
{
  set_state(player::captive_state);
  m_progress = &player::progress_captive;
} // player::apply_captive()

/*----------------------------------------------------------------------------*/
/**
 * \brief Stop the action captive.
 *
 */
void tunnel::player::apply_release()
{
  choose_idle_state();
  m_progress = &player::progress_idle;
} // player::apply_release()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action wait.
 */
void tunnel::player::apply_wait()
{ 
  if ( m_progress != &player::progress_wait ) 
    m_lazy = false;

  set_state(player::wait_state);
  m_progress = &player::progress_wait;
} // player::apply_wait()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action crouch.
 *
 */
void tunnel::player::apply_crouch()
{
  m_move_force = s_move_force_in_idle;
  set_state(player::crouch_state);
  m_progress = &player::progress_crouch;
} // player::apply_crouch()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action look_upward.
 *
 */
void tunnel::player::apply_look_upward()
{
  m_move_force = s_move_force_in_idle;
  set_state(player::look_upward_state);
  m_progress = &player::progress_look_upward;
} // player::apply_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Die.
 */
void tunnel::player::apply_die()
{
  set_state(dead_state);
  m_progress = &player::progress_dead;
} // player::apply_die()

/*----------------------------------------------------------------------------*/
/**
 * \brief Roar.
 */
void tunnel::player::apply_roar()
{
  set_state(roar_state);
  m_progress = &player::progress_roar;
} // player::apply_roar()

/*----------------------------------------------------------------------------*/
/**
 * \brief Disappear.
 */
void tunnel::player::apply_disappear()
{
  m_progress = &player::progress_idle;
  kill();
} // player::apply_disappear()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start the state "game over".
 */
void tunnel::player::apply_game_over()
{
  add_position_constraints();
  m_move_force = 0;
  set_state(game_over_state);
  m_progress = &player::progress_game_over;
} // player::apply_game_over()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to cling.
 */
void tunnel::player::apply_start_cling()
{
  set_state(start_cling_state);
  m_progress = &player::progress_start_cling;
} // player::apply_start_cling()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player cling.
 */
void tunnel::player::apply_cling()
{
  m_run_time = 0;
  set_state(cling_state);
  m_progress = &player::progress_cling;
} // player::apply_cling()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player is clung and jump.
 */
void tunnel::player::apply_clung_jump()
{
  if ( get_rendering_attributes().is_mirrored() )
    add_internal_force
      ( get_mass() * bear::universe::force_type(50000, 100000) );
  else
    add_internal_force
      ( get_mass() * bear::universe::force_type(-50000, 100000) );
} // player::apply_clung_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start to hang.
 */
void tunnel::player::apply_start_hang()
{
  set_state(start_hang_state);
  m_progress = &player::progress_start_hang;
} // player::apply_start_hang()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player hang.
 */
void tunnel::player::apply_hang()
{
  set_state(hang_state);
  m_progress = &player::progress_hang;
} // player::apply_hang()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player swim.
 */
void tunnel::player::apply_swimming()
{
  m_move_force = s_move_force_in_swimming;
  set_state(swimming_state);
  m_progress = &player::progress_swimming;
} // player::apply_swimming()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player swim when he is in floating.
 */
void tunnel::player::apply_swim_in_float()
{
  if ( get_rendering_attributes().is_mirrored() )
    add_internal_force( bear::universe::force_type(-20000 * get_mass(), 0));
  else
    add_internal_force( bear::universe::force_type(20000 * get_mass(), 0) );
} // player::apply_swim_in_float()


/*----------------------------------------------------------------------------*/
/**
 * \brief Player swim up when he is in floating.
 */
void tunnel::player::apply_swim_up_in_float()
{
  add_internal_force( bear::universe::force_type(0, 2500 * get_mass()));
} // player::apply_swim_up_in_float()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player sink.
 */
void tunnel::player::apply_sink()
{
  m_move_force = s_move_force_in_swimming;
  set_state(sink_state);
  m_progress = &player::progress_sink;
} // player::apply_swimming()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action swim_up.
 *
 */
void tunnel::player::apply_swim_up()
{
  add_internal_force( bear::universe::force_type(0, 2000 * get_mass()) );
} // player::apply_swim_up()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action swim_down.
 *
 */
void tunnel::player::apply_swim_down()
{
  add_internal_force( bear::universe::force_type(0, -900 * get_mass()) );
} // player::apply_swim_down()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action swim_jump.
 *
 */
void tunnel::player::apply_swim_jump()
{
  if ( get_rendering_attributes().is_mirrored() )
    {
      if ( m_look_upward_time )
        add_internal_force
          ( get_mass() * bear::universe::force_type(-15000, 20000));
      else if ( m_status_crouch )
        add_internal_force
          ( get_mass() * bear::universe::force_type(-15000, -1000));
      else
        add_internal_force
          ( get_mass() * bear::universe::force_type(-20000, 15000));
    }
  else
    {
      if ( m_look_upward_time )
        add_internal_force
          ( get_mass() * bear::universe::force_type(15000, 20000));
      else if ( m_status_crouch )
        add_internal_force
          ( get_mass() * bear::universe::force_type(15000, -10000));
      else
        add_internal_force
          ( get_mass() * bear::universe::force_type(20000, 15000));
    }
} // player::apply_swim_jump()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action float.
 *
 */
void tunnel::player::apply_float()
{
  m_move_force = s_move_force_in_swimming;
  set_state(float_state);
  m_progress = &player::progress_float;
} // player::apply_float()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action dive.
 *
 */
void tunnel::player::apply_dive()
{
  add_internal_force( bear::universe::force_type(0, -2000*get_mass()));
} // player::apply_float()

/*----------------------------------------------------------------------------*/
/**
 * \brief Apply the action paralyze.
 * \param duration The duration of the paralysation.
 */
void tunnel::player::apply_paralyze(bear::universe::time_type duration)
{
  m_paralyze_duration = duration;
  set_state(player::paralyze_state);
  m_progress = &player::progress_paralyze;
  start_action_model("paralyze");
} // player::apply_paralyze()

/*---------------------------------------------------------------------------*/
/**
 * \brief Choose a wait state.
 */
void tunnel::player::choose_wait_state()
{
  if ( ( get_bottom_contact().get_max() >= 0.6 ) && 
       ( get_bottom_contact().get_min() <= 0.4 ) )
    {
      std::ostringstream s;
      s << "wait" << (rand() % m_wait_state_number + 1);
      start_action_model(s.str());
    }
} // player::choose_wait_state()

/*---------------------------------------------------------------------------*/
/**
 * \brief Choose an idle state.
 */
void tunnel::player::choose_idle_state()
{
  if ( get_bottom_contact().get_max() < 0.6 )
    {
      if ( get_rendering_attributes().is_mirrored() ) 
	start_action_model("unstable_backwards");
      else
	start_action_model("unstable_ahead");
    }
  else if ( get_bottom_contact().get_min() > 0.4 )
    {
      if ( get_rendering_attributes().is_mirrored() ) 
	start_action_model("unstable_ahead");
      else
	start_action_model("unstable_backwards");
    }
  else
    start_action_model("idle");
} // player::choose_idle_state()

/*---------------------------------------------------------------------------*/
/**
 * \brief Choose a walk state.
 */
void tunnel::player::choose_walk_state()
{
  start_action_model("walk");
} // player::choose_walk_state()

/*---------------------------------------------------------------------------*/
/**
 * \brief Get the force of vertical jump.
 */
bear::universe::coordinate_type
tunnel::player::get_vertical_jump_force() const
{
  return s_vertical_jump_force;
} // player::get_vertical_jump_force()

/*---------------------------------------------------------------------------*/
/**
 * \brief Progress in the water.
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::player::progress_in_water(bear::universe::time_type elapsed_time)
{
} // player::progress_in_water()

/*----------------------------------------------------------------------------*/
/**
 * \brief Give a string representation of the item.
 * \param str (out) The result of the convertion.
 */
void tunnel::player::to_string( std::string& str ) const
{
  std::ostringstream oss;

  super::to_string(str);

  oss << "state: ";
  oss << m_states[m_current_state]->get_name();
  oss << "\n";
  oss << "action: ";
  oss << get_current_action_name();
  oss << "\n";
  oss << "can_cling: " << m_can_cling << "\n";
  oss << "status_look_upward: " << m_status_look_upward << "\n";
  oss << "status_crouch: " << m_status_crouch << "\n";

  str += oss.str();
} // player::to_string()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::player::progress_walk( bear::universe::time_type elapsed_time )
{
  brake();

  if ( has_bottom_contact() )
    {
      if ( m_last_bottom_left == get_bottom_left() )
        choose_idle_state();
      else
        {
          bear::universe::speed_type speed( get_speed() );
          // calculate the speed in the intern axis
          bear::universe::coordinate_type speed_x =
            speed.dot_product(get_x_axis());

          if( std::abs(speed_x) >= s_speed_to_run )
            {
              if ( m_run_time >= s_time_to_run )
                start_action_model("run");
            }
          else if ( speed_x == 0 )
            choose_idle_state();
          else
            m_move_force = get_move_force_in_walk();
        }
    }
  else
    test_in_sky_or_swimm();
} // player::progress_walk()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::player::progress_idle( bear::universe::time_type elapsed_time )
{
  brake();

  if ( has_bottom_contact() )
    {
      m_run_time = 0;

      if ( ( m_state_time >= s_time_to_wait ) &&
           ( m_wait_state_number != 0 ) &&
           ( !is_a_marionette() ) &&
           m_authorized_action[player_action::wait] )
        choose_wait_state();
      else
        progress_continue_idle(elapsed_time);
    }
  else
    test_in_sky_or_swimm();
} // player::progress_idle()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration when the player stay in the state idle.
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::player::progress_continue_idle
( bear::universe::time_type elapsed_time )
{
  // do nothing
} // player::progress_continue_idle()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::player::progress_jump( bear::universe::time_type elapsed_time )
{
  if ( !test_bottom_contact() )
    {
      if ( is_only_in_environment(bear::universe::water_environment) )
        start_action_model("sink");
      else if ( is_in_floating() )
        start_action_model("float");
      else if( get_speed().y <= 0 )
        start_action_model("fall");
    }
} // player::progress_jump()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::player::progress_fall( bear::universe::time_type elapsed_time )
{
  if ( !test_bottom_contact() )
    {
      if ( is_only_in_environment(bear::universe::water_environment) )
        start_action_model("sink");
      else if ( is_in_floating() )
        start_action_model("float");
      if( get_speed().y > 0 )
        start_action_model("jump");
    }
} // player::progress_fall()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::player::progress_dead( bear::universe::time_type elapsed_time )
{
  regenerate();

  start_action_model("roar");
} // player::progress_dead()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::player::progress_game_over( bear::universe::time_type elapsed_time )
{
  set_status_look_upward(false);
  set_status_crouch(false);
} // player::progress_game_over()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::player::progress_roar( bear::universe::time_type elapsed_time )
{
  // do_nothing
} // player::progress_roar()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::player::progress_run( bear::universe::time_type elapsed_time )
{
  if ( has_bottom_contact() )
    {
      bear::universe::speed_type speed;
      speed = get_speed();

      // calculate the speed in the intern axis
      bear::universe::coordinate_type speed_x =
        speed.dot_product(get_x_axis());

      if( std::abs(speed_x) < s_speed_to_run )
        {
          if( speed_x == 0 )
            choose_idle_state();
          else
            choose_walk_state();
        }
    }
  else
    test_in_sky_or_swimm();
} // player::progress_run()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::player::progress_slap( bear::universe::time_type elapsed_time )
{
  brake();

  bear::universe::speed_type speed(get_speed());
  bear::universe::coordinate_type speed_x = speed.dot_product(get_x_axis());

  if ( get_current_action_name() == "slap" )
    {
      if ( std::abs(speed_x) != 0 )
        switch_to_model_action("slap_and_walk");
    }
  else if ( get_current_action_name() == "slap_and_walk")
    {
      if( std::abs(speed_x) == 0 )
        switch_to_model_action("slap");
    }

  if ( has_right_contact() )
    apply_move_right();
  else if ( has_left_contact() )
    apply_move_left();
} // player::progress_slap()


/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::player::progress_teleport( bear::universe::time_type elapsed_time )
{
} // player::progress_teleport()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::player::progress_start_jump( bear::universe::time_type elapsed_time )
{
  m_halo_animation->next(elapsed_time);

  brake();

  if ( !has_bottom_contact() )
    test_in_sky_or_swimm();
} // player::progress_start_jump()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::player::progress_vertical_jump
( bear::universe::time_type elapsed_time )
{
  if ( !test_bottom_contact() )
    if( get_speed().y <= 0 )
      start_action_model("fall");
} // player::progress_vertical_jump()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::player::progress_crouch( bear::universe::time_type elapsed_time )
{
  brake();

  if ( !has_bottom_contact() )
    test_in_sky_or_swimm();
} // player::progress_crouch()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::player::progress_look_upward( bear::universe::time_type elapsed_time )
{
  brake();

  if ( !has_bottom_contact() )
    test_in_sky_or_swimm();
} // player::progress_look_upward()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state captive.
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::player::progress_captive( bear::universe::time_type elapsed_time )
{
  // do nothing
} // player::progress_captive()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state paralyze.
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::player::progress_paralyze( bear::universe::time_type elapsed_time )
{
  if ( m_state_time >= m_paralyze_duration )
    choose_idle_state();
} // player::progress_paralyze()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::player::progress_throw( bear::universe::time_type elapsed_time )
{
  brake();

  bear::universe::speed_type speed(get_speed());
  bear::universe::coordinate_type speed_x = speed.dot_product(get_x_axis());

  if ( get_current_action_name() == "throw" )
    {
      if ( !has_bottom_contact() )
        switch_to_model_action("throw_and_fall");
      else if( std::abs(speed_x) != 0 )
        switch_to_model_action("throw_and_walk");
    }
  else if ( get_current_action_name() == "throw_and_walk")
    {
      if ( !has_bottom_contact() )
        switch_to_model_action("throw_and_fall");
      else if( std::abs(speed_x) == 0 )
        switch_to_model_action("throw");
    }
  else if ( get_current_action_name() == "throw_and_fall")
    {
      if ( has_bottom_contact() )
        {
          if( std::abs(speed_x) == 0 )
            switch_to_model_action("throw");
          else
            switch_to_model_action("throw_and_walk");
        }
    }
} // player::progress_throw()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::player::progress_maintain( bear::universe::time_type elapsed_time )
{
  brake();

  bear::universe::speed_type speed(get_speed());
  bear::universe::coordinate_type speed_x = speed.dot_product(get_x_axis());

  if ( get_current_action_name() == "maintain" )
    {
      if ( !has_bottom_contact() )
        switch_to_model_action("maintain_and_fall");
      else if( std::abs(speed_x) != 0 )
        switch_to_model_action("maintain_and_walk");
    }
  else if ( get_current_action_name() == "maintain_and_walk" )
    {
      if ( !has_bottom_contact() )
        switch_to_model_action("maintain_and_fall");
      else if( std::abs(speed_x) == 0 )
        switch_to_model_action("maintain");
    }
  else if ( get_current_action_name() == "maintain_and_fall" )
    {
      if ( has_bottom_contact() )
        {
          if( std::abs(speed_x) == 0 )
            switch_to_model_action("maintain");
          else
            switch_to_model_action("maintain_and_walk");
        }
    }
} // player::progress_maintain()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::player::progress_wait( bear::universe::time_type elapsed_time )
{
  brake();
  
  if ( !has_bottom_contact() )
    test_in_sky_or_swimm();
} // player::progress_wait()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::player::progress_start_cling
( bear::universe::time_type elapsed_time )
{
  if ( !test_bottom_contact() )
    {
      if ( ( !get_rendering_attributes().is_mirrored()
             && has_right_contact() ) ||
           ( get_rendering_attributes().is_mirrored() && has_left_contact() ) )
        {
          if ( m_can_cling )
            {
              m_cling_orientation = get_rendering_attributes().is_mirrored();
              start_action_model("cling");
            }
          else
            choose_idle_state();
        }
    }
} // player::progress_start_cling()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::player::progress_cling( bear::universe::time_type elapsed_time )
{
  if ( !test_bottom_contact() )
    {
      if ( has_top_contact() || ( !m_can_cling  ) )
        start_action_model("fall");
      else
        {
          get_rendering_attributes().mirror(m_cling_orientation);

          bear::universe::speed_type speed = get_speed();
          speed.x = 0;
          if ( speed.y > 0 )
            speed.y = 0;
          else
            speed.y *= 0.9;

          set_speed(speed);

          if ( get_layer().has_world() )
            {
              bear::universe::force_type force
                ( - get_mass() * get_layer().get_world().get_gravity() );

              if ( (get_density() != 0) &&
                   ( get_mass() != std::numeric_limits<double>::infinity() )  )
                force += get_layer().get_world().get_gravity() * get_mass() *
                  get_layer().get_world().get_average_density
                  (get_bounding_box()) / get_density();

              add_external_force(force);
            }
        }
    }
} // player::progress_cling()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::player::progress_clung_jump
( bear::universe::time_type elapsed_time )
{
  if ( !test_bottom_contact() )
    if( get_speed().y <= 0 )
      start_action_model("fall");
} // player::progress_clung_jump()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::player::progress_start_hang
( bear::universe::time_type elapsed_time )
{
  if ( !test_bottom_contact() )
    {
      if ( ( !get_rendering_attributes().is_mirrored() &&
             has_right_contact() ) ||
           ( get_rendering_attributes().is_mirrored() && has_left_contact() ) )
        start_action_model("hang");
      else
        if ( m_state_time >= s_max_time_to_hang )
          choose_idle_state();
    }
} // player::progress_start_hang()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::player::progress_hang( bear::universe::time_type elapsed_time )
{
  if ( !test_bottom_contact() )
    {
      if ( has_top_contact() )
        start_action_model("fall");
      else if ( get_layer().has_world() )
        add_external_force
          (- get_mass() * get_layer().get_world().get_gravity());
    }
} // player::progress_hang()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::player::progress_swimming( bear::universe::time_type elapsed_time )
{
  if ( !test_bottom_contact() )
    {
      if ( !is_only_in_environment(bear::universe::water_environment) )
        {
          if ( is_in_floating() )
            start_action_model("float");
          else if( get_speed().y <= 0 )
            start_action_model("fall");
          else
            start_action_model("jump");
        }
    }

  m_look_upward_time = 0;
  m_crouch_time = 0;
} // player::progress_swimming()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::player::progress_sink( bear::universe::time_type elapsed_time )
{
  if ( !test_bottom_contact() )
    {
      if ( !is_only_in_environment(bear::universe::water_environment) )
        {
          if ( is_in_floating() )
            start_action_model("float");
          else if( get_speed().y > 0 )
            start_action_model("jump");
          else
            start_action_model("fall");
        }
    }

  if ( get_current_action_name() == "sink" )
    {
      if ( m_status_crouch )
        get_action(get_current_action_name())->get_mark
          (get_mark_id("body")).get_animation()->set_time_factor(1.5);
      else if ( m_status_look_upward )
        get_action(get_current_action_name())->get_mark
          (get_mark_id("body")).get_animation()->set_time_factor(0.6);
      else
        get_action(get_current_action_name())->get_mark
          (get_mark_id("body")).get_animation()->set_time_factor(1);

    }

  m_look_upward_time = 0;
  m_crouch_time = 0;
} // player::progress_sink()

/*---------------------------------------------------------------------------*/
/**
 * \brief Do one iteration in the state .
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::player::progress_float( bear::universe::time_type elapsed_time )
{
  if ( !test_bottom_contact() )
    {
      if ( is_only_in_environment(bear::universe::water_environment) )
        {
          start_action_model("sink");
        }
      else if ( !is_in_floating() )
        {
          if( get_speed().y > 0 )
            start_action_model("jump");
          else
            start_action_model("fall");
        }
    }
} // player::progress_float()

/*----------------------------------------------------------------------------*/
/**
 * \brief Set the state of Player.
 */
void tunnel::player::set_state(player_state_name state)
{
  if ( state != m_current_state )
    {
      m_states[m_current_state]->stop();
      m_current_state = state;
      m_states[m_current_state]->start();
      m_state_time = 0;
    }
} // player::set_state()

/*----------------------------------------------------------------------------*/
/**
 * \brief Test if Player is crushed.
 */
bool tunnel::player::is_crushed() const
{
  return ( ( has_bottom_contact() && has_top_contact() ) ||
           ( has_right_contact() && has_left_contact() ) );
} // player::is_crushed()

/*----------------------------------------------------------------------------*/
/**
 * \brief Spawn the player after his death.
 * \todo Game over if the player has no more lifes.
 * \todo Update lifes and any other counters.
 */
void tunnel::player::regenerate()
{
  m_current_tag = m_initial_tag;
  update_layer_visibility();
  update_layer_activity();

  set_center_of_mass( m_saved_position );
  stop();

  m_last_visual_time = 0;
  m_last_visuals.clear();
  m_run_time = 0;
  m_can_cling = false;
  m_lazy = false;
  m_want_clung_jump = false;
  m_move_right = false;
  m_move_left = false;
  m_last_bottom_left = bear::universe::position_type(0, 0);
  get_rendering_attributes().mirror(false);

  remove_all_links();
} // player::regenerate()

/*----------------------------------------------------------------------------*/
/**
 * \brief Indicates if Player is in the water and in the air.
 */
bool tunnel::player::is_in_floating() const
{
  bool result = false;

  if ( get_layer().has_world() )
    {
      std::set<bear::universe::environment_type> environments;
      get_layer().get_world().get_environments
        (get_bounding_box(), environments);
      result =
        ( environments.find(bear::universe::water_environment)
          != environments.end() )
        && ( environments.size() >= 1 );
    }

  return result;
} // player::is_in_floatting()

/*----------------------------------------------------------------------------*/
/**
 * \brief Update the orientation.
 */
void tunnel::player::update_orientation()
{
  if ( get_current_action_name() != "captive" )
    {
      if ( get_speed().x < 0 )
        get_rendering_attributes().mirror(true);
      else if ( get_speed().x > 0 )
        get_rendering_attributes().mirror(false);
    }
} // player::update_orientation()

/*----------------------------------------------------------------------------*/
/**
 * \brief Stop to look up.
 */
void tunnel::player::do_stop_look_upward()
{
  m_status_look_upward = false;
  m_states[m_current_state]->do_stop_look_upward();
} // state_player::do_stop_look_upward()

/*----------------------------------------------------------------------------*/
/**
 * \brief Stop to crouch.
 */
void tunnel::player::do_stop_crouch()
{
  m_status_crouch = false;
  m_states[m_current_state]->do_stop_crouch();
} // state_player::do_stop_crouch()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress the spot.
 * \param elapsed_time Elapsed time since the last call.
 */
void tunnel::player::progress_spot( bear::universe::time_type elapsed_time )
{
  bool balance_x(true);
  bool balance_y(true);

  if ( m_status_look_upward )
    {
      m_look_upward_time += elapsed_time;

      if ( m_look_upward_time >= s_time_to_look_upward )
        {
          balance_y = false;
          add_spot_gap( bear::universe::position_type(0, 5) );
        }
    }

  if ( m_status_crouch )
    {
      m_crouch_time += elapsed_time;

      if ( m_crouch_time >= s_time_to_crouch )
        {
          balance_y = false;
          add_spot_gap( bear::universe::position_type(0, -5) );
        }
    }

  if ( get_speed().x > s_speed_to_run )
    {
      set_spot_maximum(200, 220);
      balance_x = false;
      add_spot_gap( bear::universe::position_type(3, 0) );
    }
  else if ( get_speed().x < -s_speed_to_run )
    {
      set_spot_minimum(-200, -250);
      balance_x = false;
      add_spot_gap( bear::universe::position_type(-3, 0) );
    }
  else if ( get_speed().x > ( s_speed_to_run / 2 ) )
    {
      set_spot_maximum(100, 220);
      balance_x = false;
      add_spot_gap( bear::universe::position_type(1, 0) );
    }
  else if ( get_speed().x < (- s_speed_to_run / 2) )
    {
      set_spot_minimum(-100, -250);
      balance_x = false;
      add_spot_gap( bear::universe::position_type(-1, 0) );
    }

  balance_spot(balance_x, balance_y);
} // player::progress_spot()

/*---------------------------------------------------------------------------*/
/**
 * \brief Stop the player (speed and force).
 */
void tunnel::player::stop()
{
  set_state(idle_state);
  choose_idle_state();
  set_speed( bear::universe::speed_type(0, 0) );
  set_internal_force(bear::universe::force_type(0, 0));
  set_external_force(bear::universe::force_type(0, 0));
} // player::stop()

/*---------------------------------------------------------------------------*/
/**
 * \brief Test if Player walk and change state thereof.
 *         Return true if Player walk.
 */
bool tunnel::player::test_walk()
{
  bool result = false;

  if ( has_bottom_contact() )
    {
      bear::universe::speed_type speed;
      speed = get_speed();
      // calculate the speed in the intern axis
      bear::universe::coordinate_type speed_x =
        speed.dot_product(get_x_axis());

      if( std::abs(speed_x) >= s_speed_to_run )
        {
          result = true;
          start_action_model("run");
        }
      else if ( ( speed_x != 0 ) &&
                ( get_bottom_left() != m_last_bottom_left ) )
        {
          result = true;
          choose_walk_state();
        }
    }

  return result;
} // player::test_walk()

/*---------------------------------------------------------------------------*/
/**
 * \brief Test if Player walk, run or is idle and change state thereof.
 *         Return true if Player has a bottom contact.
 */
bool tunnel::player::test_bottom_contact()
{
  bool result = false;

  if ( has_bottom_contact() )
    {
      bear::universe::speed_type speed;
      speed = get_speed();

      // calculate the speed in the intern axis
      bear::universe::coordinate_type speed_x =
        speed.dot_product(get_x_axis());

      if( std::abs(speed_x) >= s_speed_to_run )
        start_action_model("run");
      else if( speed_x != 0 )
        choose_walk_state();
      else
        choose_idle_state();

      result = true;
    }

  return result;
} // player::test_bottom_contact()

/*---------------------------------------------------------------------------*/
/**
 * \brief Test if Player is in the sky or swimm and change state thereof.
 *         Return true if Player is in the sky.
 */
bool tunnel::player::test_in_sky_or_swimm()
{
  bool result = false;

  if ( !has_bottom_contact() )
    {
      result = true;

      if ( is_only_in_environment(bear::universe::water_environment) )
        start_action_model("sink");
      else if ( is_in_floating() )
        start_action_model("float");
      else if( get_speed().y <= 0 )
        start_action_model("fall");
      else
        start_action_model("jump");
    }

  return result;
} // player::test_in_sky_or_swimm()

/*---------------------------------------------------------------------------*/
/**
 * \brief Brake on x axis if Player has no direction.
 */
void tunnel::player::brake()
{
  if ( !m_move_right && !m_move_left )
    {
      bear::universe::speed_type speed = get_speed();
      speed.x *= 0.9;
      set_speed(speed);
    }
  m_move_right = false;
  m_move_left = false;
} // player::brake()

/*----------------------------------------------------------------------------*/
/**
 * \brief Call shake with the arguments corresponding to a roar.
 */
void tunnel::player::roar_shake()
{
  shake(20, 1);
} // roar_shake()

/*----------------------------------------------------------------------------*/
/**
 * \brief Shake the camera.
 * \param force The force of the shaker.
 * \param duration The duration of the shaker.
 */
void tunnel::player::shake(double force, bear::universe::time_type duration) const
{
  bear::camera_shaker::shake_around( *this, force, duration );
} // player::shake()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render halos.
 * \param visuals (out) The sprites of the item, and their positions.
 */
void tunnel::player::render_halos
( std::list<bear::engine::scene_visual>& visuals ) const
{
  render_jump_halo(visuals);
} // player::render_halos()

/*----------------------------------------------------------------------------*/
/**
 * \brief Render jump halo.
 * \param visuals (out) The sprites of the item, and their positions.
 */
void tunnel::player::render_jump_halo
( std::list<bear::engine::scene_visual>& visuals ) const
{
  if ( m_current_state == player::start_jump_state )
    {
      bear::universe::size_type height
        ( s_max_halo_height * (m_state_time / s_time_to_jump) );

      bear::visual::sprite current_sprite(m_halo_animation->get_sprite());
      current_sprite.set_height((unsigned int)height);
      current_sprite.set_angle
        ( current_sprite.get_angle() + get_visual_angle() );

      visuals.push_front
        ( bear::engine::scene_visual
          ( get_bottom_middle().x - current_sprite.width() / 2,
            get_bottom(),
            current_sprite, get_z_position()+1 ) );
    }
} // player::render_jump_halo()

/*----------------------------------------------------------------------------*/
/**
 * \brief Get the sprite representing the item without invincible visuals.
 * \param visuals (out) The sprites of the item, and their positions.
 */
void
tunnel::player::get_visuals_without_invincibility
( std::list<bear::engine::scene_visual>& visuals ) const
{
  super::get_visual(visuals);

  render_halos(visuals);
} // player::get_visuals_without_invincibility()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player starts to take a new hat.
 */
void tunnel::player::start_take_hat()
{
  if ( !m_has_hat )
    {
      if ( is_in_environment(bear::universe::water_environment) )
        set_global_substitute
          ("new_hat", new bear::visual::animation
           (get_level_globals().get_animation
            ("animation/plee/bath-cap.canim") ) );
      else
        set_global_substitute
            ("new_hat", new bear::visual::animation
             (get_level_globals().get_animation("animation/plee/cap.canim")) );
    }
  else if ( ( !m_has_main_hat ) &&
            ( !is_in_environment(bear::universe::water_environment) ) )
    set_global_substitute
        ("new_hat", new bear::visual::animation
         ( get_level_globals().get_animation("animation/plee/cap.canim") ) );
  else
    set_global_substitute("new_hat", new bear::visual::animation() );
} // player::start_take_hat()

/*----------------------------------------------------------------------------*/
/**
 * \brief Player takes a new hat.
 */
void tunnel::player::take_new_hat()
{
  if ( !m_has_hat )
    {
      m_has_hat = true;

      if ( is_in_environment(bear::universe::water_environment) )
        set_global_substitute
          ("hat", new bear::visual::animation
           (get_level_globals().get_animation
            ("animation/plee/bath-cap.canim") ) );
      else
        {
          m_has_main_hat = true;
          set_global_substitute
            ("hat", new bear::visual::animation
             (get_level_globals().get_animation("animation/plee/cap.canim")) );
        }
    }
  else if ( ( !m_has_main_hat ) &&
            ( !is_in_environment(bear::universe::water_environment) ) )
    {
      m_has_main_hat = true;
      m_has_hat = true;
      set_global_substitute
        ("hat", new bear::visual::animation
         ( get_level_globals().get_animation("animation/plee/cap.canim") ) );
    }
} // player::take_new_hat()

/*----------------------------------------------------------------------------*/
/**
 * \brief Take out the hat.
 */
void tunnel::player::take_out_hat()
{
  bear::engine::model_mark_placement m;

  if ( get_mark_placement("hat", m) )
    {
      m_has_main_hat = false;
      m_has_hat = false;

      bear::universe::position_type pos( m.get_position() );
      bear::decorative_item* item;
      item = new bear::decorative_item();

      bear::visual::sprite spr =
        get_action(get_current_action_name())->get_mark
        (m.get_mark_id()).get_main_animation()->get_sprite();

      spr.combine( get_rendering_attributes() );
      item->set_sprite(spr);

      item->set_z_position(get_z_position() + m.get_depth_position());
      item->set_phantom(false);
      item->set_can_move_items(false);
      item->set_artificial(true);
      item->set_kill_when_leaving(true);
      item->set_density(0.4);
      item->set_mass(2);

      new_item( *item );

      item->set_center_of_mass(pos);

      set_global_substitute
        ("hat", new bear::visual::animation() );
    }
} // player::take_out_hat()

/*---------------------------------------------------------------------------*/
/**
 * \brief Get the right force in walk state.
 */
bear::universe::coordinate_type
tunnel::player::get_move_force_in_walk() const
{
  return s_move_force_min_in_walk +
    std::min(m_run_time, s_time_to_run)*
    (s_move_force_max_in_walk - s_move_force_min_in_walk)
    / s_time_to_run;
  
  /*
    return s_move_force_min_in_walk +
    std::min(m_run_time, s_time_to_run)*
    (s_move_force_max_in_walk - s_move_force_min_in_walk)
    / s_time_to_run;
  */
} // player::get_move_force_in_walk()

/*---------------------------------------------------------------------------*/
/**
 * \brief Update visibility of layer.
 */
void tunnel::player::update_layer_visibility()
{
  bear::engine::level::layer_iterator it = get_level().layer_begin();

  for ( ; it != get_level().layer_end(); ++it )
    if ( it->get_tag().empty() )
      it->set_visible(true);
    else 
      it->set_visible( it->get_tag() == m_tags[m_current_tag] ); 
} // player::update_layer_visibility()

/*---------------------------------------------------------------------------*/
/**
 * \brief Update activity of layer.
 */
void tunnel::player::update_layer_activity()
{
  bear::engine::level::layer_iterator it = get_level().layer_begin();

  for ( ; it != get_level().layer_end(); ++it )
    if ( it->get_tag().empty() )
      it->set_active(true);
    else 
      it->set_active( it->get_tag() == m_tags[m_current_tag] );    
} // player::update_layer_activity()

/*----------------------------------------------------------------------------*/
/**
 * \brief Test if the player can teleport in a given tag.
 */
bool tunnel::player::check_can_teleport( unsigned int tag ) const
{
  bool result = false;
  
  bear::engine::level::layer_iterator it = get_level().layer_begin();
  
  for ( it = get_level().layer_begin(); 
        it != get_level().layer_end() && ! result ; ++it )
    {
      // TODO Ajouter test de collision
      if ( it->get_tag() == m_tags[tag] && it->has_world() )
        result = true;
    }

  return result;
} //player::check_can_teleport()

/*----------------------------------------------------------------------------*/
/**
 * \brief Update shaders.
 */
void tunnel::player::update_shaders()
{  
  bear::engine::level::layer_iterator it = get_level().layer_begin();

  // shaders
  for ( it = get_level().layer_begin(); it != get_level().layer_end(); ++it )
    if ( it->get_tag() == m_tags[m_next_tag] )
      {
        if ( it->has_world() )
          {
            bear::layer_shader * s = new bear::layer_shader();
            it->add_item(*s);
            s->set_kill_delay(0.5);
            s->add_layer_tag(m_tags[m_next_tag]);
            s->set_shader_file("shader/tunnel_target.frag");
          }
      }
    else if ( it->get_tag() == m_tags[m_current_tag] )
      {
        if ( it->has_world() )
          {
            bear::layer_shader * s = new bear::layer_shader();
            it->add_item(*s);
            s->set_kill_delay(0.5);
            s->add_layer_tag(m_tags[m_current_tag]);
            s->set_shader_file("shader/tunnel_origin.frag");
          }
      }
    else
      {
        bear::layer_shader * s = new bear::layer_shader();
        it->add_item(*s);
        s->set_kill_delay(0.4);
        s->set_shader_file("shader/tunnel_common.frag");
      }
} // player::update_shaders()

/*----------------------------------------------------------------------------*/
/**
 * \brief Teleport in new layer.
 */
void tunnel::player::teleport_in_new_layer()
{
  bear::engine::level::layer_iterator it = get_level().layer_begin();

  for ( it = get_level().layer_begin(); it != get_level().layer_end(); ++it )
    if ( it->get_tag() == m_tags[m_current_tag] && it->has_world() )
      {
        bear::universe::item_handle item = get_level().get_camera();
        if ( item != bear::universe::item_handle(NULL) )
          {
            //get_layer().drop_item(*(bear::engine::base_item*)(item.get()));
            //it->add_item(*(bear::engine::base_item*)(item.get()));
          }

        
        get_layer().drop_item(*this);
        it->add_item(*this);
      }
} // player::teleport_in_new_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Teleports the player in the target layer.
 */
void tunnel::player::on_level_progress_done()
{
  update_shaders();

  m_current_tag = m_next_tag;

  update_layer_visibility();
  update_layer_activity();
      
  teleport_in_new_layer();

  m_level_progress_done.disconnect();
} // player::on_level_progress_done()

/*----------------------------------------------------------------------------*/
/**
 * \brief Export the methods of the class.
 */
void tunnel::player::init_exported_methods()
{
  TEXT_INTERFACE_CONNECT_METHOD_0( player, take_new_hat, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, start_take_hat, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_roar, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_disappear, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_game_over, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_captive, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_crouch, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_fall, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_float, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_idle, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_jump, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_look_upward, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_run, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_sink, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_slap, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_open_tunnel, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_teleport, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_attack, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_start_cling, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_start_hang, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_cling, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_hang, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_clung_jump, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_start_jump, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_swimming, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_vertical_jump, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_wait, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_walk, void );
  TEXT_INTERFACE_CONNECT_METHOD_1
    ( player, apply_paralyze, void, bear::universe::time_type );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_swim_jump, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_swim_in_float, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, apply_swim_up_in_float, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, roar_shake, void );

  TEXT_INTERFACE_CONNECT_METHOD_0( player, save_current_position, void );

  TEXT_INTERFACE_CONNECT_METHOD_1
    ( player, authorize_action, void, const std::string& );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, authorize_all_actions, void );
  TEXT_INTERFACE_CONNECT_METHOD_0( player, disable_all_actions, void );
} // player::init_exported_methods()

/*----------------------------------------------------------------------------*/
TEXT_INTERFACE_IMPLEMENT_METHOD_LIST( tunnel::player )
