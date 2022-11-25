#include "../AoCHelper/AoCHelper.h"
#include <vector>
#include <deque>
#include <set>

/* header */
class cave
{
private:
    bool visited;
    std::string name;
    std::vector<cave *> cave_connections{};

public:
    cave(std::string _name);
    virtual bool is_visited() const;
    void visit();
    std::string get_name() const;
    void connect_cave(cave *);
    std::vector<cave *> get_cave_connections();
    bool operator<(const cave &c) const; // needed for set
};

class big_cave : public cave
{
private:
    int visit_counter;

public:
    big_cave(std::string _name);
    bool is_visited() const;
};

/* implementation */
cave::cave(std::string _name) : name(_name)
{
    visited = false;
}

bool cave::operator<(const cave &c) const
{
    return get_name() < c.get_name(); 
}

std::string cave::get_name() const { return name; }

void cave::visit() { visited = true; }

std::vector<cave *> cave::get_cave_connections() { return cave_connections; };

bool cave::is_visited() const { return visited; }

void cave::connect_cave(cave *new_cave) { cave_connections.push_back(new_cave); };

big_cave::big_cave(std::string _name) : cave(_name)
{
    visit_counter = 0;
}

bool big_cave::is_visited() const { return false; }



/* main program */
void puzzle_one(std::vector<std::string> input)
{
    
    cave* start_cave{};
    std::vector<cave*> caves{};
    std::deque<cave*> q{};
    std::vector<std::vector<std::string>> valid_paths{};

    for (std::string row : input)
    {
        std::string first_str{row.substr(0, row.find('-'))};
        std::string second_str{row.substr(row.find('-') + 1)};
        cave* c1 = new cave(first_str);
        cave* c2 = new cave(second_str);

        if (std::isupper(first_str[0]) != 0)
        {
            // big cave
            big_cave c1{first_str};
        }
        if (std::isupper(second_str[0]) != 0)
        {
            // big cave
            big_cave c2{second_str};
        }
        auto it1 = std::find_if(caves.begin(), caves.end(), [&c1] (cave* c) -> bool { return (c->get_name() == c1->get_name()); });
        if (it1 == caves.end())
        {
            caves.push_back(&*c1);
        }
        else
        {
            c1 = *it1;
        }
        auto it2 = std::find_if(caves.begin(), caves.end(), [&c2] (cave* c) -> bool { return (c->get_name() == c2->get_name()); });
        if (it2 == caves.end())
        {
            caves.push_back(&*c2);
        }
        else
        {
            c2 = *it2;
        }

        c1->connect_cave(&*c2);
        c2->connect_cave(&*c1);

        if (c1->get_name() == "start")
        {
            start_cave = c1;
        }
    }
    // bfs
    while (true)
    {
        q.push_back(start_cave);
        std::vector<std::string> visited_caves{};
        while (!q.empty() || q.front()->get_name() != "end")
        {
            visited_caves.push_back(q.front()->get_name());
            q.front()->visit();
            for (auto &&i : q.front()->get_cave_connections())
            {
                if (!i->is_visited()) {
                    q.push_back(i);
                    i->visit();
                }
            }
            q.pop_front();
        }

        if (!q.empty())
        {
            valid_paths.push_back(visited_caves);
        }

        q.clear();
    }

    size_t answer{};
    std::cout << "Puzzle one: " << answer << std::endl;
}

void puzzle_two(std::vector<std::string> input)
{

    for (std::string row : input)
    {
    }
    size_t answer{};
    std::cout << "Puzzle two: " << answer << std::endl;
}

int main()
{
    std::vector<std::string> exampleInput{"start-A",
                                          "start-b",
                                          "A-c",
                                          "A-b",
                                          "b-d",
                                          "A-end",
                                          "b-end"};
    AoCHelper a1{"2021", "12"};
    std::vector<std::string> result = a1.get_input();
    puzzle_one(exampleInput);
    puzzle_two(result);
}
