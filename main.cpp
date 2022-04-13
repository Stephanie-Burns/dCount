// -*- coding: utf-8 -*-

// @autor: Jarrod Burns
// @github: github.com/JarrodBurns
// @version 1.0.0   -   04/12/2021 


#include <iostream>
#include <string>
#include "GFX.hpp"
#include "DCount.hpp"
#include "FileHandler.hpp"


int main()
{
    GFX Graphics;
    DCount App;
    FileHandler FileManager;
    const std::string file_name = "lst.txt";
    std::string command;
    int count = FileManager.read_from_file(file_name);

    // first time setup
    App.set_from_file_history(count);
    Graphics.build_frame();
    Graphics.set_place_values(App.place_values);
    Graphics.clear_screen();
    Graphics.draw_screen();


    // main loop
    while(true)
    {
        std::cin >> command;
        App.deviate_count(command);

        Graphics.set_previous_command(App.previous_command);
        Graphics.set_place_values(App.place_values);
        Graphics.clear_screen();
        Graphics.draw_screen();

        int count_history = App.get_count();
        FileManager.write_to_file(file_name, count_history);
    }
}
