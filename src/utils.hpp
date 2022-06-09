#pragma once

#include <vector>
#include <string>

namespace Utils {

    std::vector<std::string> split(const std::string& input, const std::string& delimiter)
    {
        std::vector<std::string> result;

        std::string s = input;
        size_t pos = 0;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            result.push_back(s.substr(0, pos));
            s = s.erase(0, pos + 1);
        }

        result.push_back(s);
        return result;
    }

}
