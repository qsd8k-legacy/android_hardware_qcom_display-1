LOCAL_PATH := $(call my-dir)

ifneq ($(filter qsd8k,$(TARGET_BOARD_PLATFORM)),)
display-hals := libgralloc libgenlock libcopybit
display-hals += libhwcomposer liboverlay libqdutils
display-hals += libmemtrack
ifneq ($(TARGET_PROVIDES_LIBLIGHT),true)
display-hals += liblight
endif

include $(call all-named-subdir-makefiles,$(display-hals))

endif
