# set params
ANDROID_NDK_ROOT=/Users/nk/Development/android-ndk-r6b
GAME_ROOT=../
GAME_ANDROID_ROOT=$GAME_ROOT/android
ASSETS=$GAME_ANDROID_ROOT/assets
RESOURCE_ROOT=$GAME_ROOT/Resources

# Copy Assets
if [ -d $ASSETS ]; then
    rm -rf $ASSETS
fi

mkdir $ASSETS

#python ~/Dropbox/Games/kitty_hero/levels.full/pack_levels.py                                                  
ruby ~/Dropbox/Games/kitty_hero/scripts/compile_scripts.rb ~/Dropbox/Games/kitty_hero/compiled.sheets "$ASSETS"

for ext in "fnt" "jpg" "mp3" "prefab" "level" "plist" "txt" "ccz" "png" "json"
do
cp -rf ~/Dropbox/Games/kitty_hero/compiled.sheets/*.$ext "${ASSETS}"
done
                  
# Compile
$ANDROID_NDK_ROOT/ndk-build -C $GAME_ANDROID_ROOT $*