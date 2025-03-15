#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error in finding path from " << word1 << " to " << word2 << ": " << msg << endl;
}

// bool edit_distance_within(const std::string& str1, const std::string& str2, int d);
// bool is_adjacent(const string& word1, const string& word2);

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (!word_list.contains(end_word)) {
        error(begin_word, end_word, end_word + " is not in the dictionary");
        return {};
    } else if (begin_word == end_word)
        return {begin_word};

    queue<stack<string, vector<string>>> ladder_queue;
    stack<string, vector<string>> start = {begin_word};
    ladder_queue.push(start);
    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        stack<string, vector<string>> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder[ladder.size() - 1];

        for (string word : word_list) {
            if (is_adjacent(last_word, word) && word not in visited) {
                visited.insert(word)
                stack<string, vector<string>> new_ladder = ladder;
                new_ladder.push(word)
                if (word == end_word)
                    return new_ladder
                ladder_queue.push(new_ladder)
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream in(file_name);
    for (string word; in >> word;)
        word_list.insert(word);
}

void print_word_ladder(const vector<string>& ladder) {
    for (string word : ladder)
        cout << word << " ";
    cout << endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}