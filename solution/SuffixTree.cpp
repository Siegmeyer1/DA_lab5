#include "SuffixTree.h"

T_STree::T_STree(std::string str) {
    text = std::move(str);
    remainder = 0;
    length = 0;
    root = new TNode(text.end(), text.end());
    current = root->sLink = forSLink = root;
    for (t_index i = text.begin(); i != text.end(); ++i) {
        Extend(i);
    }
}

void T_STree::Extend(t_index symbIter) {
    remainder++;
    forSLink = root;
    while (remainder) {
        if (!length) edge = symbIter;
        auto it = current->children.find(*edge);
        TNode* next = (it == current->children.end()) ? nullptr : it->second;
        if (!next) {
            auto* leaf = new TNode(symbIter, text.end());
            current->children[*edge] = leaf;
            AddSLink(current);
        } else {
            if (JumpDown(symbIter, next)) {
                continue;
            }
            if (*(next->begin + length) == *symbIter) {
                length++;
                AddSLink(current);
                break;
            }
            auto *leaf = new TNode(symbIter, text.end());
            auto *split = new TNode(next->begin, next->begin + length);
            current->children[*edge] = split;
            split->children[*symbIter] = leaf;
            next->begin += length;
            split->children[*next->begin] = next;
            AddSLink(split);
        }
        remainder--;
        if (current == root && length) {
            length--;
            edge = symbIter - remainder + 1;
        } else current = current->sLink ? current->sLink : root;
    }
}

void T_STree::AddSLink(TNode *node) {
    if (forSLink != root) forSLink->sLink = node;
    forSLink = node;
}

bool T_STree::JumpDown(t_index pos, TNode *node) {
    int newEdgeLen = min(node->end, pos + 1) - node->begin;
    if (length >= newEdgeLen) {
        edge += newEdgeLen;
        length -= newEdgeLen;
        current = node;
        return true;
    }
    return false;
}

void T_STree::Destroy(TNode *node) {
    for (auto & i : node->children) Destroy(i.second);
    delete node;
}

T_STree::~T_STree() {
    Destroy(root);
}

void T_STree::MatchStatistics(std::string& _text) {
    size_t res = 0;
    length = 0;
    current = root;
    size_t i = 0;
    t_index iter = _text.begin();
    while (i <= _text.size()) {
        if (!length) edge = iter;
        auto it = current->children.find(*edge);
        TNode* next = (it == current->children.end()) ? nullptr : it->second;
        if (next) {
            size_t edge_len = next->end - next->begin;
            if (length >= edge_len) {
                length -= edge_len;
                edge += edge_len;
                current = next;
                continue;
            }
            bool flag = true;
            for (t_index edge_it = next->begin + length; edge_it != next->end && flag; edge_it++) {
                if (*edge_it != *iter) {
                    flag = false;
                    if (res == text.size()-1) std::cout << i+1 << '\n';
                    if (res) res--;
                    i++;
                    if (current == root) {
                        if (length) length--;
                        else iter++;
                        edge++;
                    } else current = current->sLink ? current->sLink : root;
                    continue;
                } else {
                    iter++;
                    res++;
                    length++;
                }
            }
        } else {
            if (res == text.size()-1) std::cout << i+1 << '\n';
            if (res) res--;
            i++;
            if (current == root) {
                if (length) length--;
                else iter++;
                edge++;
            } else current = current->sLink ? current->sLink : root;
        }
    }
}