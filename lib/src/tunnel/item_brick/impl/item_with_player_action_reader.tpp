/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the tunnel::item_with_player_action_reader class.
 * \author Sebastien Angibaud
 */

#include "tunnel/controller_config.hpp"
#include "tunnel/game_variables.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
template<class Base>
tunnel::item_with_player_action_reader<Base>::item_with_player_action_reader()
  : m_date(0), m_delay(0.045)
{

} // item_with_player_action_reader::item_with_player_action_reader()
/*----------------------------------------------------------------------------*/
/**
 * \brief Add a pending action in the list.
 * \param a The action to push back.
 */
template<class Base>
void tunnel::item_with_player_action_reader<Base>::add_pending_action
( const player_pending_action & a)
{
  m_pending_actions.push_back(a); 
} // item_with_player_action_reader::add_pending_action

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress input actions.
 * \param elapsed_time Elapsed time since the last call.
 */
template<class Base>
void tunnel::item_with_player_action_reader<Base>::progress_input_actions
( bear::universe::time_type elapsed_time )
{
  m_date += elapsed_time;

  this->read_input_action(elapsed_time);

  pop_actions(true);
} // item_with_player_action_reader::progress_input_actions()

/*----------------------------------------------------------------------------*/
/**
 * \brief Progress input actions without send actions.
 * \param elapsed_time Elapsed time since the last call.
 */
template<class Base>
void tunnel::item_with_player_action_reader<Base>::dummy_progress_input_actions
( bear::universe::time_type elapsed_time )
{
  m_date += elapsed_time;
  
  this->read_input_action(elapsed_time);

  pop_actions(false);
} // item_with_player_action_reader::dummy_progress_input_actions()

/*----------------------------------------------------------------------------*/
/**
 * \brief Start an action asked by the human player.
 * \param player_index The index of the player asking the action.
 * \param a The action.
 */
template<class Base>
void tunnel::item_with_player_action_reader<Base>::start_action
( unsigned int player_index, player_action::value_type a )
{
  // nothing to do
} // item_with_player_action_reader::start_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Continue an action asked by the human player.
 * \param elapsed_time How long the action is done.
 * \param player_index The index of the player asking the action.
 * \param a The action.
 */
template<class Base>
void tunnel::item_with_player_action_reader<Base>::do_action
( bear::universe::time_type elapsed_time, unsigned int player_index,
  player_action::value_type a )
{
  // nothing to do
} // item_with_player_action_reader::do_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Stop an action asked by the human player.
 * \param player_index The index of the player asking the action.
 * \param a The action.
 */
template<class Base>
void tunnel::item_with_player_action_reader<Base>::stop_action
 ( unsigned int player_index, player_action::value_type a )
{
  // nothing to do
} // item_with_player_action_reader::stop_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Read input actions without send actions.
 * \param elapsed_time Elapsed time since the last call.
 */
template<class Base>
void tunnel::item_with_player_action_reader<Base>::read_input_action
(bear::universe::time_type elapsed_time)
{
  this->progress_input_reader(elapsed_time);
} // item_with_player_action_reader::read_input_action()

/*----------------------------------------------------------------------------*/
/**
 * \brief Pop actions.
 * \param send_action Indicates if actions must be send.
 */
template<class Base>
void tunnel::item_with_player_action_reader<Base>::pop_actions
 ( bool send_action )
{
  bool ok(true);

  while(ok)
    {
      ok = false; 
      if ( ! m_pending_actions.empty() )
	//if ( m_date - m_pending_actions.front().date >= m_delay )
	  {
	    if ( send_action )
	      {
		if ( m_pending_actions.front().pending_type == 
		     player_pending_action::start_action ) 
		  start_action
		    ( m_pending_actions.front().player_index,
		      m_pending_actions.front().action );
		else if ( m_pending_actions.front().pending_type == 
			  player_pending_action::stop_action ) 
		  stop_action
		    ( m_pending_actions.front().player_index,
		      m_pending_actions.front().action );
		else if ( m_pending_actions.front().pending_type == 
			  player_pending_action::do_action ) 
		  do_action
		    ( m_pending_actions.front().duration,
		      m_pending_actions.front().player_index,
		      m_pending_actions.front().action );
	      }
	    
	    m_pending_actions.pop_front();
	    ok = true;
	  }
    }
} // item_with_player_action_reader::pop_actions()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell the player to start the action associated with a keyboard key.
 * \param key The code of the key.
 */
template<class Base>
bool tunnel::item_with_player_action_reader<Base>::key_pressed
( const bear::input::key_info& key )
{
  bool result = false;
  
  // To change if there is more players
  const unsigned int m( 1 );
  controller_config cfg;

  for ( unsigned int i=1; i<=m; ++i )
    {
      const player_action::value_type action =
        cfg.get_layout(i).get_action_from_key(key.get_code());

      if ( action != player_action::action_null )
        {
          result = true;
	  m_pending_actions.push_back
	    ( player_pending_action
	      (player_pending_action::start_action,m_date,i,action,0) );
        }
    }

  return result;
} // item_with_player_action_reader::key_pressed()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell the player to stop the action associated with a keyboard key.
 * \param key The code of the key.
 */
template<class Base>
bool tunnel::item_with_player_action_reader<Base>::key_released
( const bear::input::key_info& key )
{
  bool result = false;

  // To change if there is more players
  const unsigned int m( 1 );
  controller_config cfg;

  for ( unsigned int i=1; i<=m; ++i )
    {
      const player_action::value_type action =
        cfg.get_layout(i).get_action_from_key(key.get_code());

      if ( action != player_action::action_null )
        {
          result = true;
          m_pending_actions.push_back
	    ( player_pending_action
	      (player_pending_action::stop_action,m_date,i,action,0) );
        }
    }

  return result;
} // item_with_player_action_reader::key_released()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell the player to continue the action associated with a keyboard key.
 * \param elapsed_time How long the action is done.
 * \param key The code of the key.
 */
template<class Base>
bool tunnel::item_with_player_action_reader<Base>::key_maintained
( bear::universe::time_type elapsed_time,
  const bear::input::key_info& key )
{
  bool result = false;
  
  // To change if there is more players
  const unsigned int m( 1 );
  controller_config cfg;

  for ( unsigned int i=1; i<=m; ++i )
    {
      const player_action::value_type action =
        cfg.get_layout(i).get_action_from_key(key.get_code());

      if ( action != player_action::action_null )
        {
          result = true;
          m_pending_actions.push_back
	    ( player_pending_action
	      (player_pending_action::do_action,m_date,i,action,elapsed_time));
        }
    }

  return result;
} // item_with_player_action_reader::key_maintained()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell the player to start the action associated with a joystick button.
 * \param button The code of the button.
 * \param joy_index The index of the joystick.
 */
template<class Base>
bool tunnel::item_with_player_action_reader<Base>::button_pressed
( bear::input::joystick::joy_code button, unsigned int joy_index )
{
  bool result = false;

  // To change if there is more players
  const unsigned int m( 1 );
  controller_config cfg;

  for ( unsigned int i=1; i<=m; ++i )
    {
      const player_action::value_type action =
        cfg.get_layout(i).get_action_from_joystick(joy_index, button);

      if ( action != player_action::action_null )
        {
          result = true;
           m_pending_actions.push_back
	     ( player_pending_action
	       (player_pending_action::start_action,m_date,i,action,0));
        }
    }

  return result;
} // item_with_player_action_reader::button_pressed()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell the player to stop the action associated with a joystick button.
 * \param button The code of the button.
 * \param joy_index The index of the joystick.
 */
template<class Base>
bool tunnel::item_with_player_action_reader<Base>::button_released
( bear::input::joystick::joy_code button, unsigned int joy_index )
{
  bool result = false;
  
  // To change if there is more players
  const unsigned int m( 1 );
  controller_config cfg;

  for ( unsigned int i=1; i<=m; ++i )
    {
      const player_action::value_type action =
        cfg.get_layout(i).get_action_from_joystick(joy_index, button);

      if ( action != player_action::action_null )
        {
          result = true;
          m_pending_actions.push_back
	    ( player_pending_action
	      (player_pending_action::stop_action,m_date,i,action,0) );
        }
    }

  return result;
} // item_with_player_action_reader::button_released()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell the player to continue the action associated with a joystick
 *        button.
 * \param elapsed_time How long the action is done.
 * \param button The code of the button.
 * \param joy_index The index of the joystick.
 */
template<class Base>
bool tunnel::item_with_player_action_reader<Base>::button_maintained
( bear::universe::time_type elapsed_time,
 bear::input::joystick::joy_code button, unsigned int joy_index )
{
  bool result = false;
  
  // To change if there is more players
  const unsigned int m( 1 );
  controller_config cfg;
 
  for ( unsigned int i=1; i<=m; ++i )
    {
      const player_action::value_type action =
        cfg.get_layout(i).get_action_from_joystick(joy_index, button);

      if ( action != player_action::action_null )
        {
          result = true;
	  m_pending_actions.push_back
	    ( player_pending_action
	      (player_pending_action::do_action,m_date,i,action,elapsed_time));
        }
    }

  return result;
} // item_with_player_action_reader::button_maintained()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell the player to start the action associated with a mouse button.
 * \param button The code of the button.
 * \param pos The position of the cursor on the screen.
 */
template<class Base>
bool tunnel::item_with_player_action_reader<Base>::mouse_pressed
( bear::input::mouse::mouse_code button,
  const claw::math::coordinate_2d<unsigned int>& pos )
{
  bool result = false;
  
  // To change if there is more players
  const unsigned int m( 1 );
  controller_config cfg;

  for ( unsigned int i=1; i<=m; ++i )
    {
      const player_action::value_type action =
        cfg.get_layout(i).get_action_from_mouse(button);

      if ( action != player_action::action_null )
        {
          result = true;
           m_pending_actions.push_back
	     ( player_pending_action
	       (player_pending_action::start_action,m_date,i,action,0));
        }
    }

  return result;
} // item_with_player_action_reader::mouse_pressed()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell the player to stop the action associated with a mouse button.
 * \param button The code of the button.
 * \param pos The position of the cursor on the screen.
 */
template<class Base>
bool tunnel::item_with_player_action_reader<Base>::mouse_released
( bear::input::mouse::mouse_code button,
  const claw::math::coordinate_2d<unsigned int>& pos )
{
  bool result = false;
  
  // To change if there is more players
  const unsigned int m( 1 );
  controller_config cfg;

  for ( unsigned int i=1; i<=m; ++i )
    {
      const player_action::value_type action =
        cfg.get_layout(i).get_action_from_mouse(button);

      if ( action != player_action::action_null )
        {
          result = true;
          m_pending_actions.push_back
	    ( player_pending_action
	      (player_pending_action::stop_action,m_date,i,action,0) );
        }
    }

  return result;
} // item_with_player_action_reader::mouse_released()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tell the player to continue the action associated with a mouse button.
 * \param elapsed_time How long the action is done.
 * \param button The code of the button.
 * \param pos The position of the cursor on the screen.
 */
template<class Base>
bool tunnel::item_with_player_action_reader<Base>::mouse_maintained
( bear::universe::time_type elapsed_time,
  bear::input::mouse::mouse_code button,
  const claw::math::coordinate_2d<unsigned int>& pos )
{
  bool result = false;
  
  // To change if there is more players
  const unsigned int m( 1 );
  controller_config cfg;

  for ( unsigned int i=1; i<=m; ++i )
    {
      const player_action::value_type action =
        cfg.get_layout(i).get_action_from_mouse(button);

      if ( action != player_action::action_null )
        {
          result = true;
           m_pending_actions.push_back
	    ( player_pending_action
	      (player_pending_action::do_action,m_date,i,action,elapsed_time));
        }
    }

  return result;
} // item_with_player_action_reader::mouse_maintained()
