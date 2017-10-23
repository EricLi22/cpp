#include "JavaMain.h"
#include "jni.h"
JNIEXPORT void JNICALL Java_JavaMain_show
  (JNIEnv * env, jobject jb){
      printf("%s","cpp library\n");
}
