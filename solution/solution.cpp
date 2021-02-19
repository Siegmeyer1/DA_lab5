#include <iostream>
#include "SuffixTree.h"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string pattern, text;
    std::cin >> pattern >> text;
    pattern += '$';
    T_STree tree(pattern);
    pattern.pop_back();

    tree.MatchStatistics(text);
    return 0;
}

