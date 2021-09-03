#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <deque>
using namespace std;

class InvertedIndex {
public:
    void Add(const string& document);
    size_t GetDocumentCount() const;
    const vector<pair<size_t, size_t>>& Lookup(const string& word) const;

private:
    map<string, vector<pair<size_t,size_t>>> index;
    size_t document_count = 0;
    vector<pair<size_t, size_t>> empty_vector;
};

class SearchServer {
public:
    SearchServer() = default;
    explicit SearchServer(istream& document_input);
    void UpdateDocumentBase(istream& document_input);
    void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
    InvertedIndex index;
    const static size_t DOCUMENT_COUNT = 50'000;
};
