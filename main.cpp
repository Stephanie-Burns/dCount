// -*- coding: utf-8 -*-

// @autor: Jarrod Burns
// @github: github.com/JarrodBurns
// @version 1.0.3   -   04/17/2022 


#include "dCount\main.h"
#include "dCount\GFX.h"
#include "dCount\DCount.h"
#include "dCount\FileHandler.h"


int main()
{
    GFX Graphics;
    DCount App;
    FileHandler FileManager;

    std::string command;
    int count = FileManager.read_count_history();

    // first time setup
    App.set_from_count_history(count);
    Graphics.build_frame();
    Graphics.set_segment_values(App.segment_values);
    Graphics.clear_screen();
    Graphics.draw_screen();


    // main loop
    while (true)
    {
        std::cin >> command;
        App.deviate_count(command);

        Graphics.set_previous_command(App.previous_command);
        Graphics.set_segment_values(App.segment_values);
        Graphics.clear_screen();
        Graphics.draw_screen();

        int count_history = App.count;
        FileManager.write_count_history(count_history);
    }
}
