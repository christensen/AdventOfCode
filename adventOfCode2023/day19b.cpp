#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <ranges>
#include <map>
#include <utility>
#include <numeric>

void log(const std::string &o)
{
    std::cout << o << std::endl;
}

auto to_string = [](auto &&r) -> std::string
{
    const auto data = &*r.begin();
    const auto size = static_cast<std::size_t>(std::ranges::distance(r));

    return std::string{data, size};
};

auto split(const std::string &str, char delimiter) -> std::vector<std::string>
{
    const auto range = str | std::ranges::views::split(delimiter) |
                       std::ranges::views::transform(to_string);
    return {std::ranges::begin(range), std::ranges::end(range)};
}

unsigned long long solve(auto& workflow)
{
    unsigned long long derp = 1;
    for (auto wf : workflow) {
        auto work = split(wf.second, ',');
        unsigned long long herp = 1;
        for (auto w : work) {
            if (w.find(":") == std::string::npos) {
                break;
            }
            auto conditionAndDestination = split(w, ':');
            auto condition = conditionAndDestination.at(0);
            char smallerOrLarger = condition.find(">") != std::string::npos ? '>' : '<';
            auto statAndValue = split(condition, smallerOrLarger);
            int val = std::stoi(statAndValue.at(1));

            std::cout << condition << std::endl;

            int possibleValues = 0;
            if (smallerOrLarger == '>') {
                possibleValues = 4000 - val - 1;
            }
            else
                possibleValues = val - 1;

            std::cout << "possible values: " << possibleValues << std::endl;

            herp *= possibleValues;
        }
        derp *= herp;
    }

    return derp;
}

void readFile(const std::string &filename, auto &w)
{
    std::ifstream file(filename);
    if (!file.is_open())
        std::cerr << "Error opening file: " << filename << std::endl;

    // store workflows
    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty())
            break;
        auto labelAndWorkflow = split(line, '{');
        auto label = labelAndWorkflow.at(0);
        auto workflow = split(labelAndWorkflow.at(1), '}').at(0);
        log(workflow);
        w[label] = workflow;
    }

    file.close();
}

int main()
{
    std::string filename = "input19.txt";
    std::map<std::string, std::string> workflow;
    readFile(filename, workflow);
    log("SUM: " + std::to_string(solve(workflow)));
    return 0;
}
