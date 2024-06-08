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

Image Ergebnis1Horizontal = new Image();
string Ergebnis1HorizontalPath = "Ergebnis1-horizontal.pgm";
Image Ergebnis1Vertical = new Image();
string Ergebnis1VerticalPath = "Ergebnis1-vertical.pgm";

Image Ergebnis2_3 = new Image();
string Ergebnis2_3Path = "Ergebnis2-3.pgm";
Image Ergebnis2_11 = new Image();
string Ergebnis2_11Path = "Ergebnis2-11.pgm";
Image Ergebnis2_27 = new Image();
string Ergebnis2_27Path = "Ergebnis2-27.pgm";

// Paths
// directory
string ProjectFolder = Path.GetFullPath(Path.Combine(Directory.GetCurrentDirectory(), @"..\..\..\"));
String ZeroPaddedFolder = "ZeroPadded";
string DummiesFolder = "Dummies";

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
Ergebnis1Horizontal = Bild1.Convolve(prewittHorizontal, zeroPadding);
Ergebnis1Vertical = Bild1.Convolve(prewittVertical, zeroPadding);

// 5. Save the results of the convolutions as pgm images in the ZeroPadded and Clamped folders
// save the images with a timestamp to avoid overwriting the previous results
// Note: We might want to consider using a naming convention that includes the filter 
// and border behavior used

Console.WriteLine("Saving Ergebnis1 horizontal as pgm images...");
Ergebnis1HorizontalPath = Path.Combine(ProjectFolder, ZeroPaddedFolder, Ergebnis1HorizontalPath + 
DateTime.Now.ToString("yyyyMMddHHmmss") + ".pgm");
Ergebnis1Horizontal.WriteToFile(Ergebnis1HorizontalPath);

Console.WriteLine("Saving Ergebnis1 vertical as pgm images...");
Ergebnis1VerticalPath = Path.Combine(ProjectFolder, ZeroPaddedFolder, Ergebnis1VerticalPath +
DateTime.Now.ToString("yyyyMMddHHmmss") + ".pgm");
Ergebnis1Vertical.WriteToFile(Ergebnis1VerticalPath);

// ------------ BILD 2 ------------

// 6. Create instances of the Box filters of sizes 3, 11, and 27 using KernelFactory

Console.WriteLine("Creating Box filters...");
Kernel box3 = KernelFactory.CreateBox(3);
Kernel box11 = KernelFactory.CreateBox(11);
Kernel box27 = KernelFactory.CreateBox(27);

// 7. Convolve the loaded images with the Box filters using both border behaviors
// as filename, add the size of the box filter

Console.WriteLine("Convolving Bild2 with Box filters...");
Ergebnis2_3 = Bild2.Convolve(box3, zeroPadding);
Ergebnis2_11 = Bild2.Convolve(box11, zeroPadding);
Ergebnis2_27 = Bild2.Convolve(box27, zeroPadding);

// 8. Save the results of the convolutions as pgm images in the ZeroPadded and Clamped folders
// save the images with a timestamp to avoid overwriting the previous results

Console.WriteLine("Saving Ergebnis2_3 as pgm image...");
Ergebnis2_3Path = Path.Combine(ProjectFolder, ZeroPaddedFolder, Ergebnis2_3Path +
DateTime.Now.ToString("yyyyMMddHHmmss") + ".pgm");
Ergebnis2_3.WriteToFile(Ergebnis2_3Path);

Console.WriteLine("Saving Ergebnis2_11 as pgm image...");
Ergebnis2_11Path = Path.Combine(ProjectFolder, ZeroPaddedFolder, Ergebnis2_11Path +
DateTime.Now.ToString("yyyyMMddHHmmss") + ".pgm");
Ergebnis2_11.WriteToFile(Ergebnis2_11Path);

Console.WriteLine("Saving Ergebnis2_27 as pgm image...");
Ergebnis2_27Path = Path.Combine(ProjectFolder, ZeroPaddedFolder, Ergebnis2_27Path +
DateTime.Now.ToString("yyyyMMddHHmmss") + ".pgm");
Ergebnis2_27.WriteToFile(Ergebnis2_27Path);

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

bool displayImagesAlone = true;

if(displayImagesAlone)
{
    // Display the loaded images
    Console.WriteLine("Displaying Bild1 images: Prewitt Filters: ...");
    // printArray(Bild1.GetImageArray());
    Console.Write("Bild1: ");
    ImageView imageView1 = new ImageView("Bild1", Bild1);
    imageView1.Show();
    // printArray(Ergebnis1Horizontal.GetImageArray());
    Console.Write("Ergebnis1-horizontal: ");
    ImageView imageView1horizont = new ImageView("Ergebnis1-horizontal", Ergebnis1Horizontal);
    imageView1horizont.Show();
    // printArray(Ergebnis1Vertical.GetImageArray());
    Console.WriteLine("Ergebnis1-vertical: ");
    ImageView imageView1vertical = new ImageView("Ergebnis1-vertical", Ergebnis1Vertical);
    imageView1vertical.Show();

    Console.WriteLine("Displaying Bild2 images: Box Filters: ...");
    // printArray(Bild2.GetImageArray());
    Console.Write("Bild2: ");
    ImageView imageView2 = new ImageView("Bild2", Bild2);
    imageView2.Show();
    // printArray(Ergebnis2_3.GetImageArray());
    Console.Write("Ergebnis2-3: ");
    ImageView imageView2_3 = new ImageView("Ergebnis2-3", Ergebnis2_3);
    imageView2_3.Show();
    // printArray(Ergebnis2_11.GetImageArray());
    Console.Write("Ergebnis2-11: ");
    ImageView imageView2_11 = new ImageView("Ergebnis2-11", Ergebnis2_11);
    imageView2_11.Show();
    // printArray(Ergebnis2_27.GetImageArray());
    Console.Write("Ergebnis2-27: ");
    ImageView imageView2_27 = new ImageView("Ergebnis2-27", Ergebnis2_27);
    imageView2_27.Show();
} else {
// 9. Display the loaded images and all the results of the convolutions on the screen   
// Bild1:
Console.WriteLine("Displaying Bild1...");
// create ImageViewThree
ImageViewThree imageViewThree = new ImageViewThree("Bild1", Bild1, "Ergebnis1-horizontal", Ergebnis1Horizontal, "Ergebnis1-vertical", Ergebnis1Vertical);
imageViewThree.Show();

// Bild2:
Console.WriteLine("Displaying Bild2...");
// create ImageViewFour
ImageViewFour imageViewFour = new ImageViewFour("Bild2", Bild2, "Ergebnis2-3", Ergebnis2_3, "Ergebnis2-11", Ergebnis2_11, "Ergebnis2-27", Ergebnis2_27);
imageViewFour.Show();
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