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

        // Adds an element to the list
        void add_element(unsigned short position);
        // Updates the elements in the list
        void update_elements();

        // Update the events in the list
        virtual void update_event();

    private:

        // Number of created buttons
        unsigned int created_button = 0;
        // Elements in the list
        std::vector<std::shared_ptr<scls::GUI_Object>> a_elements;

        // Button to add a new element
        std::shared_ptr<scls::GUI_Text> a_new_element_button;
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
        // Displays the body of the home
        void display_home();
        // Hides all the bodies in the page
        void hide_all();

    private:

        // Bodies
        // Data handling body
        std::shared_ptr<scls::GUI_Object> a_body_data_handling;
        // Home body
        std::shared_ptr<scls::GUI_Object> a_body_home;

        // Navigation buttons
        // Data handling button
        std::shared_ptr<scls::GUI_Text> a_navigation_data_handling;
        // Home button
        std::shared_ptr<scls::GUI_Text> a_navigation_home;
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
