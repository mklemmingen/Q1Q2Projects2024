public class KernelFactory
{
    public static Kernel CreatePrewittVertical()
    {
        // Vertical 3x3 Prewitt filter
        int[,] values = new int[,]
        {
            { -1, 0, 1 },
            { -1, 0, 1 },
            { -1, 0, 1 }
        };
        return new Kernel(3, values);
    }

    public static Kernel CreatePrewittHorizontal()
    {
        // Horizontal 3x3 Prewitt filter
        int[,] values = new int[,]
        {
            { -1, -1, -1 },
            { 0, 0, 0 },
            { 1, 1, 1 }
        };
        return new Kernel(3, values);
    }

    public static Kernel CreateBox(int size)
    {
        // Square Box filter of the given size
        int[,] values = new int[size, size];
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                values[i, j] = 1;
            }
        }
        return new Kernel(size, values);
    }
}
