using Eto.Forms;
using Eto.Drawing;
public class ImageViewFour : Form
{
    public ImageViewFour(string PictureName1, Image image1, string PictureName2, Image image2, string PictureName3, Image image3, string PictureName4, Image image4)
    {
        Title = "ImageViewer";
        ClientSize = new Size(1200, 800);

        Content = new TableLayout
        {
            Spacing = new Size(5, 5), // space between each cell
            Padding = new Padding(10, 10, 10, 10), // space around the table's sides
            Rows =
            {
                new TableRow(
                    new TableCell(new Label { Text = PictureName1 }, true), 
                    new TableCell(new Label { Text = PictureName2 }, true),
                    new TableCell(new Label { Text = PictureName3 }, true),
                    new TableCell(new Label { Text = PictureName4 }, true)
                ),
                new TableRow(
                    CreateDrawable(image1, PictureName1),
                    CreateDrawable(image2, PictureName2),
                    CreateDrawable(image3, PictureName3),
                    CreateDrawable(image4, PictureName4)
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
            int[,] values = image.GetImageArray();
            for (int y = 0; y < image.height; y++)
            {
                for (int x = 0; x < image.width; x++)
                {
                    pixelsDrawn++;
                    int value = values[x, y]; // Get the pixel value from the image array
                    // 0 value is white, maxValue is black
                    int colorValue = 255 - (int)(255.0 * value / image.maxValue);
                    Color color = Color.FromArgb(colorValue, colorValue, colorValue);
                    e.Graphics.FillRectangle(color, x, y, 1, 1);
                }
            }
            Console.WriteLine(PictureName1 + "->Pixels drawn:" + pixelsDrawn +"|");
        };

        return drawable;
    }

}

