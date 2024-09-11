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
        __Element element_to_add;

        // Create the base of the element
        std::shared_ptr<scls::GUI_Object>& to_add = element_to_add.element_base;
        to_add = *new_object<scls::GUI_Object>(name() + "-button_" + std::to_string(created_button));
        to_add.get()->attach_bottom_in_parent();
        to_add.get()->set_background_color(scls::Color(255, 255, 255));
        to_add.get()->set_border_width_in_pixel(1);
        to_add.get()->set_height_in_scale(scls::Fraction(4, 5));
        to_add.get()->set_width_in_scale(scls::Fraction(1, 3));
        to_add.get()->set_x_in_scale(scls::Fraction(0));

        // Create the delete button
        std::shared_ptr<scls::GUI_Text>& delete_button = element_to_add.delete_button;
        if(a_type == List) {
            delete_button = *to_add.get()->new_object<scls::GUI_Text>(name() + "-button_" + std::to_string(created_button) + "_delete");
            delete_button.get()->attach_bottom_in_parent();
            delete_button.get()->set_border_width_in_pixel(1);
            delete_button.get()->set_height_in_scale(scls::Fraction(1, 5));
            delete_button.get()->set_overflighted_cursor(GLFW_HAND_CURSOR);
            delete_button.get()->set_text("Supprimer");
            delete_button.get()->set_width_in_scale(scls::Fraction(1));
            delete_button.get()->set_x_in_object_scale(scls::Fraction(1, 2));
        }

        std::shared_ptr<scls::GUI_Text>& insert_button = element_to_add.insert_button;
        if(!a_use_index && a_type == List) {
            // Create the insert button
            insert_button = *to_add.get()->new_object<scls::GUI_Text>(name() + "-button_" + std::to_string(created_button) + "_insert");
            insert_button.get()->attach_top_of_object_in_parent(delete_button);
            insert_button.get()->set_border_width_in_pixel(1);
            insert_button.get()->set_height_in_scale(scls::Fraction(1, 5));
            insert_button.get()->set_overflighted_cursor(GLFW_HAND_CURSOR);
            insert_button.get()->set_text(scls::to_utf_8_code_point("Insérer avant"));
            insert_button.get()->set_width_in_scale(scls::Fraction(1));
            insert_button.get()->set_x_in_object_scale(scls::Fraction(1, 2));
        }

        // Create the index text of the element
        std::shared_ptr<scls::GUI_Text>& index_part = element_to_add.index_text;
        index_part = *to_add.get()->new_object<scls::GUI_Text>(name() + "-button_" + std::to_string(created_button) + "_index");
        if(a_type != List) index_part.get()->attach_bottom_in_parent();
        else if(a_use_index) index_part.get()->attach_top_of_object_in_parent(delete_button);
        else index_part.get()->attach_top_of_object_in_parent(insert_button);
        index_part.get()->set_height_in_scale(scls::Fraction(1, 5));
        index_part.get()->set_width_in_scale(scls::Fraction(4, 5));
        index_part.get()->set_x_in_object_scale(scls::Fraction(1, 2));

        // Create the element content
        std::shared_ptr<scls::GUI_Text_Input>& element_content = element_to_add.element_content;
        element_content = *to_add.get()->new_object<scls::GUI_Text_Input>(name() + "-button_" + std::to_string(created_button) + "_content");
        element_content.get()->attach_top_in_parent(5);
        element_content.get()->set_border_width_in_pixel(1);
        element_content.get()->set_height_in_scale(scls::Fraction(2, 5));
        element_content.get()->set_width_in_scale(scls::Fraction(4, 5));
        element_content.get()->set_x_in_object_scale(scls::Fraction(1, 2));

        // Set the good index
        if(a_use_index) {
            element_to_add.index = a_new_element_index.get()->text();
            index_part.get()->set_text("Indice : " + a_new_element_index.get()->text());
            a_new_element_index.get()->set_text("");
        }

        if(position >= a_elements.size()) a_elements.push_back(element_to_add);
        else a_elements.insert(a_elements.begin() + position, element_to_add);
        created_button++;

        // Setup the animation
        a_currently_animated = true;
        a_curently_animated_entering_element = to_add;
        a_curently_animated_entering_state = 0;

        update_elements();
    }

    // Configure the stack / queue GUI
    void GUI_List::configure_gui_stack_queue() {
        // Create the title of the index
        a_delete_element_button = *new_object<scls::GUI_Text>(name() + "-deletel_element_button");
        a_delete_element_button.get()->attach_right_in_parent();
        a_delete_element_button.get()->attach_top_in_parent();
        a_delete_element_button.get()->set_border_width_in_pixel(1);
        a_delete_element_button.get()->set_font_size(30);
        a_delete_element_button.get()->set_height_in_pixel(30);
        a_delete_element_button.get()->set_overflighted_cursor(GLFW_HAND_CURSOR);
        a_delete_element_button.get()->set_text(scls::to_utf_8_code_point("Supprimer un élément"));
        a_delete_element_button.get()->set_texture_alignment(scls::Alignment_Texture::T_Fit);
        a_delete_element_button.get()->set_width_in_scale(scls::Fraction(1, 3));
        a_delete_element_button.get()->set_x_in_scale(scls::Fraction(0));
    }

    // Configure the text index enter GUI
    void GUI_List::configure_gui_text_index(std::string index_title) {
        a_use_index = true;

        // Create the title of the index
        std::shared_ptr<scls::GUI_Text> a_index_title = *new_object<scls::GUI_Text>(name() + "-index_title");
        a_index_title.get()->attach_right_of_object_in_parent(a_new_element_button.get());
        a_index_title.get()->attach_top_in_parent();
        a_index_title.get()->set_font_size(30);
        a_index_title.get()->set_height_in_pixel(30);
        a_index_title.get()->set_text(index_title);
        a_index_title.get()->set_texture_alignment(scls::Alignment_Texture::T_Fit);
        a_index_title.get()->set_width_in_scale(scls::Fraction(1, 3));
        a_index_title.get()->set_x_in_scale(scls::Fraction(0));
        // Create the index enter
        a_new_element_index = *new_object<scls::GUI_Text_Input>(name() + "-index");
        a_new_element_index.get()->attach_right_of_object_in_parent(a_index_title.get());
        a_new_element_index.get()->attach_top_in_parent();
        a_new_element_index.get()->set_border_width_in_pixel(1);
        a_new_element_index.get()->set_font_size(30);
        a_new_element_index.get()->set_height_in_pixel(30);
        a_new_element_index.get()->set_texture_alignment(scls::Alignment_Texture::T_Fit);
        a_new_element_index.get()->set_width_in_scale(scls::Fraction(1, 3));
        a_new_element_index.get()->set_x_in_scale(scls::Fraction(0));
    }

    // Deletes an element in the list
    void GUI_List::delete_element(unsigned short position) {
        std::shared_ptr<GUI_Object> to_delete = a_elements[position].element_base;
        a_elements.erase(a_elements.begin() + position);
        delete_child(to_delete.get()); to_delete.reset();
        update_elements();
    }

    // Updates the elements in the list
    void GUI_List::update_elements() {
        for(int i = 0;i<static_cast<int>(a_elements.size());i++) {
            // Add the good index
            if(!a_use_index) a_elements[i].index_text.get()->set_text("Indice " + std::to_string(i));

            // Place each elements
            a_elements[i].element_base.get()->attach_bottom_in_parent();
            if(i <= 0) a_elements[i].element_base.get()->attach_left_in_parent();
            else a_elements[i].element_base.get()->attach_right_of_object_in_parent(a_elements[i - 1].element_base);
        }
    }

    // Update the events in the list
    void GUI_List::update_event() {
        GUI_Object::update_event();

        if(!a_currently_animated && a_new_element_button.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            // A new element must be added
            if(a_use_index) {
                std::string index = a_new_element_index.get()->text();
                if(a_new_element_index.get()->text() != "") {
                    // Get the needed position for the element
                    unsigned short position = a_elements.size();
                    for(int i = 0;i<static_cast<int>(a_elements.size());i++) {
                        bool should_break = false;
                        for(int j = 0;j<static_cast<int>(a_elements[i].index.size())&&j<static_cast<int>(index.size());j++) {
                            // Prepare the comparaison
                            char first_char = a_elements[i].index[j]; if(first_char > 96) first_char -= 32;
                            char second_char = index[j]; if(second_char > 96) second_char -= 32;

                            // Do the comparaison
                            if(first_char > second_char) { position = i; should_break = true; break; }
                            else if(first_char < second_char) break;
                        } if(should_break) break;
                    }

                    add_element(position);
                }
            }
            else add_element(a_elements.size());
        }

        // An element must be delete
        if(!a_currently_animated && a_elements.size() > 0 && a_delete_element_button.get() != 0 && a_delete_element_button.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            a_currently_animated = true;
            if(a_delete_element_index < 0) a_curently_animated_leaving_element = a_elements[a_elements.size() - static_cast<unsigned int>(-a_delete_element_index)].element_base;
            else a_curently_animated_leaving_element = a_elements[a_delete_element_index].element_base;
            a_curently_animated_leaving_state = 0;
        }

        // Check each animations
        int entering_animation_i = -1;
        int leaving_animation_i = -1;
        for(int i = 0;i<static_cast<int>(a_elements.size());i++) {
            if(a_type == List) {
                // Check if an insert button is pressed
                if(!a_use_index && !a_currently_animated && a_elements[i].insert_button.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
                    // Create the element
                    add_element(i);
                    i++;
                }

                // Check if a delete button is pressed
                if(!a_currently_animated && a_elements[i].delete_button.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
                    a_currently_animated = true;
                    a_curently_animated_leaving_element = a_elements[i].element_base;
                    a_curently_animated_leaving_state = 0;
                }
            }

            // Check the entering animation
            if(a_curently_animated_entering_state >= 0) {
                if(a_curently_animated_entering_element.get() == a_elements[i].element_base.get()) {
                    if(a_curently_animated_entering_state >= a_curently_animated_leaving_state_max) {
                        // Close the animation
                        a_curently_animated_entering_element.reset();
                        a_curently_animated_entering_state = -1;
                        a_currently_animated = false;

                        // Restart the simulation
                        update_elements();
                    }
                    else {
                        a_elements[i].element_base.get()->attach_bottom_in_parent(static_cast<double>(a_elements[i].element_base.get()->height_in_pixel()) * -(1.0 - a_curently_animated_entering_state / a_curently_animated_entering_state_max));
                        a_curently_animated_entering_state += window_struct().delta_time();
                        entering_animation_i = i;
                    }
                }
                else if(entering_animation_i != -1) {
                    if(entering_animation_i == i - 1) {
                        if(i <= 1) {
                            a_elements[i].element_base.get()->attach_left_in_parent(static_cast<double>(a_elements[i - 1].element_base.get()->width_in_pixel()) * (a_curently_animated_entering_state / a_curently_animated_entering_state_max));
                        }
                        else {
                            a_elements[i].element_base.get()->attach_right_of_object_in_parent(a_elements[i - 2].element_base.get(), static_cast<double>(a_elements[i - 1].element_base.get()->width_in_pixel()) * (a_curently_animated_entering_state / a_curently_animated_entering_state_max));
                        }
                    }
                    else {
                        a_elements[i].element_base.get()->attach_right_of_object_in_parent(a_elements[i - 1].element_base);
                    }
                }
            }

            // Check the leaving animation
            if(a_curently_animated_leaving_state >= 0) {
                if(a_curently_animated_leaving_element.get() == a_elements[i].element_base.get()) {
                    if(a_curently_animated_leaving_state >= a_curently_animated_leaving_state_max) {
                        // Close the animation
                        a_curently_animated_leaving_element.reset();
                        a_curently_animated_leaving_state = -1;
                        a_currently_animated = false;

                        // Apply the modification
                        delete_element(i);
                        i--;
                    }
                    else {
                        a_elements[i].element_base.get()->attach_bottom_in_parent(static_cast<double>(a_elements[i].element_base.get()->height_in_pixel()) * -(a_curently_animated_leaving_state / a_curently_animated_leaving_state_max));
                        a_curently_animated_leaving_state += window_struct().delta_time();
                        leaving_animation_i = i;
                    }
                }
                else if(leaving_animation_i != -1) {
                    if(leaving_animation_i == i - 1) {
                        if(i <= 1) {
                            a_elements[i].element_base.get()->attach_left_in_parent(static_cast<double>(a_elements[i - 1].element_base.get()->width_in_pixel()) * (1.0 - a_curently_animated_leaving_state / a_curently_animated_leaving_state_max));
                        }
                        else {
                            a_elements[i].element_base.get()->attach_right_of_object_in_parent(a_elements[i - 2].element_base.get(), static_cast<double>(a_elements[i - 1].element_base.get()->width_in_pixel()) * (1.0 - a_curently_animated_leaving_state / a_curently_animated_leaving_state_max));
                        }
                    }
                    else {
                        a_elements[i].element_base.get()->attach_right_of_object_in_parent(a_elements[i - 1].element_base);
                    }
                }
            }
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
        else if(object_name == "body_ds_optimisation") {
            a_body_ds_optimisation = *parent->new_object<scls::GUI_Object>(object_name);
            return a_body_ds_optimisation;
        }
        else if(object_name == "body_stack_queue") {
            a_body_stack_queue = *parent->new_object<scls::GUI_Object>(object_name);
            return a_body_stack_queue;
        }
        else if(object_name == "hub_body") {
            a_body_home = *parent->new_object<scls::GUI_Object>(object_name);
            return a_body_home;
        }
        else if(object_name == "hub_navigation_data_handling") {
            a_navigation_data_handling = *parent->new_object<scls::GUI_Text>(object_name);
            return a_navigation_data_handling;
        }
        else if(object_name == "hub_navigation_ds_optimisation") {
            a_navigation_ds_optimisation = *parent->new_object<scls::GUI_Text>(object_name);
            return a_navigation_ds_optimisation;
        }
        else if(object_name == "hub_navigation_home") {
            a_navigation_home = *parent->new_object<scls::GUI_Text>(object_name);
            return a_navigation_home;
        }
        else if(object_name == "hub_navigation_stack_queue") {
            a_navigation_stack_queue = *parent->new_object<scls::GUI_Text>(object_name);
            return a_navigation_stack_queue;
        }
        else if(object_type == "gui_list") {
            std::shared_ptr<GUI_List> to_return = *parent->new_object<GUI_List>(object_name);
            if(object_name == "body_ds_optimisation_list") to_return.get()->configure_gui_text_index("Nom :");
            else if(object_name == "body_stack_queue_queue") to_return.get()->set_queue();
            else if(object_name == "body_stack_queue_stack") to_return.get()->set_stack();
            return to_return;
        }
        return scls::GUI_Page::__create_loaded_object_from_type(object_name, object_type, parent);
    }

    // Check the navigation event
    void Data_Structure_Page::check_navigation_events() {
        if(a_navigation_home.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            // The home button is clicked
            display_home();
        }
        if(a_navigation_ds_optimisation.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            // The data structure optimisation button is clicked
            display_ds_optimisation();
        }
        if(a_navigation_data_handling.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            // The data handling button is clicked
            display_data_handling();
        }
        if(a_navigation_stack_queue.get()->is_clicked_during_this_frame(GLFW_MOUSE_BUTTON_LEFT)) {
            // The stack / queue button is clicked
            display_stack_queue();
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

    // Displays the body of the data structure optimisation
    void Data_Structure_Page::display_ds_optimisation() {
        hide_all();
        if(a_body_ds_optimisation.get() != 0) a_body_ds_optimisation.get()->set_visible(true);
    }

    // Displays the body of the stack / queue
    void Data_Structure_Page::display_stack_queue() {
        hide_all();
        if(a_body_stack_queue.get() != 0) a_body_stack_queue.get()->set_visible(true);
    }

    // Hide all the bodies in the page
    void Data_Structure_Page::hide_all() {
        if(a_body_data_handling.get() != 0) a_body_data_handling.get()->set_visible(false);
        if(a_body_ds_optimisation.get() != 0) a_body_ds_optimisation.get()->set_visible(false);
        if(a_body_home.get() != 0) a_body_home.get()->set_visible(false);
        if(a_body_stack_queue.get() != 0) a_body_stack_queue.get()->set_visible(false);
    }

    // Update the events in the page
    void Data_Structure_Page::update_event() {
        scls::GUI_Page::update_event();

        check_navigation_events();
    }
}
