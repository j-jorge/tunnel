/*----------------------------------------------------------------------------*/
/**
 * \brief Computes the brightness of a color.
 * \param color The color of which we compute the brightness.
 */
float get_brightness( vec3 color )
{
  return 0.71516 * color.r + 0.212671 * color.g + 0.072169 * color.b;
} // get_brightness()

/*----------------------------------------------------------------------------*/
/**
 * \brief Adjusts a color to match the effect inside the tunnel.
 * \param color The color to adjust.
 * \param intensity The intensity of the effect.
 */
vec4 apply_inside_effect( vec4 color, float intensity )
{
  float brightness = get_brightness( color.rgb );

  const vec3 inside_color = vec3( 1, 0.984, 0.863 );

  vec3 result =
    intensity * inside_color * brightness
    + color.rgb * (0.3 + (1 - intensity) * 0.7);

  float x_mod = mod( gl_FragCoord.x, 4 );
  float y_mod = mod( gl_FragCoord.y, 4 );

  result += ((x_mod + y_mod) / 6) * 0.1 * intensity;
  result = clamp( result, vec3(0, 0, 0), vec3(1, 1, 1) );

  return vec4( result.r, result.g, result.b, color.a );
} // apply_inside_effect()

