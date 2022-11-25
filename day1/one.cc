#include "../AoCHelper/AoCHelper.h"
#include <vector>

void step_one(std::vector<std::string> input) 
{   
    int counter{0};
    int previous{0};
    for (std::string row : input)
    {
        if (std::stoi(row) > previous) 
        {
            counter++;
        }
        previous = std::stoi(row);
    }
    counter--; // skipping first read
    std::cout << "Puzzle one: " << counter << std::endl; 
    
}

void step_two(std::vector<std::string> input) 
{   
    int counter{-1}; // skipping first read
    int previous{0};
    for (size_t i = 0; i+2 < input.size(); i++)
    {
        
        int value_one{std::stoi(input[i])};
        int value_two{std::stoi(input[i+1])};
        int value_three{std::stoi(input[i+2])};
        int sum = value_one + value_two + value_three;
        if (sum > previous) 
        {
            counter++;
        }
        previous = sum;
        
    }
    
    std::cout << "Puzzle two: " << counter << std::endl; 
    
}

int main() {
    AoCHelper a1{"2021", "1"};
    std::vector<std::string> result = a1.get_input();
    step_one(result);
    step_two(result);
}
