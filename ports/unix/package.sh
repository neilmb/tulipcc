# package.sh
# packages the Tulip Deskop binary into a macOS app, universal binary, notarizes / codesigns for distribution

# Build for arm then intel
make WHICH_ARCH=arm64 clean
make WHICH_ARCH=arm64
make WHICH_ARCH=x86_64 clean
make WHICH_ARCH=x86_64
# lipo them together
lipo -create -output tulip tulip.x86_64 tulip.arm64
rm tulip.x86_64
rm tulip.arm64

# Now make the app bundle
rm -rf Tulip\ CC.app
mkdir -p Tulip\ CC.app/Contents/{MacOS,Resources,Frameworks,libs}
cp tulip Tulip\ CC.app/Contents/MacOS
cp Info.plist Tulip\ CC.app/Contents/
cp -a SDL2.framework Tulip\ CC.app/Contents/Frameworks/
cp libs/libsoundio.2.0.0.dylib Tulip\ CC.app/Contents/libs/
#lipo -create -output Tulip\ CC.app/Contents/libs/libsoundio.2.0.0.dylib /usr/local/homebrew/Cellar/libsoundio/2.0.0/lib/libsoundio.2.0.0.dylib /opt/homebrew/Cellar/libsoundio/2.0.0/lib/libsoundio.2.0.0.dylib 
install_name_tool -add_rpath @executable_path/../Frameworks Tulip\ CC.app/Contents/MacOS/tulip
install_name_tool -change "@@HOMEBREW_PREFIX@@/opt/libsoundio/lib/libsoundio.2.dylib" "@executable_path/../libs/libsoundio.2.0.0.dylib" "Tulip CC.app/Contents/MacOS/tulip"
#install_name_tool -change "/opt/homebrew/opt/libsoundio/lib/libsoundio.2.dylib" "@executable_path/../libs/libsoundio.2.0.0.dylib" "Tulip CC.app/Contents/MacOS/tulip"
cp tulip.icns Tulip\ CC.app/Contents/Resources/
codesign -s "Developer ID Application: Brian Whitman (Y6CQ3JU8G4)" Tulip\ CC.app/Contents/libs/libsoundio.2.0.0.dylib -f
codesign -s "Developer ID Application: Brian Whitman (Y6CQ3JU8G4)" Tulip\ CC.app/Contents/Frameworks/SDL2.framework/Versions/A/SDL2 -f
codesign -s "Developer ID Application: Brian Whitman (Y6CQ3JU8G4)" Tulip\ CC.app/Contents/MacOS/tulip -f
#/System/Library/Frameworks/CoreServices.framework/Frameworks/LaunchServices.framework/Support/lsregister -f "Tulip CC.app"
#zip -r TulipCC.zip Tulip\ CC.app 
#rm -rf Tulip\ CC.app
#spctl -avv Tulip\ CC.app

# xcrun altool --list-providers -u "brian.whitman@variogr.am" -p app-spec-pw


