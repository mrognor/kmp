#include <string>
#include <iostream>
#include <vector>

std::vector<std::size_t> prefix_func(const std::string& str)
{
    if (str.empty()) return std::vector<std::size_t>();

    std::size_t len = str.length();
    std::vector<std::size_t> res(len);
    res[0] = 0;
    std::size_t k = 0;

    for (std::size_t i = 1; i < len; ++i)
    {
        while (k > 0 && str[i] != str[k]) --k;
        
        if (str[i] == str[k]) ++k;
        res[i] = k;
    }

    return res;
}

std::size_t find_first(const std::string& find_in, const std::string& str_to_find)
{
    if (find_in.empty()) return std::string::npos;

    std::size_t res = std::string::npos;
    std::size_t find_len = str_to_find.length();
    std::vector<std::size_t> prefix_vec = prefix_func(str_to_find);

    std::size_t k = 0;
    for (std::size_t i = 0; i < find_in.length(); ++i)
    {
        if (find_in[i] == str_to_find[k])
        {
            ++k;
            if (k == find_len)
            {
                res = i - (find_len - 1);
                break;
            }
        }
        else 
        {
            k = prefix_vec[k];
        }
    }

    return res;
}

std::vector<std::size_t> find_all(const std::string& find_in, const std::string& str_to_find)
{
    if (find_in.empty()) return std::vector<std::size_t>();

    std::vector<std::size_t> res;
    std::size_t find_len = str_to_find.length();
    std::vector<std::size_t> prefix_vec = prefix_func(str_to_find);

    std::size_t k = 0;
    for (std::size_t i = 0; i < find_in.length(); ++i)
    {
        if (find_in[i] == str_to_find[k])
        {
            ++k;
            if (k == find_len)
            {
                res.emplace_back(i - (find_len - 1));
                k = 0;
            }
        }
        else 
        {
            k = prefix_vec[k];
        }
    }

    return res;
}

void print_prefix(const std::string& str)
{
    std::vector<std::size_t> res = prefix_func(str);
    std::cout << "[";
    for (std::size_t i = 0; i < str.length() - 1; ++i)
        std::cout << res[i] << ", ";
    std::cout << res.back() << "]" << std::endl;
}

void print_founded_all(const std::string& find_in, const std::string& str_to_find)
{
    std::vector<std::size_t> res = find_all(find_in, str_to_find);
    std::cout << "[";
    for (std::size_t i = 0; i < res.size() - 1; ++i)
        std::cout << res[i] << ", ";
    std::cout << res.back() << "]" << std::endl;
}

int main()
{
    print_prefix("abcdabcabcdabcdab");

    std::cout << find_first("abcdabcabcdabcdabgde", "abgde") << std::endl;

    print_founded_all("abcdabcabcdabcdab", "ab");
}
