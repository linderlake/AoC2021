#include "../AoCHelper/AoCHelper.h"
#include <vector>
#include <set>

void flash_octopus(std::pair<int, int> octopus_coordinates, int (&octopus_map)[10][10], std::set<std::pair<int, int>> &flashed_octopus_map, size_t &flashes)
{
    if (flashed_octopus_map.find({octopus_coordinates.first, octopus_coordinates.second}) != flashed_octopus_map.end())
    {
        return; // already flashed this iteration, don't flash twice
    }

    std::vector<std::pair<int, int>> neighbor_coordinates{
        {octopus_coordinates.first + 1, octopus_coordinates.second},     // down one
        {octopus_coordinates.first + 1, octopus_coordinates.second + 1}, // down one, right one
        {octopus_coordinates.first + 1, octopus_coordinates.second - 1}, // down one, left one
        {octopus_coordinates.first - 1, octopus_coordinates.second},     // up one
        {octopus_coordinates.first - 1, octopus_coordinates.second + 1}, // up one, right one
        {octopus_coordinates.first - 1, octopus_coordinates.second - 1}, // up one, left one
        {octopus_coordinates.first, octopus_coordinates.second + 1},     // right one
        {octopus_coordinates.first, octopus_coordinates.second - 1},     // left one
    };
    flashed_octopus_map.insert({octopus_coordinates.first, octopus_coordinates.second});
    octopus_map[octopus_coordinates.first][octopus_coordinates.second] = 0;

    for (auto &&i : neighbor_coordinates)
    {
        // check corners and edges
        if (i.first < 0 || i.first > 9 || i.second < 0 || i.second > 9)
            continue;

        octopus_map[i.first][i.second]++;
        if (octopus_map[i.first][i.second] > 9)
        {
            flash_octopus({i.first, i.second}, octopus_map, flashed_octopus_map, flashes);
        };
    }
    flashes++;
}

void puzzle_one(std::vector<std::string> input)
{
    int octopus_map[10][10]{};
    std::set<std::pair<int, int>> flashed_octopus_map{};
    // int flashed_octopus_map[10][10]{};
    size_t answer{};

    for (size_t i = 0; i < input.size(); i++)
    {
        for (size_t j = 0; j < input[i].size(); j++)
        {
            octopus_map[i][j] = input[i][j] - '0';
            // flashed_octopus_map[i][j] = 0;
        }
    }

    for (size_t x = 0; x < 100; x++)
    {
        for (size_t i = 0; i < 10; i++)
        {
            for (size_t j = 0; j < 10; j++)
            {
                octopus_map[i][j]++;
                if (octopus_map[i][j] > 9)
                    flash_octopus({i, j}, octopus_map, flashed_octopus_map, answer);
            }
        }

        for (auto &&c : flashed_octopus_map)
        {
            octopus_map[c.first][c.second] = 0;
        }

        flashed_octopus_map.clear();
    }

    std::cout << "Puzzle one: " << answer << std::endl;
}

void puzzle_two(std::vector<std::string> input)
{

    int octopus_map[10][10]{};
    std::set<std::pair<int, int>> flashed_octopus_map{};
    // int flashed_octopus_map[10][10]{};
    size_t answer{};

    for (size_t i = 0; i < input.size(); i++)
    {
        for (size_t j = 0; j < input[i].size(); j++)
        {
            octopus_map[i][j] = input[i][j] - '0';
            // flashed_octopus_map[i][j] = 0;
        }
    }

    for (size_t x = 0; x < 1000; x++)
    {
        for (size_t i = 0; i < 10; i++)
        {
            for (size_t j = 0; j < 10; j++)
            {
                octopus_map[i][j]++;
                if (octopus_map[i][j] > 9)
                    flash_octopus({i, j}, octopus_map, flashed_octopus_map, answer);
            }
        }
        if (flashed_octopus_map.size() == 100)
        {
            answer = x + 1;
            break;
        }
        for (auto &&c : flashed_octopus_map)
        {
            octopus_map[c.first][c.second] = 0;
        }

        flashed_octopus_map.clear();
    }
    std::cout << "Puzzle two: " << answer << std::endl;
}

int main()
{
    std::vector<std::string> exampleInput{"5483143223",
                                          "2745854711",
                                          "5264556173",
                                          "6141336146",
                                          "6357385478",
                                          "4167524645",
                                          "2176841721",
                                          "6882881134",
                                          "4846848554",
                                          "5283751526"};
    AoCHelper a1{"2021", "11"};
    std::vector<std::string> result = a1.get_input();
    puzzle_one(result);
    puzzle_two(result);
}
