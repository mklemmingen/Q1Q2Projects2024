public class Kernel {
    public int Size { get; }
    public double[,] Values { get; }

    public Kernel(int size, double[,] values) {
        Size = size;
        Values = values;
    }
}