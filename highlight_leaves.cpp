#include <iostream>
#include <cstdlib>
#include <fstream>
#include "tinyxml2.h"
#include "lodepng.h"

struct Boundary{
    int x1, y1;
    int x2, y2;
    Boundary* next;
};

Boundary* extract_bounds(tinyxml2::XMLNode* node) {
    /*
        Extracts bound information from leaf node and adds it to the passed Boundary Structure
        Returns true if boundary information was found and added to the structure, returns false if boundary information was not found
    */
    tinyxml2::XMLElement* leaf = node->ToElement();

    //If leaf node is not created or does not have bound information, it should be ignored
    if (!leaf || !leaf->Attribute("bounds")){
        return nullptr;
    }
    
    std::string bound_str = leaf->Attribute("bounds");
    if(bound_str.empty()) return nullptr; 

    Boundary* bound = new Boundary();
    
    int left_bracket[2];
    int right_bracket[2];
    int comma[2];

    left_bracket[0] = bound_str.find("[", 0);
    left_bracket[1] = bound_str.find("[", left_bracket[0]+1);
    right_bracket[0] = bound_str.find("]", 0);
    right_bracket[1] = bound_str.find("]", right_bracket[0]+1);
    comma[0] = bound_str.find(",", 0);
    comma[1] = bound_str.find(",", comma[0]+1);

    bound->x1 = std::stoi(bound_str.substr(left_bracket[0]+1, comma[0]-left_bracket[0]-1));
    bound->y1 = std::stoi(bound_str.substr(comma[0]+1, right_bracket[0]-comma[0]-1));
    bound->x2 = std::stoi(bound_str.substr(left_bracket[1]+1, comma[1]-left_bracket[1]-1));
    bound->y2 = std::stoi(bound_str.substr(comma[1]+1, right_bracket[1]-comma[1]-1));
    //std::cout << bound->x1 << ", " << bound->y1 << ", " << bound->x2 << ", " << bound->y2 << std::endl;

    return bound;
}

Boundary* find_leaf_bounds(tinyxml2::XMLNode* node) {
    
    /*
        Recursively searches XML Tree for all leaf nodes, creates linked list of boundary information
        Returns total number of leaf nodes with boundary info found (For Debugging)
    */
    Boundary* bound_list = nullptr;
    Boundary* current_bound;
    Boundary* temp_bound;
    while(node){
        if (node->NoChildren()) {
            
            current_bound = extract_bounds(node);
            if (current_bound){
                //If a new bound is made, push to the top of the stack
                current_bound->next = bound_list;
                bound_list = current_bound;
            }
        } else {
            //If recursion creates a new list of boundaries, push full list to top of stack
            current_bound = find_leaf_bounds(node->FirstChild());
            temp_bound = current_bound;
            while(temp_bound->next){
                temp_bound = temp_bound->next;
            }
            temp_bound->next = bound_list;
            bound_list = current_bound;
        }
        node = node->NextSibling();
    }
    return bound_list;
}

int main(int argc, char *argv[]){

    std::string xml_path, png_path;

    if (argc == 2) {
        xml_path = argv[1];
        xml_path = xml_path + ".xml"; 
        png_path = argv[1];
        png_path = png_path + ".png";
    } else if (argc == 3) {
        xml_path = argv[1];
        png_path = argv[2];
    } else {
        std::cout << "Usage: ./main path_to_files/filename_without_extension OR ./main path_to_xml/filename.xml path_to_png/filename.png" << std::endl;
        return 1;
    }

    tinyxml2::XMLDocument file;
    if(file.LoadFile(xml_path.c_str())){
        std::cout << "Error Parsing File: " << xml_path << std::endl;
        std::cout << "Parser Error: " << file.ErrorStr() << std::endl;
        std::cout << "Ending Program\n";
        return 1;
    }

    tinyxml2::XMLNode* root = file.FirstChild();

    Boundary* bound_list = find_leaf_bounds(root);

    while(bound_list){
        std::cout << bound_list->x1 << ", " << bound_list->y1 << ", " << bound_list->x2 << ", " << bound_list->y2 << std::endl;
        bound_list = bound_list->next;
    }
}
