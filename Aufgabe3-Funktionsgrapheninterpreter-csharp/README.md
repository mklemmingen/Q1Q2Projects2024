
# Marty (as researched on microsoft.com and Bing Copilot (provided by Hochschule))

You can install .NET MAUI by downloading and installing the latest .NET SDK from the .NET website.

For Visual Studio Code, you can add .NET support by installing the C# DEV kit extension.
<https://marketplace.visualstudio.com/items?itemName=ms-dotnettools.csdevkit>

Also install the MAUI extension.

VIDEO-GUIDE: https://learn.microsoft.com/en-us/shows/visual-studio-toolbox/getting-started-with-maui-in-visual-studio-code#time=04m30s

---------------------------------------------------------------------------------------------------------------------------

If you download the extensions separately, ensure that you also have the .NET SDK on your local environment. The .NET SDK is a software development environment used for developing .NET applications.
<https://aka.ms/vscDocs/dotnet/download>

-----------------------------------------------------

You’ll also need to install the MAUI templates by running the following command in your terminal:

dotnet new -i Microsoft.Maui.Templates

Once you’ve installed .NET MAUI, you can create a new MAUI project by running:

dotnet new maui -n FunctionGraphInterpreter

Run the app by entering the following command in the command shell:

To run your .NET MAUI application, you can use Visual Studio 2022 or the .NET CLI12. Here are the steps for both methods:

Visual Studio 2022:

    Open your .NET MAUI project in Visual Studio 20221.
    In the Visual Studio toolbar, use the Debug Target drop-down to select the platform you want to run your app on (e.g., Android Emulators, iOS Simulators, or Local Machine for Windows)1.
    Press the Debug button (or press F5) to build and run your app1.

.NET CLI:

    Open a command prompt in the root directory of your .NET MAUI project2.

    (if not build yet, do not use this with force if already done)
    Build your project with the command: dotnet build ./FunctionGraphInterpreter.csproj2

    install workloads:
    dotnet workload restore

    Run your project with the command: dotnet run --project ./FunctionGraphInterpreter.csproj

-----------------------------------------------------

remmember to add all files to .gitignore that include personal computer file paths
