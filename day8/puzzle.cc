#include "../AoCHelper/AoCHelper.h"
#include <vector>

void puzzle_one(std::vector<std::string> input)
{
    std::vector<std::string> signals{};
        for (std::string row : input)
            {
                row.erase(0, row.find("|") + 2);
                while (row.find(" ") != std::string::npos)
                {
                    signals.push_back(row.substr(0, row.find(" ")));
                    row.erase(0, row.find(" ") + 1);
                }
                signals.push_back(row);
            }
        
    
    size_t answer{};
    for (std::string signal : signals)
    {
        if (signal.length() == 2 || signal.length() == 3 || signal.length() == 4 || signal.length() == 7)
        {
            answer++;
        }

    }
    
    std::cout << "Puzzle one: " << answer << std::endl;
}

std::string operator-(std::string& string_one, std::string& string_two) 
{
    std::string return_string{string_one};
    for (char c1 : string_one)
    {
        for (char c2 : string_two)
        {
            if (c1 == c2 && return_string.find(c1) != std::string::npos)
            {
                return_string.erase(return_string.find(c1), 1);
            }
        }
    }
    
    return return_string;
}



void puzzle_two(std::vector<std::string> input)
{
    size_t answer{};
    std::vector<std::pair <std::vector<std::string>, std::vector<std::string>> > signal_db{};
    for (std::string row : input)
            {
                std::vector<std::string> signal_input{};
                std::vector<std::string> signal_output{};
                std::string input_string = row.substr(0, row.find("|") - 1);
                std::string output_string = row.substr(row.find("|") + 2);
                
                while (input_string.find(" ") != std::string::npos)
                {
                    signal_input.push_back(input_string.substr(0, input_string.find(" ")));
                    input_string.erase(0, input_string.find(" ") + 1);
                }
                signal_input.push_back(input_string.substr(0, input_string.find(" ")));

                while (output_string.find(" ") != std::string::npos)
                {
                    signal_output.push_back(output_string.substr(0, output_string.find(" ")));
                    output_string.erase(0, output_string.find(" ") + 1);
                }
                signal_output.push_back(output_string.substr(0, output_string.find(" ")));
                

                signal_db.push_back({signal_input, signal_output});
            }

    for (std::pair signal_pair : signal_db)
    {
        std::vector<std::string> decoded_digit_strings(10);            
        for (std::string digit_string : signal_pair.first)
        {
            // find all "easy" digits first
            switch (digit_string.length())
            {
                case 2:
                    decoded_digit_strings[1] = digit_string;
                    break;
                case 3:
                    decoded_digit_strings[7] = digit_string;
                    break;
                case 4:
                    decoded_digit_strings[4] = digit_string;
                    break;
                case 7:
                    decoded_digit_strings[8] = digit_string;
                    break;
                default:
                    break;
            }
        }
        std::string roof_digit{decoded_digit_strings[7] - decoded_digit_strings[1]}; // roof
        std::string help_digit_1{decoded_digit_strings[4] - decoded_digit_strings[1]};
        std::string help_digit_2{decoded_digit_strings[4] + roof_digit};
        
         
        for (std::string digit_string : signal_pair.first)
        {
            // decode the nine
            if (std::count(decoded_digit_strings.begin(), decoded_digit_strings.end(), digit_string) == 0)
            {   
                if (digit_string.length() == 6 && (digit_string - help_digit_2).length() == 1) {
                    decoded_digit_strings[9] = digit_string;
                    break;
                }
            }
        }

        std::string floor_digit{decoded_digit_strings[9] - help_digit_2};

        std::string floor_left_digit{decoded_digit_strings[8] - decoded_digit_strings[9]};
        

        for (std::string digit_string : signal_pair.first)
        {
            // decode the six
            if (std::count(decoded_digit_strings.begin(), decoded_digit_strings.end(), digit_string) == 0)
            {   
                if (digit_string.length() == 6) // either 0 or 6
                {
                    std::string temp_helper{roof_digit + floor_left_digit + floor_digit};
                    temp_helper = digit_string - temp_helper;
                    if ((temp_helper - decoded_digit_strings[1]).length() == 2) {
                        
                        decoded_digit_strings[6] = digit_string;
                        break;
                    }
                }
            }
        }
        std::string roof_right_digit{decoded_digit_strings[1] - decoded_digit_strings[6]};
        for (std::string digit_string : signal_pair.first)
        {
            // decode the zero
            if (std::count(decoded_digit_strings.begin(), decoded_digit_strings.end(), digit_string) == 0)
            {   
                if (digit_string.length() == 6) // 0
                {
                    decoded_digit_strings[0] = digit_string;
                }
                }
        }
        std::string middle_digit = decoded_digit_strings[8] - decoded_digit_strings[0];
        std::string floor_right_digit{decoded_digit_strings[1] - roof_right_digit};
        std::string helper_digit_3{roof_digit + roof_right_digit + middle_digit + floor_right_digit + floor_digit + floor_left_digit};
        std::string roof_left_digit{decoded_digit_strings[8] - helper_digit_3};
        
        decoded_digit_strings[2] = roof_digit + roof_right_digit + middle_digit + floor_left_digit + floor_digit;
        decoded_digit_strings[3] = roof_digit + roof_right_digit + middle_digit + floor_right_digit + floor_digit;
        decoded_digit_strings[5] = roof_digit + roof_left_digit + middle_digit + floor_right_digit + floor_digit;
        std::string output_digits{};
        // decode output
        for (std::string output_string : signal_pair.second)
        {
            std::sort(output_string.begin(), output_string.end());
            for (int i = 0; i < decoded_digit_strings.size(); i++)
            {
                std::sort(decoded_digit_strings[i].begin(), decoded_digit_strings[i].end());
                if (output_string == decoded_digit_strings[i]) {
                    output_digits += std::to_string(i);
                }
            }
        }
        answer += std::stoi(output_digits);
    }

    std::cout << "Puzzle two: " << answer << std::endl;
}

int main()
{
    std::vector<std::string> exampleInput{"acedgfb cdfbe gcdfa fbcad dab cefabd cdfgeb eafb cagedb ab | cdfeb fcadb cdfeb cdbaf"};
    AoCHelper a1{"2021", "8"};
    std::vector<std::string> result = a1.get_input();
    puzzle_one(result);
    puzzle_two(result);
}
