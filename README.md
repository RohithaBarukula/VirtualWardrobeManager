## Virtual Wardrobe Manager

### Project Description

The Virtual Wardrobe Manager is a C++ application that allows users to manage a virtual wardrobe. Users can add and categorize clothing items, plan outfits for the week, track how often each item is worn, and save/load their wardrobe and weekly plans. This project follows Object-Oriented Programming (OOP) principles, providing a modular and reusable design.

### Key Features

- *Add Items*: Users can add items to their wardrobe by specifying a name and category (e.g., Top, Bottom, Accessory, Footwear).
- *Remove Items*: Users can remove items from their wardrobe by name.
- *View Items by Category*: Users can view items in the wardrobe filtered by category.
- *Plan Outfits*: Users can plan outfits for each day of the week and track the frequency of item usage.
- *Save and Load*: The application saves the wardrobe and weekly plan to files (wardrobe_data.txt and weekly_plan.txt) and loads them upon startup.

### OOP Principles

This project is designed with the following Object-Oriented Programming principles:

1. *Encapsulation*:
   - Each class (ClothingItem, WardrobeManager, and OutfitPlanner) encapsulates data and behavior specific to its purpose, hiding internal details and exposing only necessary functionality.
   - ClothingItem manages individual clothing attributes, WardrobeManager handles the entire collection of items, and OutfitPlanner manages weekly outfits.
   
2. *Abstraction*:
   - The project simplifies complex operations into easy-to-understand classes:
     - ClothingItem represents an individual piece of clothing.
     - WardrobeManager represents the wardrobe, with methods for adding, removing, and viewing items.
     - OutfitPlanner handles daily outfit planning and weekly plan management.
   - Each class provides a clear interface, hiding the details of how these operations are carried out.

3. *Separation of Concerns*:
   - The WardrobeManager and OutfitPlanner classes are designed to manage different responsibilities, ensuring that each class is focused on a single purpose. WardrobeManager handles item management, while OutfitPlanner focuses on outfit planning.

4. *Code Reusability*:
   - Each class can be extended independently. For instance, WardrobeManager could be expanded to include more complex wardrobe functionalities, and OutfitPlanner could be modified to support seasonal outfits without affecting the core functionality.

### Project Structure


VirtualWardrobe/
├── include/
│   ├── ClothingItem.h       # Header for ClothingItem class
│   ├── OutfitPlanner.h      # Header for OutfitPlanner class
│   └── WardrobeManager.h    # Header for WardrobeManager class
├── src/
│   ├── main.cpp             # Main file with user interface
│   ├── ClothingItem.cpp     # Implementation of ClothingItem class
│   ├── WardrobeManager.cpp  # Implementation of WardrobeManager class
│   └── OutfitPlanner.cpp    # Implementation of OutfitPlanner class
├── build/                   # Directory for compiled files
├── CMakeLists.txt           # CMake configuration file
└── README.md                # Project documentation


### Installation and Running Instructions

1. *Clone the Repository*:
   
   git clone <repository-url>
   cd VirtualWardrobe
   

2. *Build the Project*:
   
   mkdir build
   cd build
   cmake -DCMAKE_OSX_ARCHITECTURES=arm64 ..
   make
   

3. *Run the Application*:
   
   ./VirtualWardrobe
   

4. *Using the Application*:
   - *Add Items*: Follow the prompts to enter an item name and select a category.
   - *Remove Items*: Enter the name of the item to remove.
   - *View Items*: Select a category to view items of that type.
   - *Plan Outfits*: Select a day and add items by name for each outfit.
   - *Save and Exit*: Saves all data to wardrobe_data.txt and weekly_plan.txt.

### Example Usage

The main menu in the terminal provides options:

--- Virtual Wardrobe ---
1. Add new item
2. Remove an item
3. View items by category
4. Plan outfit for a day
5. View weekly outfit plan
6. Save and exit
Enter your choice:


### Dependencies

- *CMake*: To build the project.
- *C++ Compiler*: Compatible with C++14 or later.

### Files for Data Storage

- *wardrobe_data.txt*: Stores the wardrobe data, including item name, category, and usage count.
- *weekly_plan.txt*: Stores the weekly plan with each day's outfit items.

This project provides a modular and extensible foundation for virtual wardrobe management, emphasizing OOP principles for maintainability and scalability.
