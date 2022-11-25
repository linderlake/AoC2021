#include "../AoCHelper/AoCHelper.h"
#include <vector>

void puzzle_one(std::vector<std::string> input)
{
    int horizontal{0};
    int depth{0};
    for (std::string row : input)
    {
        size_t eqPos = row.find(" ");
        if (row.substr(0, eqPos) == "forward")
        {
            horizontal += std::stoi(row.substr(eqPos));
        }
        else if (row.substr(0, eqPos) == "down")
        {
            depth += std::stoi(row.substr(eqPos));
        }
        else if (row.substr(0, eqPos) == "up")
        {
            depth -= std::stoi(row.substr(eqPos));
        }
    }
    size_t answer = horizontal * depth;
    std::cout << "Puzzle one: " << answer << std::endl;
}

void puzzle_two(std::vector<std::string> input)
{
    size_t aim{0};
    int horizontal{0};
    int depth{0};
    for (std::string row : input)
    {
        size_t eqPos = row.find(" ");
        if (row.substr(0, eqPos) == "forward")
        {
            horizontal += std::stoi(row.substr(eqPos));
            depth += aim * std::stoi(row.substr(eqPos));
        }
        else if (row.substr(0, eqPos) == "down")
        {
            aim += std::stoi(row.substr(eqPos));
        }
        else if (row.substr(0, eqPos) == "up")
        {
            aim -= std::stoi(row.substr(eqPos));
        }
    }
    size_t answer = horizontal * depth;
    std::cout << "Puzzle two: " << answer << std::endl;
}

int main()
{

    AoCHelper a1{"2021", "2"};
    std::vector<std::string> result = a1.get_input();
    puzzle_one(result);
    puzzle_two(result);
}