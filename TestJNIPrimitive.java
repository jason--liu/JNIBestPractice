public class TestJNIPrimitive {
    static {
        System.loadLibrary("hello");
    }

    private native double average (int n1, int n2);
    public static void main(String args[]) {
        System.out.println("In java, the average is " + new TestJNIPrimitive().average(3,2));
    }
}