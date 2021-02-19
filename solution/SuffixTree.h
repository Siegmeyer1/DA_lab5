#ifndef DA_LAB5_SUFFIXTREE_H
#define DA_LAB5_SUFFIXTREE_H

#include <iostream>
#include <string>
#include <map>

typedef std::string::iterator t_index;

class TNode {
public:
    t_index begin, end;
    std::map<char, TNode*> children;
    TNode* sLink;
    TNode(t_index begin, t_index end): begin(begin), end(end), sLink(nullptr) {};
    ~TNode() {};
};

class T_STree {
public:
    T_STree(std::string str);
    void MatchStatistics(std::string& _text);
    ~T_STree();

private:
    std::string text;
    TNode *root, *forSLink, *current;
    size_t length, remainder;
    t_index edge;
    void Extend(t_index symbIter);
    void AddSLink(TNode* node);
    bool JumpDown(t_index pos, TNode* node);
    void Destroy(TNode* node);
};


#endif //DA_LAB5_SUFFIXTREE_H
