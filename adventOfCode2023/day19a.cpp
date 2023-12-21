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

bool checkIfLargerOrSmaller(int partStat, int workPart, char smallerOrLarger)
{
    std::cout << "checking smaller or larger: " << partStat << smallerOrLarger << workPart << std::endl;
    if (smallerOrLarger == '>') {
        return partStat > workPart;
    }
    else
        return partStat < workPart;
}

int solve(auto& workflow, auto& parts)
{
    std::vector<int> acceptedPartsSums;
    for (auto& p : parts) {
        auto wf = workflow.find("in");
        // check part stats
        // store parts as numbers only
        // vector 0 - 3: x, m, a, s
        auto statStrings = split(p, ',');
        std::vector<int> stats;
        for (auto& ss : statStrings)
            stats.push_back(std::stoi(split(ss, '=').at(1)));

        // break down instructions in workflow
        bool moreWorkForThisPart = true;
        while (moreWorkForThisPart) {
            auto work = split(wf->second, ',');
            for (auto& w : work) {
                if (w.find(":") != std::string::npos) {
                    // this is a check...
                    log("WORK: " + w);
                    auto conditionAndDestination = split(w, ':');
                    auto condition = conditionAndDestination.at(0);
                    auto destination = conditionAndDestination.at(1);
                    char smallerOrLarger = condition.find(">") != std::string::npos ? '>' : '<';
                    auto statAndValue = split(condition, smallerOrLarger);
                    auto stat = statAndValue.at(0);
                    int val = std::stoi(statAndValue.at(1));
                    int i = stat == "x" ? 0 : stat == "m" ? 1 : stat == "a" ? 2 : 3;

                    log("number to index vector: " + std::to_string(i));
                    log("size of vector: " + std::to_string(stats.size()));

                    if (checkIfLargerOrSmaller(stats.at(i), val, smallerOrLarger)) {
                        log("looking for destination: " + destination);
                        if (destination == "A") {
                            log("ACCEPTED");
                            acceptedPartsSums.push_back(std::accumulate(stats.begin(), stats.end(), 0));
                            moreWorkForThisPart = false;
                            break;
                        }
                        else if (destination == "R") {
                            log("REJECTED");
                            moreWorkForThisPart = false;
                            break;
                        }
                        else {
                            wf = workflow.find(destination);
                            break;
                        }
                    }
                }
                else {
                    // this is either a direct instructions to move to other workflow or A/R
                    if (w == "A") {
                        log("ACCEPTED");
                        acceptedPartsSums.push_back(std::accumulate(stats.begin(), stats.end(), 0));
                        moreWorkForThisPart = false;
                        break;
                    }
                    else if (w == "R") {
                        log("REJECTED");
                        moreWorkForThisPart = false;
                        break;
                    }
                    else {
                        wf = workflow.find(w);
                        break;
                    }
                }
            }
        }
    }

    return std::accumulate(acceptedPartsSums.begin(), acceptedPartsSums.end(), 0);
}

void readFile(const std::string &filename, auto &w, auto &p)
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

    // store parts
    while (std::getline(file, line))
        p.push_back(split(split(line, '{').at(1), '}').at(0));
    file.close();
}

int main()
{
    std::string filename = "input19.txt";
    std::map<std::string, std::string> workflow;
    std::vector<std::string> parts;
    readFile(filename, workflow, parts);
    log("SUM: " + std::to_string(solve(workflow, parts)));
    return 0;
}
