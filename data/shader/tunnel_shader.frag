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

const vec4 g_border_color = vec4( 0.9, 0.95, 0.99, 1 );
const vec4 g_border_edge_color = vec4( 1, 1, 1, 1 );
const float g_border_edge_width = 0.04;

float get_brightness( vec3 color )
{
  return 0.71516 * color.r + 0.212671 * color.g + 0.072169 * color.b;
} // get_brightness()

float curve_outside( float v )
{
  return sin( v * 3.14159 / 2 );
}

float curve_inside( float v )
{
  return sin( -v * 3.14159 / 2 );
} // curve_inside()

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

vec4 get_color_inside( vec4 color, float position_in_tunnel )
{
  if ( position_in_tunnel == 0 )
    return g_border_color;
  else if ( position_in_tunnel >= -g_border_edge_width )
    return g_border_edge_color;
  else
    {
      // we are clearly inside
      float brightness = get_brightness( color.rgb );

      const vec3 inside_color = vec3( 1, 0.984, 0.863 );
      vec3 result =
        clamp
        ( inside_color * brightness + color.rgb * 0.3,
          vec3(0, 0, 0), vec3(1, 1, 1) );

      if ( position_in_tunnel >= -1 ) // we are on the annulus
        {
          const vec3 inside_annulus_color = vec3(1, 1, 1);

          result =
            mix
            ( inside_annulus_color, result,
              curve_inside( position_in_tunnel ) );
        }

      return vec4( result.r, result.g, result.b, color.a );
    }
} // get_color_inside()

vec4 get_color_outside( vec4 color, float position_outside_tunnel )
{
  if ( position_outside_tunnel == 0 )
    return g_border_color;
  else if ( position_outside_tunnel <= g_border_edge_width )
    return g_border_edge_color;
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
