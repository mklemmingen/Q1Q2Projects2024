public class ClampingBorderBehavior : BorderBehavior
{
    public override int GetPixelValue(int i, int j, Image image)
    {
        int width = image.width;
        int height = image.height;

        int clampedI = Math.Max(0, Math.Min(i, width - 1));
        int clampedJ = Math.Max(0, Math.Min(j, height - 1));

        return image.GetImageArray()[clampedI, clampedJ];
    }
}