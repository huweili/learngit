LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := my_test
LOCAL_SRC_FILES := $(call all-subdir-c-files)
LOCAL_C_INCLUDES := $(call all-include-dirs)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include
include $(BUILD_EXECUTABLE)
