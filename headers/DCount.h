// -*- coding: utf-8 -*-

// @autor: Jarrod Burns
// @github: github.com/JarrodBurns


class DCount
{
private:
    const std::vector<std::string> special_commands =
    { "R", "-", "*", "/", "**", "//" };


    void set_segment_values()
        // Converts a number into it's place values and assigns them accordingly.
        // For count < 10,000 | count = 905, Result: 0, 9, 0, 5
    {
        // convert to string and pad to 4 digits
        std::string i = std::to_string(count);
        std::string count_repr = std::string(4 - i.size(), '0').append(i);

        if (count_repr.size() > 4)
        {
            std::cerr << "[ERROR] Count may not exceed 9999.";
            return;
        }

        // assignment
        for (int i = 0; i < 4; i++)
        {
            segment_values[i] = count_repr[i] - '0';
        }
    }


    int parse_user_input(std::string user_input)
        // Checks user input against a predefined list of commands.
        // Registered commands: 'R', '-', '/', '*', "//", "**"
        // If successful, the index of that command will be returned.
    {
        auto iter = find(special_commands.begin(), special_commands.end(),
            user_input);

        if (iter != special_commands.end())
        {
            int index = iter - special_commands.begin();
            return index;
        }
        return -1;
    }

public:
    std::vector<int> segment_values = { 0, 0, 0, 0 };
    std::string previous_command;
    int count = 0;


    void set_from_count_history(int count_history)
        // Setter for count from file history.
        // Intended for use with file history, to set
        // a saved value from the last session.
    {
        count = count_history;
        set_segment_values();
    }


    void set_previous_command(std::string command)
    {
        previous_command = command;
    }


    void deviate_count(std::string user_input)
        // Increments or decrements the count based on user input.
        // Range 0 < 10,000
    {
        int i = parse_user_input(user_input);

        switch (i)
        {
        case 0:     // Reset
            set_previous_command("R");
            count = 0;
            break;

        case 1:     // Sub (1)
            set_previous_command("-");
            count < 1       ?   count = 0   :   --count;
            break;

        case 2:     // Add (10)
            set_previous_command("*");
            count > 9998    ?  count = 9999 :   count += 10;
            break;

        case 3:     // Sub (10)
            set_previous_command("/");
            count < 10      ?  count = 0    :   count -= 10;
            break;

        case 4:     // Add (100)
            set_previous_command("**");
            count > 9900    ?  count = 9999 :   count += 100;
            break;

        case 5:     // Sub (100)
            set_previous_command("//");
            count < 100     ?  count = 0    :   count -= 100;
            break;

        default:    // Add (1)
            set_previous_command("(any)");
            count > 9998    ?  count = 9999 :   ++count;
            break;
        };

        set_segment_values();

    }
};
