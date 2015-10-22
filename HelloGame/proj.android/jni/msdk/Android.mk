LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
LOCAL_MODULE := MSDK

MSDK_CPP_LIST := $(wildcard $(LOCAL_PATH)/*.cpp)
LOCAL_SRC_FILES := $(MSDK_CPP_LIST:$(LOCAL_PATH)/%=%)
         
LOCAL_C_INCLUDES := $(LOCAL_PATH)/CommonFiles

LOCAL_LDLIBS := -llog 

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
