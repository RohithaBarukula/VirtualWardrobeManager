// week_planner.cpp

#include "week_planner.h"
#include <FL/Fl_Box.H>
#include <FL/Fl_Scroll.H>
#include <random>
#include <algorithm>
#include <vector>
#include <string>
#include <map>              // Added to recognize std::map

// Reference the external wardrobe map
extern std::map<std::string, std::vector<std::string>> wardrobe;

// Data structure to hold an outfit
struct Outfit {
    std::string shirt;
    std::string pants;
    std::string shoes;
    std::string accessory;
};

// Global variable to store the planner
std::vector<Outfit> weeklyPlanner;

// Pointer to the "View Weekly Planner" button to enable/disable it
static Fl_Button* viewPlannerButton = nullptr;

// Function to set the view planner button pointer
void setViewPlannerButton(Fl_Button* button) {
    viewPlannerButton = button;
}

// **Added backButtonCallback function**
static void backButtonCallback(Fl_Widget* w, void* window) {
    ((Fl_Window*)window)->hide();
}

// Function to generate a random outfit
Outfit generateRandomOutfit() {
    Outfit outfit;
    std::vector<std::string> shirtsAndHoodies = wardrobe["Shirts"];
    shirtsAndHoodies.insert(shirtsAndHoodies.end(), wardrobe["Hoodies"].begin(), wardrobe["Hoodies"].end());

    // Helper lambda to get a random item from a vector
    auto getRandomItem = [](const std::vector<std::string>& items) -> std::string {
        if (items.empty()) return "No items available";
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, items.size() - 1);
        return items[dis(gen)];
    };

    outfit.shirt = getRandomItem(shirtsAndHoodies);
    outfit.pants = getRandomItem(wardrobe["Pants"]);
    outfit.shoes = getRandomItem(wardrobe["Shoes"]);
    outfit.accessory = getRandomItem(wardrobe["Accessories"]);

    return outfit;
}

// Function to generate outfits for the week
void generateWeeklyPlanner() {
    weeklyPlanner.clear();
    for (int i = 0; i < 7; ++i) {
        weeklyPlanner.push_back(generateRandomOutfit());
    }
}

// Function to update the display with the weekly planner
void updatePlannerDisplay(Fl_Scroll* scroll) {
    scroll->clear();  // Clear existing widgets
    scroll->begin();

    int y_offset = 10;
    const char* daysOfWeek[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    for (size_t i = 0; i < weeklyPlanner.size(); ++i) {
        Outfit& outfit = weeklyPlanner[i];

        Fl_Box* dayBox = new Fl_Box(20, y_offset, 100, 20, daysOfWeek[i]);
        dayBox->labelfont(FL_BOLD);
        y_offset += 25;

        Fl_Box* shirtBox = new Fl_Box(40, y_offset, 300, 20);
        shirtBox->copy_label(("Shirt/Hoodie: " + outfit.shirt).c_str());
        y_offset += 20;

        Fl_Box* pantsBox = new Fl_Box(40, y_offset, 300, 20);
        pantsBox->copy_label(("Pants: " + outfit.pants).c_str());
        y_offset += 20;

        Fl_Box* shoesBox = new Fl_Box(40, y_offset, 300, 20);
        shoesBox->copy_label(("Shoes: " + outfit.shoes).c_str());
        y_offset += 20;

        Fl_Box* accessoryBox = new Fl_Box(40, y_offset, 300, 20);
        accessoryBox->copy_label(("Accessory: " + outfit.accessory).c_str());
        y_offset += 30;  // Add extra space before next day
    }

    scroll->end();
    scroll->redraw();
}

// Callback for the "Regenerate" button
void regeneratePlannerCallback(Fl_Widget* w, void* data) {
    Fl_Scroll* scroll = (Fl_Scroll*)data;
    generateWeeklyPlanner();
    updatePlannerDisplay(scroll);
}

// Callback for the "Looks Good" button
void savePlannerCallback(Fl_Widget* w, void* data) {
    // Save the planner (already stored in weeklyPlanner)
    // Enable the "View Weekly Planner" button
    if (viewPlannerButton) {
        viewPlannerButton->activate();
    }

    // Display confirmation dialog
    Fl_Window* confirmationWindow = new Fl_Window(200, 100, "Planner Saved");
    Fl_Box* message = new Fl_Box(20, 20, 160, 40, "Weekly planner saved!");
    Fl_Button* okButton = new Fl_Button(60, 60, 80, 30, "OK");
    okButton->callback([](Fl_Widget* w, void* data) {
        ((Fl_Window*)w->window())->hide();
    }, nullptr);
    confirmationWindow->end();
    confirmationWindow->show();

    // Close the planner window
    ((Fl_Window*)data)->hide();
}

// Function to open the week planner window
void openWeekPlannerWindow(Fl_Widget* w, void* data) {
    Fl_Window* plannerWindow = new Fl_Window(500, 500, "Weekly Planner");

    // Create a scrollable area to display the outfits
    Fl_Scroll* scroll = new Fl_Scroll(0, 0, 500, 400);
    scroll->box(FL_NO_BOX);

    // Generate initial planner
    generateWeeklyPlanner();
    updatePlannerDisplay(scroll);

    // "Regenerate" button
    Fl_Button* regenerateButton = new Fl_Button(100, 420, 100, 30, "Regenerate");
    regenerateButton->callback(regeneratePlannerCallback, scroll);

    // "Looks Good" button
    Fl_Button* looksGoodButton = new Fl_Button(300, 420, 100, 30, "Looks Good");
    looksGoodButton->callback(savePlannerCallback, plannerWindow);

    plannerWindow->end();
    plannerWindow->show();
}

// Function to view the saved planner
void viewSavedPlanner(Fl_Widget* w, void* data) {
    if (weeklyPlanner.empty()) {
        // No planner saved
        Fl_Window* warningWindow = new Fl_Window(200, 100, "No Planner");
        Fl_Box* message = new Fl_Box(20, 20, 160, 40, "No weekly planner saved.");
        Fl_Button* okButton = new Fl_Button(60, 60, 80, 30, "OK");
        okButton->callback([](Fl_Widget* w, void* data) {
            ((Fl_Window*)w->window())->hide();
        }, nullptr);
        warningWindow->end();
        warningWindow->show();
        return;
    }

    Fl_Window* plannerWindow = new Fl_Window(500, 500, "Saved Weekly Planner");

    // Create a scrollable area to display the outfits
    Fl_Scroll* scroll = new Fl_Scroll(0, 0, 500, 450);
    scroll->box(FL_NO_BOX);

    // Display the saved planner
    updatePlannerDisplay(scroll);

    // "Close" button
    Fl_Button* closeButton = new Fl_Button(200, 460, 100, 30, "Close");
    closeButton->callback(backButtonCallback, plannerWindow);  // Use local backButtonCallback

    plannerWindow->end();
    plannerWindow->show();
}