#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <iterator>
#include <array>
#include <random>
#include <numeric>

static auto const ORDER = 2;
static auto const LENGTH = 2500;


int main () {
    auto model = std::map<std::string, std::map<std::string, std::size_t>> ();
    auto text = std::string ();
    std::copy (std::istreambuf_iterator<char> (std::cin),
        std::istreambuf_iterator<char> (), 
        std::back_inserter (text));
    for (auto i = 0u; i < text.size (); ++i) {
        auto key = text.substr (i, ORDER);
        model.emplace (key, std::map<std::string, std::size_t> ());
    }
    for (auto i = 0u; i < text.size () - ORDER; ++i) {
        auto key0 = text.substr (i, ORDER);
        auto key1 = text.substr (i+ORDER, ORDER);
        ++model [key0] [key1];
    }
    
    auto temp = std::vector<std::string> ();
    for (const auto& i: model) {
        temp.emplace_back (i.first);
    }
    std::random_shuffle (std::begin (temp), std::end (temp));

    auto old_word = temp [0];
    text = temp [0];

    std::random_device rd;
    std::mt19937 gen (rd ());

    static const auto pick_word = [&] (const auto& table) {
        if (table.empty ())
            throw std::runtime_error ("empty table");
        auto dist = std::vector<std::uint32_t> ();
        auto list = std::vector<std::string> ();
        for (const auto& i : table) {
            dist.push_back (unsigned (i.second));
            list.push_back (i.first);
        }
        auto dstr = std::discrete_distribution<std::uint32_t> (dist.begin (), dist.end ());        
        return list [dstr (gen)];
    };

    for (auto i = 0u; i < (LENGTH/ORDER); ++i) try {
        auto new_word = pick_word (model.at (old_word));
        old_word = new_word;
        text.append (new_word);
    }
    catch (const std::exception&) {
        auto temp = std::vector<std::string> ();
        for (const auto& i: model) 
            temp.emplace_back (i.first);        
        std::random_shuffle (std::begin (temp), std::end (temp));
        old_word = temp [0];
    }

    std::cout << text;
    return 0;
}