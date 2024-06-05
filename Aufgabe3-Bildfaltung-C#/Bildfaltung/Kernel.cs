public class Kernel {
    public int Size { get; }
    public int[,] Values { get; }

    public Kernel(int size, int[,] values) {
        Size = size;
        Values = values;
    }
}