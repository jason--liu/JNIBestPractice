public class TestJNIPrimitiveArray {
    static {
        System.loadLibrary("hello");
    }

    private native double[] sumAndAverage(int[] num);
    public static void main(String args[]){
        int[] num = {22, 23, 33};
        double[] result = new TestJNIPrimitiveArray().sumAndAverage(num);
        System.out.println("In Java, the sum is " + result[0]);
        System.out.println("In Java, the average " + result[1]);
    }
}