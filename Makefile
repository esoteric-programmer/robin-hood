# TARGET #

TARGET := 3DS
LIBRARY := 0

ifeq ($(TARGET),3DS)
    ifeq ($(strip $(DEVKITPRO)),)
        $(error "Please set DEVKITPRO in your environment. export DEVKITPRO=<path to>devkitPro")
    endif

    ifeq ($(strip $(DEVKITARM)),)
        $(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
    endif
endif

# COMMON CONFIGURATION #

NAME := robin_hood

BUILD_DIR := build
OUTPUT_DIR := output
INCLUDE_DIRS := src
SOURCE_DIRS := src

EXTRA_OUTPUT_FILES :=

LIBRARY_DIRS := $(DEVKITPRO)/libctru
LIBRARIES := sf2d citro3d  ctru

BUILD_FLAGS :=
RUN_FLAGS :=

VERSION_MAJOR := 0
VERSION_MINOR := 1
VERSION_MICRO := 1

# 3DS CONFIGURATION #

TITLE := Robin Hoods platform game
LONGTITLE := Robin Hoods platform game
DESCRIPTION := Platformer
AUTHOR := Matthias
PRODUCT_CODE := CTR-P-CRHP
UNIQUE_ID := 0xF9174

SYSTEM_MODE := 64MB
SYSTEM_MODE_EXT := Legacy

ICON_FLAGS := --flags visible,ratingrequired,recordusage --cero 153 --esrb 153 --usk 153 --pegigen 153 --pegiptr 153 --pegibbfc 153 --cob 153 --grb 153 --cgsrr 153

ROMFS_DIR := romfs
BANNER_AUDIO := audio/cia-banner.wav
BANNER_IMAGE := art/cia-banner.png
ICON := icon.png

# INTERNAL #

include buildtools/make_base
