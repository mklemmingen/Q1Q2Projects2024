public class ZeroPaddingBorderBehavior : BorderBehavior
{
    public override int GetPixelValue(int i, int j, Image image)
    {
        // logic to return 0 for (i, j) outside of the image
    }
}