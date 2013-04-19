#version 120

uniform sampler2D texture;

/*----------------------------------------------------------------------------*/
/**
 * \brief Computes a color of a fragment of the player while he is in the
 *        tunnel.
 */
void main(void)
{
  gl_FragColor = texture2D(texture, gl_TexCoord[0].st);
} // main()
