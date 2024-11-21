// week_planner.h

#ifndef WEEK_PLANNER_H
#define WEEK_PLANNER_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>   // Added to recognize Fl_Button
#include <vector>
#include <string>
#include <map>              // Added to recognize std::map

// Declare the external wardrobe map
extern std::map<std::string, std::vector<std::string>> wardrobe;

// Function to open the week planner window
void openWeekPlannerWindow(Fl_Widget* w, void* data);

// Function to view the saved planner
void viewSavedPlanner(Fl_Widget* w, void* data);

// Function to set the view planner button
void setViewPlannerButton(Fl_Button* button);

#endif // WEEK_PLANNER_H