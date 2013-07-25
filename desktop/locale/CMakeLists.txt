include( FindGettext OPTIONAL )

if( GETTEXT_FOUND )
  subdirs( tunnel )
endif( GETTEXT_FOUND )

