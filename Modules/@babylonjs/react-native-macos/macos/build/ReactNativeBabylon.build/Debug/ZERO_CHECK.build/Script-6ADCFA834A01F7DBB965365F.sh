#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/jihoobyeon/Desktop/BabylonReactNative/Modules/@babylonjs/react-native-macos/macos
  make -f /Users/jihoobyeon/Desktop/BabylonReactNative/Modules/@babylonjs/react-native-macos/macos/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/jihoobyeon/Desktop/BabylonReactNative/Modules/@babylonjs/react-native-macos/macos
  make -f /Users/jihoobyeon/Desktop/BabylonReactNative/Modules/@babylonjs/react-native-macos/macos/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/jihoobyeon/Desktop/BabylonReactNative/Modules/@babylonjs/react-native-macos/macos
  make -f /Users/jihoobyeon/Desktop/BabylonReactNative/Modules/@babylonjs/react-native-macos/macos/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/jihoobyeon/Desktop/BabylonReactNative/Modules/@babylonjs/react-native-macos/macos
  make -f /Users/jihoobyeon/Desktop/BabylonReactNative/Modules/@babylonjs/react-native-macos/macos/CMakeScripts/ReRunCMake.make
fi

