if( RP_NO_MANPAGES )
  message("Ignoring manpages, on user's demand.")
else( RP_NO_MANPAGES )
  if(DOCBOOK_TO_MAN_FOUND)
    docbook_create_man( tunnel-man 6 tunnel.sgml )
  else(DOCBOOK_TO_MAN_FOUND)
    message("docbook-to-man was not found on your system. The manpages of "
      "Tunnel are not generated.")
  endif(DOCBOOK_TO_MAN_FOUND)
endif( RP_NO_MANPAGES )

