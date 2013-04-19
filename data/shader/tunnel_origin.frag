#version 120

#pragma include "tunnel_shader.frag"

uniform sampler2D texture;

void main(void)
{
  vec4 color = texture2D(texture, gl_TexCoord[0].st);
  float position = locate_coordinate_in_tunnel( gl_FragCoord.xy );

  if ( position <= 0 )
    gl_FragColor.a = 0;
  else
    gl_FragColor = get_color_outside( color, position );
} // main()
