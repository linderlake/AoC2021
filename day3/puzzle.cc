#include "../AoCHelper/AoCHelper.h"
#include <string>
#include <vector>

int binary_to_decimal(std::string const binary, bool invert=false) 
{   

    int sum{0};
    int bin_counter{1};
    for (int i = binary.size() - 1; i >= 0; i--)
    {
       if(binary[i] == '1'  && !invert) {
           sum += bin_counter;
       } 
       else if (binary[i] == '0' && invert)
       {
           sum += bin_counter;
       }
       bin_counter = bin_counter * 2;
    }
    return sum;

}

void puzzle_one(std::vector<std::string> input)
{
    bool runonce = true;
    int totcounter = 0;
    std::vector<double> avgArray{};
    std::string sum{};
    for (std::string row : input)
    {
        if (runonce) {
            for(char& bit : row) {
                avgArray.push_back(0); // populate array with 0's
                runonce = false;
            }
        }
        int counter{0};

        for(char bit : row) {
            avgArray[counter] += bit - '0';
            counter++;
        }
        totcounter++;
    }

    for (auto i : avgArray)
    {
        auto avg = i / totcounter;
        if(avg < 0.5) { 
            // 0
            sum += "0";
        } else { 
            // 1
            sum += "1";
        }
    }
    int sum_ones = binary_to_decimal(sum); // gamma
    int sum_zeros = binary_to_decimal(sum, true); // epsilon

    int answer{sum_ones * sum_zeros};
    std::cout << "Puzzle one: " << answer << std::endl;
}

std::string determine_ratings(std::vector<std::string> input, bool co2_scrubber=false)
{
    std::vector<int> valid_positions{};

    for (size_t i = 0; i < input.size(); i++)
    {
        valid_positions.push_back(i);
    };
    std::string oxygen_generator_rating{};
    int bitcounter{0};
    for(char bit : input.at(0)) {
        int counter{0};
        int total{0};
        std::vector<int> one_positions{};
        std::vector<int> zero_positions{};

            for (int position : valid_positions)
            {  
                char currentbit = input[position][bitcounter];
                if(currentbit == '0') {
                    zero_positions.push_back(position);
                } else {
                    one_positions.push_back(position);
                }
                total += currentbit - '0';
                counter++;
            }
        bitcounter++;
        double most_common_bit = (double)total / (double)counter;

        valid_positions.clear();
        if(co2_scrubber) {
            if (most_common_bit < 0.5) {
                //next_bit = 1;
                std::copy(one_positions.begin(), one_positions.end(), std::back_inserter(valid_positions));
            } else {
                //next_bit = 0;
                std::copy(zero_positions.begin(), zero_positions.end(), std::back_inserter(valid_positions));
            }
        } else {
            if (most_common_bit >= 0.5) {
                //next_bit = 1;
                std::copy(one_positions.begin(), one_positions.end(), std::back_inserter(valid_positions));
            } else {
                //next_bit = 0;
                std::copy(zero_positions.begin(), zero_positions.end(), std::back_inserter(valid_positions));
            }
        }
        if(valid_positions.size() == 1) {
            return input[valid_positions[0]];
        }
    }
    return "";
}

void puzzle_two(std::vector<std::string> input)
{
    int oxygen_generator_rating = binary_to_decimal(determine_ratings(input));
    int co2_scrubber = binary_to_decimal(determine_ratings(input, true));
    size_t answer = binary_to_decimal(determine_ratings(input)) * binary_to_decimal(determine_ratings(input, true));
    std::cout << "Puzzle two: " << answer << std::endl;
}

int main()
{

    AoCHelper a1{"2021", "3"};
    std::vector<std::string> result = a1.get_input();
    puzzle_one(result);
    puzzle_two(result);
}
