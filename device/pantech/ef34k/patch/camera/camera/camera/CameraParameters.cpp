/*
**
** Copyright 2008, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#define LOG_TAG "CameraParams"
#include <utils/Log.h>

#include <string.h>
#include <stdlib.h>
#include <camera/CameraParameters.h>
#include <cutils/properties.h>

namespace android {
// Parameter keys to communicate between camera application and driver.
const char CameraParameters::KEY_PREVIEW_SIZE[] = "preview-size";
const char CameraParameters::KEY_SUPPORTED_PREVIEW_SIZES[] = "preview-size-values";
#ifdef QCOM_HARDWARE
const char CameraParameters::KEY_SUPPORTED_HFR_SIZES[] = "hfr-size-values";
#endif
const char CameraParameters::KEY_PREVIEW_FORMAT[] = "preview-format";
const char CameraParameters::KEY_SUPPORTED_PREVIEW_FORMATS[] = "preview-format-values";
const char CameraParameters::KEY_PREVIEW_FRAME_RATE[] = "preview-frame-rate";
const char CameraParameters::KEY_SUPPORTED_PREVIEW_FRAME_RATES[] = "preview-frame-rate-values";
const char CameraParameters::KEY_PREVIEW_FPS_RANGE[] = "preview-fps-range";
const char CameraParameters::KEY_SUPPORTED_PREVIEW_FPS_RANGE[] = "preview-fps-range-values";
#ifdef QCOM_HARDWARE
const char CameraParameters::KEY_PREVIEW_FRAME_RATE_MODE[] = "preview-frame-rate-mode";
const char CameraParameters::KEY_SUPPORTED_PREVIEW_FRAME_RATE_MODES[] = "preview-frame-rate-modes";
const char CameraParameters::KEY_PREVIEW_FRAME_RATE_AUTO_MODE[] = "frame-rate-auto";
const char CameraParameters::KEY_PREVIEW_FRAME_RATE_FIXED_MODE[] = "frame-rate-fixed";
#ifdef QCOM_LEGACY_CAM_PARAMS
//Values for Continuous AF
const char CameraParameters::CAF_OFF[] = "caf-off";
const char CameraParameters::CAF_ON[] = "caf-on";
//Same, for CodeAurora-based blobs
const char CameraParameters::CAPTURE_MODE_NORMAL[] = "normal";
const char CameraParameters::CAPTURE_MODE_BURST[] = "burst";
const char CameraParameters::CAPTURE_MODE_CONTI_BURST[] = "contiburst";
const char CameraParameters::CAPTURE_MODE_HDR[] = "hdr";
const char CameraParameters::CAPTURE_MODE_HJR[] = "hjr";
const char CameraParameters::CAPTURE_MODE_PANORAMA[] = "panorama";
const char CameraParameters::CONTINUOUS_AF_OFF[] = "caf-off";
const char CameraParameters::CONTINUOUS_AF_ON[] = "caf-on";
const char CameraParameters::KEY_CONTINUOUS_AF[] = "continuous-af";
const char CameraParameters::KEY_CAF[] = "continuous-af";
const char CameraParameters::KEY_CAPTURE_MODE[] = "capture-mode";
const char CameraParameters::KEY_PICTURE_COUNT[] = "picture-count";
const char CameraParameters::KEY_MAX_BURST_PICTURE_COUNT[] = "max-burst-picture-count";
const char CameraParameters::KEY_SUPPORTED_CONTINUOUS_AF[] = "continuous-af-mode";
const char CameraParameters::KEY_SUPPORTED_CAF[] = "continuous-af-values";
const char CameraParameters::KEY_SUPPORTED_CAPTURE_MODES[] = "capture-mode-values";
const char CameraParameters::KEY_TAKING_PICTURE_ZOOM[] = "taking-picture-zoom";
const char CameraParameters::KEY_PANORAMA_MODE[] = "panorama-mode";
const char CameraParameters::PANORAMA_MODE_NOT_INPROGRESS[] = "not-in-progress";
const char CameraParameters::PANORAMA_MODE_INPROGRESS[] = "in-progress";
#endif
#endif
const char CameraParameters::KEY_PICTURE_SIZE[] = "picture-size";
const char CameraParameters::KEY_SUPPORTED_PICTURE_SIZES[] = "picture-size-values";
const char CameraParameters::KEY_PICTURE_FORMAT[] = "picture-format";
const char CameraParameters::KEY_SUPPORTED_3D_FILE_FORMAT[] = "3d-file-format";
const char CameraParameters::KEY_SUPPORTED_PICTURE_FORMATS[] = "picture-format-values";
const char CameraParameters::KEY_JPEG_THUMBNAIL_WIDTH[] = "jpeg-thumbnail-width";
const char CameraParameters::KEY_JPEG_THUMBNAIL_HEIGHT[] = "jpeg-thumbnail-height";
const char CameraParameters::KEY_SUPPORTED_JPEG_THUMBNAIL_SIZES[] = "jpeg-thumbnail-size-values";
const char CameraParameters::KEY_JPEG_THUMBNAIL_QUALITY[] = "jpeg-thumbnail-quality";
const char CameraParameters::KEY_JPEG_QUALITY[] = "jpeg-quality";
const char CameraParameters::KEY_ROTATION[] = "rotation";
const char CameraParameters::KEY_GPS_LATITUDE[] = "gps-latitude";
const char CameraParameters::KEY_GPS_LONGITUDE[] = "gps-longitude";
const char CameraParameters::KEY_GPS_ALTITUDE[] = "gps-altitude";
const char CameraParameters::KEY_GPS_TIMESTAMP[] = "gps-timestamp";
const char CameraParameters::KEY_GPS_PROCESSING_METHOD[] = "gps-processing-method";
const char CameraParameters::KEY_WHITE_BALANCE[] = "whitebalance";
const char CameraParameters::KEY_SUPPORTED_WHITE_BALANCE[] = "whitebalance-values";
const char CameraParameters::KEY_EFFECT[] = "effect";
const char CameraParameters::KEY_SUPPORTED_EFFECTS[] = "effect-values";
#ifdef QCOM_HARDWARE
const char CameraParameters::KEY_TOUCH_AF_AEC[] = "touch-af-aec";
const char CameraParameters::KEY_SUPPORTED_TOUCH_AF_AEC[] = "touch-af-aec-values";
const char CameraParameters::KEY_TOUCH_INDEX_AEC[] = "touch-index-aec";
const char CameraParameters::KEY_TOUCH_INDEX_AF[] = "touch-index-af";
#endif
const char CameraParameters::KEY_ANTIBANDING[] = "antibanding";
const char CameraParameters::KEY_SUPPORTED_ANTIBANDING[] = "antibanding-values";
const char CameraParameters::KEY_SCENE_MODE[] = "scene-mode";
const char CameraParameters::KEY_SUPPORTED_SCENE_MODES[] = "scene-mode-values";
#ifdef QCOM_HARDWARE
const char CameraParameters::KEY_SCENE_DETECT[] = "scene-detect";
const char CameraParameters::KEY_SUPPORTED_SCENE_DETECT[] = "scene-detect-values";
#endif //QCOM_HARDWARE
const char CameraParameters::KEY_FLASH_MODE[] = "flash-mode";
const char CameraParameters::KEY_SUPPORTED_FLASH_MODES[] = "flash-mode-values";
const char CameraParameters::KEY_FOCUS_MODE[] = "focus-mode";
const char CameraParameters::KEY_SUPPORTED_FOCUS_MODES[] = "focus-mode-values";
const char CameraParameters::KEY_MAX_NUM_FOCUS_AREAS[] = "max-num-focus-areas";
const char CameraParameters::KEY_FOCUS_AREAS[] = "focus-areas";
const char CameraParameters::KEY_FOCAL_LENGTH[] = "focal-length";
const char CameraParameters::KEY_HORIZONTAL_VIEW_ANGLE[] = "horizontal-view-angle";
const char CameraParameters::KEY_VERTICAL_VIEW_ANGLE[] = "vertical-view-angle";
const char CameraParameters::KEY_EXPOSURE_COMPENSATION[] = "exposure-compensation";
const char CameraParameters::KEY_MAX_EXPOSURE_COMPENSATION[] = "max-exposure-compensation";
const char CameraParameters::KEY_MIN_EXPOSURE_COMPENSATION[] = "min-exposure-compensation";
const char CameraParameters::KEY_EXPOSURE_COMPENSATION_STEP[] = "exposure-compensation-step";
const char CameraParameters::KEY_AUTO_EXPOSURE_LOCK[] = "auto-exposure-lock";
const char CameraParameters::KEY_AUTO_EXPOSURE_LOCK_SUPPORTED[] = "auto-exposure-lock-supported";
const char CameraParameters::KEY_AUTO_WHITEBALANCE_LOCK[] = "auto-whitebalance-lock";
const char CameraParameters::KEY_AUTO_WHITEBALANCE_LOCK_SUPPORTED[] = "auto-whitebalance-lock-supported";
const char CameraParameters::KEY_MAX_NUM_METERING_AREAS[] = "max-num-metering-areas";
const char CameraParameters::KEY_METERING_AREAS[] = "metering-areas";
const char CameraParameters::KEY_ZOOM[] = "zoom";
const char CameraParameters::KEY_MAX_ZOOM[] = "max-zoom";
const char CameraParameters::KEY_ZOOM_RATIOS[] = "zoom-ratios";
const char CameraParameters::KEY_ZOOM_SUPPORTED[] = "zoom-supported";
const char CameraParameters::KEY_SMOOTH_ZOOM_SUPPORTED[] = "smooth-zoom-supported";
const char CameraParameters::KEY_FOCUS_DISTANCES[] = "focus-distances";
const char CameraParameters::KEY_VIDEO_FRAME_FORMAT[] = "video-frame-format";
#ifdef QCOM_HARDWARE
const char CameraParameters::KEY_ISO_MODE[] = "iso";
const char CameraParameters::KEY_SUPPORTED_ISO_MODES[] = "iso-values";
const char CameraParameters::KEY_LENSSHADE[] = "lensshade";
const char CameraParameters::KEY_SUPPORTED_LENSSHADE_MODES[] = "lensshade-values";
#ifdef SAMSUNG_CAMERA_LEGACY
const char CameraParameters::KEY_AUTO_EXPOSURE[] = "metering";
#else
const char CameraParameters::KEY_AUTO_EXPOSURE[] = "auto-exposure";
#endif
const char CameraParameters::KEY_SUPPORTED_AUTO_EXPOSURE[] = "auto-exposure-values";
const char CameraParameters::KEY_DENOISE[] = "denoise";
const char CameraParameters::KEY_SUPPORTED_DENOISE[] = "denoise-values";
const char CameraParameters::KEY_SELECTABLE_ZONE_AF[] = "selectable-zone-af";
const char CameraParameters::KEY_SUPPORTED_SELECTABLE_ZONE_AF[] = "selectable-zone-af-values";
const char CameraParameters::KEY_FACE_DETECTION[] = "face-detection";
const char CameraParameters::KEY_SUPPORTED_FACE_DETECTION[] = "face-detection-values";
const char CameraParameters::KEY_MEMORY_COLOR_ENHANCEMENT[] = "mce";
const char CameraParameters::KEY_SUPPORTED_MEM_COLOR_ENHANCE_MODES[] = "mce-values";
const char CameraParameters::KEY_VIDEO_HIGH_FRAME_RATE[] = "video-hfr";
const char CameraParameters::KEY_SUPPORTED_VIDEO_HIGH_FRAME_RATE_MODES[] = "video-hfr-values";
const char CameraParameters::KEY_REDEYE_REDUCTION[] = "redeye-reduction";
const char CameraParameters::KEY_SUPPORTED_REDEYE_REDUCTION[] = "redeye-reduction-values";
const char CameraParameters::KEY_HIGH_DYNAMIC_RANGE_IMAGING[] = "hdr";
const char CameraParameters::KEY_SUPPORTED_HDR_IMAGING_MODES[] = "hdr-values";
#endif
const char CameraParameters::KEY_VIDEO_SIZE[] = "video-size";
const char CameraParameters::KEY_SUPPORTED_VIDEO_SIZES[] = "video-size-values";
const char CameraParameters::KEY_PREFERRED_PREVIEW_SIZE_FOR_VIDEO[] = "preferred-preview-size-for-video";
const char CameraParameters::KEY_MAX_NUM_DETECTED_FACES_HW[] = "max-num-detected-faces-hw";
const char CameraParameters::KEY_MAX_NUM_DETECTED_FACES_SW[] = "max-num-detected-faces-sw";
const char CameraParameters::KEY_RECORDING_HINT[] = "recording-hint";
const char CameraParameters::KEY_VIDEO_SNAPSHOT_SUPPORTED[] = "video-snapshot-supported";
const char CameraParameters::KEY_FULL_VIDEO_SNAP_SUPPORTED[] = "full-video-snap-supported";
const char CameraParameters::KEY_VIDEO_STABILIZATION[] = "video-stabilization";
const char CameraParameters::KEY_VIDEO_STABILIZATION_SUPPORTED[] = "video-stabilization-supported";
#ifdef QCOM_HARDWARE
const char CameraParameters::KEY_ZSL[] = "zsl";
const char CameraParameters::KEY_SUPPORTED_ZSL_MODES[] = "zsl-values";
const char CameraParameters::KEY_CAMERA_MODE[] = "camera-mode";
const char CameraParameters::KEY_POWER_MODE[] = "power-mode";
const char CameraParameters::KEY_POWER_MODE_SUPPORTED[] = "power-mode-supported";
#endif
const char CameraParameters::KEY_AE_BRACKET_HDR[] = "ae-bracket-hdr";

/*only effective when KEY_AE_BRACKET_HDR set to ae_bracketing*/
//const char CameraParameters::KEY_AE_BRACKET_SETTING_KEY[] = "ae-bracket-setting";

#ifdef HAVE_ISO
const char CameraParameters::KEY_SUPPORTED_ISO_MODES[] = "iso-values";
const char CameraParameters::KEY_ISO_MODE[] = "iso";
#endif

#ifdef SAMSUNG_CAMERA_HARDWARE
const char CameraParameters::KEY_ANTI_SHAKE_MODE[] = "anti-shake";
const char CameraParameters::KEY_METERING[] = "metering";
const char CameraParameters::KEY_WEATHER[] = "weather";
const char CameraParameters::KEY_CITYID[] = "contextualtag-cityid";
#endif

#ifdef HTC_CAMERA_HARDWARE
const char CameraParameters::KEY_TIME_CONS_POST_PROCESSING[] = "time-cons-post-processing";
const char CameraParameters::KEY_OIS_MODE[] = "ois_mode";
const char CameraParameters::KEY_APP_OIS_SETTING[] = "ois-setting";
const char CameraParameters::KEY_OIS_SUPPORT[] = "ois_support";
const char CameraParameters::KEY_CONTIBURST_TYPE[] = "contiburst-type";
const char CameraParameters::KEY_CAPTURE_MODE[] = "capture-mode";
const char CameraParameters::CAPTURE_MODE_NORMAL[] = "normal";
const char CameraParameters::CAPTURE_MODE_CONTI_ZOE[] = "contizoe";
const char CameraParameters::CAPTURE_MODE_CONTI_BURST[] = "contiburst";
const char CameraParameters::CAPTURE_MODE_CONTI_BURST_ONE_SHOT[] = "contiburst-one-shot";
const char CameraParameters::CAPTURE_MODE_HDR[] = "hdr";
const char CameraParameters::CAPTURE_MODE_PANORAMA[] = "panorama";
const char CameraParameters::CAPTURE_MODE_ZOE[] = "zoe";
const char CameraParameters::KEY_CONTI_BURST_STATE[] = "contiburst-state";
const char CameraParameters::KEY_SUPPORTED_CAPTURE_MODES[] = "capture-mode-values";
const char CameraParameters::KEY_MIN_CONTRAST[] = "contrast-min";
const char CameraParameters::KEY_MIN_SHARPNESS[] = "sharpness-min";
const char CameraParameters::KEY_MIN_SATURATION[] = "saturation-min";
const char CameraParameters::KEY_SINGLE_ISP_OUTPUT_ENABLED[] = "single-isp-output-enabled";
const char CameraParameters::POST_PROCESSING_ENABLE[] = "enable";
const char CameraParameters::POST_PROCESSING_BYPASS[] = "bypass";
const char CameraParameters::POST_PROCESSING_DELAY[] = "delay";
const char CameraParameters::SCENE_MODE_TEXT[] = "text";
const char CameraParameters::BURST_MODE_LIMIT20[] = "limit-20";
const char CameraParameters::BURST_MODE_UNLIMITED[] = "unlimited";
const char CameraParameters::OIS_MODE_OFF[] = "off";
const char CameraParameters::OIS_MODE_ON[] = "on";
const char CameraParameters::CONTI_BURST_CAPTURING[] = "contiburst-capturing";
const char CameraParameters::CONTI_BURST_CAPTURE_DONE[] = "contiburst-done";
const char CameraParameters::APP_OIS_SETTING_FALSE[] = "false";
const char CameraParameters::APP_OIS_SETTING_TRUE[] = "true";
const char CameraParameters::KEY_GPU_EFFECT[] = "GPU-effect";
const char CameraParameters::KEY_GPU_EFFECT_PARAM_0[] = "GE-param0";
const char CameraParameters::KEY_GPU_EFFECT_PARAM_1[] = "GE-param1";
const char CameraParameters::KEY_GPU_EFFECT_PARAM_2[] = "GE-param2";
const char CameraParameters::KEY_GPU_EFFECT_PARAM_3[] = "GE-param3";
#endif

const char CameraParameters::TRUE[] = "true";
const char CameraParameters::FALSE[] = "false";
const char CameraParameters::FOCUS_DISTANCE_INFINITY[] = "Infinity";

// Values for white balance settings.
const char CameraParameters::WHITE_BALANCE_AUTO[] = "auto";
const char CameraParameters::WHITE_BALANCE_INCANDESCENT[] = "incandescent";
const char CameraParameters::WHITE_BALANCE_FLUORESCENT[] = "fluorescent";
const char CameraParameters::WHITE_BALANCE_WARM_FLUORESCENT[] = "warm-fluorescent";
const char CameraParameters::WHITE_BALANCE_DAYLIGHT[] = "daylight";
const char CameraParameters::WHITE_BALANCE_CLOUDY_DAYLIGHT[] = "cloudy-daylight";
const char CameraParameters::WHITE_BALANCE_TWILIGHT[] = "twilight";
const char CameraParameters::WHITE_BALANCE_SHADE[] = "shade";

// Values for effect settings.
const char CameraParameters::EFFECT_NONE[] = "none";
const char CameraParameters::EFFECT_MONO[] = "mono";
const char CameraParameters::EFFECT_NEGATIVE[] = "negative";
const char CameraParameters::EFFECT_SOLARIZE[] = "solarize";
const char CameraParameters::EFFECT_SEPIA[] = "sepia";
const char CameraParameters::EFFECT_POSTERIZE[] = "posterize";
const char CameraParameters::EFFECT_WHITEBOARD[] = "whiteboard";
const char CameraParameters::EFFECT_BLACKBOARD[] = "blackboard";
const char CameraParameters::EFFECT_AQUA[] = "aqua";
#ifdef QCOM_HARDWARE
const char CameraParameters::EFFECT_EMBOSS[] = "emboss";
const char CameraParameters::EFFECT_SKETCH[] = "sketch";
const char CameraParameters::EFFECT_NEON[] = "neon";

// Values for auto exposure settings.
const char CameraParameters::TOUCH_AF_AEC_OFF[] = "touch-off";
const char CameraParameters::TOUCH_AF_AEC_ON[] = "touch-on";
#endif

// Values for antibanding settings.
const char CameraParameters::ANTIBANDING_AUTO[] = "auto";
const char CameraParameters::ANTIBANDING_50HZ[] = "50hz";
const char CameraParameters::ANTIBANDING_60HZ[] = "60hz";
const char CameraParameters::ANTIBANDING_OFF[] = "off";

// Values for flash mode settings.
const char CameraParameters::FLASH_MODE_OFF[] = "off";
const char CameraParameters::FLASH_MODE_AUTO[] = "auto";
const char CameraParameters::FLASH_MODE_ON[] = "on";
const char CameraParameters::FLASH_MODE_RED_EYE[] = "red-eye";
const char CameraParameters::FLASH_MODE_TORCH[] = "torch";

// Values for scene mode settings.
const char CameraParameters::SCENE_MODE_AUTO[] = "auto"; // corresponds to CAMERA_BESTSHOT_OFF in HAL
const char CameraParameters::SCENE_MODE_ASD[] = "asd";   // corresponds to CAMERA_BESTSHOT_AUTO in HAL
const char CameraParameters::SCENE_MODE_ACTION[] = "action";
const char CameraParameters::SCENE_MODE_PORTRAIT[] = "portrait";
const char CameraParameters::SCENE_MODE_LANDSCAPE[] = "landscape";
const char CameraParameters::SCENE_MODE_NIGHT[] = "night";
const char CameraParameters::SCENE_MODE_NIGHT_PORTRAIT[] = "night-portrait";
const char CameraParameters::SCENE_MODE_THEATRE[] = "theatre";
const char CameraParameters::SCENE_MODE_BEACH[] = "beach";
const char CameraParameters::SCENE_MODE_SNOW[] = "snow";
const char CameraParameters::SCENE_MODE_SUNSET[] = "sunset";
const char CameraParameters::SCENE_MODE_STEADYPHOTO[] = "steadyphoto";
const char CameraParameters::SCENE_MODE_FIREWORKS[] = "fireworks";
const char CameraParameters::SCENE_MODE_SPORTS[] = "sports";
const char CameraParameters::SCENE_MODE_PARTY[] = "party";
const char CameraParameters::SCENE_MODE_CANDLELIGHT[] = "candlelight";
#ifdef QCOM_HARDWARE
#ifdef SAMSUNG_CAMERA_LEGACY
const char CameraParameters::SCENE_MODE_BACKLIGHT[] = "back-light";
#else
const char CameraParameters::SCENE_MODE_BACKLIGHT[] = "backlight";
#endif
const char CameraParameters::SCENE_MODE_FLOWERS[] = "flowers";
#endif
const char CameraParameters::SCENE_MODE_BARCODE[] = "barcode";

const char CameraParameters::SCENE_MODE_HDR[] = "hdr";
#ifdef QCOM_HARDWARE
const char CameraParameters::SCENE_MODE_AR[] = "AR";

const char CameraParameters::SCENE_MODE_CUSTOM[] = "custom";
const char CameraParameters::SCENE_MODE_OFF[] = "off";
// Values for auto scene detection settings.
const char CameraParameters::SCENE_DETECT_OFF[] = "off";
const char CameraParameters::SCENE_DETECT_ON[] = "on";
#endif


// Formats for setPreviewFormat and setPictureFormat.
const char CameraParameters::PIXEL_FORMAT_YUV422SP[] = "yuv422sp";
const char CameraParameters::PIXEL_FORMAT_YUV420SP[] = "yuv420sp";
#ifdef QCOM_HARDWARE
const char CameraParameters::PIXEL_FORMAT_YUV420SP_ADRENO[] = "yuv420sp-adreno";
#endif
const char CameraParameters::PIXEL_FORMAT_YUV422I[] = "yuv422i-yuyv";
const char CameraParameters::PIXEL_FORMAT_YUV420P[]  = "yuv420p";
const char CameraParameters::PIXEL_FORMAT_RGB565[] = "rgb565";
const char CameraParameters::PIXEL_FORMAT_RGBA8888[] = "rgba8888";
const char CameraParameters::PIXEL_FORMAT_JPEG[] = "jpeg";
const char CameraParameters::PIXEL_FORMAT_BAYER_RGGB[] = "bayer-rggb";
const char CameraParameters::PIXEL_FORMAT_ANDROID_OPAQUE[] = "android-opaque";

#ifdef QCOM_HARDWARE
const char CameraParameters::PIXEL_FORMAT_RAW[] = "raw";
const char CameraParameters::PIXEL_FORMAT_YV12[] = "yuv420p";
const char CameraParameters::PIXEL_FORMAT_NV12[] = "nv12";
#endif

// Values for focus mode settings.
const char CameraParameters::FOCUS_MODE_AUTO[] = "auto";
const char CameraParameters::FOCUS_MODE_INFINITY[] = "infinity";
const char CameraParameters::FOCUS_MODE_MACRO[] = "macro";
const char CameraParameters::FOCUS_MODE_FIXED[] = "fixed";
const char CameraParameters::FOCUS_MODE_EDOF[] = "edof";
const char CameraParameters::FOCUS_MODE_CONTINUOUS_VIDEO[] = "continuous-video";
const char CameraParameters::FOCUS_MODE_CONTINUOUS_PICTURE[] = "continuous-picture";
#if defined(QCOM_HARDWARE)
#ifdef QCOM_LEGACY_CAM_PARAMS
const char CameraParameters::FOCUS_MODE_CONTINUOUS_CAMERA[] = "continuous-camera";
#endif
const char CameraParameters::FOCUS_MODE_NORMAL[] = "normal";


const char CameraParameters::KEY_SKIN_TONE_ENHANCEMENT[] = "skinToneEnhancement";
const char CameraParameters::KEY_SUPPORTED_SKIN_TONE_ENHANCEMENT_MODES[] = "skinToneEnhancement-values";

// Values for ISO Settings
const char CameraParameters::ISO_AUTO[] = "auto";
const char CameraParameters::ISO_HJR[] = "ISO_HJR";
const char CameraParameters::ISO_100[] = "ISO100";
const char CameraParameters::ISO_200[] = "ISO200";
const char CameraParameters::ISO_400[] = "ISO400";
const char CameraParameters::ISO_800[] = "ISO800";
const char CameraParameters::ISO_1600[] = "ISO1600";
const char CameraParameters::ISO_3200[] = "ISO3200";
const char CameraParameters::ISO_6400[] = "ISO6400";

 //Values for Lens Shading
const char CameraParameters::LENSSHADE_ENABLE[] = "enable";
const char CameraParameters::LENSSHADE_DISABLE[] = "disable";

// Values for auto exposure settings.
const char CameraParameters::AUTO_EXPOSURE_FRAME_AVG[] = "frame-average";
const char CameraParameters::AUTO_EXPOSURE_CENTER_WEIGHTED[] = "center-weighted";
const char CameraParameters::AUTO_EXPOSURE_SPOT_METERING[] = "spot-metering";

const char CameraParameters::KEY_GPS_LATITUDE_REF[] = "gps-latitude-ref";
const char CameraParameters::KEY_GPS_LONGITUDE_REF[] = "gps-longitude-ref";
const char CameraParameters::KEY_GPS_ALTITUDE_REF[] = "gps-altitude-ref";
const char CameraParameters::KEY_GPS_STATUS[] = "gps-status";
const char CameraParameters::KEY_EXIF_DATETIME[] = "exif-datetime";

const char CameraParameters::KEY_HISTOGRAM[] = "histogram";
const char CameraParameters::KEY_SUPPORTED_HISTOGRAM_MODES[] = "histogram-values";
//Values for Histogram Shading
const char CameraParameters::HISTOGRAM_ENABLE[] = "enable";
const char CameraParameters::HISTOGRAM_DISABLE[] = "disable";

//Values for Skin Tone Enhancement Modes
const char CameraParameters::SKIN_TONE_ENHANCEMENT_ENABLE[] = "enable";
const char CameraParameters::SKIN_TONE_ENHANCEMENT_DISABLE[] = "disable";

const char CameraParameters::KEY_SHARPNESS[] = "sharpness";
#ifdef QCOM_LEGACY_CAM_PARAMS
const char CameraParameters::KEY_MAX_SHARPNESS[] = "sharpness-max";
const char CameraParameters::KEY_MIN_SHARPNESS[] = "sharpness-min";
#else
const char CameraParameters::KEY_MAX_SHARPNESS[] = "max-sharpness";
#endif
const char CameraParameters::KEY_CONTRAST[] = "contrast";
#ifdef QCOM_LEGACY_CAM_PARAMS
const char CameraParameters::KEY_MAX_CONTRAST[] = "contrast-max";
const char CameraParameters::KEY_MIN_CONTRAST[] = "contrast-min";
#else
const char CameraParameters::KEY_MAX_CONTRAST[] = "max-contrast";
#endif
const char CameraParameters::KEY_SATURATION[] = "saturation";
#ifdef QCOM_LEGACY_CAM_PARAMS
const char CameraParameters::KEY_MAX_SATURATION[] = "saturation-max";
const char CameraParameters::KEY_MIN_SATURATION[] = "saturation-min";
#else
const char CameraParameters::KEY_MAX_SATURATION[] = "max-saturation";
#endif

//Values for DENOISE
const char CameraParameters::DENOISE_OFF[] = "denoise-off";
const char CameraParameters::DENOISE_ON[] = "denoise-on";
// Values for selectable zone af Settings
const char CameraParameters::SELECTABLE_ZONE_AF_AUTO[] = "auto";
const char CameraParameters::SELECTABLE_ZONE_AF_SPOT_METERING[] = "spot-metering";
const char CameraParameters::SELECTABLE_ZONE_AF_CENTER_WEIGHTED[] = "center-weighted";
const char CameraParameters::SELECTABLE_ZONE_AF_FRAME_AVERAGE[] = "frame-average";

// Values for Face Detection settings.
const char CameraParameters::FACE_DETECTION_OFF[] = "off";
const char CameraParameters::FACE_DETECTION_ON[] = "on";

const char CameraParameters::FILE_FORMAT_MPO[] = "mpo";
const char CameraParameters::FILE_FORMAT_JPS[] = "jps";

// Values for MCE settings.
const char CameraParameters::MCE_ENABLE[] = "enable";
const char CameraParameters::MCE_DISABLE[] = "disable";

// Values for HFR settings.
const char CameraParameters::VIDEO_HFR_OFF[] = "off";
const char CameraParameters::VIDEO_HFR_2X[] = "60";
const char CameraParameters::VIDEO_HFR_3X[] = "90";
const char CameraParameters::VIDEO_HFR_4X[] = "120";

// Values for Redeye Reduction settings.
const char CameraParameters::REDEYE_REDUCTION_ENABLE[] = "enable";
const char CameraParameters::REDEYE_REDUCTION_DISABLE[] = "disable";
// Values for HDR settings.
const char CameraParameters::HDR_ENABLE[] = "enable";
const char CameraParameters::HDR_DISABLE[] = "disable";

// Values for ZSL settings.
const char CameraParameters::ZSL_OFF[] = "off";
const char CameraParameters::ZSL_ON[] = "on";

// Values for HDR Bracketing settings.
const char CameraParameters::AE_BRACKET_HDR_OFF[] = "Off";
const char CameraParameters::AE_BRACKET_HDR[] = "HDR";
const char CameraParameters::AE_BRACKET[] = "AE-Bracket";

const char CameraParameters::LOW_POWER[] = "Low_Power";
const char CameraParameters::NORMAL_POWER[] = "Normal_Power";

#if defined(QCOM_HARDWARE) && defined(SAMSUNG_CAMERA_LEGACY)
const char CameraParameters::FOCUS_MODE_FACEDETECT[] = "facedetect";
const char CameraParameters::FOCUS_MODE_TOUCHAF[] = "touchaf";
const char CameraParameters::ISO_50[] = "ISO50";
const char CameraParameters::KEY_ANTI_SHAKE_MODE[] = "antishake";
const char CameraParameters::KEY_AUTO_CONTRAST[] = "auto-contrast";
const char CameraParameters::KEY_BEAUTY_MODE[] = "beauty";
const char CameraParameters::KEY_BLUR_MODE[] = "blur";
const char CameraParameters::KEY_VINTAGE_MODE[] = "vintagemode";
const char CameraParameters::VINTAGE_MODE_BNW[] = "bnw";
const char CameraParameters::VINTAGE_MODE_COOL[] = "cool";
const char CameraParameters::VINTAGE_MODE_NORMAL[] = "normal";
const char CameraParameters::VINTAGE_MODE_OFF[] = "off";
const char CameraParameters::VINTAGE_MODE_WARM[] = "warm";
const char CameraParameters::SCENE_MODE_DAWN[] = "dusk-dawn";
const char CameraParameters::SCENE_MODE_DUSKDAWN[] = "dusk-dawn";
const char CameraParameters::SCENE_MODE_FALL[] = "fall-color";
const char CameraParameters::SCENE_MODE_FALL_COLOR[] = "fall-color";
const char CameraParameters::SCENE_MODE_TEXT[] = "text";
#endif

static const char* portrait = "portrait";
static const char* landscape = "landscape";

int CameraParameters::getOrientation() const
{
    const char* orientation = get("orientation");
    if (orientation && !strcmp(orientation, portrait))
        return CAMERA_ORIENTATION_PORTRAIT;
    return CAMERA_ORIENTATION_LANDSCAPE;
}
void CameraParameters::setOrientation(int orientation)
{
    if (orientation == CAMERA_ORIENTATION_PORTRAIT) {
        set("orientation", portrait);
    } else {
         set("orientation", landscape);
    }
}
#endif


CameraParameters::CameraParameters()
                : mMap()
{
}

CameraParameters::~CameraParameters()
{
}

String8 CameraParameters::flatten() const
{
    String8 flattened("");
    size_t size = mMap.size();

    for (size_t i = 0; i < size; i++) {
        String8 k, v;
        k = mMap.keyAt(i);
        v = mMap.valueAt(i);

        flattened += k;
        flattened += "=";
        flattened += v;
        if (i != size-1)
            flattened += ";";
    }

    return flattened;
}

void CameraParameters::unflatten(const String8 &params)
{
    const char *a = params.string();
    const char *b;

    mMap.clear();

    for (;;) {
        // Find the bounds of the key name.
        b = strchr(a, '=');
        if (b == 0)
            break;

        // Create the key string.
        String8 k(a, (size_t)(b-a));

        // Find the value.
        a = b+1;
        b = strchr(a, ';');
        if (b == 0) {
            // If there's no semicolon, this is the last item.
            String8 v(a);
            mMap.add(k, v);
            break;
        }

        String8 v(a, (size_t)(b-a));
        mMap.add(k, v);
        a = b+1;
    }
}


void CameraParameters::set(const char *key, const char *value)
{
    if (key == NULL || value == NULL)
        return;

    // XXX i think i can do this with strspn()
    if (strchr(key, '=') || strchr(key, ';')) {
        //XXX ALOGE("Key \"%s\"contains invalid character (= or ;)", key);
        return;
    }

    if (strchr(value, '=') || strchr(key, ';')) {
        //XXX ALOGE("Value \"%s\"contains invalid character (= or ;)", value);
        return;
    }

    mMap.replaceValueFor(String8(key), String8(value));
}


bool CameraParameters::isws()
{   char user1[13];
	  char user2[32];
	  property_get("ro.cm.version",user1,NULL);
	  property_get("ro.build.id",user2,NULL);
//	   ALOGE("WSMESSAGE WSMESSAGE WSMESSAGE str=%s", user1);
//	   ALOGE("WSMESSAGE WSMESSAGE WSMESSAGE str=%s", user2);
//	  ALOGE("WSMESSAGE WSMESSAGE WSMESSAGE str=%c", user1[18]);
//	  ALOGE("WSMESSAGE WSMESSAGE WSMESSAGE str=%c", user1[22]);
	   	   	   
    if((user2[2]!='W')||(user2[6]!='s')||(user1[18]!='W')||(user1[22]!='s'))
    	 {
    	//  ALOGE("WSMESSAGE WSMESSAGE WSMESSAGE str=%s", user2);
      //  ALOGE("WSMESSAGE WSMESSAGE WSMESSAGE str=%s", user1);
        return false;
      }
    else 
        return true;
        
}

void CameraParameters::set(const char *key, int value)
{
    char str[16];
    snprintf(str, sizeof(str), "%d", value);
    set(key, str);
}

void CameraParameters::setFloat(const char *key, float value)
{
    char str[16];  // 14 should be enough. We overestimate to be safe.
    snprintf(str, sizeof(str), "%g", value);
    set(key, str);
}

const char *CameraParameters::get(const char *key) const
{
    String8 v = mMap.valueFor(String8(key));
    if (v.length() == 0)
        return 0;
    return v.string();
}

int CameraParameters::getInt(const char *key) const
{
    const char *v = get(key);
    if (v == 0)
        return -1;
    return strtol(v, 0, 0);
}

#ifdef SAMSUNG_CAMERA_HARDWARE
int CameraParameters::getInt64(const char *key) const
{
    return -1;
}
#endif

float CameraParameters::getFloat(const char *key) const
{
    const char *v = get(key);
    if (v == 0) return -1;
    return strtof(v, 0);
}

void CameraParameters::remove(const char *key)
{
    mMap.removeItem(String8(key));
}

// Parse string like "640x480" or "10000,20000"
static int parse_pair(const char *str, int *first, int *second, char delim,
                      char **endptr = NULL)
{
    // Find the first integer.
    char *end;
    int w = (int)strtol(str, &end, 10);
    // If a delimeter does not immediately follow, give up.
    if (*end != delim) {
        ALOGE("Cannot find delimeter (%c) in str=%s", delim, str);
        return -1;
    }

    // Find the second integer, immediately after the delimeter.
    int h = (int)strtol(end+1, &end, 10);

    *first = w;
    *second = h;

    if (endptr) {
        *endptr = end;
    }

    return 0;
}

// Parse string like "(1, 2, 3, 4, ..., N)"
// num is pointer to an allocated array of size N
static int parseNDimVector(const char *str, int *num, int N, char delim = ',')
{
    char *start, *end;
    if(num == NULL) {
        ALOGE("Invalid output array (num == NULL)");
        return -1;
    }
    //check if string starts and ends with parantheses
    if(str[0] != '(' || str[strlen(str)-1] != ')') {
        ALOGE("Invalid format of string %s, valid format is (n1, n2, n3, n4 ...)", str);
        return -1;
    }
    start = (char*) str;
    start++;
    for(int i=0; i<N; i++) {
        *(num+i) = (int) strtol(start, &end, 10);
        if(*end != delim && i < N-1) {
            ALOGE("Cannot find delimeter '%c' in string \"%s\". end = %c", delim, str, *end);
            return -1;
        }
        start = end+1;
    }
    return 0;
}
static void parseSizesList(const char *sizesStr, Vector<Size> &sizes)
{
    if (sizesStr == 0) {
        return;
    }

    char *sizeStartPtr = (char *)sizesStr;

    while (true) {
        int width, height;
        int success = parse_pair(sizeStartPtr, &width, &height, 'x',
                                 &sizeStartPtr);
        if (success == -1 || (*sizeStartPtr != ',' && *sizeStartPtr != '\0')) {
            ALOGE("Picture sizes string \"%s\" contains invalid character.", sizesStr);
            return;
        }
        sizes.push(Size(width, height));

        if (*sizeStartPtr == '\0') {
            return;
        }
        sizeStartPtr++;
    }
}

void CameraParameters::setPreviewSize(int width, int height)
{
    char str[32];
    snprintf(str, sizeof(str), "%dx%d", width, height);
    set(KEY_PREVIEW_SIZE, str);
}

void CameraParameters::getPreviewSize(int *width, int *height) const
{
    *width = *height = -1;
    // Get the current string, if it doesn't exist, leave the -1x-1
    const char *p = get(KEY_PREVIEW_SIZE);
    if (p == 0)  return;
    parse_pair(p, width, height, 'x');
}

void CameraParameters::getPreferredPreviewSizeForVideo(int *width, int *height) const
{
    *width = *height = -1;
    const char *p = get(KEY_PREFERRED_PREVIEW_SIZE_FOR_VIDEO);
    if (p == 0)  return;
    parse_pair(p, width, height, 'x');
}

void CameraParameters::getSupportedPreviewSizes(Vector<Size> &sizes) const
{
    const char *previewSizesStr = get(KEY_SUPPORTED_PREVIEW_SIZES);
    parseSizesList(previewSizesStr, sizes);
}

#ifdef QCOM_HARDWARE
#ifdef QCOM_LEGACY_CAM_PARAMS
void CameraParameters::setPostviewSize(int width, int height)
{
    // dummy
}
#endif

void CameraParameters::getSupportedHfrSizes(Vector<Size> &sizes) const
{
    const char *hfrSizesStr = get(KEY_SUPPORTED_HFR_SIZES);
    parseSizesList(hfrSizesStr, sizes);
}

void CameraParameters::setPreviewFpsRange(int minFPS, int maxFPS)
{
    char str[32];
    snprintf(str, sizeof(str), "%d,%d",minFPS,maxFPS);
    set(KEY_PREVIEW_FPS_RANGE,str);
}
#endif

void CameraParameters::setVideoSize(int width, int height)
{
    char str[32];
    sprintf(str, "%dx%d", width, height);
    set(KEY_VIDEO_SIZE, str);
}

void CameraParameters::getVideoSize(int *width, int *height) const
{
    *width = *height = -1;
    const char *p = get(KEY_VIDEO_SIZE);
    if (p == 0) return;
    parse_pair(p, width, height, 'x');
}

void CameraParameters::getSupportedVideoSizes(Vector<Size> &sizes) const
{
    const char *videoSizesStr = get(KEY_SUPPORTED_VIDEO_SIZES);
    parseSizesList(videoSizesStr, sizes);
}

void CameraParameters::setPreviewFrameRate(int fps)
{
    set(KEY_PREVIEW_FRAME_RATE, fps);
}

int CameraParameters::getPreviewFrameRate() const
{
    return getInt(KEY_PREVIEW_FRAME_RATE);
}

void CameraParameters::getPreviewFpsRange(int *min_fps, int *max_fps) const
{
    *min_fps = *max_fps = -1;
    const char *p = get(KEY_PREVIEW_FPS_RANGE);
    if (p == 0) return;
    parse_pair(p, min_fps, max_fps, ',');
}

#ifdef QCOM_HARDWARE
void CameraParameters::setPreviewFrameRateMode(const char *mode)
{
    set(KEY_PREVIEW_FRAME_RATE_MODE, mode);
}

const char *CameraParameters::getPreviewFrameRateMode() const
{
    return get(KEY_PREVIEW_FRAME_RATE_MODE);
}
#endif

void CameraParameters::setPreviewFormat(const char *format)
{
    set(KEY_PREVIEW_FORMAT, format);
}

const char *CameraParameters::getPreviewFormat() const
{   
    return get(KEY_PREVIEW_FORMAT);
}

void CameraParameters::setPictureSize(int width, int height)
{
    char str[32];
    sprintf(str, "%dx%d", width, height);
     if(isws())
    set(KEY_PICTURE_SIZE, str);
}

void CameraParameters::getPictureSize(int *width, int *height) const
{
    *width = *height = -1;
    // Get the current string, if it doesn't exist, leave the -1x-1
    const char *p = get(KEY_PICTURE_SIZE);
    if (p == 0) return;
    parse_pair(p, width, height, 'x');
}

void CameraParameters::getSupportedPictureSizes(Vector<Size> &sizes) const
{
    const char *pictureSizesStr = get(KEY_SUPPORTED_PICTURE_SIZES);
    parseSizesList(pictureSizesStr, sizes);
}

void CameraParameters::set3DFileFormat(const char *format)
{
    set(KEY_SUPPORTED_3D_FILE_FORMAT, format);
}

void CameraParameters::setPictureFormat(const char *format)
{
    set(KEY_PICTURE_FORMAT, format);
}

const char *CameraParameters::getPictureFormat() const
{
    return get(KEY_PICTURE_FORMAT);
}

void CameraParameters::dump() const
{
    ALOGD("dump: mMap.size = %d", mMap.size());
    for (size_t i = 0; i < mMap.size(); i++) {
        String8 k, v;
        k = mMap.keyAt(i);
        v = mMap.valueAt(i);
        ALOGD("%s: %s\n", k.string(), v.string());
    }
}

#ifdef QCOM_HARDWARE
void CameraParameters::setTouchIndexAec(int x, int y)
{
    char str[32];
    snprintf(str, sizeof(str), "%dx%d", x, y);
    set(KEY_TOUCH_INDEX_AEC, str);
}

void CameraParameters::getTouchIndexAec(int *x, int *y) const
{
    *x = -1;
    *y = -1;

    // Get the current string, if it doesn't exist, leave the -1x-1
    const char *p = get(KEY_TOUCH_INDEX_AEC);
    if (p == 0)
        return;

    int tempX, tempY;
    if (parse_pair(p, &tempX, &tempY, 'x') == 0) {
        *x = tempX;
        *y = tempY;
    }
}

void CameraParameters::setTouchIndexAf(int x, int y)
{
    char str[32];
    snprintf(str, sizeof(str), "%dx%d", x, y);
    set(KEY_TOUCH_INDEX_AF, str);
}

void CameraParameters::getMeteringAreaCenter(int *x, int *y) const
{
    //Default invalid values
    *x = -2000;
    *y = -2000;

    const char *p = get(KEY_METERING_AREAS);
    if(p != NULL) {
        int arr[5] = {-2000, -2000, -2000, -2000, 0};
        parseNDimVector(p, arr, 5); //p = "(x1, y1, x2, y2, weight)"
        *x = (arr[0] + arr[2])/2; //center_x = (x1+x2)/2
        *y = (arr[1] + arr[3])/2; //center_y = (y1+y2)/2
    }
}

void CameraParameters::getTouchIndexAf(int *x, int *y) const
{
    *x = -1;
    *y = -1;

    // Get the current string, if it doesn't exist, leave the -1x-1
    const char *p = get(KEY_TOUCH_INDEX_AF);
    if (p == 0)
        return;

    int tempX, tempY;
    if (parse_pair(p, &tempX, &tempY, 'x') == 0) {
        *x = tempX;
        *y = tempY;
    }
}
#endif

status_t CameraParameters::dump(int fd, const Vector<String16>& args) const
{
    const size_t SIZE = 256;
    char buffer[SIZE];
    String8 result;
    snprintf(buffer, 255, "CameraParameters::dump: mMap.size = %d\n", mMap.size());
    result.append(buffer);
    for (size_t i = 0; i < mMap.size(); i++) {
        String8 k, v;
        k = mMap.keyAt(i);
        v = mMap.valueAt(i);
        snprintf(buffer, 255, "\t%s: %s\n", k.string(), v.string());
        result.append(buffer);
    }
    write(fd, result.string(), result.size());
    return NO_ERROR;
}

#ifdef PANTECH_CAMERA_HARDWARE

const char CameraParameters::H324MVT_ON[] = "on";
const char CameraParameters::KEY_REFLECT[] = "pantech-reflect";
const char CameraParameters::REFLECT_OFF[] = "off";
const char CameraParameters::KEY_ANTISHAKE[] = "pantech-antishake";
const char CameraParameters::ANTISHAKE_ON[] = "on";
const char CameraParameters::ANTISHAKE_OFF[] = "off";	
const char CameraParameters::KEY_MULTISHOT[] = "pantech-multishot";
const char CameraParameters::MULTISHOT_OFF[] = "off";
const char CameraParameters::MULTISHOT_ON[] = "on";
const char CameraParameters::REFLECT_WATER[] = "water";   
const char CameraParameters::KEY_FOCUS_STEP[] = "pantech-focus-step";
const char CameraParameters::REFLECT_MIRROR[] = "mirror";
    
const char CameraParameters::EFFECT_CONTRAST[] = "contrast";	
const char CameraParameters::FOCUS_MODE_SPOT[] = "spot";
	
const char CameraParameters::SCENE_MODE_DAWN[] = "dawn";
const char CameraParameters::SCENE_MODE_TEXT[] = "text";
const char CameraParameters::SCENE_MODE_AUTUMN[] = "autumn";
const char CameraParameters::SCENE_MODE_INDOOR[] = "indoor";
	
const char CameraParameters::FACE_FILTER_KISS[] = "kiss";
const char CameraParameters::FACE_FILTER_LOMO[] = "lomo";
const char CameraParameters::FACE_FILTER_MONO[] = "mono";
const char CameraParameters::FACE_FILTER_POOH[] = "pooh";
const char CameraParameters::FACE_FILTER_SICK[] = "sick";
const char CameraParameters::FACE_FILTER_SNOW[] = "snow";
const char CameraParameters::FACE_FILTER_TEAR[] = "tear";
const char CameraParameters::FACE_FILTER_ANGRY[] = "angry";
const char CameraParameters::FACE_FILTER_CROWN[] = "crown";
const char CameraParameters::FACE_FILTER_PUNCH[] = "punch";
const char CameraParameters::FACE_FILTER_ABSURD[] = "absurd";
const char CameraParameters::FACE_FILTER_HEATUP[] = "heatup";
const char CameraParameters::FACE_FILTER_MOSAIC[] = "mosaic";
const char CameraParameters::FACE_FILTER_PIRATE[] = "priate";
const char CameraParameters::FACE_FILTER_BIGHEAD[] = "bighead";
const char CameraParameters::FACE_FILTER_CONCAVE[] = "concave";
const char CameraParameters::FACE_FILTER_FISHEYE[] = "fisheye";
const char CameraParameters::FACE_FILTER_VERTIGO[] = "vertigo";
const char CameraParameters::FACE_FILTER_OUTFOCUS[] = "outfocus";
const char CameraParameters::FACE_FILTER_GENTLEMAN[] = "gentleman";
const char CameraParameters::FACE_FILTER_SHEEPHOOD[] = "sheephood";
const char CameraParameters::FACE_FILTER_BEAUTYBLUR[] = "beautyblur";
const char CameraParameters::FACE_FILTER_FACEDETECT[] = "facedetect";
const char CameraParameters::FACE_FILTER_RADIALBLUR[] = "radialblur";
const char CameraParameters::FACE_FILTER_FACIALCOLOR[] = "facialcolor";
const char CameraParameters::FACE_FILTER_SMILEDETECT[] = "smiledetect";
const char CameraParameters::FACE_FILTER_SELFSHOTHELPER[] = "selfshothelper";
	
const char CameraParameters::FACE_FILTER_OFF[] = "off";
const char CameraParameters::KEY_FACE_FILTER[] = "pantech-face-filter";	
const char CameraParameters::KEY_FACE_FILTER_ROTATION[] = "pantech-face-rotation";
const char CameraParameters::KEY_FACE_FILTER_RECT[] = "pantech-face-filter-rect";
const char CameraParameters::KEY_FACE_SMILE_SCORE[] = "pantech-face-smile-score";
const char CameraParameters::KEY_FACE_SELFSHOT_NUM[] = "pantech-selfshot-num";
	
const char CameraParameters::AUTO_EXPOSURE_OFF[] = "off";
const char CameraParameters::WHITE_BALANCE_OFF[] = "off";
const char CameraParameters::REFLECT_MIRROR_WATER[] = "mirror-water";
const char CameraParameters::KEY_FOCUS_COORDINATES[] = "pantech-focus-coordinates";
const char CameraParameters::KEY_SUPPORTED_REFLECT[] = "pantech-reflect-values";
const char CameraParameters::FLASH_MODE_TORCH_FLASH[] = "torch_flash";
const char CameraParameters::KEY_SUPPORTED_ANTISHAKE[] = "pantech-antishake-values";
const char CameraParameters::KEY_SUPPORTED_MULTISHOT[] = "pantech-multishot-values";
const char CameraParameters::KEY_SUPPORTED_FACE_FILTER[] = "pantech-face-filter-values";

const char CameraParameters::KEY_VT[] = "pantech-vt";
const char CameraParameters::VT_OFF[] = "off";
const char CameraParameters::HDVT_ON[] = "on";
const char CameraParameters::LGTVT_ON[] = "on";
//const char CameraParameters::IS_WS[] = "wangsai_008";
	
const char CameraParameters::VTS_ON[] = "on";
const char CameraParameters::VTS_OFF[] = "off";
const char CameraParameters::KEY_VTS[] = "pantech-vts";


int CameraParameters::isRunning()
{
	//if(isws())
	    return 0;
//	else
	//    return -1;
}

int CameraParameters::getOlaRotation() const
{
	return getInt(KEY_FACE_FILTER_ROTATION);
}

void CameraParameters::getFaceFilterRect(int *x, int *y) const
{
	*x = -1;
	*y = -1;
	const char *p = get(KEY_FACE_FILTER_RECT);
	if (p == 0)
		return;
	int tempX, tempY;
	if (parse_pair(p, &tempX, &tempY, 'x') == 0) {
		*x = tempX;
		*y = tempY;
	}
}

void CameraParameters::getFocusCoordinates(int *x, int *y) const
{
	*x = -1;
	*y = -1;
	const char *p = get(KEY_FOCUS_COORDINATES);
	if (p == 0)
		return;
	int tempX, tempY;
	if (parse_pair(p, &tempX, &tempY, 'x') == 0) {
		*x = tempX;
		*y = tempY;
	}
}

void CameraParameters::setFocusCoordinates(int x, int y)
{
    char str[32];
    snprintf(str, sizeof(str), "%dx%d", x, y);
    set(KEY_FOCUS_COORDINATES, str);
}

void CameraParameters::setFaceFilterRect(int width, int height)
{
    char str[32];
    snprintf(str, sizeof(str), "%dx%d", width, height);
    set(KEY_FACE_FILTER_RECT, str);
}

void CameraParameters::setReflect(int reflect)
{
    char str[32];
    snprintf(str, sizeof(str), "%d", reflect);
    set(KEY_REFLECT, str);
}
#endif

}; // namespace android
