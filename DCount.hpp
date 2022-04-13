// -*- coding: utf-8 -*-

// @autor: Jarrod Burns
// @github: github.com/JarrodBurns
// @version 1.0.0   -   04/12/2021 


#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>

class DCount
{
public:
    const std::vector<std::string> special_commands = 
    {"R", "-", "*", "/", "**", "//"};
    std::vector<int> place_values = {0, 0, 0, 0};
    std::string previous_command;
    int count = 0;


    void set_from_file_history(int count_history)
    // Setter for count from file history.
    // Intended for use with file history, to set
    // a saved value from the last session.
    {
        count = count_history;
        set_place_values();
    }


    int get_count()
    {
        return count;
    }


    void set_place_values()
    // Converts a number into it's place values.
    // For count < 10,000 | count = 905, Result: 0, 9, 0, 5
    {
        int thousands_place = floor(count / 1000);
        int thousands_remainder = count - (thousands_place * 1000);

        int hundreds_place = floor(thousands_remainder / 100);
        int hundreds_remainder = thousands_remainder - hundreds_place * 100;

        int tens_place = floor(hundreds_remainder / 10);

        // 10s remainder and ones place are the same thing
        // so we forgo the unnecessary variable creation.
        int ones_place = hundreds_remainder - tens_place * 10;

        // Setting the place values to their container
        place_values[0] = thousands_place;
        place_values[1] = hundreds_place;
        place_values[2] = tens_place;
        place_values[3] = ones_place;
    }


    void set_previous_command(std::string command)
    {
        previous_command = command;
    }


    int parse_user_input(std::string user_input)
    // Checks user input against a predefined list of commands.
    // Registered commands: 'R', '-', '/', '*'
    // If sucessful, the index of that command will be returned.
    {
        auto iter = find(special_commands.begin(), special_commands.end(),
            user_input);
        
        if(iter != special_commands.end())
        {
            int index = iter - special_commands.begin();
            return index;
        }
            return -1;
    }


    void deviate_count(std::string user_input)
    // Increments or decrements the count based on the users input.
    // Range 0 < 10,000
    {
        int i = parse_user_input(user_input);

        switch(i)
        {
            case 0:                                              // Reset: "R"
                set_previous_command("R");
                count = 0;
                break;

            case 1:                                       // Subtract one: "-"
                set_previous_command("-");
                if(count > 0)
                {
                    count -= 1;
                } 
                else
                {
                    count = 0;
                }
                break;

            case 2:                                            // Add ten: "*"
                set_previous_command("*");
                if(count < 9990)
                {
                    count += 10;
                }
                else
                {
                    count = 9999;
                }
                break;

            case 3:                                       // Subtract ten: "/"
                set_previous_command("/");
                if(count > 10)
                {
                    count -= 10;
                }
                else
                {
                    count = 0;
                }
                break;

            case 4:                                            // Add 100: "/"
                set_previous_command("**");
                if(count < 9900)
                {
                    count += 100;
                }
                else
                {
                    count = 9999;
                }
                break;

            case 5:                                       // Subtract 100: "/"
                set_previous_command("//");
                if(count > 100)
                {
                    count -= 100;
                }
                else
                {
                    count = 0;
                }
                break;

            case -1:
                set_previous_command("(any)");  // Add one: any key not listed
                if(count < 9999)
                {
                    count += 1;
                }
                else
                {
                    count = 9999;
                }
                break;   

            default:                                                  // ERROR
            {
                // Something went horribly wrong if this triggers, good luck.
                std::clog << "User input is an unrecognized command.";
                std::cerr;
                break;
            }

        };
        set_place_values();
    }
};
