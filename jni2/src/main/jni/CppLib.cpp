#include "com_eric_demo_JavaMain.h"
#include "jni.h"
JNIEXPORT void JNICALL Java_com_eric_demo_JavaMain_show
  (JNIEnv * env, jobject jb){
      printf("%s","cpp library\n");
}
