//
//  main.cpp skeleton
//  lab3
//
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>
#include <valarray>

using namespace std;

#include "globals.h"
#include "shape.h"

// This is the shape array, to be dynamically allocated
shape** shapesArray; 

// The number of shapes in the database, to be incremented every time a shape is successfully created
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// check if name of shape exists: return true if it exists
bool checkNameExist(string name) {
    for (int i = 0; i < shapeCount; i++)
        if (shapesArray[i] != NULL)
            if (name == shapesArray[i]->getName())
                return true;
    return false;
}

int main() {

    string line;
    string command;
    
    // Prompt for input and get a line from standard input
    cout << "> ";         
    getline(cin, line);   

    while (!cin.eof()) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so the flags are cleared
        stringstream lineStream (line);

        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        string name;
        string type;
        int location_x = 0;
        int location_y = 0;
        int size_x = 0;
        int size_y = 0;
        int angle = 0;
        int i = 0;
        int arg = -1;
        
        // Check for the command and act accordingly       
        if (command == "maxShapes") {
            lineStream >> max_shapes;
            shapesArray = new shape* [max_shapes]; // allocate an array of pointers
            cout << "New database: max shapes is " << max_shapes << endl;
        }
        
        else if (command == "create") {
            while (i < 6) {
                if (i == 0) lineStream >> name;
                if (i == 1) lineStream >> type;
                if (i == 2) lineStream >> location_x;
                if (i == 3) lineStream >> location_y;
                if (i == 4) lineStream >> size_x;
                if (i == 5) lineStream >> size_y;
                if (lineStream.fail()) {
                    if(lineStream.eof()) {
                        if (i == 0) arg = 2; // too few arguments and also no name
                        else arg = 1;
                    }
                    else arg = 0; // too invalid argument
                    break;
                }
                i++;
            }
            
            lineStream >> ws;
            // check if all arguments are correct type
            if (arg == 0)
                cout << "Error: invalid argument\n";
            // check if name is valid
            else if (name == "ellipse" || name == "rectangle" || name == "triangle" || name == "all" || name == "maxShapes" 
                    || name == "create" || name == "move" || name == "rotate" || name == "draw" || name == "delete") 
                cout << "Error: invalid shape name\n";
            // check if name exists
            else if (checkNameExist(name)) 
                cout << "Error: shape " << name << " exists\n";
            // check if type is valid
            else if (type != "rectangle" && type != "triangle" && type != "ellipse" && arg != 1 && arg != 2) 
                cout << "Error: invalid shape type\n";
            // check if value for loc and size is not negative
            else if ((location_x < 0 || location_y < 0 || size_x < 0 || size_y <0) && arg != 1 && arg != 2) 
                cout << "Error: invalid value\n";
            // check if there are too many arguments
            else if (lineStream.peek() >= 0) 
                cout << "Error: too many arguments\n";
            // check if there are too few arguments
            else if (arg == 1 || arg == 2) 
                cout << "Error: too few arguments\n";
            // check if shape array is full
            else if (shapeCount == max_shapes) 
                cout << "Error: shape array is full\n";
            // if no errors, declare a new object that is pointed to by an array index
            else {
                shapesArray[shapeCount] = new shape(name, type, location_x, location_y, size_x, size_y);
                shapeCount++;
                cout << "Created " << name << ": " << type << " " << location_x << " " << location_y << " " << size_x << " " << size_y << endl;
            }
        } 
        
        else if (command == "move") {
            while (i < 3) {
                if (i == 0) lineStream >> name;
                if (i == 1) lineStream >> location_x;
                if (i == 2) lineStream >> location_y;
                if (lineStream.fail()) {
                    if(lineStream.eof()) {
                        if (i == 0) arg = 2; // too few arguments and also no name
                        else arg = 1;
                    }
                    else arg = 0; // too invalid argument
                    break;
                }
                i++;
            }
            
            lineStream >> ws;
            // check if all arguments are correct type
            if (arg == 0)
                cout << "Error: invalid argument\n";
            // check if name is valid
            else if (name == "ellipse" || name == "rectangle" || name == "triangle" || name == "all" || name == "maxShapes" 
                    || name == "create" || name == "move" || name == "rotate" || name == "draw" || name == "delete") 
                cout << "Error: invalid shape name\n";
            // check if shape is found
            else if (!checkNameExist(name) && arg != 2) 
                cout << "Error: shape " << name << " not found\n";
            // check if value for loc and size is not negative
            else if ((location_x < 0 || location_y < 0) && arg != 1 && arg != 2) 
                cout << "Error: invalid value\n";
            // check if there are too many arguments
            else if (lineStream.peek() >= 0) 
                cout << "Error: too many arguments\n";
            // check if there are too few arguments
            else if (arg == 1 || arg == 2) 
                cout << "Error: too few arguments\n";
            else {
                for (int j=0; j < shapeCount; j++) {
                    if (name == shapesArray[j]->getName()) {
                        shapesArray[j]->setXlocation(location_x);
                        shapesArray[j]->setYlocation(location_y);
                    }
                }
                cout << "Moved " << name << " to " << location_x << " " << location_y << endl;
            }
        }
        
        else if (command == "rotate") {
            while (i < 2) {
                if (i == 0) lineStream >> name;
                if (i == 1) lineStream >> angle;
                if (lineStream.fail()) {
                    if(lineStream.eof()) {
                        if (i == 0) arg = 2; // too few arguments and also no name
                        else arg = 1;
                    }
                    else arg = 0; // too invalid argument
                    break;
                }
                i++;
            }
            
            lineStream >> ws;
            // check if all arguments are correct type
            if (arg == 0)
                cout << "Error: invalid argument\n";
            // check if name is valid
            else if (name == "ellipse" || name == "rectangle" || name == "triangle" || name == "all" || name == "maxShapes" 
                    || name == "create" || name == "move" || name == "rotate" || name == "draw" || name == "delete") 
                cout << "Error: invalid shape name\n";
            // check if shape is found
            else if (!checkNameExist(name) && arg != 2) 
                cout << "Error: shape " << name << " not found\n";
            // check if value for loc and size is not negative
            else if ((angle < 0 || angle > 360) && arg != 1 && arg != 2) 
                cout << "Error: invalid value\n";
            // check if there are too many arguments
            else if (lineStream.peek() >= 0) 
                cout << "Error: too many arguments\n";
            // check if there are too few arguments
            else if (arg == 1 || arg == 2) 
                cout << "Error: too few arguments\n";
            else {
                for (int j=0; j < shapeCount; j++) 
                    if (name == shapesArray[j]->getName()) 
                        shapesArray[j]->setRotate(angle);
                cout << "Rotated " << name << " by " << angle << " degrees" << endl;
            }
        } 
        
        else if (command == "draw") {
            lineStream >> name;
            if (lineStream.fail()) {
                if (lineStream.eof()) arg = 1; // too few arguments
                else arg = 0; // too invalid argument
            }

            lineStream >> ws;
            // check if all arguments are correct type
            if (arg == 0)
                cout << "Error: invalid argument\n";
            // check if shape is found
            else if (!checkNameExist(name) && arg != 1 && name != "all")
                cout << "Error: shape " << name << " not found\n";
            // check if there are too many arguments
            else if (lineStream.peek() >= 0)
                cout << "Error: too many arguments\n";
            // check if there are too few arguments
            else if (arg == 1)
                cout << "Error: too few arguments\n";
            else {
                if (name == "all") { 
                    cout << "Drew all shapes\n";
                    for (int j = 0; j < shapeCount; j++)
                        if (shapesArray[j] != NULL)
                            shapesArray[j]->draw(); // print each existing shape name
                } 
                else {
                    cout << "Drew " << name << endl;
                    for (int j = 0; j < shapeCount; j++) {
                        if (name == shapesArray[j]->getName())
                            shapesArray[j]->draw(); // print desired shape name
                    }
                }
            }
        }
        
        else if (command == "delete") {
            lineStream >> name;
            if (lineStream.fail()) {
                if (lineStream.eof()) arg = 1; // too few arguments
                else arg = 0; // too invalid argument
            }

            lineStream >> ws;
            // check if all arguments are correct type
            if (arg == 0)
                cout << "Error: invalid argument\n";
            // check if shape is found
            else if (!checkNameExist(name) && arg != 1 && name != "all")
                cout << "Error: shape " << name << " not found\n";
            // check if there are too many arguments
            else if (lineStream.peek() >= 0)
                cout << "Error: too many arguments\n";
            // check if there are too few arguments
            else if (arg == 1)
                cout << "Error: too few arguments\n";
            else {
                if (name == "all") {
                    cout << "Deleted: all shapes\n";
                    for (int j = 0; j < shapeCount; j++) {
                        delete shapesArray[j]; // delete each pointer to object shape and set to NULL
                        shapesArray[j] = NULL;
                    }
                    shapeCount = 0;
                }
                else {
                    cout << "Deleted shape " << name << endl;
                    for (int j = 0; j < shapeCount; j++) {
                        if (shapesArray[j] != NULL)
                            if (name == shapesArray[j]->getName()) {
                                delete shapesArray[j]; // delete desired shape name pointer to object and set to NULL
                                shapesArray[j] = NULL;
                        }
                    }
                }
            }
        }
    
        else cout << "Error: invalid command\n";
        
        // clear flags and ignore the rest of user input
        lineStream.clear();
        lineStream.ignore(10000, '\n');
        // Once the command has been processed, prompt for the next command
        cout << "> ";          
        getline(cin, line);   
        
    }  // End input loop until EOF.
    return 0;
}

