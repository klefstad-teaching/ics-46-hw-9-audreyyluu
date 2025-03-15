#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error in finding path from " << word1 << " to " << word2 << ": " << msg << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    size_t len1 = str1.length();
    size_t len2 = str2.length();
    int diff = 0;

    if (len1 == len2) {
        for (int i=0; i<len1 && diff<=1; ++i) {
            if (tolower(str1[i]) != tolower(str2[i]))
                ++diff;
        }
    } else if (len1 - len2 == 1) {
        int i = 0, j = 0;
        while (j<len2 && diff<=1) {
            if (tolower(str1[i]) != tolower(str2[j]))
                ++diff;
            else
                ++j;
            ++i;
        }
    } else if (len2 - len1 == 1) {
        int i = 0, j = 0;
        while (i<len1 && diff<=1) {
            if (tolower(str1[i]) != tolower(str2[j]))
                ++diff;
            else
                ++i;
            ++j;
        }
    } else return false;

    return diff <= 1;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (!word_list.contains(end_word)) {
        error(begin_word, end_word, end_word + " is not in the dictionary");
        return {};
    } else if (begin_word == end_word) {
        error(begin_word, end_word, " begin and end words are the same");
        return {};
    }

    queue<vector<string>> ladder_queue;
    vector<string> start = {begin_word};
    ladder_queue.push(start);
    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder[ladder.size() - 1];

        for (string word : word_list) {
            if (!visited.contains(word) && is_adjacent(last_word, word)) {
                visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                if (word == end_word)
                    return new_ladder;
                ladder_queue.push(new_ladder);
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
    load_words(word_list, "src/words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}