#pragma once

#include <vector>
#include <string>

namespace Utils {

    /**
     * @brief split the given string in different parts based on the given delimiter
     *
     * @param input
     * @param delimiter
     *
     * @return an array with the splitted parts of the given string, if the delimiter is not found
     *         worst case scenario returns [input]
     */
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
