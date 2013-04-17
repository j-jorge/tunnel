#version 120

uniform sampler2D texture;
uniform float tunnel_radius;
uniform float center_x;
uniform float center_y;

void main(void)
{
  vec4 color = texture2D(texture, gl_TexCoord[0].st);

  float dx = gl_FragCoord.x - center_x;
  float dy = gl_FragCoord.y - center_y;

  if ( sqrt( dx * dx + dy * dy ) < tunnel_radius )
    color.a = 0;
  else
    {
      float light = 0.71516 * color.r + 0.212671 * color.g + 0.072169 * color.b;
      const float c = 0.1;

      color.rgb = mix( color.rgb, vec3( light, light, light ), c );
    }

  gl_FragColor = color;
}
