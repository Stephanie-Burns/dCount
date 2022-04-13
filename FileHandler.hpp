// -*- coding: utf-8 -*-

// @autor: Jarrod Burns
// @github: github.com/JarrodBurns
// @version 1.0.0   -   04/12/2021 


#include <fstream>
#include <string>

class FileHandler
{
public:
    void write_to_file(std::string file_handle, int value)
    {
        // Write File
        std::ofstream write_file(file_handle);
        write_file << value;
        write_file.close();

    }


    int read_from_file(std::string file_handle)
    {
        // Read File
        std::string last_known_count;
        std::ifstream read_file(file_handle);
        if(getline(read_file, last_known_count))
        {
            read_file.close();
            return stoi(last_known_count);
        }
        return 0;
    }
};
