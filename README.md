# Android_XML_Leaf_Highlight
Solution for CSCI 535 Assignment 1

This program takes xml files captured from the uiautomator framwork in Android, as well as a related png, and highlights the individual leaf-level components by drawing a yellow box around them and outputting the resulting png.

Compilation: 

    g++ highlight_leaves.cpp tinyxml2.cpp lodepng.cpp -o highlight_leaves

Running:
There are two ways to run the program:

If both the xml file and the png file are in the same directory, then this program can be run with one argument, the path for both files without the extension:
    
    ./highlight_leaves PathToFiles/file_name

If the xml and png files are in different directories, then they can also be pass as two seperate arguments, still with their paths:
    
    ./highlight_leaves PathToXMLFile/file_name.xml PathToPNGFile/file_name.png

If the file names are correct and the xml file is valid, the program should run to completion.
The resulting png will be placed in the results folder in the repository, bearing the same name as the png file put in, but with "modified_" tagged to the front

Note: Lodepng (lodepng.h, lodepng.cpp) and TinyXML (tinyxml2.h, tinyxml2.cpp) are all libraries I found online, and do not belong to me.