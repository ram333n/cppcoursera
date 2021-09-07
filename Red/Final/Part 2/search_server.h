#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <deque>
#include <mutex>
#include <future>
using namespace std;

class InvertedIndex {
public:
    void Add(const string& document);
    size_t GetDocumentCount() const;
    const vector<pair<size_t, size_t>>& Lookup(string_view word) const;

private:
    string_view GetClonedView(string_view s);

    map<string_view, vector<pair<size_t,size_t>>> index;
    size_t document_count = 0;
    vector<pair<size_t, size_t>> empty_vector;
    deque<string> storage;
   // mutex m;
};

class SearchServer {
public:
    SearchServer() = default;
    explicit SearchServer(istream& document_input);
    void UpdateDocumentBaseSingleThread(istream& document_input);
    void UpdateDocumentBase(istream& document_input);
    void AddQueriesStreamSingleThread(istream& query_input, ostream& search_results_output);
    void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
    InvertedIndex index;
    vector<future<void>> futures;
    mutex m;
};
