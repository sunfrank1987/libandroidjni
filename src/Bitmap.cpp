//
// Created by fz on 3/13/20.
//

#include "Bitmap.h"
#include "jutils-details.hpp"

using namespace jni;

const char *CJNIBitmapConfig::m_classname = "android/graphics/Bitmap$Config";

CJNIBitmapConfig CJNIBitmapConfig::valueOf(const std::string& name) {
    //

    return CJNIBitmapConfig(call_static_method<jhobject>(m_classname,
                                                   "valueOf", "(Ljava/lang/String;)Landroid/graphics/Bitmap$Config;",
                                                   jcast<jhstring>(name)));
}


const char *CJNIBitmap::m_classname = "android/graphics/Bitmap";

CJNIBitmap CJNIBitmap::createBitmap(int width, int height, const CJNIBitmapConfig &config) {
    return CJNIBitmap(call_static_method<jhobject>(m_classname,
                                                   "createBitmap",
                                                   "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;",
                                                   width, height, config.get_raw()));
}
