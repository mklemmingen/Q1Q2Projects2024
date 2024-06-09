public class ZeroPaddingBorderBehavior : BorderBehavior
{
    public override int GetPixelValue(int i, int j, Image image)
    {
        int width = image.width;
        int height = image.height;

        if (i < 0 || i >= width || j < 0 || j >= height)
        { 
            return 0;
        }
        else
        {
            return image.GetImageArray()[i, j];
        }
    }
}