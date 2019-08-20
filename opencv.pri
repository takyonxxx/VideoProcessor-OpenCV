DEFINES += CERES_FOUND

win32 {
    release{
    INCLUDEPATH += $$(OPENCV_DIR)/vc15/x64/include

    LIBS += -L$$(OPENCV_DIR)/vc15/x64/lib/release \
            -lopencv_aruco340 \
            -lopencv_bgsegm340 \
            -lopencv_calib3d340 \
            -lopencv_ccalib340 \
            -lopencv_core340 \
            -lopencv_datasets340 \
            -lopencv_dnn340 \
            -lopencv_dpm340 \
            -lopencv_face340 \
            -lopencv_features2d340 \
            -lopencv_flann340 \
            -lopencv_fuzzy340 \
            -lopencv_hdf340 \
            -lopencv_highgui340 \
            -lopencv_img_hash340 \
            -lopencv_imgcodecs340 \
            -lopencv_imgproc340 \
            -lopencv_line_descriptor340 \
            -lopencv_ml340 \
            -lopencv_objdetect340 \
            -lopencv_optflow340 \
            -lopencv_phase_unwrapping340 \
            -lopencv_photo340 \
            -lopencv_plot340 \
            -lopencv_reg340 \
            -lopencv_rgbd340 \
            -lopencv_saliency340 \
            -lopencv_sfm340 \
            -lopencv_shape340 \
            -lopencv_stereo340 \
            -lopencv_stitching340 \
            -lopencv_structured_light340 \
            -lopencv_superres340 \
            -lopencv_surface_matching340 \
            -lopencv_text340 \
            -lopencv_tracking340 \
            -lopencv_video340 \
            -lopencv_videoio340 \
            -lopencv_videostab340 \
            -lopencv_viz340 \
            -lopencv_xfeatures2d340 \
            -lopencv_ximgproc340 \
            -lopencv_xobjdetect340 \
            -lopencv_xphoto340
    }
    debug{
    INCLUDEPATH += $$(OPENCV_DIR)/vc15/x64/include
    LIBS += -L$$(OPENCV_DIR)/vc15/x64/lib/debug \
            -lopencv_aruco340d \
            -lopencv_bgsegm340d \
            -lopencv_calib3d340d \
            -lopencv_ccalib340d \
            -lopencv_core340d \
            -lopencv_datasets340d \
            -lopencv_dnn340d \
            -lopencv_dpm340d \
            -lopencv_face340d \
            -lopencv_features2d340d \
            -lopencv_flann340d \
            -lopencv_fuzzy340d \
            -lopencv_hdf340d \
            -lopencv_highgui340d \
            -lopencv_img_hash340d \
            -lopencv_imgcodecs340d \
            -lopencv_imgproc340d \
            -lopencv_line_descriptor340d \
            -lopencv_ml340d \
            -lopencv_objdetect340d \
            -lopencv_optflow340d \
            -lopencv_phase_unwrapping340d \
            -lopencv_photo340d \
            -lopencv_plot340d \
            -lopencv_reg340d \
            -lopencv_rgbd340d \
            -lopencv_saliency340d \
            -lopencv_sfm340d \
            -lopencv_shape340d \
            -lopencv_stereo340d \
            -lopencv_stitching340d \
            -lopencv_structured_light340d \
            -lopencv_superres340d \
            -lopencv_surface_matching340d \
            -lopencv_text340d \
            -lopencv_tracking340d \
            -lopencv_video340d \
            -lopencv_videoio340d \
            -lopencv_videostab340d \
            -lopencv_viz340d \
            -lopencv_xfeatures2d340d \
            -lopencv_ximgproc340d \
            -lopencv_xobjdetect340d \
            -lopencv_xphoto340d
    }
}

android {    

INCLUDEPATH += $$(OPENCV_DIR)/android/native/jni/include

LIBS += -L$$(OPENCV_DIR)/android/native/libs/armeabi-v7a \
        -lopencv_aruco \
        -lopencv_bgsegm \
        -lopencv_bioinspired \
        -lopencv_calib3d \
        -lopencv_ccalib \
        -lopencv_core \
        -lopencv_datasets \
        -lopencv_dnn \
        -lopencv_dpm \
        -lopencv_face \
        -lopencv_features2d \
        -lopencv_flann \
        -lopencv_fuzzy \
        -lopencv_highgui \
        -lopencv_img_hash \
        -lopencv_imgcodecs \
        -lopencv_imgproc \
        -lopencv_line_descriptor \
        -lopencv_ml \
        -lopencv_objdetect \
        -lopencv_optflow \
        -lopencv_phase_unwrapping \
        -lopencv_photo \
        -lopencv_plot \
        -lopencv_reg \
        -lopencv_rgbd \
        -lopencv_saliency \
        -lopencv_sfm \
        -lopencv_shape \
        -lopencv_stereo \
        -lopencv_stitching \
        -lopencv_structured_light \
        -lopencv_superres \
        -lopencv_surface_matching \
        -lopencv_text \
        -lopencv_tracking \
        -lopencv_video \
        -lopencv_videoio \
        -lopencv_videostab \
        -lopencv_xfeatures2d \
        -lopencv_ximgproc \
        -lopencv_xobjdetect \
        -lopencv_xphoto

ANDROID_EXTRA_LIBS += \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_aruco.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_bgsegm.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_bioinspired.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_calib3d.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_ccalib.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_core.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_datasets.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_dnn.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_dpm.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_face.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_features2d.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_flann.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_fuzzy.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_highgui.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_img_hash.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_imgcodecs.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_imgproc.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_line_descriptor.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_ml.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_objdetect.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_optflow.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_phase_unwrapping.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_photo.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_plot.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_reg.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_rgbd.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_saliency.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_sfm.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_shape.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_stereo.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_stitching.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_structured_light.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_superres.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_surface_matching.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_text.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_tracking.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_video.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_videoio.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_videostab.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_xfeatures2d.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_ximgproc.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_xobjdetect.so \
    $$(OPENCV_DIR)/android/native/libs/armeabi-v7a/libopencv_xphoto.so
}
