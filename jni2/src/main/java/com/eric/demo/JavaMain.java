package com.eric.demo;
//javah com.eric.demo.JavaMain
//javac com.eric.demo.JavaMain.java
//java com.eric.demo.JavaMain  -Djava.library.path=/code/jni2/src/main/jni
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
