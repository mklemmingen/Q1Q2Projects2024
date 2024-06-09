using System.IO;
using Eto.Forms;
using Eto.Drawing;

// logic to perform the filter operations with both zero-padding and clamping ( 1 - 9 )

// ------------ SETUP ------------

// printing that setup is starting
Console.WriteLine("Setup is starting...");

// Variables

Image Bild1 = new Image();
Image Bild2 = new Image();

Image Ergebnis1HorizontalZeroPad = new Image();
string Ergebnis1HorizontalZeroPadPath = "Ergebnis1-horizontal-ZeroPad";
Image Ergebnis1VerticalZeroPad = new Image();
string Ergebnis1VerticalZeroPadPath = "Ergebnis1-vertical-ZeroPad";

Image Ergebnis1HorizontalClamp = new Image();
string Ergebnis1HorizontalClampPath = "Ergebnis1-horizontal-Clamp";
Image Ergebnis1VerticalClamp = new Image();
string Ergebnis1VerticalClampPath = "Ergebnis1-vertical-Clamp";

Image Ergebnis2_3_Zero = new Image();
string Ergebnis2_3_Zero_Path = "Ergebnis2-3-Zero";
Image Ergebnis2_3_Clamp = new Image();
string Ergebnis2_3_Clamp_Path = "Ergebnis2-3-Clamp";

Image Ergebnis2_11_Zero = new Image();
string Ergebnis2_11_Zero_Path = "Ergebnis2-11-Zero";
Image Ergebnis2_11_Clamp = new Image();
string Ergebnis2_11_ClampPath = "Ergebnis2-11-Clamp";


Image Ergebnis2_27_Zero = new Image();
string Ergebnis2_27_Zero_Path = "Ergebnis2-27-Zero";
Image Ergebnis2_27 = new Image();
string Ergebnis2_27Path = "Ergebnis2-27";
Image Ergebnis2_27_Clamp = new Image();
string Ergebnis2_27_ClampPath = "Ergebnis2-27-Clamp";

// Paths
// directory
string ProjectFolder = Path.GetFullPath(Path.Combine(Directory.GetCurrentDirectory(), @"..\..\..\"));
String ZeroPaddedFolder = "ZeroPadded";
string DummiesFolder = "Dummies";
String ClampFolder = "Clamped";

// images
string Bild1Path = "Bild3.pgm";
string Bild2Path = "Bild4.pgm";

// 1. Load the given images (Bild1.pgm and Bild2.pgm)

// Bild 1: filtered once with horizontal, once with vertical prewitt
// save as Ergebnis1-horizontal.pgm and Ergebnis1-vertical.pgm later on
Console.WriteLine("Loading Bild1.pgm...");
Bild1.ReadFromFile(Path.Combine(ProjectFolder, DummiesFolder, Bild1Path));

// Bild 2: filtered with a box filter of sizes 3, 11 and 27. 
// save as Ergebnis 2-3.pgm, Ergebnis 2-11.pgm and Ergebnis 2-27.pgm later on
Console.WriteLine("Loading Bild2.pgm...");
Bild2.ReadFromFile(Path.Combine(ProjectFolder, DummiesFolder, Bild2Path));


// ------------ BILD 1 ------------

// 2. Create instances of ZeroPaddingBorderBehavior and ClampingBorderBehavior

Console.WriteLine("Creating border behaviors...");
ZeroPaddingBorderBehavior zeroPadding = new ZeroPaddingBorderBehavior();
ClampingBorderBehavior clamping = new ClampingBorderBehavior();

// 3. Create instances of the vertical and horizontal Prewitt filters using KernelFactory

Console.WriteLine("Creating Prewitt filters...");
Kernel prewittHorizontal = KernelFactory.CreatePrewittHorizontal();
Kernel prewittVertical = KernelFactory.CreatePrewittVertical();

// 4. Convolve the loaded images with the Prewitt filters using both border behaviors
// add type of padding as new name of file
// save the images with a timestamp to avoid overwriting the previous results
// Note: We might want to create separate Image instances for each convolution result

Console.WriteLine("Convolving Bild1 with Prewitt filters...");

Ergebnis1HorizontalZeroPad = Bild1.Convolve(prewittHorizontal, zeroPadding);
Ergebnis1VerticalZeroPad = Bild1.Convolve(prewittVertical, zeroPadding);

Ergebnis1HorizontalClamp = Bild1.Convolve(prewittHorizontal, clamping);
Ergebnis1VerticalClamp = Bild1.Convolve(prewittVertical, clamping);

// 5. Save the results of the convolutions as pgm images in the ZeroPadded and Clamped folders
// save the images with a timestamp to avoid overwriting the previous results
// Note: We might want to consider using a naming convention that includes the filter 
// and border behavior used

// zero padding

Console.WriteLine("Saving Ergebnis1 horizontal zero pad as pgm images...");
Ergebnis1HorizontalZeroPadPath = Path.Combine(ProjectFolder, ZeroPaddedFolder, Ergebnis1HorizontalZeroPadPath + 
DateTime.Now.ToString("yyyyMMddHHmmss") + ".pgm");
Ergebnis1HorizontalZeroPad.WriteToFile(Ergebnis1HorizontalZeroPadPath);

Console.WriteLine("Saving Ergebnis1 vertical as pgm images...");
Ergebnis1VerticalZeroPadPath = Path.Combine(ProjectFolder, ZeroPaddedFolder, Ergebnis1VerticalZeroPadPath +
DateTime.Now.ToString("yyyyMMddHHmmss") + ".pgm");
Ergebnis1VerticalZeroPad.WriteToFile(Ergebnis1VerticalZeroPadPath);

// clamping

Console.WriteLine("Saving Ergebnis1 horizontal clamped as pgm images...");
Ergebnis1HorizontalClampPath = Path.Combine(ProjectFolder, ClampFolder, Ergebnis1HorizontalClampPath +
DateTime.Now.ToString("yyyyMMddHHmmss") + ".pgm");
Ergebnis1HorizontalClamp.WriteToFile(Ergebnis1HorizontalClampPath);

Console.WriteLine("Saving Ergebnis1 vertical clamped as pgm images...");
Ergebnis1VerticalClampPath = Path.Combine(ProjectFolder, ClampFolder, Ergebnis1VerticalClampPath +
DateTime.Now.ToString("yyyyMMddHHmmss") + ".pgm");
Ergebnis1VerticalClamp.WriteToFile(Ergebnis1VerticalClampPath);


// ------------ BILD 2 ------------

// 6. Create instances of the Box filters of sizes 3, 11, and 27 using KernelFactory

Console.WriteLine("Creating Box filters...");
Kernel box3 = KernelFactory.CreateBox(3);
Kernel box11 = KernelFactory.CreateBox(11);
Kernel box27 = KernelFactory.CreateBox(27);

// 7. Convolve the loaded images with the Box filters using both border behaviors
// as filename, add the size of the box filter

Console.WriteLine("Convolving Bild2 with Box filters...");
Ergebnis2_3_Zero = Bild2.Convolve(box3, zeroPadding);
Ergebnis2_11_Zero = Bild2.Convolve(box11, zeroPadding);
Ergebnis2_27_Zero = Bild2.Convolve(box27, zeroPadding);

Ergebnis2_3_Clamp = Bild2.Convolve(box3, clamping);
Ergebnis2_11_Clamp = Bild2.Convolve(box11, clamping);
Ergebnis2_27_Clamp = Bild2.Convolve(box27, clamping);

// 8. Save the results of the convolutions as pgm images in the ZeroPadded and Clamped folders
// save the images with a timestamp to avoid overwriting the previous results

Console.WriteLine("Saving Ergebnis2_3 as pgm image...");
Ergebnis2_3_Zero_Path = Path.Combine(ProjectFolder, ZeroPaddedFolder, Ergebnis2_3_Zero_Path +
DateTime.Now.ToString("yyyyMMddHHmmss") + ".pgm");
Ergebnis2_3_Zero.WriteToFile(Ergebnis2_3_Zero_Path);
Ergebnis2_3_Clamp_Path = Path.Combine(ProjectFolder, ClampFolder, Ergebnis2_3_Clamp_Path +
DateTime.Now.ToString("yyyyMMddHHmmss") + ".pgm");
Ergebnis2_3_Clamp.WriteToFile(Ergebnis2_3_Clamp_Path);

Console.WriteLine("Saving Ergebnis2_11 as pgm image...");
Ergebnis2_11_Zero_Path = Path.Combine(ProjectFolder, ZeroPaddedFolder, Ergebnis2_11_Zero_Path +
DateTime.Now.ToString("yyyyMMddHHmmss") + ".pgm");
Ergebnis2_11_Zero.WriteToFile(Ergebnis2_11_Zero_Path);
Ergebnis2_11_ClampPath = Path.Combine(ProjectFolder, ClampFolder, Ergebnis2_11_ClampPath +
DateTime.Now.ToString("yyyyMMddHHmmss") + ".pgm");
Ergebnis2_11_Clamp.WriteToFile(Ergebnis2_11_ClampPath);

Console.WriteLine("Saving Ergebnis2_27 as pgm image...");
Ergebnis2_27_Zero_Path = Path.Combine(ProjectFolder, ZeroPaddedFolder, Ergebnis2_27_Zero_Path +
DateTime.Now.ToString("yyyyMMddHHmmss") + ".pgm");
Ergebnis2_27_Zero.WriteToFile(Ergebnis2_27_Zero_Path);

// ------------ DISPLAY ------------

var thread = new Thread(() =>
{
// Start the application event loop
Application app;
if (Environment.OSVersion.Platform == PlatformID.Win32NT)
{
    app = new Application(new Eto.Wpf.Platform());
}
else if (Environment.OSVersion.Platform == PlatformID.Unix)
{
    //app = new Application(new Eto.Gtk.Platform());
    throw new NotSupportedException("Unsupported platform");
}
else if (Environment.OSVersion.Platform == PlatformID.MacOSX)
{
    app = new Application(new Eto.Mac.Platform());
}
else
{
    throw new NotSupportedException("Unsupported platform");
}

// displaying Images Alone is used for debugging, since pixel drawn counter is used
bool displayImagesAlone = false;

if(displayImagesAlone)
{
    // Display the loaded images
    Console.WriteLine("Displaying Bild1 images: Prewitt Filters: ...");
    // printArray(Bild1.GetImageArray());
    ImageView imageView1 = new ImageView("Bild1", Bild1);
    imageView1.Show();
    // printArray(Ergebnis1Horizontal.GetImageArray());
    ImageView imageView1horizont = new ImageView("Ergebnis1-horizontal-ZeroPad", Ergebnis1HorizontalZeroPad);
    imageView1horizont.Show();
    // printArray(Ergebnis1Vertical.GetImageArray());
    ImageView imageView1vertical = new ImageView("Ergebnis1-vertical-ZeroPad", Ergebnis1VerticalZeroPad);
    imageView1vertical.Show();
    //printArray(Ergebnis1Vertical.GetImageArray());
    ImageView imageView1horizontClamp = new ImageView("Ergebnis1-horizontal-Clamp", Ergebnis1HorizontalClamp);
    imageView1horizontClamp.Show();
    //printArray(Ergebnis1Vertical.GetImageArray());
    ImageView imageView1verticalClamp = new ImageView("Ergebnis1-vertical-Clamp", Ergebnis1VerticalClamp);
    imageView1verticalClamp.Show();

    Console.WriteLine("Displaying Bild2 images: Box Filters: ...");
    // printArray(Bild2.GetImageArray());
    ImageView imageView2 = new ImageView("Bild2", Bild2);
    imageView2.Show();
    // printArray(Ergebnis2_3.GetImageArray());
    ImageView imageView2_3 = new ImageView("Ergebnis2-3", Ergebnis2_3_Zero);
    imageView2_3.Show();
    // printArray(Ergebnis2_11.GetImageArray());
    ImageView imageView2_11 = new ImageView("Ergebnis2-11", Ergebnis2_11_Zero);
    imageView2_11.Show();
    // printArray(Ergebnis2_27.GetImageArray());
    ImageView imageView2_27 = new ImageView("Ergebnis2-27", Ergebnis2_27_Zero);
    imageView2_27.Show();
    // printArray(Ergebnis2_3.GetImageArray());
    ImageView imageView2_3_Clamp = new ImageView("Ergebnis2-3-Clamp", Ergebnis2_3_Clamp);
    imageView2_3_Clamp.Show();
    // printArray(Ergebnis2_11.GetImageArray());
    ImageView imageView2_11_Clamp = new ImageView("Ergebnis2-11-Clamp", Ergebnis2_11_Clamp);
    imageView2_11_Clamp.Show();
    // printArray(Ergebnis2_27.GetImageArray());
    ImageView imageView2_27_Clamp = new ImageView("Ergebnis2-27-Clamp", Ergebnis2_27_Clamp);
    imageView2_27_Clamp.Show();
} else {
// 9. Display the loaded images and all the results of the convolutions on the screen   
// Bild1:
Console.WriteLine("Displaying Bild1...");
// create ImageViewThree for zeropad
ImageViewThree imageViewThree = new ImageViewThree("Bild1", Bild1, "Ergebnis1-horizontal-ZeroPad", 
Ergebnis1HorizontalZeroPad, "Ergebnis1-vertical-ZeroPad", Ergebnis1VerticalZeroPad);
imageViewThree.Show();
// create ImageViewThree for clamp
ImageViewThree imageViewThreeClamp = new ImageViewThree("Bild1", Bild1, "Ergebnis1-horizontal-Clamp",
Ergebnis1HorizontalClamp, "Ergebnis1-vertical-Clamp", Ergebnis1VerticalClamp);
imageViewThreeClamp.Show();

// Bild2:
Console.WriteLine("Displaying Bild2...");
// create ImageViewFour
ImageViewFour imageViewFour = new ImageViewFour("Bild2", Bild2, "Ergebnis2-3-Zero", Ergebnis2_3_Zero, 
"Ergebnis2-11-Zero", Ergebnis2_11_Zero, "Ergebnis2-27-Zero", Ergebnis2_27_Zero);
imageViewFour.Show();
// create ImageViewFour for clamp
ImageViewFour imageViewFourClamp = new ImageViewFour("Bild2", Bild2, "Ergebnis2-3-Clamp", Ergebnis2_3_Clamp, 
"Ergebnis2-11-Clamp", Ergebnis2_11_Clamp, "Ergebnis2-27-Clamp", Ergebnis2_27_Clamp);
imageViewFourClamp.Show();
}

app.Run();
});
thread.SetApartmentState(ApartmentState.STA); // Set the thread to STA
thread.Start();
thread.Join(); 

void printArray(int[,] array)
{
    for (int i = 0; i < array.GetLength(0); i++)
    {
        for (int j = 0; j < array.GetLength(1); j++)
        {
            Console.Write(array[i, j] + " ");
        }
        Console.WriteLine();
    }
}