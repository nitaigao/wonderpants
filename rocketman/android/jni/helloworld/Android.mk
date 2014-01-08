LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := game
LOCAL_CPPFLAGS += -std=gnu++0x 
LOCAL_CPPFLAGS += -DFULL_GAME=1
#LOCAL_CPPFLAGS += -DCOCOS2D_DEBUG=2
#LOCAL_CPPFLAGS += -DCHEATS=1

BOX2D_FILES := ../../../libs/Box2D/Common/b2BlockAllocator.cpp \
	../../../libs/Box2D/Common/b2Draw.cpp \
	../../../libs/Box2D/Common/b2Math.cpp \
	../../../libs/Box2D/Common/b2Settings.cpp \
	../../../libs/Box2D/Common/b2StackAllocator.cpp \
	../../../libs/Box2D/Common/b2Timer.cpp \
	../../../libs/Box2D/Dynamics/b2Body.cpp \
	../../../libs/Box2D/Dynamics/b2ContactManager.cpp \
	../../../libs/Box2D/Dynamics/b2Fixture.cpp \
	../../../libs/Box2D/Dynamics/b2Island.cpp \
	../../../libs/Box2D/Dynamics/b2World.cpp \
	../../../libs/Box2D/Dynamics/b2WorldCallbacks.cpp \
	../../../libs/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp \
	../../../libs/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp \
	../../../libs/Box2D/Dynamics/Contacts/b2CircleContact.cpp \
	../../../libs/Box2D/Dynamics/Contacts/b2Contact.cpp \
	../../../libs/Box2D/Dynamics/Contacts/b2ContactSolver.cpp \
	../../../libs/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp \
	../../../libs/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp \
	../../../libs/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp \
	../../../libs/Box2D/Dynamics/Contacts/b2PolygonContact.cpp \
	../../../libs/Box2D/Dynamics/Joints/b2DistanceJoint.cpp \
	../../../libs/Box2D/Dynamics/Joints/b2FrictionJoint.cpp \
	../../../libs/Box2D/Dynamics/Joints/b2GearJoint.cpp \
	../../../libs/Box2D/Dynamics/Joints/b2Joint.cpp \
	../../../libs/Box2D/Dynamics/Joints/b2MouseJoint.cpp \
	../../../libs/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp \
	../../../libs/Box2D/Dynamics/Joints/b2PulleyJoint.cpp \
	../../../libs/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp \
	../../../libs/Box2D/Dynamics/Joints/b2RopeJoint.cpp \
	../../../libs/Box2D/Dynamics/Joints/b2WeldJoint.cpp \
	../../../libs/Box2D/Dynamics/Joints/b2WheelJoint.cpp \
	../../../libs/Box2D/Rope/b2Rope.cpp \
	../../../libs/Box2D/Collision/b2BroadPhase.cpp \
	../../../libs/Box2D/Collision/b2CollideCircle.cpp \
	../../../libs/Box2D/Collision/b2CollideEdge.cpp \
	../../../libs/Box2D/Collision/b2CollidePolygon.cpp \
	../../../libs/Box2D/Collision/b2Collision.cpp \
	../../../libs/Box2D/Collision/b2Distance.cpp \
	../../../libs/Box2D/Collision/b2DynamicTree.cpp \
	../../../libs/Box2D/Collision/b2TimeOfImpact.cpp \
	../../../libs/Box2D/Collision/Shapes/b2ChainShape.cpp \
	../../../libs/Box2D/Collision/Shapes/b2CircleShape.cpp \
	../../../libs/Box2D/Collision/Shapes/b2EdgeShape.cpp \
	../../../libs/Box2D/Collision/Shapes/b2PolygonShape.cpp

LUA_FILES := ../../../libs/lua/lapi.c \
	../../../libs/lua/lauxlib.c \
	../../../libs/lua/lbaselib.c \
	../../../libs/lua/lcode.c \
	../../../libs/lua/ldblib.c \
	../../../libs/lua/ldebug.c \
	../../../libs/lua/ldo.c \
	../../../libs/lua/ldump.c \
	../../../libs/lua/lfunc.c \
	../../../libs/lua/lgc.c \
	../../../libs/lua/linit.c \
	../../../libs/lua/liolib.c \
	../../../libs/lua/llex.c \
	../../../libs/lua/lmathlib.c \
	../../../libs/lua/lmem.c \
	../../../libs/lua/loadlib.c \
	../../../libs/lua/lobject.c \
	../../../libs/lua/lopcodes.c \
	../../../libs/lua/loslib.c \
	../../../libs/lua/lparser.c \
	../../../libs/lua/lstate.c \
	../../../libs/lua/lstring.c \
	../../../libs/lua/lstrlib.c \
	../../../libs/lua/ltable.c \
	../../../libs/lua/ltablib.c \
	../../../libs/lua/ltm.c \
	../../../libs/lua/lundump.c \
	../../../libs/lua/lvm.c \
	../../../libs/lua/lzio.c \
	../../../libs/lua/print.c \


APP_FILES := $(wildcard $(LOCAL_PATH)/../../../Classes/*.cpp)
PLATFORM_FILES := $(wildcard $(LOCAL_PATH)/../../../android-os/*.cpp)
JSON_FILES := $(wildcard $(LOCAL_PATH)/../../../libs/json/*.cpp)

LOCAL_SRC_FILES := \
	main.cpp \
	$(APP_FILES:$(LOCAL_PATH)/%=%) \
	$(PLATFORM_FILES:$(LOCAL_PATH)/%=%) \
	$(LUA_FILES:$(LOCAL_PATH)/%=%) \
	$(BOX2D_FILES:$(LOCAL_PATH)/%=%) \
	$(JSON_FILES:$(LOCAL_PATH)/%=%) \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes \
					$(LOCAL_PATH)/../../../libs \
					$(LOCAL_PATH)/../../../libs/cocos2dx \
					$(LOCAL_PATH)/../../../libs/cocos2dx/platform \
					$(LOCAL_PATH)/../../../libs/cocos2dx/platform/android \
					$(LOCAL_PATH)/../../../libs/cocos2dx/platform/android/jni \
					$(LOCAL_PATH)/../../../libs/cocos2dx/include \
					$(LOCAL_PATH)/../../../libs/CocosDenshion/include \
					$(LOCAL_PATH)/../../../libs/lua \
					$(LOCAL_PATH)/../../../libs/json \
					$(LOCAL_PATH)/../../../libs/Box2D \
					$(LOCAL_PATH)/../../../libs/Box2D/Collision \
					$(LOCAL_PATH)/../../../libs/Box2D/Common \
					$(LOCAL_PATH)/../../../libs/Box2D/Dynamics \
					$(LOCAL_PATH)/../../../libs/Box2D/Rope \
					$(LOCAL_PATH)/../../../android-os


LOCAL_LDLIBS := -L$(call host-path, $(LOCAL_PATH)/../../libs/$(TARGET_ARCH_ABI)) \
                -lcocos2d -llog -lcocosdenshion \
				-lGLESv1_CM
            
include $(BUILD_SHARED_LIBRARY)
