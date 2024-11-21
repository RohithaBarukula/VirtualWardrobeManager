#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Scroll.H>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <algorithm>
#include "outfit_generator.h"
#include "week_planner.h"


// Global map to store items for each category
std::map<std::string, std::vector<std::string>> wardrobe;

// Initialize wardrobe items
void initializeWardrobe() {
    wardrobe["Shirts"] = {"White T-Shirt", "Blue Polo", "Red Hoodie", "Black Shirt", "Grey Sweater","Crop top","Crew neck"};
    wardrobe["Pants"] = {"Blue Jeans", "Black Trousers", "Khaki Pants", "Joggers", "Cargo Pants","torn jeans","olive legging"};
    wardrobe["Hoodies"] = {"Black Hoodie", "Grey Zip-Up", "Red Pullover", "Blue Hoodie", "Green Hoodie"};
    wardrobe["Shoes"] = {"Running Shoes", "Sneakers", "Boots", "Sandals", "Formal Shoes","Air max","jordans"};
    wardrobe["Accessories"] = {"Watch", "Belt", "Hat", "Sunglasses", "Scarf"};
}

// Function to close a window
void backButtonCallback(Fl_Widget* w, void* window) {
    ((Fl_Window*)window)->hide();
}

// Function to create an item list window for each category with scroll
void openItemListWindow(const char* categoryName) {
    Fl_Window* itemWindow = new Fl_Window(300, 300, categoryName);

    // Create a scrollable area for items
    Fl_Scroll* scroll = new Fl_Scroll(0, 0, 300, 260);
    scroll->begin();

    // Display items in the scrollable area
    int y_offset = 10;
    for (size_t i = 0; i < wardrobe[categoryName].size(); ++i) {
        Fl_Box* itemBox = new Fl_Box(20, y_offset, 260, 20, wardrobe[categoryName][i].c_str());
        itemBox->box(FL_NO_BOX);
        itemBox->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
        y_offset += 25;
    }

    scroll->end();

    // Add a "Back" button outside the scrollable area
    Fl_Button* backButton = new Fl_Button(220, 270, 60, 30, "Back");
    backButton->callback(backButtonCallback, itemWindow);

    itemWindow->end();
    itemWindow->show();
}

// Function to open the Add Item window
void openAddItemWindow(Fl_Widget* w, void* data) {
    Fl_Window* addItemWindow = new Fl_Window(300, 200, "Add Item");

    // Dropdown for category selection
    Fl_Choice* categoryChoice = new Fl_Choice(120, 30, 150, 25, "Category:");
    categoryChoice->add("Shirts|Pants|Hoodies|Shoes|Accessories");

    // Input box for item name
    Fl_Input* itemNameInput = new Fl_Input(120, 70, 150, 25, "Item Name:");
    categoryChoice->user_data(itemNameInput);  // Store itemNameInput as user data

    // Add to Wardrobe button
    Fl_Button* addToWardrobeButton = new Fl_Button(100, 120, 100, 30, "Add to Wardrobe");
    addToWardrobeButton->callback([](Fl_Widget* w, void* data) {
        Fl_Choice* categoryChoice = (Fl_Choice*)data;
        const Fl_Menu_Item* selectedCategoryItem = categoryChoice->mvalue();
        const char* selectedCategory = selectedCategoryItem ? selectedCategoryItem->label() : nullptr;
        Fl_Input* itemNameInput = (Fl_Input*)categoryChoice->user_data();
        std::string itemName = itemNameInput->value();

        // Add the new item to the selected category
        if (selectedCategory && !itemName.empty()) {
            wardrobe[selectedCategory].push_back(itemName);
            std::cout << "Item '" << itemName << "' added to " << selectedCategory << "!" << std::endl;

            // Display a confirmation message
            Fl_Window* confirmationWindow = new Fl_Window(200, 100, "Item Added");
            Fl_Box* message = new Fl_Box(20, 20, 160, 40, "Item added successfully!");
            Fl_Button* okButton = new Fl_Button(60, 60, 80, 30, "OK");
            okButton->callback(backButtonCallback, confirmationWindow);
            confirmationWindow->end();
            confirmationWindow->show();
        } else {
            std::cout << "Error: Please select a category and enter an item name." << std::endl;
        }
    }, categoryChoice);

    // Show the Add Item window
    addItemWindow->end();
    addItemWindow->show();
}

// Function to confirm and delete the item from wardrobe
void confirmDeleteCallback(Fl_Widget* w, void* data) {
    auto* itemData = (std::pair<std::string, std::string>*)data;
    std::string category = itemData->first;
    std::string selectedItem = itemData->second;

    // Debug: Print category and item selected
    std::cout << "Attempting to delete item - Category: " << category << ", Selected Item: " << selectedItem << std::endl;

    auto& items = wardrobe[category];
    auto it = std::find(items.begin(), items.end(), selectedItem);
    if (it != items.end()) {
        items.erase(it);  // Permanently delete the item
        std::cout << "Successfully deleted item '" << selectedItem << "' from category '" << category << "'!" << std::endl;

        // Display a deletion confirmation message
        Fl_Window* deletedWindow = new Fl_Window(200, 100, "Item Deleted");
        Fl_Box* message = new Fl_Box(20, 20, 160, 40, "Item deleted successfully!");
        Fl_Button* okButton = new Fl_Button(60, 60, 80, 30, "OK");
        okButton->callback(backButtonCallback, deletedWindow);
        deletedWindow->end();
        deletedWindow->show();
    } else {
        std::cout << "Error: Item '" << selectedItem << "' not found in category '" << category << "'!" << std::endl;
    }

    // Close confirmation window
    ((Fl_Window*)w->window())->hide();

    // Clean up allocated memory
    delete itemData;
}

// Function to open a delete confirmation window
void openDeleteConfirmation(std::pair<std::string, std::string>* itemData) {
    Fl_Window* confirmWindow = new Fl_Window(200, 100, "Confirm Delete");
    Fl_Box* message = new Fl_Box(20, 20, 160, 20, "Are you sure?");
    Fl_Button* yesButton = new Fl_Button(30, 60, 60, 30, "Yes");
    Fl_Button* noButton = new Fl_Button(110, 60, 60, 30, "No");

    yesButton->callback(confirmDeleteCallback, itemData);
    noButton->callback([](Fl_Widget* w, void* data) {
        ((Fl_Window*)w->window())->hide();
        delete (std::pair<std::string, std::string>*)data;
    }, itemData);

    confirmWindow->end();
    confirmWindow->show();
}

// Struct to hold pointers to category and item choices
struct DeleteData {
    Fl_Choice* categoryChoice;
    Fl_Choice* itemChoice;
};

// Function to open the Delete Item window
void openDeleteItemWindow(Fl_Widget* w, void* data) {
    Fl_Window* deleteItemWindow = new Fl_Window(300, 200, "Delete Item");

    // Dropdown for category selection
    Fl_Choice* categoryChoice = new Fl_Choice(120, 30, 150, 25, "Category:");
    categoryChoice->add("Shirts|Pants|Hoodies|Shoes|Accessories");

    // Dropdown for item selection
    Fl_Choice* itemChoice = new Fl_Choice(120, 70, 150, 25, "Select Item:");

    // Populate itemChoice based on selected category
    categoryChoice->callback([](Fl_Widget* w, void* data) {
        Fl_Choice* categoryChoice = (Fl_Choice*)w;
        Fl_Choice* itemChoice = (Fl_Choice*)data;
        itemChoice->clear();

        const Fl_Menu_Item* selectedCategoryItem = categoryChoice->mvalue();
        const char* selectedCategory = selectedCategoryItem ? selectedCategoryItem->label() : nullptr;

        if (selectedCategory) {
            // Populate itemChoice dropdown with items in the selected category
            for (const auto& item : wardrobe[selectedCategory]) {
                itemChoice->add(item.c_str());
            }
        }
        itemChoice->redraw();
    }, itemChoice);

    // Create DeleteData struct
    DeleteData* deleteData = new DeleteData{categoryChoice, itemChoice};

    // Delete button
    Fl_Button* deleteButton = new Fl_Button(90, 130, 120, 30, "Delete from Wardrobe");
    deleteButton->callback([](Fl_Widget* w, void* data) {
        DeleteData* deleteData = (DeleteData*)data;
        Fl_Choice* categoryChoice = deleteData->categoryChoice;
        Fl_Choice* itemChoice = deleteData->itemChoice;

        const Fl_Menu_Item* selectedCategoryItem = categoryChoice->mvalue();
        const char* selectedCategory = selectedCategoryItem ? selectedCategoryItem->label() : nullptr;

        const Fl_Menu_Item* selectedItemMenu = itemChoice->mvalue();
        const char* selectedItem = selectedItemMenu ? selectedItemMenu->label() : nullptr;

        if (selectedCategory && selectedItem) {
            // Create a pair to pass both category and item to confirmDeleteCallback
            auto* itemData = new std::pair<std::string, std::string>(selectedCategory, selectedItem);
            openDeleteConfirmation(itemData);
        } else {
            std::cout << "Error: Please select both a category and an item to delete." << std::endl;
        }
    }, deleteData);

    // Clean up deleteData when the window is closed
    deleteItemWindow->callback([](Fl_Widget* w, void* data) {
        DeleteData* deleteData = (DeleteData*)w->user_data();
        delete deleteData;
        w->hide();
    }, nullptr);
    deleteItemWindow->user_data(deleteData);

    deleteItemWindow->end();
    deleteItemWindow->show();
}

/*// Dummy function for "Generate Outfit" button
void generateOutfitCallback(Fl_Widget* w, void* data) {
    printf("Generate Outfit button clicked.\n");
}*/

// Function to create the wardrobe window with category buttons
void openWardrobeWindow(Fl_Widget* w, void* mainWindow) {
    Fl_Window* wardrobeWindow = new Fl_Window(400, 300, "Wardrobe Options");

    // Create buttons for wardrobe categories
    Fl_Button* shirtsButton = new Fl_Button(50, 50, 120, 30, "Shirts");
    shirtsButton->callback([](Fl_Widget*, void*) { openItemListWindow("Shirts"); });

    Fl_Button* pantsButton = new Fl_Button(50, 90, 120, 30, "Pants");
    pantsButton->callback([](Fl_Widget*, void*) { openItemListWindow("Pants"); });

    Fl_Button* hoodiesButton = new Fl_Button(50, 130, 120, 30, "Hoodies");
    hoodiesButton->callback([](Fl_Widget*, void*) { openItemListWindow("Hoodies"); });

    Fl_Button* shoesButton = new Fl_Button(50, 170, 120, 30, "Shoes");
    shoesButton->callback([](Fl_Widget*, void*) { openItemListWindow("Shoes"); });

    Fl_Button* accessoriesButton = new Fl_Button(50, 210, 120, 30, "Accessories");
    accessoriesButton->callback([](Fl_Widget*, void*) { openItemListWindow("Accessories"); });

    // "Add Item" button
    Fl_Button* addItemButton = new Fl_Button(200, 50, 120, 30, "Add an Item");
    addItemButton->callback(openAddItemWindow);

    // "Delete Item" button
    Fl_Button* deleteItemButton = new Fl_Button(200, 90, 120, 30, "Delete an Item");
    deleteItemButton->callback(openDeleteItemWindow);

    // Add "Back" button to go back to main window
    Fl_Button* backButton = new Fl_Button(320, 10, 60, 30, "Back");
    backButton->callback(backButtonCallback, wardrobeWindow);

    wardrobeWindow->end();
    wardrobeWindow->show();
}

// Function to apply consistent styling to buttons
void styleButton(Fl_Button* button) {
    button->color(fl_rgb_color(70, 130, 180));   // Set background color
    button->labelcolor(FL_WHITE);                // Set label color
    button->labelfont(FL_HELVETICA_BOLD);        // Set label font
    button->labelsize(14);                       // Set label size
    button->box(FL_FLAT_BOX);                    // Set button box style
    button->align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE);  // Center the label
}

int main() {
    Fl::scheme("plastic");

    initializeWardrobe();  // Initialize wardrobe items

    Fl_Window* window = new Fl_Window(400, 300, "Virtual Wardrobe");
    window->color(FL_WHITE);

    // Create "View Wardrobe" button
    Fl_Button* viewButton = new Fl_Button(30, 50, 140, 50, "View Wardrobe");
    styleButton(viewButton);
    viewButton->callback(openWardrobeWindow, window);

    // Create "Generate Outfit" button
    Fl_Button* generateButton = new Fl_Button(220, 50, 140, 50, "Generate Outfit");
    styleButton(generateButton);
    generateButton->callback(openOutfitGeneratorWindow);

    // Create "Plan for the Week" button
    Fl_Button* planWeekButton = new Fl_Button(30, 120, 140, 50, "Plan for the Week");
    styleButton(planWeekButton);
    planWeekButton->callback(openWeekPlannerWindow);

    // Create "View Weekly Planner" button (initially disabled)
    Fl_Button* viewPlannerButton = new Fl_Button(220, 120, 140, 50, "View Weekly Planner");
    styleButton(viewPlannerButton);
    viewPlannerButton->callback(viewSavedPlanner);
    viewPlannerButton->deactivate();  // Deactivate until a planner is saved

    // Store the viewPlannerButton for later use
    setViewPlannerButton(viewPlannerButton);

    window->end();
    window->show();

    return Fl::run();
}