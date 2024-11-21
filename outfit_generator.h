// outfit_generator.h

#ifndef OUTFIT_GENERATOR_H
#define OUTFIT_GENERATOR_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <map>
#include <vector>
#include <string>

// Declare the external wardrobe map
extern std::map<std::string, std::vector<std::string>> wardrobe;

// Function to open the outfit generator window
void openOutfitGeneratorWindow(Fl_Widget* w, void* data);

#endif // OUTFIT_GENERATOR_H