package com.eric.demo;
/**
* 在java目录下
*
* 生成头文件
* javah com.eric.demo.JavaMain
*
* 编译
* javac com.eric.demo.JavaMain.java
*
* 运行
* java com.eric.demo.JavaMain  -Djava.library.path=/code/jni2/src/main/jni
*/

public class JavaMain{
  public static void main(String[] args){
    System.out.println("Ok!");
    new JavaMain().show();
  }

  public native void show();
  static{
    System.loadLibrary("cpp");
  }
}
