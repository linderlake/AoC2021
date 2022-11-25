#include "../AoCHelper/AoCHelper.h"
#include <vector>

class bingobricka
{
public:
    bingobricka();
    void add_new_row(std::vector<int>);
    void new_bingo_number(int);
    bool is_winner();
    int get_sum_of_bingobricka();

private:
    std::vector<std::vector<std::pair<int, bool>>> bingonummer{};
};

bingobricka::bingobricka(){};

int bingobricka::get_sum_of_bingobricka()
{
    int sum_of_bingobricka{};
    for (auto row : bingonummer)
    {
        for (auto p : row)
        {
            if (!p.second)
            {
                sum_of_bingobricka += p.first;
            }
        }
    }
    return sum_of_bingobricka;
}

void bingobricka::add_new_row(std::vector<int> numbers)
{
    std::vector<std::pair<int, bool>> temp_vector{};
    std::transform(numbers.begin(), numbers.end(), back_inserter(temp_vector), [](int i) -> std::pair<int, bool> { return std::pair<int, bool>{i, false}; });
    bingonummer.push_back(temp_vector);
}

bool bingobricka::is_winner()
{

    // check horizontal direction
    for (auto row : bingonummer)
    {
        if (row[0].second &&
            row[1].second &&
            row[2].second &&
            row[3].second &&
            row[4].second)
        {
            return true;
        }
    }

    // check vertical direction
    for (size_t i = 0; i < bingonummer.size(); i++)
    {
        if (bingonummer[0][i].second &&
            bingonummer[1][i].second &&
            bingonummer[2][i].second &&
            bingonummer[3][i].second &&
            bingonummer[4][i].second)
        {
            return true;
        }
    }

    return false;
}

void bingobricka::new_bingo_number(int new_number)
{
    for (auto &row : bingonummer)
    {
        for (auto &p : row)
        {
            if (p.first == new_number)
            {
                p.second = true;
            }
        }
    }
}

void puzzle_one(std::vector<std::string> input)
{
    std::vector<int> bingolotto{};
    std::string bingolotto_numbers{input[0]};
    int answer{};
    bool runonce = true;

    // read bingo input
    while (bingolotto_numbers.find(",") != std::string::npos)
    {
        bingolotto.push_back(std::stoi(bingolotto_numbers.substr(0, bingolotto_numbers.find(","))));
        bingolotto_numbers.erase(0, bingolotto_numbers.find(",") + 1);
    }
    bingolotto.push_back(std::stoi(bingolotto_numbers.substr(0, 2)));

    std::vector<bingobricka> bingobrickor{};
    for (size_t i = 1; i < input.size(); i += 6)
    {
        // build bingobrädor
        bingobricka b1{};

        for (size_t j = i + 1; j <= i + 5; j++)
        {
            std::vector<int> temp_vector{};
            temp_vector.push_back(std::stoi(input[j].substr(0, 2)));
            temp_vector.push_back(std::stoi(input[j].substr(3, 2)));
            temp_vector.push_back(std::stoi(input[j].substr(6, 2)));
            temp_vector.push_back(std::stoi(input[j].substr(9, 2)));
            temp_vector.push_back(std::stoi(input[j].substr(12, 2)));
            b1.add_new_row(temp_vector);
        }
        bingobrickor.push_back(b1);
    }

    // spela bingolotto
    for (auto &&number : bingolotto)
    {
        for (auto &&bricka : bingobrickor)
        {
            bricka.new_bingo_number(number);

            if (bricka.is_winner())
            {
                // sum all unmarked numbers of winning bingobräda
                answer = bricka.get_sum_of_bingobricka() * number;
                std::cout << "Puzzle one: " << answer << std::endl;
                return;
            }
        }
    }
    
}


void puzzle_two(std::vector<std::string> input)
{
    std::vector<int> bingolotto{};
    std::string bingolotto_numbers{input[0]};
    int answer{};
    bool runonce = true;

    // read bingo input
    while (bingolotto_numbers.find(",") != std::string::npos)
    {
        bingolotto.push_back(std::stoi(bingolotto_numbers.substr(0, bingolotto_numbers.find(","))));
        bingolotto_numbers.erase(0, bingolotto_numbers.find(",") + 1);
    }
    bingolotto.push_back(std::stoi(bingolotto_numbers.substr(0, 2)));

    std::vector<std::pair<bingobricka, bool>> bingobrickor{};
    for (size_t i = 1; i < input.size(); i += 6)
    {
        // build bingobrädor
        bingobricka b1{};

        for (size_t j = i + 1; j <= i + 5; j++)
        {
            std::vector<int> temp_vector{};
            temp_vector.push_back(std::stoi(input[j].substr(0, 2)));
            temp_vector.push_back(std::stoi(input[j].substr(3, 2)));
            temp_vector.push_back(std::stoi(input[j].substr(6, 2)));
            temp_vector.push_back(std::stoi(input[j].substr(9, 2)));
            temp_vector.push_back(std::stoi(input[j].substr(12, 2)));
            b1.add_new_row(temp_vector);
        }
        bingobrickor.push_back({b1, false});
    }
    int bingo_winners{0};
    // spela bingolotto
    for (auto &&number : bingolotto)
    {
        for (auto &&bricka : bingobrickor)
        {
            if (!bricka.second) { // stop playing when won
                bricka.first.new_bingo_number(number);
                if (bricka.first.is_winner())
                {
                    // find if this bricka was the last winner
                    if (bingo_winners == bingobrickor.size() - 1) {
                        answer = bricka.first.get_sum_of_bingobricka() * number;
                         std::cout << "Puzzle two: " << answer << std::endl;
                         return;
                    }
                        bricka.second = true;
                        bingo_winners++;
                }
            }


            
        }
        
    }
   
    
}

int main()
{
    AoCHelper a1{"2021", "4"};
    std::cout << "Välkomna till Bingolottostudion i GÖTEBORG!" << std::endl;
    std::vector<std::string> result = a1.get_input();
    puzzle_one(result);
    puzzle_two(result);
}
