/**
 * \file
 * \brief The shader functions used to draw the tunnel in the various layers of
 *        the game.
 * \author Julien Jorge
 */

/** \brief The current radius of the tunnel. */
uniform float g_tunnel_radius;

/** \brief The x-coordinate of the center of the tunnel on the screen. */
uniform float g_tunnel_center_x;

/** \brief The y-coordinate of the center of the tunnel on the screen. */
uniform float g_tunnel_center_y;

/** \brief The intenisty of the effect. */
uniform float g_intensity;

/** \brief The color of the border of the tunnel. */
const vec4 g_border_color = vec4( 0.9, 0.95, 0.99, 1 );

/** \brief The width of the edges border of the tunnel. */
const float g_border_edge_width = 0.04;

#pragma include "tunnel_inside_effect.frag"

/*----------------------------------------------------------------------------*/
/**
 * \brief Computes the intensity of the annulus outside the tunnel.
 * \param v The relative position on the annulus. 0 means on the edge of the
 *        tunnel, -1 means on the outter side.
 */
float curve_outside( float v )
{
  return sin( v * 3.14159 / 2 );
} // curve_outside()

/*----------------------------------------------------------------------------*/
/**
 * \brief Computes the intensity of the annulus inside the tunnel.
 * \param v The relative position on the annulus. 0 means on the inner side, -1
 *        means on the edge of the tunnel.
 */
float curve_inside( float v )
{
  return sin( -v * 3.14159 / 2 );
} // curve_inside()

/*----------------------------------------------------------------------------*/
/**
 * \brief Tells where a given coordinate is relatively to the tunnel.
 * \param f The coordinate to locate.
 * \return The function returns the following values according to the following
 *         criteria:
 *  - 0 if f is on the border of the tunnel,
 *  - a number in (0, 1] if f is in the outside annulus of the tunnel,
 *  - a number greater that 1 if f is in the outside of the tunnel and outside
 *    the annulus,
 *  - a number in [-1, 0) if f is in the inside annulus of the tunnel,
 *  - a number lesser than -1 if f is inside the tunnel but not in the annulus
 *    of the tunnel. 
 */
float locate_coordinate_in_tunnel( vec2 f )
{
  float dx = f.x - g_tunnel_center_x;
  float dy = f.y - g_tunnel_center_y;
  float distance = sqrt( dx * dx + dy * dy );

  if ( abs( distance - g_tunnel_radius ) < 1 ) // on the border
    return 0.0;
  else if ( distance < g_tunnel_radius ) // we're inside
    {
      const float inside_gradient = 50;
      return (distance - g_tunnel_radius) / inside_gradient;
    }
  else // we're outside
    {
      const float outside_gradient = 30;
      return (distance - g_tunnel_radius) / outside_gradient;
    }
} // locate_coordinate_in_tunnel()

/*----------------------------------------------------------------------------*/
/**
 * \brief Adjusts a color to match the effect inside the tunnel.
 * \param color The color to adjust.
 * \param position_in_tunnel The position in the tunnel, as returned by
 *        locate_coordinate_in_tunnel().
 */
vec4 get_color_inside( vec4 color, float position_in_tunnel )
{
  if ( position_in_tunnel == 0 )
    return g_border_color;
  else if ( position_in_tunnel >= -g_border_edge_width )
    return vec4( 0.75, 0.75, 0.75, 1 );
  else
    {
      vec3 result = apply_inside_effect( color, g_intensity ).rgb;

      if ( position_in_tunnel >= -1 ) // we are on the annulus
        {
          const vec3 inside_annulus_color = vec3(0, 0, 0);

          result =
            mix
            ( inside_annulus_color, result,
              curve_inside( position_in_tunnel ) );
        }

      return vec4( result.r, result.g, result.b, color.a );
    }
} // get_color_inside()

/*----------------------------------------------------------------------------*/
/**
 * \brief Adjusts a color to match the effect outside the tunnel.
 * \param color The color to adjust.
 * \param position_outside_tunnel The position outside the tunnel, as returned
 *        by locate_coordinate_in_tunnel().
 */
vec4 get_color_outside( vec4 color, float position_outside_tunnel )
{
  if ( position_outside_tunnel == 0 )
    return g_border_color;
  else if ( position_outside_tunnel <= g_border_edge_width )
    return vec4( 1, 1, 1, 1 );
  else
    {
      vec3 result = color.rgb;

      if ( position_outside_tunnel <= 1 ) // we are on the annulus
        {
          const vec3 outside_annulus_color = vec3( 0.9, 0.95, 0.99 );

          result =
            mix
            ( outside_annulus_color, result,
              curve_outside( position_outside_tunnel ) );
        }

      return vec4( result.r, result.g, result.b, color.a );
    }
} // get_color_outside()
