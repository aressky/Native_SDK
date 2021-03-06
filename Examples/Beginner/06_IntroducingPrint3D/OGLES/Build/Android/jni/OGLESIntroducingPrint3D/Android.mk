LOCAL_PATH := $(call my-dir)/../../../../../../../..
PVRSDKDIR := $(realpath $(LOCAL_PATH))

ASSETDIR := $(PVRSDKDIR)/Examples/Beginner/06_IntroducingPrint3D/OGLES/Build/Android/assets

CPY := cp
SEPARATOR := /
ifeq ($(HOST_OS),windows)
CPY := copy
SEPARATOR := \\
endif

# Module OGLESIntroducingPrint3D
include $(CLEAR_VARS)

LOCAL_MODULE    := OGLESIntroducingPrint3D

### Add all source file names to be included in lib separated by a whitespace
LOCAL_SRC_FILES  := Examples/Beginner/06_IntroducingPrint3D/OGLES/OGLESIntroducingPrint3D.cpp \
                    Shell/PVRShell.cpp \
                    Shell/API/KEGL/PVRShellAPI.cpp \
                    Shell/OS/Android/PVRShellOS.cpp

LOCAL_C_INCLUDES := $(PVRSDKDIR)/Shell \
                    $(PVRSDKDIR)/Shell/API/KEGL \
                    $(PVRSDKDIR)/Shell/OS/Android \
                    $(PVRSDKDIR)/Builds/Include \
                    $(PVRSDKDIR)/Tools \
                    $(PVRSDKDIR)/Tools/OGLES

LOCAL_CFLAGS := -DBUILD_OGLES

LOCAL_LDLIBS := -llog \
                -landroid \
                -lEGL \
                -lGLESv1_CM

LOCAL_STATIC_LIBRARIES := android_native_app_glue \
                          oglestools

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)

### Copy our external files to the assets folder, but only do it for the first abi
ifeq ($(TARGET_ARCH_ABI),$(firstword $(NDK_APP_ABI)))

all:  \
	$(ASSETDIR)/Text.txt \
	$(ASSETDIR)/arial_36.pvr \
	$(ASSETDIR)/starjout_60.pvr \
	$(ASSETDIR)/title_36.pvr \
	$(ASSETDIR)/title_46.pvr \
	$(ASSETDIR)/title_56.pvr

$(ASSETDIR):
	-mkdir "$(ASSETDIR)"

$(ASSETDIR)/Text.txt: $(PVRSDKDIR)/Examples/Beginner/06_IntroducingPrint3D/OGLES/Text.txt $(ASSETDIR)
	$(CPY) $(subst /,$(SEPARATOR),"$<" "$(ASSETDIR)")

$(ASSETDIR)/arial_36.pvr: $(PVRSDKDIR)/Examples/Beginner/06_IntroducingPrint3D/OGLES/arial_36.pvr $(ASSETDIR)
	$(CPY) $(subst /,$(SEPARATOR),"$<" "$(ASSETDIR)")

$(ASSETDIR)/starjout_60.pvr: $(PVRSDKDIR)/Examples/Beginner/06_IntroducingPrint3D/OGLES/starjout_60.pvr $(ASSETDIR)
	$(CPY) $(subst /,$(SEPARATOR),"$<" "$(ASSETDIR)")

$(ASSETDIR)/title_36.pvr: $(PVRSDKDIR)/Examples/Beginner/06_IntroducingPrint3D/OGLES/title_36.pvr $(ASSETDIR)
	$(CPY) $(subst /,$(SEPARATOR),"$<" "$(ASSETDIR)")

$(ASSETDIR)/title_46.pvr: $(PVRSDKDIR)/Examples/Beginner/06_IntroducingPrint3D/OGLES/title_46.pvr $(ASSETDIR)
	$(CPY) $(subst /,$(SEPARATOR),"$<" "$(ASSETDIR)")

$(ASSETDIR)/title_56.pvr: $(PVRSDKDIR)/Examples/Beginner/06_IntroducingPrint3D/OGLES/title_56.pvr $(ASSETDIR)
	$(CPY) $(subst /,$(SEPARATOR),"$<" "$(ASSETDIR)")

endif

