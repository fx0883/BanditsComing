LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

APP_STL := gnustl_static #GNU STL
APP_CPPFLAGS := -fexceptions -frtti #允许异常功能，及运行时类型识别
APP_CPPFLAGS +=-std=c++11 #允许使用c++11的函数等功能
APP_CPPFLAGS +=-fpermissive  #此项有效时表示宽松的编译形式，


LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

# 定义 all-cpp-files 返回当前路径和 Classes 路径想的所有 cpp 文件，注意：这里只考虑 cpp 而没有 c，如果需要自行添加
define all-cpp-files
$(patsubst jni/%,%, $(shell find $(LOCAL_PATH)/../../Classes/ $(LOCAL_PATH)/hellocpp -name "*.cpp"))
endef

# 这里使用新的方式替换换来的方式，以自动添加源文件
LOCAL_SRC_FILES := $(call all-cpp-files)

#LOCAL_SRC_FILES := hellocpp/main.cpp \
#                  ../../Classes/AppDelegate.cpp \
#                  ../../Classes/HelloWorldScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
                    $(LOCAL_PATH)/../../cocos2d/extensions \
                    $(LOCAL_PATH)/../../cocos2d/cocos \
                    $(LOCAL_PATH)/../../cocos2d/cocos/editor-support/cocostudio \
                    $(LOCAL_PATH)/../../cocos2d/cocos/editor-support \
                    $(LOCAL_PATH)/../../cocos2d/cocos/ui \



LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_ui_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static


include $(BUILD_SHARED_LIBRARY)

# $(call import-module,CocosDenshion/android)
# $(call import-module,cocos2dx)
$(call import-module,ui)
$(call import-module,extensions)
# 根据自己需要是否启用，上面的静态库同样
$(call import-module,2d)
$(call import-module,audio/android)
$(call import-module,Box2D)
$(call import-module,editor-support/cocostudio)