// -*- coding: utf-8 -*-

// @autor: Jarrod Burns
// @github: github.com/JarrodBurns
// @version 1.0.2   -   04/14/2022 


#include "headers\main.hpp"
#include "headers\GFX.hpp"
#include "headers\DCount.hpp"
#include "headers\FileHandler.hpp"


int main()
{
    GFX Graphics;
    DCount App;
    FileHandler FileManager;

    const std::string file_name = "last_count.txt";

    std::string command;
    int count = FileManager.read_from_file(file_name);

    // first time setup
    App.set_from_file_history(count);
    Graphics.build_frame();
    Graphics.set_segment_values(App.segment_values);
    Graphics.clear_screen();
    Graphics.draw_screen();

 
    // main loop
    while(true)
    {
        std::cin >> command;
        App.deviate_count(command);

        Graphics.set_previous_command(App.previous_command);
        Graphics.set_segment_values(App.segment_values);
        Graphics.clear_screen();
        Graphics.draw_screen();

        int count_history = App.count;
        FileManager.write_to_file(file_name, count_history);
    }
}
