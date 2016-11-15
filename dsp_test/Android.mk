LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := spidev_test1
LOCAL_SRC_FILES := $(call all-subdir-c-files)
LOCAL_C_INCLUDES := $(call all-include-dirs)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include
include $(BUILD_EXECUTABLE)
$(warning "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!my-dir"$(call my-dir))
$(warning "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!CLEAR_VARS"$(call CLEAR_VARS))
$(warning "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!all-subdir-c-files"$(call all-subdir-c-files))
$(warning "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!all-include-dirs"$(call all-include-dirs))
$(warning "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!LOCAL_PATH"$(LOCAL_PATH))
