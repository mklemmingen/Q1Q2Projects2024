
Marty (as researched on microsoft.com and Bing Copilot (provided by Hochschule))

You can install .NET MAUI by downloading and installing the latest .NET SDK from the .NET website. 

For Visual Studio Code, you can add .NET support by installing the C# DEV kit extension. 
https://marketplace.visualstudio.com/items?itemName=ms-dotnettools.csdevkit

If you download the extensions separately, ensure that you also have the .NET SDK on your local environment. The .NET SDK is a software development environment used for developing .NET applications.
https://aka.ms/vscDocs/dotnet/download

-----------------------------------------------------

You’ll also need to install the MAUI templates by running the following command in your terminal:

dotnet new -i Microsoft.Maui.Templates

Once you’ve installed .NET MAUI, you can create a new MAUI project by running:

dotnet new maui -n FunctionGraphInterpreter

Run the app by entering the following command in the command shell:

dotnet run

---------

remmember to add all files to .gitignore that include personal computer file paths.