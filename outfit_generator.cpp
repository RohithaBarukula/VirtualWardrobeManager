// outfit_generator.cpp

#include "outfit_generator.h"
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <random>
#include <algorithm>

// Reference the external wardrobe map
extern std::map<std::string, std::vector<std::string>> wardrobe;

// Function to generate a random item from a category
std::string getRandomItem(const std::string& category) {
    std::vector<std::string> items;

    if (category == "Shirt/Hoodie") {
        // Combine shirts and hoodies
        items.insert(items.end(), wardrobe["Shirts"].begin(), wardrobe["Shirts"].end());
        items.insert(items.end(), wardrobe["Hoodies"].begin(), wardrobe["Hoodies"].end());
    } else {
        items = wardrobe[category];
    }

    if (items.empty()) return "No items available";
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, items.size() - 1);
    return items[dis(gen)];
}

// Function to update the outfit display
void updateOutfitDisplay(Fl_Box* shirtBox, Fl_Box* pantsBox, Fl_Box* shoesBox, Fl_Box* accessoryBox) {
    std::string shirt = getRandomItem("Shirt/Hoodie");
    std::string pants = getRandomItem("Pants");
    std::string shoes = getRandomItem("Shoes");
    std::string accessory = getRandomItem("Accessories");

    // Concatenate the labels
    std::string shirtLabel = "Shirt/Hoodie: " + shirt;
    std::string pantsLabel = "Pants: " + pants;
    std::string shoesLabel = "Shoes: " + shoes;
    std::string accessoryLabel = "Accessory: " + accessory;

    // Use copy_label() to safely set the labels
    shirtBox->copy_label(shirtLabel.c_str());
    pantsBox->copy_label(pantsLabel.c_str());
    shoesBox->copy_label(shoesLabel.c_str());
    accessoryBox->copy_label(accessoryLabel.c_str());

    // Redraw the boxes to update the display
    shirtBox->redraw();
    pantsBox->redraw();
    shoesBox->redraw();
    accessoryBox->redraw();
}

// Callback for the "Regenerate" button
void regenerateCallback(Fl_Widget* w, void* data) {
    auto* outfitBoxes = (std::vector<Fl_Box*>*)data;
    updateOutfitDisplay(outfitBoxes->at(0), outfitBoxes->at(1), outfitBoxes->at(2), outfitBoxes->at(3));
}

// Callback for the "Looks Good" button
void looksGoodCallback(Fl_Widget* w, void* data) {
    // Display confirmation dialog
    Fl_Window* confirmationWindow = new Fl_Window(200, 100, "Outfit Selected");
    Fl_Box* message = new Fl_Box(20, 20, 160, 40, "Outfit selected successfully!");
    Fl_Button* okButton = new Fl_Button(60, 60, 80, 30, "OK");
    okButton->callback([](Fl_Widget* w, void* data) {
        ((Fl_Window*)w->window())->hide();
    }, nullptr);
    confirmationWindow->end();
    confirmationWindow->show();

    // Close the outfit generator window
    ((Fl_Window*)data)->hide();
}

// Function to open the outfit generator window
void openOutfitGeneratorWindow(Fl_Widget* w, void* data) {
    Fl_Window* outfitWindow = new Fl_Window(400, 300, "Generated Outfit");

    // Create boxes to display the outfit items
    Fl_Box* shirtBox = new Fl_Box(50, 50, 300, 30, "");
    Fl_Box* pantsBox = new Fl_Box(50, 90, 300, 30, "");
    Fl_Box* shoesBox = new Fl_Box(50, 130, 300, 30, "");
    Fl_Box* accessoryBox = new Fl_Box(50, 170, 300, 30, "");

    shirtBox->labelsize(14);
    pantsBox->labelsize(14);
    shoesBox->labelsize(14);
    accessoryBox->labelsize(14);

    // Store the boxes in a vector for easy access
    auto* outfitBoxes = new std::vector<Fl_Box*>{shirtBox, pantsBox, shoesBox, accessoryBox};

    // Generate the initial outfit
    updateOutfitDisplay(shirtBox, pantsBox, shoesBox, accessoryBox);

    // "Regenerate" button
    Fl_Button* regenerateButton = new Fl_Button(80, 220, 100, 30, "Regenerate");
    regenerateButton->callback(regenerateCallback, outfitBoxes);

    // "Looks Good" button
    Fl_Button* looksGoodButton = new Fl_Button(220, 220, 100, 30, "Looks Good");
    looksGoodButton->callback(looksGoodCallback, outfitWindow);

    // Clean up outfitBoxes when the window is closed
    outfitWindow->callback([](Fl_Widget* w, void* data) {
        auto* boxes = (std::vector<Fl_Box*>*)data;
        delete boxes;
        w->hide();
    }, outfitBoxes);

    outfitWindow->end();
    outfitWindow->show();
}