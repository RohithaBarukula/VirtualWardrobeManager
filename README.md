## Virtual Wardrobe Manager

### Project Description

The Virtual Wardrobe Manager is a C++ application aimed at efficient wardrobe organization and management. It simplifies tasks such as categorizing clothing items, generating daily and weekly outfits, and tracking the usage of wardrobe items. The application is built using Object-Oriented Programming (OOP) principles, ensuring scalability and ease of future enhancement. Features include outfit generation, weekly outfit planning, and wardrobe management, making it a user-friendly and practical solution for everyday wardrobe needs.

### Key Features

- *Add Items*: Users can add items to their wardrobe by specifying a name and category (e.g., Top, Bottom, Accessory, Footwear).
- *Remove Items*: Users can remove items from their wardrobe by name.
- *View Items by Category*: Users can view items in the wardrobe filtered by category.
- *Regenarate*: Regenerates outfits upon selection.
- *Plan Outfits*: Users can plan outfits for each day of the week and track the frequency of item usage.
- *Save and Load*: The application saves the wardrobe and weekly plan to files (wardrobe_data.txt and weekly_plan.txt) and loads them upon startup.



### Methodology

#### Wardrobe Management

The wardrobe is stored as a std::map, where categories (e.g., Shirts, Pants, Shoes) serve as keys, and the corresponding items are stored as std::vector<std::string> values.

#### Operations Users can perform:

- Add new items via a form-based GUI.

- Delete items using category and item selection interfaces.

- Browse items through scrollable category-specific lists.

### Outfit Generation

- Daily Outfit Generation combines random items from different categories (e.g., Shirt, Pants) into a cohesive outfit using std::random_device and std::uniform_int_distribution for random selection.

#### Weekly Planner:

- Generates outfits for each day of the week, stored as a std::vector of Outfit structs.

- Displays outfits with labeled boxes in a scrollable window.

- Enables users to regenerate or save plans for future reference.

### Graphical User Interface (GUI)

- Built using the FLTK library for lightweight and customizable windows and widgets.

#### Features include:

- Scrollable views for browsing wardrobe items and weekly plans.

- Dynamic updates for labels and buttons to reflect real-time actions.

- Confirmation dialogs for actions like saving plans or deleting items.



This project provides a modular and extensible foundation for virtual wardrobe management, emphasizing OOP principles for maintainability and scalability.
