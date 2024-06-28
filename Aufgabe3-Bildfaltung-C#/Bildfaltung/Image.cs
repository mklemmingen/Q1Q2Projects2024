using System.Text;

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
    // 0
    // 3
    // 0 

    // We need to read the file, parse the header, 
    // and then read the pixel values
    // --------------------------------------

    private int[,] imageArray = new int[0, 0];

    public int width;
    public int height;
    private string magicNumber = "";
    public int maxValue = 0;

    public void ReadFromFile(string filename)
    {
        // Read the file
        string[] lines = File.ReadAllLines(filename);

        // Parse the header
        magicNumber = lines[0];
        if (magicNumber != "P2")
        {
            throw new Exception($"Invalid PGM file. Expected magic number 'P2', but got '{magicNumber}'");
        }

        // check if there is a # in line 2
        string[] dimensions;
        int lineIndex;
        if (lines[1].Contains("#"))
        {
            dimensions = lines[1].Split(null);
            width = int.Parse(dimensions[0]);
            height = int.Parse(dimensions[1]);
            maxValue = int.Parse(lines[2]);
            lineIndex = 4; // Start reading pixel values from the 5th line
        } else {
            dimensions = lines[2].Split(null);
            width = int.Parse(dimensions[0]);
            height = int.Parse(dimensions[1]);
            maxValue = int.Parse(lines[3]);
            lineIndex = 3; // Start reading pixel values from the 4th line
        }
        Console.WriteLine("Image Read with: " + width + "x" + height + " pixels");

        // Initialize the image array
        imageArray = new int[height, width];

        // Read the pixel values
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (lineIndex >= lines.Length)
                {
                    throw new Exception($"Insufficient data in lines for column {j} at row {i}");
                }

                int pixelValue;
                if (!int.TryParse(lines[lineIndex], out pixelValue))
                {
                    throw new Exception($"Invalid pixel value '{lines[lineIndex]}' at column {j} row {i}");
                }

                imageArray[i, j] = pixelValue;
                lineIndex++; // Move to the next line for the next pixel value
            }
        }
    }



    public void WriteToFile(string filename)
    {
        // Create a list to store the lines of the image
        List<string> lines = new List<string>();

        // Add the header
        lines.Add(magicNumber);

        // Add the dimensions
        lines.Add($"{imageArray.GetLength(1)} {imageArray.GetLength(0)}");

        // Add the maximum value
        lines.Add(maxValue.ToString());
        
        // Add the pixel values
        for (int i = 0; i < imageArray.GetLength(0); i++)
        {
            for (int j = 0; j < imageArray.GetLength(1); j++)
            {
                lines.Add(imageArray[i, j].ToString());
            }
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

        // console print of the current percentage of the image processed
        int totalPixels = imageArray.GetLength(0) * imageArray.GetLength(1);
        Console.WriteLine("Total Pixels before Convolve: " + totalPixels);
        int processedPixels = 0;
        Console.WriteLine("Convolve: Processing image...");

        Console.WriteLine("Completion: ");

        // Iterate over the imageArray and apply the kernel
        for (int i = 0; i < imageArray.GetLength(0); i++)
        {
            for (int j = 0; j < imageArray.GetLength(1); j++)
            {
                // Print the percentage of the image processed
                processedPixels++;
                // Apply the kernel to the pixel at (i, j)
                result.imageArray[i, j] = (int)ConvolvePixel(i, j, kernel, borderBehavior);
            }
            // every 10 percent of the pixels processed, print an "*" without a newline
            if (processedPixels % (totalPixels/10) == 0)
            {
                Console.Write("*");
            }
        }

        Console.WriteLine("\n" + "Total Pixels after Convolve: " + processedPixels);

        // Set the width, height, and maxValue of the result image
        result.width = imageArray.GetLength(1);
        result.height = imageArray.GetLength(0);
        result.maxValue = maxValue;

        return result;
    }

    private double ConvolvePixel(int i, int j, Kernel kernel, BorderBehavior borderBehavior)
    {
        // logic to apply the kernel to a single pixel
        // and return the resulting value

        double sum = 0;

        // Iterate over the kernel and apply it to the pixel at (i, j)
        for (int k = 0; k < kernel.Size; k++)
        {
            for (int l = 0; l < kernel.Size; l++)
            {
                int x = i + k - kernel.Size / 2;
                int y = j + l - kernel.Size / 2;

                // Apply the border behavior to handle out-of-bounds pixels
                double pixelValue = borderBehavior.GetPixelValue(x, y, this);

                // Multiply the pixel value by the kernel value and add it to the sum
                sum += pixelValue * kernel.Values[k, l];
            }
        }
        return Normalize(sum, 0, 255); // Add this line
    }

    // getter for the array
    public int[,] GetImageArray()
    {
        return imageArray;
    }

    private double Normalize(double value, int min, int max)
{
    if (value < min)
    {
        return min;
    }
    else if (value > max)
    {
        return max;
    }
    else
    {
        return value;
    }
}
}