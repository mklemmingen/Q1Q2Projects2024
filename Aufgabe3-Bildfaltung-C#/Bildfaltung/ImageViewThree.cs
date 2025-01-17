using Eto.Forms;
using Eto.Drawing;
public class ImageViewThree : Form
{
    public ImageViewThree(string PictureName1, Image image1, string PictureName2, Image image2, string PictureName3, Image image3)
    {
        Title = "PGM Image Viewer by MKL";
        ClientSize = new Size(image1.width*3, image1.height);

        Content = new TableLayout
        {
            Spacing = new Size(5, 5), // space between each cell
            Padding = new Padding(10, 10, 10, 10), // space around the table's sides
            Rows =
            {
                new TableRow(
                    new TableCell(new Label { Text = PictureName1 }, true), 
                    new TableCell(new Label { Text = PictureName2 }, true),
                    new Label { Text = PictureName3 }
                ),
                new TableRow(
                    CreateDrawable(image1, PictureName1),
                    CreateDrawable(image2, PictureName2),
                    CreateDrawable(image3, PictureName3)
                ),
                new TableRow { ScaleHeight = true }
            }
        };
    }

private Drawable CreateDrawable(Image image, string PictureName1)
    {
        var drawable = new Drawable
        {
            Size = new Size(image.width, image.height),
            BackgroundColor = Colors.White,
        };

        drawable.Paint += (sender, e) =>
        {
            int pixelsDrawn = 0;
            int widthLoop = 0;
            int heightLoop = 0;

            int height = image.height;
            int width = image.width;

            int[,] values = image.GetImageArray();
            
            // console print out to tell how many entries are in the array
            Console.Write(PictureName1 + "->Array size: " + values.Length + "\n");

            for (int y = 0; y < height; y++)
            {
                widthLoop++;
                for (int x = 0; x < width; x++)
                {
                    pixelsDrawn++;
                    int value = values[y, x]; // Get the pixel value from the image array
                    // 0 value is white, maxValue is black
                    int colorValue = 255 - (int)(255.0 * value / image.maxValue);
                    Color color = Color.FromArgb(colorValue, colorValue, colorValue);
                    e.Graphics.FillRectangle(color, x, y, 1, 1);
                    heightLoop++;
                }
            }
            Console.Write(PictureName1 + "->Pixels drawn:" + pixelsDrawn);
            Console.Write("| Run the loop: " + widthLoop + "x" + heightLoop + "\n");
        };
        return drawable;
    }

}

