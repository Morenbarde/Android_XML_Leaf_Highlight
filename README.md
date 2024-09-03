# Android_XML_Leaf_Highlight
Solution for CSCI 535 Assignment 1

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