// -*- coding: utf-8 -*-

// @autor: Jarrod Burns
// @github: github.com/JarrodBurns


class FileHandler
{
    // Reads and writes the file "value.dat"
    // This file stores the last seen counter value
    // for reference the next time the app starts.

private:
    static const std::filesystem::path get_appdata_path()
        // Returns a Windows path to ...current_user/app data/local/dCount/value.dat
    {
        WCHAR szPath[MAX_PATH];
        if (SHGetFolderPathAndSubDirW(
            NULL,
            CSIDL_LOCAL_APPDATA | CSIDL_FLAG_CREATE,
            NULL,
            SHGFP_TYPE_CURRENT,
            L"dCount",
            szPath) != S_OK
            )
        {
            throw 99;
        }
        return std::filesystem::path(szPath) / L"value.dat";
    }

public:
    static int read_count_history()
    {
        std::ifstream read_file(get_appdata_path());
        if (read_file.is_open())
        {
            int value;
            read_file >> value;
            read_file.close();
            return value;
        }
        return 0;
    }


    static void write_count_history(int value)
    {
        std::ofstream write_file(get_appdata_path());
        if (write_file.is_open())
        {
            write_file << value;
            write_file.close();
        }
    }
};
