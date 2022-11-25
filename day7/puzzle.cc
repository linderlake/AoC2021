#include "../AoCHelper/AoCHelper.h"
#include <vector>

long calculate_fuel(int position, std::vector<int> &crab_positions)
{
    long total{};
    for (int c : crab_positions)
    {
        total += std::abs(position - c);
    }
    return total;
}

long calculate_fuel_puzzle_two(int position, std::vector<int> &crab_positions)
{
    // crab engineering safe
    long total{};
    for (int c : crab_positions)
    {
        for (size_t i = 1; i <= std::abs(position - c); i++)
        {
            total += i;
        }
        
    }
    return total;
}

void puzzle_one(std::vector<std::string> input)
{
    std::vector<int> crab_positions{};

    // parse input
    for (std::string row : input)
    {
            while (row.find(",") != std::string::npos)
            {
                int crab =  std::stoi(row.substr(0, row.find(",")));
                crab_positions.push_back(crab);
                row.erase(0, row.find(",") + 1);
            }
            crab_positions.push_back(std::stoi(row));
    }

    std::sort(crab_positions.begin(), crab_positions.end());
    int lowest_pos{crab_positions[0]};
    int highest_pos{crab_positions[crab_positions.size()-1]};
    int optimal_pos{0};
    long optimal_fuel{-1};
    for (int i = lowest_pos; i <= highest_pos; i++)
    {
        long fuel_cost = calculate_fuel(i, crab_positions);
        if (optimal_fuel == -1 || fuel_cost < optimal_fuel)
        {
            optimal_pos = i;
            optimal_fuel = fuel_cost;
        }
    }
    
    long answer{optimal_fuel};
    std::cout << "Puzzle one: " << answer << std::endl;
}

void puzzle_two(std::vector<std::string> input)
{
    std::vector<int> crab_positions{};

    // parse input
    for (std::string row : input)
    {
        for (std::string row : input)
        {
            while (row.find(",") != std::string::npos)
            {
                int crab =  std::stoi(row.substr(0, row.find(",")));
                crab_positions.push_back(crab);
                row.erase(0, row.find(",") + 1);
            }
            crab_positions.push_back(std::stoi(row));
        }
    }

    std::sort(crab_positions.begin(), crab_positions.end());
    int lowest_pos{crab_positions[0]};
    int highest_pos{crab_positions[crab_positions.size()-1]};
    int optimal_pos{0};
    long optimal_fuel{-1};
    for (int i = lowest_pos; i <= highest_pos; i++)
    {
        long fuel_cost = calculate_fuel_puzzle_two(i, crab_positions);
        if (optimal_fuel == -1 || fuel_cost < optimal_fuel)
        {
            optimal_pos = i;
            optimal_fuel = fuel_cost;
        }
    }
    
    long answer{optimal_fuel};
    std::cout << "Puzzle one: " << answer << std::endl;
}

int main()
{
    std::vector<std::string> exampleInput{"16, 1, 2, 0, 4, 2, 7, 1, 2, 14"};
    AoCHelper a1{"2021", "7"};
    std::vector<std::string> result = a1.get_input();
    puzzle_one(result);
    puzzle_two(result);
}
