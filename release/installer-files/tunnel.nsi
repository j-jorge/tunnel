; Windows installer for Tunnel

!include "MUI2.nsh"

;--------------------------------

; The name of the installer
Name "Tunnel"

; The file to write
OutFile tunnel.exe

; The default installation directory
InstallDir "$LOCALAPPDATA\Tunnel"
InstallDirRegKey HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\tunnel" "UninstallString"

SetCompressor /SOLID lzma

;Request application privileges for Windows Vista
RequestExecutionLevel user

;--------------------------------
; Interface Configuration

!define MUI_HEADERIMAGE
        !define MUI_HEADERIMAGE_BITMAP "banner.bmp"

!define MUI_WELCOMEFINISHPAGE_BITMAP "welcome.bmp" 

;--------------------------------

Var StartMenuFolder

;--------------------------------

!insertmacro MUI_PAGE_WELCOME

!insertmacro MUI_PAGE_DIRECTORY

;Start Menu Folder Page Configuration
!define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKCU" 
!define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\Tunnel" 
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "Start Menu Folder"
  
!insertmacro MUI_PAGE_STARTMENU Application $StartMenuFolder
  
!insertmacro MUI_PAGE_INSTFILES

!define MUI_FINISHPAGE_SHOWREADME "$INSTDIR\Readme.txt"
!define MUI_FINISHPAGE_RUN "$INSTDIR\bin\tunnel-launcher.exe"
!define MUI_FINISHPAGE_RUN_TEXT "Launch the game."
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_LANGUAGE "English"

;--------------------------------
Section "Install"

  ; Set output path to the installation directory.
  SetOutPath "$INSTDIR\bin"
  
  File /r "bin\*.dll"
  File /r "bin\tunnel-launcher.exe"

  SetOutPath "$INSTDIR\share\super-great-park"

  File /r "share\super-great-park\"

  SetOutPath "$INSTDIR\share\locale"

  File /r "share\locale\"

  SetOutPath "$INSTDIR"

  File "tunnel.ico"
  File "ReadMe.txt"

  CreateDirectory "$SMPROGRAMS\Tunnel"

  SetOutPath "$INSTDIR\bin"

  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
    
    CreateShortCut "$SMPROGRAMS\Tunnel\Tunnel.lnk" "$INSTDIR\bin\tunnel-launcher.exe" "" "$INSTDIR\tunnel.ico"

    SetOutPath "$INSTDIR"

    CreateDirectory "$SMPROGRAMS\$StartMenuFolder"

    CreateShortCut "$SMPROGRAMS\Tunnel\Uninstall.lnk" "$INSTDIR\uninst-tunnel.exe"

    CreateShortCut "$SMPROGRAMS\Tunnel\ReadMe.lnk" "$INSTDIR\ReadMe.txt"

  !insertmacro MUI_STARTMENU_WRITE_END

SectionEnd ; end of "Install"

;--------------------------------
Section -PostInstall

  WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\tunnel" "DisplayName" "Tunnel (uninstall)"

  WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\tunnel" "UninstallString" '"$INSTDIR\uninst-tunnel.exe"'

  WriteUninstaller "uninst-tunnel.exe"

SectionEnd

UninstallText "Ready to uninstall Tunnel."

;--------------------------------
Section "Uninstall"
  DeleteRegKey HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\tunnel"
  Delete "$INSTDIR\uninst-tunnel.exe"
  Delete "$INSTDIR\tunnel.ico"
  Delete "$INSTDIR\ReadMe.txt"

  !insertmacro MUI_STARTMENU_GETFOLDER Application $StartMenuFolder
    
  Delete "$SMPROGRAMS\$StartMenuFolder\Uninstall.lnk"
  Delete "$SMPROGRAMS\$StartMenuFolder\Tunnel.lnk"
  Delete "$SMPROGRAMS\$StartMenuFolder\ReadMe.lnk"
  RMDir "$SMPROGRAMS\$StartMenuFolder"

  RMDir /r "$SMPROGRAMS\Tunnel"
  RMDir /r "$INSTDIR\share"
  RMDir /r "$INSTDIR\bin"

SectionEnd
