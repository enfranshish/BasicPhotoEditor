## Read Me ##

This is a rough draft of a basic photo editor that runs from command line

### Additional documentation ###
Open CV installation is required to build this application.

OS and IDE:
Code compiled on Windows 11 in Visual Studio Code IDE.
Executables were made using Makefile with mingw32-make

Overleaf report:
https://www.overleaf.com/read/gpqhwfthpkxs 

### Clone ###
In the desired repository, run ```git clone https://github.com/enfranshish/SimplePhotoEditor```

### Build ###
To build the exe, run ```make bin/editor``` from the main project folder. The intalled make compiler name may vary by machine. This project was made using mingw32-make

### Run ###
The binary file is not included in the repository. You must first build the exe. To run the exe, launch command line from the project folder and enter the command ```bin/editor <full/filepath/to/image```

The main function launches with a required argument of image path. Use sliders to adjust
image, buttons to save images or reset sliders. Program will terminate if either image
window or control window is closed.
