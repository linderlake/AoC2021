#include "../AoCHelper/AoCHelper.h"
#include <vector>

void puzzle_one(std::vector<std::string> input)
{
    int coordinates[1000][1000] = {};
    for (std::string row : input)
    {
        // get coordinates
        std::string line_start = row.substr(0, row.find("->") - 1);
        std::string line_end = row.substr(row.find("->") + 3);
        int start_x{std::stoi(line_start.substr(0, line_start.find(",")))};
        int start_y{std::stoi(line_start.substr(line_start.find(",") + 1))};
        int end_x{std::stoi(line_end.substr(0, line_end.find(",")))};
        int end_y{std::stoi(line_end.substr(line_end.find(",") + 1))};

        if (start_x != end_x && start_y != end_y) 
        {
            // diagonal line, should be ignored
            continue;
        }

        if (start_x > end_x) {
            // flip
            int temp = end_x;
            end_x = start_x;
            start_x = temp;
        }

        if (start_y > end_y) {
            // flip
            int temp = end_y;
            end_y = start_y;
            start_y = temp;
        }


        // draw x
        for (size_t i = start_x; i <= end_x; i++)
        {
            // draw y
            for (size_t j = start_y; j <= end_y; j++)
            {
                coordinates[i][j] = coordinates[i][j] + 1;
            }
        }

    }

    size_t answer{};
    for (size_t i = 0; i < 1000; i++)
    {
        for (size_t j = 0; j < 1000; j++)
        {
            if (coordinates[i][j] >= 2) {
                answer++;
            }
        }
        
    }

    
    std::cout << "Puzzle one: " << answer << std::endl;
}

void puzzle_two(std::vector<std::string> input)
{
    int coordinates[1000][1000] = {};
    for (std::string row : input)
    {
        // get coordinates
        std::string line_start = row.substr(0, row.find("->") - 1);
        std::string line_end = row.substr(row.find("->") + 3);
        int start_x{std::stoi(line_start.substr(0, line_start.find(",")))};
        int start_y{std::stoi(line_start.substr(line_start.find(",") + 1))};
        int end_x{std::stoi(line_end.substr(0, line_end.find(",")))};
        int end_y{std::stoi(line_end.substr(line_end.find(",") + 1))};

        if (start_x != end_x && start_y != end_y) 
        {
            // diagonal line

            int offsetx = end_x - start_x;
            int offsety = end_y - start_y;
            int getpos_x = offsetx / std::abs(offsetx);
            int getpos_y = offsety / std::abs(offsety);

            for (int i = 0; i <= std::abs(offsetx); i++)
            {
                int i_x = i * getpos_x;
                int i_y = i * getpos_y;
                
                coordinates[start_x + i_x][start_y + i_y] = coordinates[start_x + i_x][start_y + i_y] + 1; 
            }

        } 
        else 
        {
            if (start_x > end_x) {
                // flip
                int temp = end_x;
                end_x = start_x;
                start_x = temp;
            }
    
            if (start_y > end_y) {
                // flip
                int temp = end_y;
                end_y = start_y;
                start_y = temp;
            }
             // draw x
                for (size_t i = start_x; i <= end_x; i++)
                {
                    // draw y
                    for (size_t j = start_y; j <= end_y; j++)
                    {
                        coordinates[i][j] = coordinates[i][j] + 1;
                    }
                }
        }

    }

    size_t answer{};
    for (size_t i = 0; i < 1000; i++)
    {
        for (size_t j = 0; j < 1000; j++)
        {
            if (coordinates[i][j] >= 2) {
                answer++;
            }
        }
        
    }

    
    std::cout << "Puzzle two: " << answer << std::endl;
}

int main()
{

    AoCHelper a1{"2021", "5"};
    std::vector<std::string> result = a1.get_input();
    puzzle_one(result);
    puzzle_two(result);
    return 0;
}
