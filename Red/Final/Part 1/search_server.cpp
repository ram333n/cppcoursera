#include "search_server.h"
#include "iterator_range.h"
#include "parse.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>

vector<string> SplitIntoWords(const string& line) {
    istringstream words_input(line);
    return { istream_iterator<string>(words_input), istream_iterator<string>() };
}

SearchServer::SearchServer(istream& document_input) {
    UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
    InvertedIndex new_index;

    for (string current_document; getline(document_input, current_document); ) {
        new_index.Add(move(current_document));
    }

    index = move(new_index);
}

void SearchServer::AddQueriesStream(
    istream& query_input, ostream& search_results_output
) {

    vector<size_t> docid_count(index.GetDocumentCount(), 0);

    for (string current_query; getline(query_input, current_query);) {
        const auto words = SplitIntoWords(current_query);

        for (const auto& word : words) {
            for (const auto& docid : index.Lookup(word)) {
                docid_count[docid.first]+=docid.second;
            }
        }

        vector<pair<size_t, size_t>> search_results;

        for (size_t i = 0; i < docid_count.size(); ++i) {
            if (docid_count[i] > 0) {
                search_results.push_back({ i, docid_count[i] });
            }
        }

        size_t step = min<size_t>(5u, search_results.size());
        partial_sort(
            begin(search_results),
            begin(search_results) + step,
            end(search_results),
            [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
                int64_t lhs_docid = lhs.first;
                auto lhs_hit_count = lhs.second;
                int64_t rhs_docid = rhs.first;
                auto rhs_hit_count = rhs.second;
                return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
            }
        );

        search_results_output << current_query << ':';
        for (auto [docid, hitcount] : Head(search_results, 5)) {
            search_results_output << " {"
                << "docid: " << docid << ", "
                << "hitcount: " << hitcount << '}';
        }
        search_results_output << '\n';

        if (!query_input.eof()) {
            for (const auto& p : search_results) {
                docid_count[p.first] = 0;
            }
        }

    }
}

void InvertedIndex::Add(const string& document) {

    const size_t docid = document_count++;
    for (const auto& word : SplitIntoWords(document)) {
        auto& found_vector = index[word];

        auto found_record = find_if(begin(found_vector),
                                    end(found_vector),
                                    [docid](const pair<size_t, size_t>& p) {
                                        return p.first == docid;
                                    });
        if (found_record != end(found_vector)) {
            found_record->second++;
        }
        else {
            found_vector.push_back({ docid, 1 });
        }
    }
}

size_t InvertedIndex::GetDocumentCount() const {
    return document_count;
}

const vector<pair<size_t, size_t>>& InvertedIndex::Lookup(const string& word) const {
    if (auto it = index.find(word); it != index.end()) {
        return it->second;
    }
    else {
        return empty_vector;
    }
}
