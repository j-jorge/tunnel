/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
package com.stuffomatic.tunnel;

import org.libsdl.app.SDLActivity;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.view.WindowManager;

public class Tunnel extends SDLActivity
{
    static {
        System.loadLibrary( "gnustl_shared" );
        System.loadLibrary( "tunnel" );
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        hideActionBars();
        addVisibilityChangeListener();
    }

    /**
     * Tells the system to open a given URL.
     * @param url The URL to open.
     */
    public void openUrl( String url ) {

        final Intent browserIntent =
            new Intent( Intent.ACTION_VIEW, Uri.parse(url) );
        startActivity(browserIntent);
    }

    /**
     * Tells the system to show the home screen.
     */
    public void showHome() {

        final Intent homeIntent = new Intent( Intent.ACTION_MAIN );
        homeIntent.addCategory( Intent.CATEGORY_HOME );
        startActivity(homeIntent);
    }

    /**
     * Returns the name of the device on which the game is running.
     */
    public String getDeviceModelName() {
        
        return Build.MANUFACTURER + ", " + Build.PRODUCT + ", " + Build.MODEL;
    }

    /**
     * Hides the action bar such that the game uses the full screen.
     */
    private void hideActionBars() {

        getWindow().getDecorView().setSystemUiVisibility
            ( View.SYSTEM_UI_FLAG_LOW_PROFILE
              | View.SYSTEM_UI_FLAG_LAYOUT_STABLE
              | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
              | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
              | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
              | View.SYSTEM_UI_FLAG_FULLSCREEN
              | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY );
    }

    private void addVisibilityChangeListener() {

        final View decorView = getWindow().getDecorView();

        decorView.setOnSystemUiVisibilityChangeListener
            ( new View.OnSystemUiVisibilityChangeListener() {
                @Override
                public void onSystemUiVisibilityChange( int visibility ) {
        
                    if ( (visibility & View.SYSTEM_UI_FLAG_FULLSCREEN) == 0 ) {
                        hideActionBars();
                    }
                }
            } );
    }
}
