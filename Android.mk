LOCAL_PATH := $(call my-dir)

display-hals := libgralloc libgenlock libcopybit
display-hals += libhwcomposer liboverlay libqdutils
display-hals += libmemtrack
include $(call all-named-subdir-makefiles,$(display-hals))

