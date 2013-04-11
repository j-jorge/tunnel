/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file player_proxy.cpp
 * \brief Automatically generated implementation for tunnel::player_proxy.
 */
#include "tunnel/player_proxy.hpp"

/*
                                  WARNING
                 *** This file is automatically generated. ***
             *** Do not edit. All changes will be overwritten. ***
*/

#include "tunnel/player.hpp"

tunnel::player_proxy::player_proxy()
: m_player(NULL)
{

}

tunnel::player_proxy::player_proxy( player* p )
: m_player(p)
{

}

tunnel::player_proxy::player_proxy( bear::universe::physical_item* p )
: m_player( dynamic_cast<player*>(p) )
{

}

bool tunnel::player_proxy::operator==( player* p ) const
{
  return m_player == p;
}

bool tunnel::player_proxy::operator!=( player* p ) const
{
  return m_player != p;
}

bool tunnel::player_proxy::operator==( const player_proxy& that ) const
{
  return m_player == that.m_player;
}

bool tunnel::player_proxy::operator!=( const player_proxy& that ) const
{
  return m_player != that.m_player;
}

tunnel::player* tunnel::player_proxy::get_player_instance() const
{
  return m_player;
}

bear::universe::coordinate_type tunnel::player_proxy::get_vertical_jump_force() const
{
  // Automatically generated. Do not edit this file.
  return m_player->get_vertical_jump_force();
}

bear::universe::position_type tunnel::player_proxy::hot_spot() const
{
  // Automatically generated. Do not edit this file.
  return m_player->hot_spot();
}

bool tunnel::player_proxy::get_status_crouch() const
{
  // Automatically generated. Do not edit this file.
  return m_player->get_status_crouch();
}

bool tunnel::player_proxy::get_status_look_upward() const
{
  // Automatically generated. Do not edit this file.
  return m_player->get_status_look_upward();
}

bool tunnel::player_proxy::is_a_marionette() const
{
  // Automatically generated. Do not edit this file.
  return m_player->is_a_marionette();
}

bool tunnel::player_proxy::is_clung() const
{
  // Automatically generated. Do not edit this file.
  return m_player->is_clung();
}

bool tunnel::player_proxy::set_u_integer_field( const std::string& name, unsigned int value ) const
{
  // Automatically generated. Do not edit this file.
  return m_player->set_u_integer_field(name,value);
}

bool tunnel::player_proxy::want_clung_jump() const
{
  // Automatically generated. Do not edit this file.
  return m_player->want_clung_jump();
}

double tunnel::player_proxy::get_jump_time_ratio() const
{
  // Automatically generated. Do not edit this file.
  return m_player->get_jump_time_ratio();
}

void tunnel::player_proxy::add_spot_gap( const bear::universe::position_type& gap ) const
{
  // Automatically generated. Do not edit this file.
  m_player->add_spot_gap(gap);
}

void tunnel::player_proxy::apply_attack() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_attack();
}

void tunnel::player_proxy::apply_captive() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_captive();
}

void tunnel::player_proxy::apply_cling() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_cling();
}

void tunnel::player_proxy::apply_clung_jump() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_clung_jump();
}

void tunnel::player_proxy::apply_continue_jump() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_continue_jump();
}

void tunnel::player_proxy::apply_crouch() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_crouch();
}

void tunnel::player_proxy::apply_die() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_die();
}

void tunnel::player_proxy::apply_disappear() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_disappear();
}

void tunnel::player_proxy::apply_dive() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_dive();
}

void tunnel::player_proxy::apply_fall() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_fall();
}

void tunnel::player_proxy::apply_float() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_float();
}

void tunnel::player_proxy::apply_game_over() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_game_over();
}

void tunnel::player_proxy::apply_hang() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_hang();
}

void tunnel::player_proxy::apply_idle() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_idle();
}

void tunnel::player_proxy::apply_impulse_jump() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_impulse_jump();
}

void tunnel::player_proxy::apply_jump() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_jump();
}

void tunnel::player_proxy::apply_look_upward() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_look_upward();
}

void tunnel::player_proxy::apply_move_left() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_move_left();
}

void tunnel::player_proxy::apply_move_right() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_move_right();
}

void tunnel::player_proxy::apply_paralyze(bear::universe::time_type duration) const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_paralyze(duration);
}

void tunnel::player_proxy::apply_release() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_release();
}

void tunnel::player_proxy::apply_roar() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_roar();
}

void tunnel::player_proxy::apply_run() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_run();
}

void tunnel::player_proxy::apply_sink() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_sink();
}

void tunnel::player_proxy::apply_slap() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_slap();
}

void tunnel::player_proxy::apply_start_cling() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_start_cling();
}

void tunnel::player_proxy::apply_start_hang() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_start_hang();
}

void tunnel::player_proxy::apply_start_jump() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_start_jump();
}

void tunnel::player_proxy::apply_swim_down() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_swim_down();
}

void tunnel::player_proxy::apply_swim_in_float() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_swim_in_float();
}

void tunnel::player_proxy::apply_swim_jump() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_swim_jump();
}

void tunnel::player_proxy::apply_swimming() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_swimming();
}

void tunnel::player_proxy::apply_swim_up() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_swim_up();
}

void tunnel::player_proxy::apply_swim_up_in_float() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_swim_up_in_float();
}

void tunnel::player_proxy::apply_vertical_jump() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_vertical_jump();
}

void tunnel::player_proxy::apply_wait() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_wait();
}

void tunnel::player_proxy::apply_walk() const
{
  // Automatically generated. Do not edit this file.
  m_player->apply_walk();
}

void tunnel::player_proxy::authorize_action( const std::string& a ) const
{
  // Automatically generated. Do not edit this file.
  m_player->authorize_action(a);
}

void tunnel::player_proxy::authorize_all_actions() const
{
  // Automatically generated. Do not edit this file.
  m_player->authorize_all_actions();
}

void tunnel::player_proxy::balance_spot( bool x, bool y ) const
{
  // Automatically generated. Do not edit this file.
  m_player->balance_spot(x,y);
}

void tunnel::player_proxy::choose_idle_state() const
{
  // Automatically generated. Do not edit this file.
  m_player->choose_idle_state();
}

void tunnel::player_proxy::choose_wait_state() const
{
  // Automatically generated. Do not edit this file.
  m_player->choose_wait_state();
}

void tunnel::player_proxy::choose_walk_state() const
{
  // Automatically generated. Do not edit this file.
  m_player->choose_walk_state();
}

void tunnel::player_proxy::disable_all_actions() const
{
  // Automatically generated. Do not edit this file.
  m_player->disable_all_actions();
}

void tunnel::player_proxy::do_action( bear::universe::time_type elapsed_time, player_action::value_type a ) const
{
  // Automatically generated. Do not edit this file.
  m_player->do_action(elapsed_time,a);
}

void tunnel::player_proxy::do_start_crouch() const
{
  // Automatically generated. Do not edit this file.
  m_player->do_start_crouch();
}

void tunnel::player_proxy::do_start_look_upward() const
{
  // Automatically generated. Do not edit this file.
  m_player->do_start_look_upward();
}

void tunnel::player_proxy::get_visual( std::list<bear::engine::scene_visual>& visuals ) const
{
  // Automatically generated. Do not edit this file.
  m_player->get_visual(visuals);
}

void tunnel::player_proxy::on_enters_layer() const
{
  // Automatically generated. Do not edit this file.
  m_player->on_enters_layer();
}

void tunnel::player_proxy::pre_cache() const
{
  // Automatically generated. Do not edit this file.
  m_player->pre_cache();
}

void tunnel::player_proxy::progress( bear::universe::time_type elapsed_time ) const
{
  // Automatically generated. Do not edit this file.
  m_player->progress(elapsed_time);
}

void tunnel::player_proxy::save_current_position() const
{
  // Automatically generated. Do not edit this file.
  m_player->save_current_position();
}

void tunnel::player_proxy::save_position( const bear::universe::position_type& p ) const
{
  // Automatically generated. Do not edit this file.
  m_player->save_position(p);
}

void tunnel::player_proxy::set_authorized_action(player_action::value_type a, bool value) const
{
  // Automatically generated. Do not edit this file.
  m_player->set_authorized_action(a,value);
}

void tunnel::player_proxy::set_can_cling(bool status) const
{
  // Automatically generated. Do not edit this file.
  m_player->set_can_cling(status);
}

void tunnel::player_proxy::set_marionette( bool b) const
{
  // Automatically generated. Do not edit this file.
  m_player->set_marionette(b);
}

void tunnel::player_proxy::set_spot_balance_move( bear::universe::coordinate_type x, bear::universe::coordinate_type y ) const
{
  // Automatically generated. Do not edit this file.
  m_player->set_spot_balance_move(x,y);
}

void tunnel::player_proxy::set_spot_maximum( bear::universe::coordinate_type x, bear::universe::coordinate_type y ) const
{
  // Automatically generated. Do not edit this file.
  m_player->set_spot_maximum(x,y);
}

void tunnel::player_proxy::set_spot_minimum( bear::universe::coordinate_type x, bear::universe::coordinate_type y ) const
{
  // Automatically generated. Do not edit this file.
  m_player->set_spot_minimum(x,y);
}

void tunnel::player_proxy::set_status_crouch(bool status) const
{
  // Automatically generated. Do not edit this file.
  m_player->set_status_crouch(status);
}

void tunnel::player_proxy::set_status_look_upward(bool status) const
{
  // Automatically generated. Do not edit this file.
  m_player->set_status_look_upward(status);
}

void tunnel::player_proxy::set_want_clung_jump(bool status) const
{
  // Automatically generated. Do not edit this file.
  m_player->set_want_clung_jump(status);
}

void tunnel::player_proxy::start_action_model(const std::string& action) const
{
  // Automatically generated. Do not edit this file.
  m_player->start_action_model(action);
}

void tunnel::player_proxy::start_action( player_action::value_type a ) const
{
  // Automatically generated. Do not edit this file.
  m_player->start_action(a);
}

void tunnel::player_proxy::stop_action( player_action::value_type a ) const
{
  // Automatically generated. Do not edit this file.
  m_player->stop_action(a);
}

void tunnel::player_proxy::stop() const
{
  // Automatically generated. Do not edit this file.
  m_player->stop();
}

void tunnel::player_proxy::update_throw_time_ratio() const
{
  // Automatically generated. Do not edit this file.
  m_player->update_throw_time_ratio();
}

bear::engine::level& tunnel::player_proxy::get_level() const
{
  // Automatically generated. Do not edit this file.
  return m_player->get_level();
}

bear::engine::level_globals& tunnel::player_proxy::get_level_globals() const
{
  // Automatically generated. Do not edit this file.
  return m_player->get_level_globals();
}

bool tunnel::player_proxy::has_owner() const
{
  // Automatically generated. Do not edit this file.
  return m_player->has_owner();
}

const bear::universe::world& tunnel::player_proxy::get_owner() const
{
  // Automatically generated. Do not edit this file.
  return m_player->get_owner();
}

bear::visual::bitmap_rendering_attributes tunnel::player_proxy::get_rendering_attributes() const
{
  // Automatically generated. Do not edit this file.
  return m_player->get_rendering_attributes();
}

void tunnel::player_proxy::set_auto_mirror( bool b )
{
  // Automatically generated. Do not edit this file.
  m_player->set_auto_mirror(b);
}

bool tunnel::player_proxy::has_bottom_contact() const
{
  // Automatically generated. Do not edit this file.
  return m_player->has_bottom_contact();
}

bear::universe::position_type tunnel::player_proxy::get_center_of_mass() const
{
  // Automatically generated. Do not edit this file.
  return m_player->get_center_of_mass();
}

bear::universe::position_type tunnel::player_proxy::get_bottom_middle() const
{
  // Automatically generated. Do not edit this file.
  return m_player->get_bottom_middle();
}

bear::universe::position_type tunnel::player_proxy::get_top_left() const
{
  // Automatically generated. Do not edit this file.
  return m_player->get_top_left();
}

bear::universe::position_type tunnel::player_proxy::get_top_right() const
{
  // Automatically generated. Do not edit this file.
  return m_player->get_top_right();
}

bear::universe::position_type tunnel::player_proxy::get_bottom_left() const
{
  // Automatically generated. Do not edit this file.
  return m_player->get_bottom_left();
}

bear::universe::position_type tunnel::player_proxy::get_bottom_right() const
{
  // Automatically generated. Do not edit this file.
  return m_player->get_bottom_right();
}

bear::universe::position_type tunnel::player_proxy::get_top_middle() const
{
  // Automatically generated. Do not edit this file.
  return m_player->get_top_middle();
}

bear::universe::coordinate_type tunnel::player_proxy::get_horizontal_middle() const
{
  // Automatically generated. Do not edit this file.
  return m_player->get_horizontal_middle();
}

bear::universe::coordinate_type tunnel::player_proxy::get_vertical_middle() const
{
  // Automatically generated. Do not edit this file.
  return m_player->get_vertical_middle();
}

bear::universe::coordinate_type tunnel::player_proxy::get_bottom() const
{
  // Automatically generated. Do not edit this file.
  return m_player->get_bottom();
}

bear::universe::coordinate_type tunnel::player_proxy::get_top() const
{
  // Automatically generated. Do not edit this file.
  return m_player->get_top();
}

bear::universe::coordinate_type tunnel::player_proxy::get_left() const
{
  // Automatically generated. Do not edit this file.
  return m_player->get_left();
}

bear::universe::coordinate_type tunnel::player_proxy::get_right() const
{
  // Automatically generated. Do not edit this file.
  return m_player->get_right();
}

bear::universe::rectangle_type tunnel::player_proxy::get_bounding_box() const
{
  // Automatically generated. Do not edit this file.
  return m_player->get_bounding_box();
}

void tunnel::player_proxy::set_forced_movement( const bear::universe::forced_movement& m )
{
  // Automatically generated. Do not edit this file.
  m_player->set_forced_movement(m);
}

bool tunnel::player_proxy::has_forced_movement() const
{
  // Automatically generated. Do not edit this file.
  return m_player->has_forced_movement();
}

void tunnel::player_proxy::clear_forced_movement()
{
  // Automatically generated. Do not edit this file.
  m_player->clear_forced_movement();
}

bear::universe::size_type tunnel::player_proxy::get_width() const
{
  // Automatically generated. Do not edit this file.
  return m_player->get_width();
}

bear::universe::size_type tunnel::player_proxy::get_height() const
{
  // Automatically generated. Do not edit this file.
  return m_player->get_height();
}

bear::universe::speed_type tunnel::player_proxy::get_speed() const
{
  // Automatically generated. Do not edit this file.
  return m_player->get_speed();
}

void tunnel::player_proxy::add_internal_force( bear::universe::force_type f ) const
{
  // Automatically generated. Do not edit this file.
  m_player->add_internal_force(f);
}

void tunnel::player_proxy::add_external_force( bear::universe::force_type f ) const
{
  // Automatically generated. Do not edit this file.
  m_player->add_external_force(f);
}

double tunnel::player_proxy::get_mass() const
{
  // Automatically generated. Do not edit this file.
  return m_player->get_mass();
}

void tunnel::player_proxy::set_mass( double m ) const
{
  // Automatically generated. Do not edit this file.
  m_player->set_mass(m);
}

int tunnel::player_proxy::get_z_position() const
{
  // Automatically generated. Do not edit this file.
  return m_player->get_z_position();
}

void tunnel::player_proxy::set_z_position(int z)
{
  // Automatically generated. Do not edit this file.
  m_player->set_z_position(z);
}

double tunnel::player_proxy::get_density() const
{
  // Automatically generated. Do not edit this file.
  return m_player->get_density();
}

void tunnel::player_proxy::set_density( double d ) const
{
  // Automatically generated. Do not edit this file.
  m_player->set_density(d);
}

void tunnel::player_proxy::set_system_angle( double a ) const
{
  // Automatically generated. Do not edit this file.
  m_player->set_system_angle(a);
}

std::string tunnel::player_proxy::get_current_action_name() const
{
  // Automatically generated. Do not edit this file.
  return m_player->get_current_action_name();
}

bool tunnel::player_proxy::get_mark_placement( const std::string& mark_name, bear::engine::model_mark_placement& m ) const
{
  // Automatically generated. Do not edit this file.
  return m_player->get_mark_placement(mark_name,m);
}

void tunnel::player_proxy::switch_action(player_action::value_type a, player_action::value_type b)
{
  // Automatically generated. Do not edit this file.
  m_player->switch_action(a,b);
}

void tunnel::player_proxy::clear_switched_action(player_action::value_type a, player_action::value_type b)
{
  // Automatically generated. Do not edit this file.
  m_player->clear_switched_action(a,b);
}
