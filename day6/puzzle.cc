#include "../AoCHelper/AoCHelper.h"
#include <vector>

void puzzle_one(std::vector<std::string> input)
{
    std::vector<int> fishVector{};

    // parse input
    for (std::string row : input)
    {
        while (row.find(",") != std::string::npos)
        {
            int fish =  std::stoi(row.substr(0, row.find(",")));
            fishVector.push_back(fish);
            row.erase(0, row.find(",") + 1);
        }
        fishVector.push_back(std::stoi(row.substr(0, 2)));
    }

    // simulate. 1 iteration = 1 day.
    for (size_t i = 0; i < 80; i++)
    {
        std::vector<int> newFishes;

        std::transform(fishVector.begin(), fishVector.end(), fishVector.begin(),  [&newFishes] (int fish) -> int {
                if (fish == 0) {
                    newFishes.push_back(8);
                    return 6;
                } else {
                    return fish - 1;
                }
            });

        std::copy(newFishes.begin(), newFishes.end(), back_inserter(fishVector));

    }
    
    size_t answer{fishVector.size()};
    std::cout << "Puzzle one: " << answer << std::endl;
}

void puzzle_two(std::vector<std::string> input)
{

    std::vector<int> fishVector{};

    // parse input
    for (std::string row : input)
    {
        while (row.find(",") != std::string::npos)
        {
            int fish =  std::stoi(row.substr(0, row.find(",")));
            fishVector.push_back(fish);
            row.erase(0, row.find(",") + 1);
        }
        fishVector.push_back(std::stoi(row.substr(0, 2)));
    }

    std::map<int, long long> fishBuckets{};
                    //day count
    fishBuckets.insert({0, 0});
    fishBuckets.insert({1, 0});
    fishBuckets.insert({2, 0});
    fishBuckets.insert({3, 0});
    fishBuckets.insert({4, 0});
    fishBuckets.insert({5, 0});
    fishBuckets.insert({6, 0});
    fishBuckets.insert({7, 0});
    fishBuckets.insert({8, 0});


    std::for_each(fishVector.begin(), fishVector.end(), [&fishBuckets] (int fish) {
        fishBuckets.insert_or_assign(fish, fishBuckets.find(fish)->second + 1);
    });

    // simulate. 1 iteration = 1 day.
    for (size_t i = 1; i <= 256 + 1; i++)
    {
        long newBornFishes{fishBuckets.find(0)->second};
        long resetFishes{fishBuckets.find(0)->second};
        
        fishBuckets.insert_or_assign(0, fishBuckets.find(1)->second);
        fishBuckets.insert_or_assign(1, fishBuckets.find(2)->second);
        fishBuckets.insert_or_assign(2, fishBuckets.find(3)->second);
        fishBuckets.insert_or_assign(3, fishBuckets.find(4)->second);
        fishBuckets.insert_or_assign(4, fishBuckets.find(5)->second);
        fishBuckets.insert_or_assign(5, fishBuckets.find(6)->second);
        fishBuckets.insert_or_assign(6, (fishBuckets.find(7)->second + resetFishes));
        fishBuckets.insert_or_assign(7, fishBuckets.find(8)->second);
        fishBuckets.insert_or_assign(8, newBornFishes);
    }

    long answer{};
    for (size_t i = 0; i < 8; i++)
    {
        answer += fishBuckets.find(i)->second;
    }
    
    std::cout << "Puzzle two: " << answer << std::endl;
}

int main()
{
    std::vector<std::string> exampleInput{"3", "4" , "3", "1" ,"2"};
    AoCHelper a1{"2021", "6"};
    std::vector<std::string> result = a1.get_input();
    puzzle_one(result);
    puzzle_two(result);
}
