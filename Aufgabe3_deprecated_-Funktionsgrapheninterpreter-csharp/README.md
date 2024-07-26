
# Marty:

## For FuGAIn_folder with VS



## For FuGAIn_folder with VSCODE

You can install .NET MAUI by downloading and installing the latest .NET SDK from the .NET website.

https://dotnet.microsoft.com/en-us/download/dotnet/6.0

We should use 6.0 instead of the new 8.0, since android and mac development is not able to be done with the current MAUI on any version above 6.0
Fucked around and found out on that one. 
Make sure you are signed in into vscode to use the needed extensions for c#

---------- install workloads

dotnet workload install maui
dotnet workload install maui-android
dotnet workload install maui-ios

---------- install android-sdk

Install Command line tools only 
https://developer.android.com/studio#command-tools


Build & Run the app by entering the following command in the command shell:

---------- cd into project folder

dotnet build
dotnet run

-----------------------------------------------------

remmember to add all files to .gitignore that include personal computer file paths

------------------------------------------------------

For Debugging Error codes:
https://learn.microsoft.com/en-us/dotnet/core/tools/sdk-errors/

## For .NET Project overall

CMD/STRG+shift+P

    install .NET global ... then version 6



-----------------------------------------------------
-----------------------------------------------------

# Old Research:

You’ll also need to install the MAUI templates by running the following command in your terminal:

dotnet new -i Microsoft.Maui.Templates

Once you’ve installed .NET MAUI, you can create a new MAUI project by running:

dotnet new maui -n FunctionGraphInterpreter

or:

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





