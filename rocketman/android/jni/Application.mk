# it is needed for ndk-r5
APP_STL := gnustl_static
APP_MODULES := cocos2d cocosdenshion game
APP_CPPFLAGS += -std=gnu++0x -fpermissive
#APP_OPTIM := debug