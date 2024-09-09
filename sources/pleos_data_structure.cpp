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
// This file contains the source code of pleos_data_structure.h.
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

// Include SCLS Graphic Benoit
#include "../headers/pleos_data_structure.h"

// The namespace "pleos" is used to simplify the all.
namespace pleos {

    // GUI_List constructor
    GUI_List::GUI_List(scls::_Window_Advanced_Struct& window, std::string name, scls::GUI_Object* parent) : scls::GUI_Object(window, name, parent) {
        set_border_width_in_pixel(1);

        // Create the button to add new elements
        a_new_element_button = *new_object<scls::GUI_Text>(name + "-new_element_button");
        a_new_element_button.get()->attach_top_in_parent();
        a_new_element_button.get()->set_border_width_in_pixel(1);
        a_new_element_button.get()->set_font_size(30);
        a_new_element_button.get()->set_height_in_pixel(30);
        a_new_element_button.get()->set_overflighted_cursor(GLFW_HAND_CURSOR);
        a_new_element_button.get()->set_text(scls::to_utf_8_code_point("Nouvel élément"));
        a_new_element_button.get()->set_texture_alignment(scls::Alignment_Texture::T_Fit);
        a_new_element_button.get()->set_width_in_scale(scls::Fraction(1, 3));
        a_new_element_button.get()->set_x_in_scale(scls::Fraction(0));
    }

    // Add an element to the list
    void GUI_List::add_element(unsigned short position) {
        std::shared_ptr<scls::GUI_Object> to_add = *new_object<scls::GUI_Object>(name() + "-button_" + std::to_string(created_button));
        to_add.get()->attach_bottom_in_parent();
        to_add.get()->set_border_width_in_pixel(1);
        to_add.get()->set_height_in_scale(scls::Fraction(4, 5));
        to_add.get()->set_width_in_scale(scls::Fraction(1, 3));
        to_add.get()->set_x_in_scale(scls::Fraction(0));
        if(position >= a_elements.size()) a_elements.push_back(to_add);
        else a_elements.insert(a_elements.begin() + position, to_add);
        created_button++;
        std::cout << "A" << std::endl;
    }

    // Updates the elements in the list
    void GUI_List::update_elements() {
        for(int i = 0;i<static_cast<int>(a_elements.size());i++) {
            // Place each elements
            if(i == 0) a_elements[i].get()->attach_left_in_parent();
            //else a_elements[i].get()->attach_right_of_object_in_parent(a_elements[i - 1]);
        }
    }

    // Update the events in the list
    void GUI_List::update_event() {
        if(a_new_element_button.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            // A new element must be added
            add_element(a_elements.size());
        }
    }

    // Data_Structure_Page constructor
    Data_Structure_Page::Data_Structure_Page(scls::_Window_Advanced_Struct* window_struct, std::string name) : scls::GUI_Page(window_struct, name) {}

    // Create an object from a type
    std::shared_ptr<scls::GUI_Object> Data_Structure_Page::__create_loaded_object_from_type(std::string object_name, std::string object_type, scls::GUI_Object* parent) {
        if(object_name == "body_data_handling") {
            a_body_data_handling = *parent->new_object<scls::GUI_Object>(object_name);
            return a_body_data_handling;
        }
        else if(object_name == "hub_body") {
            a_body_home = *parent->new_object<scls::GUI_Object>(object_name);
            return a_body_home;
        }
        else if(object_name == "hub_navigation_data_handling") {
            a_navigation_data_handling = *parent->new_object<scls::GUI_Text>(object_name);
            return a_navigation_data_handling;
        }
        else if(object_name == "hub_navigation_home") {
            a_navigation_home = *parent->new_object<scls::GUI_Text>(object_name);
            return a_navigation_home;
        }
        else if(object_type == "gui_list") { return *parent->new_object<GUI_List>(object_name); }
        return scls::GUI_Page::__create_loaded_object_from_type(object_name, object_type, parent);
    }

    // Check the navigation event
    void Data_Structure_Page::check_navigation_events() {
        if(a_navigation_home.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            // The home button is clicked
            display_home();
        }
        if(a_navigation_data_handling.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            // The data handling button is clicked
            display_data_handling();
        }
    }

    // Displays the body of the data handling
    void Data_Structure_Page::display_data_handling() {
        hide_all();
        if(a_body_data_handling.get() != 0) a_body_data_handling.get()->set_visible(true);
    }

    // Displays the body of the home
    void Data_Structure_Page::display_home() {
        hide_all();
        if(a_body_home.get() != 0) a_body_home.get()->set_visible(true);
    }

    // Hide all the bodies in the page
    void Data_Structure_Page::hide_all() {
        if(a_body_data_handling.get() != 0) a_body_data_handling.get()->set_visible(false);
        if(a_body_home.get() != 0) a_body_home.get()->set_visible(false);
    }

    // Update the events in the page
    void Data_Structure_Page::update_event() {
        scls::GUI_Page::update_event();

        check_navigation_events();
    }
}
