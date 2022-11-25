#include "AoCHelper.h"
#include <vector>
#include <string>
#include <iostream>

int main()
{
  AoCHelper a1{"2021", "1"};
  std::vector<std::string> result = a1.get_input();
  std::copy(result.begin(), result.end(),
          std::ostream_iterator<std::string>{std::cout});
          
          
}