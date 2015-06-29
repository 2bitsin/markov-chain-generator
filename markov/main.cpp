#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <regex>
#include <map>
#include <vector>
#include <set>
#include <random>

int main () {
    auto const ORDER = 2;

    std::string data;

    std::copy (std::istreambuf_iterator<char> (std::cin), 
        std::istreambuf_iterator<char> (), 
        std::back_inserter (data));

    static const auto tok_rex = std::regex (R"([\-\'a-zA-Z]+|\?|\!|\.{1,3}|\,|[\r\n]+|\(|\))", std::regex::optimize);
    std::sregex_token_iterator ti (data.begin (), data.end (), tok_rex);
    std::sregex_token_iterator te;
    

    auto cntx = std::vector<std::string> {};
    for (auto i = 0; i < ORDER; ++i) {
        cntx.emplace_back ("");
    }
    auto dict = std::map<
        std::vector<std::string>, 
        std::vector<std::string>> 
        ();
    auto allw = std::set<std::string> ();

    std::for_each (ti, te, [&cntx, &dict, &allw] (const auto& tok) {
        allw.emplace (tok);
        dict [cntx].emplace_back (tok);
        cntx.erase (cntx.begin (), cntx.begin () + 1u);
        cntx.emplace_back (tok);
    });

    std::random_device my_rand;

    
    
    cntx = std::vector<std::string> (allw.begin (), allw.end ());
    std::random_shuffle (std::begin (cntx), std::end (cntx));
    cntx.erase (std::begin (cntx) + ORDER, std::end (cntx));

    auto text = cntx;
    
    for (auto i = 0; i < 50; ++i) {
        auto tmp = dict [cntx];
        std::random_shuffle (std::begin (tmp), std::end (tmp));
        text.push_back (tmp [0]);
        cntx.erase (cntx.begin (), cntx.begin () + 1u);
        cntx.emplace_back (tmp [0]);
    }

    for (const auto& word: text) {
        std::cout << word;
    }

}