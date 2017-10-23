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
