using Eto.Forms;
using Eto.Drawing;
public class ImageView : Form
{
    public ImageView(string PictureName1, Image image1)
    {
        Title = "PGM Image Viewer by MKL";
        ClientSize = new Size(image1.width, image1.height + 50);

        Content = new TableLayout
        {
            Spacing = new Size(5, 5), // space between each cell
            Padding = new Padding(10, 10, 10, 10), // space around the table's sides
            Rows =
            {
                new TableRow(
                    new TableCell(new Label { Text = PictureName1 }, true)
                ),
                new TableRow(
                    CreateDrawable(image1, PictureName1)
                )
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

