public class TestJNIString {
    static {
        System.loadLibrary("hello");
    }

    private native String sayhello(String msg);
    public static void main(String args[]) {
        String result = new TestJNIString().sayhello("Hello from Java");
        System.out.println("In Java, the returned string is :" + result);
    }
}