//******************
//
// pleos_data_structure.cpp
//
//******************
// Presentation :
//
// PLEOS, by Aster System, is a project which aims education.
// By using the power of SCLS and other Aster System's tools, we created  this.
// We want to make education easier for everyone (teachers, as students and pupils).
// The software is made in french, because the main goal is France educational system.
// For more information, see : https://aster-system.github.io/aster-system/projects/pleos.html.
//
// The "Data Structure" part aims IT lesson.
// Its goal is to explain data structure easily for everyone, SAASF reader.
//
// This file contains the page of the Data Structure plugin.
//
//******************
//
// License (GPL V3.0) :
//
// Copyright (C) 2024 by Aster System, Inc. <https://aster-system.github.io/aster-system/>
// This file is part of PLEOS.
// PLEOS is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
// PLEOS is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with PLEOS. If not, see <https://www.gnu.org/licenses/>.
//

#ifndef PLEOS_DATA_STRUCTURE
#define PLEOS_DATA_STRUCTURE

// Include SCLS Graphic Benoit
#include "../../../scls-graphic-benoit/scls_graphic.h"

// The namespace "pleos" is used to simplify the all.
namespace pleos {

    class GUI_List : public scls::GUI_Object {
        // Class representating a list in a GUI object
    public:

        // GUI_List constructor
        GUI_List(scls::_Window_Advanced_Struct& window, std::string name, scls::GUI_Object* parent);
        // GUI_List destructor
        ~GUI_List() {a_elements.clear();};

        // Configure the stack / queue GUI
        void configure_gui_stack_queue();
        // Configure the text index enter GUI
        void configure_gui_text_index(std::string index_title);
        // Set the list as a stack / queue
        void set_queue() {a_type = Queue;configure_gui_stack_queue();a_delete_element_index = 0;};
        void set_stack() {a_type = Stack;configure_gui_stack_queue();a_delete_element_index = -1;};

        // Adds an element to the list
        void add_element(unsigned short position);
        // Deletes an element in the list
        void delete_element(unsigned short position);
        // Updates the elements in the list
        void update_elements();

        // Update the events in the list
        virtual void update_event();

    private:

        // GUI of an element in the list
        struct __Element {
            // Destructor of an element
            ~__Element() {index_text.reset();insert_button.reset();delete_button.reset();element_content.reset();element_base.reset();};

            // Base of the element in the GUI
            std::shared_ptr<scls::GUI_Object> element_base;
            // Content of the element
            std::shared_ptr<scls::GUI_Text_Input> element_content;

            // Delete button in the GUI
            std::shared_ptr<scls::GUI_Text> delete_button;
            // Insert button in the GUI
            std::shared_ptr<scls::GUI_Text> insert_button;

            // Value of the index (if text)
            std::string index = "";
            // Text containing the index of the element in the GUI
            std::shared_ptr<scls::GUI_Text> index_text;
        };

        // If the structure is currently animated
        bool a_currently_animated = false;
        // Currently animated entering element
        std::shared_ptr<scls::GUI_Object> a_curently_animated_entering_element;
        // Currently animated leaving state
        double a_curently_animated_entering_state = -1;
        double a_curently_animated_entering_state_max = 0.3;
        // Currently animated leaving element
        std::shared_ptr<scls::GUI_Object> a_curently_animated_leaving_element;
        // Currently animated leaving state
        double a_curently_animated_leaving_state = -1;
        double a_curently_animated_leaving_state_max = 0.3;
        // If the structure use the text index or not
        bool a_use_index = false;

        // Number of created buttons
        unsigned int created_button = 0;
        // Elements in the list
        std::vector<__Element> a_elements;
        // Type of the structure
        enum {List, Queue, Stack} a_type = List;

        // Button to delete an element
        std::shared_ptr<scls::GUI_Text> a_delete_element_button;
        // Index of the element to delete
        short a_delete_element_index = 0;
        // Button to add a new element
        std::shared_ptr<scls::GUI_Text> a_new_element_button;
        // Get the index of the new element
        std::shared_ptr<scls::GUI_Text_Input> a_new_element_index;
    };

    class Data_Structure_Page : public scls::GUI_Page {
        // Class representating the data structure page for PLEOS
    public:

        // Data_Structure_Page constructor
        Data_Structure_Page(scls::_Window_Advanced_Struct* window_struct, std::string name);

        // Function called after an XML loading
        virtual void after_xml_loading() {GUI_Page::after_xml_loading();display_home();};
        // Loads an object in a page from XML
        virtual std::shared_ptr<scls::GUI_Object> __create_loaded_object_from_type(std::string object_name, std::string object_type, scls::GUI_Object* parent);

        // Check the navigation event
        void check_navigation_events();
        // Update the events in the page
        virtual void update_event();

        // Displays the body of the data handling
        void display_data_handling();
        // Displays the body of the data structure optimisation
        void display_ds_optimisation();
        // Displays the body of the home
        void display_home();
        // Displays the body of the stack / queue
        void display_stack_queue();
        // Hides all the bodies in the page
        void hide_all();

    private:

        // Bodies
        // Data handling body
        std::shared_ptr<scls::GUI_Object> a_body_data_handling;
        // Data structure optimisation body
        std::shared_ptr<scls::GUI_Object> a_body_ds_optimisation;
        // Home body
        std::shared_ptr<scls::GUI_Object> a_body_home;
        // Stack / queue body
        std::shared_ptr<scls::GUI_Object> a_body_stack_queue;

        // Navigation buttons
        // Data handling button
        std::shared_ptr<scls::GUI_Text> a_navigation_data_handling;
        // Data structure optimisation button
        std::shared_ptr<scls::GUI_Text> a_navigation_ds_optimisation;
        // Home button
        std::shared_ptr<scls::GUI_Text> a_navigation_home;
        // Stack / queue button
        std::shared_ptr<scls::GUI_Text> a_navigation_stack_queue;
    };

    class __Temp_Pleos_Window : public scls::Window {
        // Temporary used window by PLEOS
    public :
        // __Temp_Pleos_Window constructor
        __Temp_Pleos_Window(unsigned int w, unsigned int h, std::string path) : scls::Window(w, h, path) {}

        // Create an object in the window
        std::shared_ptr<scls::Object> __create_loaded_object_from_type(std::string object_name, std::string object_type) {
            if(object_name == "data_structure_page") {
                std::shared_ptr<Data_Structure_Page> hub = *new_page_2d<Data_Structure_Page>(object_name);

                // Return the good object
                std::shared_ptr<scls::Object> to_return = hub;
                return to_return;
            } return scls::Window::__create_loaded_object_from_type(object_name, object_type);
        }
    };
}

#endif // PLEOS_DATA_STRUCTURE
