#ifdef ANDROID
#include <jni.h>
#include <android/log.h>
JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_MainActivity_nativeBackPressed(JNIEnv* env, jobject this){
    __android_log_write(ANDROID_LOG_ERROR, "MCPE081DECOMP", "Java_com_mojang_minecraftpe_MainActivity_nativeBackPressed - not implemented");
}
JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_MainActivity_nativeBackSpacePressed(JNIEnv* env, jobject this){
    __android_log_write(ANDROID_LOG_ERROR, "MCPE081DECOMP", "Java_com_mojang_minecraftpe_MainActivity_nativeBackSpacePressed - not implemented");
}
JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_MainActivity_nativeLoginData(JNIEnv* env, jobject this, jstring a, jstring b, jstring c, jstring d){
    __android_log_write(ANDROID_LOG_ERROR, "MCPE081DECOMP", "Java_com_mojang_minecraftpe_MainActivity_nativeLoginData - not implemented");
}
JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_MainActivity_nativeRegisterThis(JNIEnv* env, jobject this){
    __android_log_write(ANDROID_LOG_ERROR, "MCPE081DECOMP", "Java_com_mojang_minecraftpe_MainActivity_nativeRegisterThis - not implemented");
}
JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_MainActivity_nativeReturnKeyPressed(JNIEnv* env, jobject this){
    __android_log_write(ANDROID_LOG_ERROR, "MCPE081DECOMP", "Java_com_mojang_minecraftpe_MainActivity_nativeReturnKeyPressed - not implemented");
}
JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_MainActivity_nativeSetTextboxText(JNIEnv* env, jobject this, jstring s){
    __android_log_write(ANDROID_LOG_ERROR, "MCPE081DECOMP", "Java_com_mojang_minecraftpe_MainActivity_nativeSetTextboxText - not implemented");
}
JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_MainActivity_nativeStopThis(JNIEnv* env, jobject this){
    __android_log_write(ANDROID_LOG_ERROR, "MCPE081DECOMP", "Java_com_mojang_minecraftpe_MainActivity_nativeStopThis - not implemented");
}
JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_MainActivity_nativeSuspend(JNIEnv* env, jobject this){
    __android_log_write(ANDROID_LOG_ERROR, "MCPE081DECOMP", "Java_com_mojang_minecraftpe_MainActivity_nativeSuspend - not implemented");
}
JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_MainActivity_nativeTypeCharacter(JNIEnv* env, jobject this, jstring s){
    __android_log_write(ANDROID_LOG_ERROR, "MCPE081DECOMP", "Java_com_mojang_minecraftpe_MainActivity_nativeTypeCharacter - not implemented");
}
JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_MainActivity_nativeUnregisterThis(JNIEnv* env, jobject this){
    __android_log_write(ANDROID_LOG_ERROR, "MCPE081DECOMP", "Java_com_mojang_minecraftpe_MainActivity_nativeUnregisterThis - not implemented");
}
JNIEXPORT void JNICALL Java_com_mojang_minecraftpe_MainActivity_nativeWebRequestCompleted(JNIEnv* env, jobject this, jint a2, jlong a3, jint a4, jstring a5){
    __android_log_write(ANDROID_LOG_ERROR, "MCPE081DECOMP", "Java_com_mojang_minecraftpe_MainActivity_nativeWebRequestCompleted - not implemented");
}
JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    //TODO some stuff
    return JNI_VERSION_1_6;
}
#endif
