using Eto.Forms;
using Eto.Drawing;
public class ImageViewThree : Form
{
    public ImageViewThree(string PictureName1, Image image1, string PictureName2, Image image2, string PictureName3, Image image3)
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
                    new Label { Text = PictureName3 }
                ),
                new TableRow(
                    CreateDrawable(image1),
                    CreateDrawable(image2),
                    CreateDrawable(image3)
                ),
                new TableRow { ScaleHeight = true }
            }
        };
    }

    private Drawable CreateDrawable(Image image)
    {
        var drawable = new Drawable
        {
            Size = new Size(400, 400),
            BackgroundColor = Colors.White,
        };

        drawable.Paint += (sender, e) =>
        {
            int[,] values = image.GetImageArray();
            for (int y = 0; y < image.height; y++)
            {
                for (int x = 0; x < image.width; x++)
                {
                    int value = values[x, y]; // Get the pixel value from the image array
                    // 0 value is white, maxValue is black
                    int colorValue = 255 - (int)(255.0 * value / image.maxValue);
                    Color color = Color.FromArgb(colorValue, colorValue, colorValue);
                    e.Graphics.FillRectangle(color, x * 2, y * 2, 2, 2);
                }
            }
        };

        return drawable;
    }

}

