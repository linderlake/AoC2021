#include "AoCHelper.h"

namespace {
    std::string get_token()
    {
        std::ifstream token_file("token.txt");
        std::string token;
        std::getline(token_file, token);
        return token;
    }
}

AoCHelper::AoCHelper(std::string year, std::string day) 
{
        token = get_token();
        current_year = year;
        current_day = day;
};

std::vector<std::string> AoCHelper::download_input() {
  try {
    curlpp::Cleanup cleaner;
    curlpp::Easy request;
    std::stringstream response;
    request.setOpt(new curlpp::options::Url("https://adventofcode.com/" + current_year +  "/day/" + current_day + "/input"));
    request.setOpt(curlpp::options::Cookie("session=" + token));
    request.setOpt( new curlpp::options::WriteStream( &response ) );
    //std::cout << request << std::endl;
    request.perform();
    std::vector<std::string> result{};     
    std::string line;
    while(getline(response, line))
    {
     result.push_back(line);
    }

    return result;
  }
  catch ( curlpp::LogicError & e ) {
    std::cout << e.what() << std::endl;
  }
  catch ( curlpp::RuntimeError & e ) {
    std::cout << e.what() << std::endl;
  }
}

bool AoCHelper::file_exists(const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}

std::vector<std::string> AoCHelper::get_input()
{
    std::string file_name{"./day" + current_day + "input.txt"};
    if (!file_exists(file_name)) {
        std::vector<std::string> result{download_input()};
        std::ofstream output_file(file_name);
        std::ostream_iterator<std::string> output_iterator(output_file, "\n");
        std::copy(result.begin(), result.end(), output_iterator);
        return result;
    } 
    else // read from file
    {
      std::ifstream input_text{file_name};
      std::vector<std::string> result{};
      std::string line;
      while(getline(input_text, line))
      {
       result.push_back(line);
      }
      return result;
    }
};