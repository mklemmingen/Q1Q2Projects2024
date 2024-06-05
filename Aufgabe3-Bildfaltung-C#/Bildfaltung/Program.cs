using System.IO;

// logic to perform the filter operations with both zero-padding and clamping ( 1 - 9 )

// ------------ SETUP ------------

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
string ZeroPaddedFolder = "ZeroPadded";
string ClampedFolder = "Clamped";
string DummiesFolder = "Dummies";

// images
string Bild1Path = "Bild1.pgm";
string Bild2Path = "Bild2.pgm";

// 1. Load the given images (Bild1.pgm and Bild2.pgm)

// Bild 1: filtered once with horizontal, once with vertical prewitt
// save as Ergebnis1-horizontal.pgm and Ergebnis1-vertical.pgm later on
Bild1.ReadFromFile(Path.Combine(DummiesFolder, Bild1Path));

// Bild 2: filtered with a box filter of sizes 3, 11 and 27. 
// save as Ergebnis 2-3.pgm, Ergebnis 2-11.pgm and Ergebnis 2-27.pgm later on
Bild2.ReadFromFile(Path.Combine(DummiesFolder, Bild2Path));


// ------------ BILD 1 ------------

// 2. Create instances of ZeroPaddingBorderBehavior and ClampingBorderBehavior

ZeroPaddingBorderBehavior zeroPadding = new ZeroPaddingBorderBehavior();
ClampingBorderBehavior clamping = new ClampingBorderBehavior();

// 3. Create instances of the vertical and horizontal Prewitt filters using KernelFactory

Kernel prewittHorizontal = KernelFactory.CreatePrewittHorizontal();
Kernel prewittVertical = KernelFactory.CreatePrewittVertical();

// 4. Convolve the loaded images with the Prewitt filters using both border behaviors
// add type of padding as new name of file
// save the images with a timestamp to avoid overwriting the previous results
// Note: We might want to create separate Image instances for each convolution result

Ergebnis1Horizontal = Bild1.Convolve(prewittHorizontal, zeroPadding);
Ergebnis1Vertical = Bild1.Convolve(prewittVertical, zeroPadding);

// 5. Save the results of the convolutions as pgm images in the ZeroPadded and Clamped folders
// save the images with a timestamp to avoid overwriting the previous results
// Note: We might want to consider using a naming convention that includes the filter 
// and border behavior used

Ergebnis1HorizontalPath = Path.Combine(ZeroPaddedFolder, Ergebnis1HorizontalPath + 
DateTime.Now.ToString("yyyyMMddHHmmss") + ".pgm");
Ergebnis1Horizontal.WriteToFile(Ergebnis1HorizontalPath);

Ergebnis1VerticalPath = Path.Combine(ZeroPaddedFolder, Ergebnis1VerticalPath +
DateTime.Now.ToString("yyyyMMddHHmmss") + ".pgm");
Ergebnis1Vertical.WriteToFile(Ergebnis1VerticalPath);

// ------------ BILD 2 ------------

// 6. Create instances of the Box filters of sizes 3, 11, and 27 using KernelFactory

Kernel box3 = KernelFactory.CreateBox(3);
Kernel box11 = KernelFactory.CreateBox(11);
Kernel box27 = KernelFactory.CreateBox(27);

// 7. Convolve the loaded images with the Box filters using both border behaviors
// as filename, add the size of the box filter

Ergebnis2_3 = Bild2.Convolve(box3, zeroPadding);
Ergebnis2_11 = Bild2.Convolve(box11, zeroPadding);
Ergebnis2_27 = Bild2.Convolve(box27, zeroPadding);

// 8. Save the results of the convolutions as pgm images in the ZeroPadded and Clamped folders
// save the images with a timestamp to avoid overwriting the previous results

Ergebnis2_3Path = Path.Combine(ZeroPaddedFolder, Ergebnis2_3Path +
DateTime.Now.ToString("yyyyMMddHHmmss") + ".pgm");
Ergebnis2_3.WriteToFile(Ergebnis2_3Path);

Ergebnis2_11Path = Path.Combine(ZeroPaddedFolder, Ergebnis2_11Path +
DateTime.Now.ToString("yyyyMMddHHmmss") + ".pgm");
Ergebnis2_11.WriteToFile(Ergebnis2_11Path);

Ergebnis2_27Path = Path.Combine(ZeroPaddedFolder, Ergebnis2_27Path +
DateTime.Now.ToString("yyyyMMddHHmmss") + ".pgm");
Ergebnis2_27.WriteToFile(Ergebnis2_27Path);

// ------------ DISPLAY ------------


// 9. Display the loaded images and all the results of the convolutions on the screen   
// Bild1:
// Original
DisplayImage(Path.Combine(DummiesFolder, Bild1Path));
// Ergebnis1-horizontal.pgm
DisplayImage(Ergebnis1HorizontalPath);
// Ergebnis1-vertical.pgm
DisplayImage(Ergebnis1VerticalPath);

// Bild2:
// Original
DisplayImage(Path.Combine(DummiesFolder, Bild2Path));
// Ergebnis2-3.pgm
DisplayImage(Ergebnis2_3Path);
// Ergebnis2-11.pgm
DisplayImage(Ergebnis2_11Path);
// Ergebnis2-27.pgm
DisplayImage(Ergebnis2_27Path);

void DisplayImage(string imagePath)
{
    // Use Process.Start to open the default image viewer, should work on all platforms
    System.Diagnostics.Process.Start(imagePath);
}