#include "../AoCHelper/AoCHelper.h"
#include <vector>
#include <queue>

int const array_width = 100;
int const array_height = 100;

class queue_helper
{
private:
    std::queue<std::pair<int, int>> coordinates_to_process{};

public:
    std::queue<std::pair<int, int>> &get_queue();
};

std::queue<std::pair<int, int>> &queue_helper::get_queue()
{
    return coordinates_to_process;
}

struct height_int
{
    int height{};
    bool visited = false;
    bool basin_visited = false;
};

long find_basin(std::pair<int, int> coordinates, height_int (&heightmap)[100][100])
{   
    long total{1};
    height_int &current_height = heightmap[coordinates.first][coordinates.second];
    current_height.basin_visited = true;
    if (coordinates.first > 0)
    {
        height_int &height1 = heightmap[(coordinates.first) - 1][coordinates.second]; // up one square
        if (height1.height < 9 && !height1.basin_visited)
        {
            height1.basin_visited = true;
            total += find_basin({(coordinates.first) - 1, coordinates.second}, heightmap);
        }
    }

    if (coordinates.first < array_height - 1)
    {
        height_int &height2 = heightmap[(coordinates.first) + 1][coordinates.second]; // down one square
       if (height2.height < 9 && !height2.basin_visited)
        {
            height2.basin_visited = true;
            total += find_basin({(coordinates.first) + 1, coordinates.second}, heightmap);
        }
    }

    if (coordinates.second > 0)
    {
        height_int &height3 = heightmap[coordinates.first][coordinates.second - 1]; // left one square
        if (height3.height < 9 && !height3.basin_visited)
        {
             height3.basin_visited = true;
             total += find_basin({(coordinates.first), coordinates.second - 1}, heightmap);
        }
    }

    if (coordinates.second < array_width - 1)
    {
        height_int &height4 = heightmap[coordinates.first][coordinates.second + 1]; // right one square
        if (height4.height < 9 && !height4.basin_visited)
        {
             height4.basin_visited = true;
             total += find_basin({(coordinates.first), coordinates.second + 1}, heightmap);
        }
    }
    return total;
}

void find_adjacent_lower_points(std::pair<int, int> coordinates, height_int (&heightmap)[100][100], queue_helper &q, std::vector<std::pair<int, int>> &lowest_coordinates)
{
    height_int &current_height = heightmap[coordinates.first][coordinates.second];
    bool highest = true;
    if (coordinates.first > 0)
    {
        height_int &height1 = heightmap[(coordinates.first) - 1][coordinates.second]; // up one square
        if (height1.height <= current_height.height)
        {
            highest = false;
            if (!height1.visited)
            {
                q.get_queue().push({coordinates.first - 1, coordinates.second});
                height1.visited = true;
            }
        }
    }

    if (coordinates.first < array_height - 1)
    {
        height_int &height2 = heightmap[(coordinates.first) + 1][coordinates.second]; // down one square
        if (height2.height <= current_height.height)
        {
            highest = false;
            if (!height2.visited)
            {
                q.get_queue().push({coordinates.first + 1, coordinates.second});
                height2.visited = true;
            }
        }
    }

    if (coordinates.second > 0)
    {
        height_int &height3 = heightmap[coordinates.first][coordinates.second - 1]; // left one square
        if (height3.height <= current_height.height)
        {
            highest = false;
            if (!height3.visited)
            {
                q.get_queue().push({coordinates.first, coordinates.second - 1});
                height3.visited = true;
            }
        }
    }

    if (coordinates.second < array_width - 1)
    {
        height_int &height4 = heightmap[coordinates.first][coordinates.second + 1]; // right one square
        if (height4.height <= current_height.height)
        {
            highest = false;
            if (!height4.visited)
            {
                q.get_queue().push({coordinates.first, coordinates.second + 1});
                height4.visited = true;
            }
        }
    }

    if (highest && std::find(lowest_coordinates.begin(), lowest_coordinates.end(), coordinates) == lowest_coordinates.end())
    {
        // lowest point found
       
        lowest_coordinates.push_back(coordinates);
        current_height.visited = true;
    }
}

void puzzle_one(std::vector<std::string> input)
{
    queue_helper q{};
    std::vector<std::pair<int, int>> lowest_coordinates{};

    height_int heightmap[100][100] = {};

    for (size_t y = 0; y < input.size(); y++)
    {
        for (size_t x = 0; x < input[y].size(); x++)
        {
            heightmap[y][x].height = std::stoi(input[y].substr(x, 1));
        }
    }

    // bfs
    for (size_t y = 0; y < input.size(); y++)
    {
        for (size_t x = 0; x < input[y].size(); x++)
        {
            std::pair<int, int> current_coords = {y, x};
            find_adjacent_lower_points(current_coords, heightmap, q, lowest_coordinates);

            while (!q.get_queue().empty())
            {
                current_coords = q.get_queue().front();
                q.get_queue().pop();
                find_adjacent_lower_points(current_coords, heightmap, q, lowest_coordinates);
            }
        }
    }
    size_t answer{};
    for (std::pair<int, int> coords : lowest_coordinates)
    {
        answer += 1 + heightmap[coords.first][coords.second].height;
    }

    std::cout << "Puzzle one: " << answer << std::endl;
}


void puzzle_two(std::vector<std::string> input)
{
    queue_helper q{};
    std::vector<std::pair<int, int>> lowest_coordinates{};

    height_int heightmap[100][100] = {};

    for (size_t y = 0; y < input.size(); y++)
    {
        for (size_t x = 0; x < input[y].size(); x++)
        {
            heightmap[y][x].height = std::stoi(input[y].substr(x, 1));
        }
    }

    // bfs
    for (size_t y = 0; y < input.size(); y++)
    {
        for (size_t x = 0; x < input[y].size(); x++)
        {
            std::pair<int, int> current_coords = {y, x};
            find_adjacent_lower_points(current_coords, heightmap, q, lowest_coordinates);

            while (!q.get_queue().empty())
            {
                current_coords = q.get_queue().front();
                q.get_queue().pop();
                find_adjacent_lower_points(current_coords, heightmap, q, lowest_coordinates);
            }
        }
    }

    std::vector<long> basins{};
    for (std::pair<int, int> coords : lowest_coordinates)
    {

        long sum = find_basin(coords, heightmap);
        basins.push_back(sum);
    }
    std::sort(basins.begin(), basins.end(), std::greater<long>());
    long answer{basins[0] * basins[1] * basins[2]};
    std::cout << "Puzzle two: " << answer << std::endl;

}

int main()
{
    std::vector<std::string> exampleInput{"2199943210", "3987894921", "9856789892", "8767896789", "9899965678"};
    AoCHelper a1{"2021", "9"};
    std::vector<std::string> result = a1.get_input();
    puzzle_one(result);
    puzzle_two(result);
}
