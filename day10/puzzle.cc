#include "../AoCHelper/AoCHelper.h"
#include <vector>
#include <set>

std::map<char, size_t> score{
    {')', 3},
    {']', 57},
    {'}', 1197},
    {'>', 25137}};

std::map<char, long> score_puzzletwo{
    {'(', 1},
    {'[', 2},
    {'{', 3},
    {'<', 4}};

size_t calc_corrupted_lines(std::string row)
{
    std::vector<std::pair<char, char>> valid_chunks = {{'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'}};
    std::set<char> chunk_starts{'(', '[', '{', '<'};
    std::set<char> chunk_ends{')', ']', '}', '>'};
    std::stack<char> chunks{};
    for (char character : row)

        if (chunk_starts.find(character) != chunk_starts.end())
        {
            chunks.push(character);
        }
        else
        {
            for (size_t i = 0; i < valid_chunks.size(); i++)
            {
                if (character == valid_chunks[i].second)
                {
                    // we've found the end chunk
                    // is the top of the stack matching start chunk?
                    if (chunks.top() == valid_chunks[i].first)
                    {
                        // correct
                        chunks.pop();
                    }
                    else
                    {
                        return score.find(character)->second;
                        // go to next line
                    }
                }
            }
        }
    return 0;
}

void puzzle_one(std::vector<std::string> input)
{

    size_t answer{};

    for (std::string row : input)
    {
        answer += calc_corrupted_lines(row);
    }

    std::cout << "Puzzle one: " << answer << std::endl;
}

void puzzle_two(std::vector<std::string> input)
{
    std::vector<std::string> cleaned_input{input};
    std::vector<std::pair<char, char>> valid_chunks = {{'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'}};
    std::set<char> chunk_starts{'(', '[', '{', '<'};
    std::set<char> chunk_ends{')', ']', '}', '>'};

    for (std::string row : input)
    {
        std::stack<char> chunks{};
        bool corrupt = false;
        for (char character : row)

            if (chunk_starts.find(character) != chunk_starts.end())
            {
                chunks.push(character);
            }
            else
            {
                for (size_t i = 0; i < valid_chunks.size(); i++)
                {
                    if (character == valid_chunks[i].second)
                    {
                        // we've found the end chunk
                        // is the top of the stack matching start chunk?
                        if (chunks.top() == valid_chunks[i].first)
                        {
                            // correct
                            chunks.pop();
                        }
                        else
                        {
                            // corrupt
                            corrupt = true;
                        }
                    }
                }
            }
        if (corrupt)
        {
            cleaned_input.erase(std::remove(cleaned_input.begin(), cleaned_input.end(), row));
        }
    }

    std::vector<long> score_vector{};
    for (std::string row : cleaned_input)
    {
        long score{0};
        std::stack<char> chunks{};
        for (size_t i = 0; i < row.length(); i++)
        {
            char character = row[i];
            if (chunk_starts.find(character) != chunk_starts.end())
            {
                chunks.push(character);
            }
            else
            {
                for (size_t j = 0; j < valid_chunks.size(); j++)
                {
                    if (chunks.top() == valid_chunks[j].first)
                    {
                        chunks.pop();
                        break;
                    }
                }
            }
            if (i == row.length() - 1 && !chunks.empty())
            {
                while (!chunks.empty())
                {
                   
                    score *= 5;
                    score += score_puzzletwo.find(chunks.top())->second;
                    chunks.pop();
                }
            }
        }
        score_vector.push_back(score);
    }
    std::sort(score_vector.begin(), score_vector.end());
    int median = score_vector.size() / 2;
    long answer{score_vector[median]};
    std::cout << "Puzzle two: " << answer << std::endl;
}

int main()
{
    std::vector<std::string> exampleInput{"[({(<(())[]>[[{[]{<()<>>", "[(()[<>])]({[<{<<[]>>(", "{([(<{}[<>[]}>{[]{[(<()>", "(((({<>}<{<{<>}{[]{[]{}", "[[<[([]))<([[{}[[()]]]", "[{[{({}]{}}([{[{{{}}([]", "{<[[]]>}<{[{[{[]{()[[[]", "[<(<(<(<{}))><([]([]()", "<{([([[(<>()){}]>(<<{{", "<{([{{}}[<[[[<>{}]]]>[]]"};
    std::vector<std::string> exampleInput2{"{([(<{}[<>[]}>{[]{[(<()>"};
    std::vector<std::string> exampleInput3{"<{([{{}}[<[[[<>{}]]]>[]]"};
    AoCHelper a1{"2021", "10"};
    std::vector<std::string> result = a1.get_input();
    puzzle_one(result);
    puzzle_two(result);
}
