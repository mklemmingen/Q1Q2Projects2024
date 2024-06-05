public class Image
{
    // --- Research Information about PMG -----

    // simple format for grayscale images
    // The first line is a header that starts with "P2"
    // The second line is the width and height of the image
    // The third line is the maximum value of the pixels
    // The rest of the lines are the pixel values

    // Example:
    // P2
    // 3 3
    // 255
    // 0 0 0
    // 0 255 0
    // 0 0 0

    // We need to read the file, parse the header, 
    // and then read the pixel values
    // --------------------------------------

    private int[,] imageArray;

    public void ReadFromFile(string filename)
    {
        // logic to read a pgm image into a 2D int array
        // and store it in the imageArray field

        // Read the file
        string[] lines = File.ReadAllLines(filename);
        
        // Parse the header
        string header = lines[0];
        string[] dimensions = lines[1].Split(' ');
        int width = int.Parse(dimensions[0]);
        int height = int.Parse(dimensions[1]);
        int maxValue = int.Parse(lines[2]);

        // Initialize the image array
        imageArray = new int[height, width];

        // Read the pixel values
        for (int i = 0; i < height; i++)
        {
            string[] pixelValues = lines[i + 3].Split(' ');
            for (int j = 0; j < width; j++)
            {
                imageArray[i, j] = int.Parse(pixelValues[j]);
            }
        }

        // The imageArray now contains the pixel values of the image
    }

    public void WriteToFile(string filename)
    {
        // logic to write a 2D int array into a pgm image

        // Create a list to store the lines of the image
        List<string> lines = new List<string>();

        // Add the header
        lines.Add("P2");

        // Add the dimensions
        lines.Add($"{imageArray.GetLength(1)} {imageArray.GetLength(0)}");

        // Add the maximum value
        lines.Add("255");
        
        // Add the pixel values
        for (int i = 0; i < imageArray.GetLength(0); i++)
        {
            StringBuilder line = new StringBuilder();
            for (int j = 0; j < imageArray.GetLength(1); j++)
            {
                line.Append(imageArray[i, j]);
                if (j < imageArray.GetLength(1) - 1)
                {
                    line.Append(" ");
                }
            }
            lines.Add(line.ToString());
        }

        // Write the lines to the file
        File.WriteAllLines(filename, lines);
    }

    public Image Convolve(Kernel kernel, BorderBehavior borderBehavior)
    {
        // logic to convolve the image with a filter kernel
        // Returning a new Image as the result of the convolution

        // Create a new Image to store the result
        Image result = new Image();

        // Initialize the imageArray for the result
        result.imageArray = new int[imageArray.GetLength(0), imageArray.GetLength(1)];

        // Iterate over the imageArray and apply the kernel
        for (int i = 0; i < imageArray.GetLength(0); i++)
        {
            for (int j = 0; j < imageArray.GetLength(1); j++)
            {
                // Apply the kernel to the pixel at (i, j)
                result.imageArray[i, j] = ConvolvePixel(i, j, kernel, borderBehavior);
            }
        }

        return result;
    }
}