public class HelloJNI {
    static {
        System.out.println(System.getProperty("java.library.path"));
        System.loadLibrary("hello");
    }

    private native void sayhello();
    public static void main(String[] args) {
        new HelloJNI().sayhello();
    }
}