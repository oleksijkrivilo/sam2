#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string shorten(const string& str, int max_length, int left_offset_delta = 0, int suffix_length = 0, int ellipsis_length = 1, int right_offset = 1) {
    int left_offset = max_length - ellipsis_length - right_offset - left_offset_delta;
    right_offset += suffix_length + left_offset_delta;
    string ellipsis = (max_length == 3) ? "." : (max_length == 4 ? ".." : "...");

    if (left_offset < 1) left_offset = 1;
    int start_len = min((int)str.size(), left_offset);
    int end_len = min((int)str.size() - start_len, right_offset);
    return str.substr(0, start_len) + ellipsis + str.substr(str.size() - end_len);
}

int countOccurrences(const vector<string>& input, const string& value) {
    int count = 0;
    for (const auto& item : input) {
        if (item == value) ++count;
    }
    return count;
}

int getNextSuffix(vector<string>& keys, vector<int>& counts, const string& key) {
    for (size_t i = 0; i < keys.size(); ++i) {
        if (keys[i] == key) {
            return ++counts[i];
        }
    }
    keys.push_back(key);
    counts.push_back(1);
    return 1;
}

bool isDuplicate(const vector<string>& output, const string& value) {
    return find(output.begin(), output.end(), value) != output.end();
}

int main() {
    int max_length;
    cout << "Maximum length: ";
    cin >> max_length;
    cin.ignore(); // clear newline

    if (max_length < 3) {
        cerr << "Max length can't be smaller than 3" << endl;
        return 1;
    }

    cout << "Enter strings (empty line to finish):" << endl;
    vector<string> input;
    string line;
    while (getline(cin, line)) {
        if (line.empty()) break;
        input.push_back(line);
    }

    vector<string> suffix_keys;
    vector<int> suffix_counts;
    vector<string> output;

    for (const auto& line : input) {
        string prepared_line = line;
        string suffix = "";

        if (countOccurrences(input, line) > 1) {
            int count = getNextSuffix(suffix_keys, suffix_counts, line);
            suffix = to_string(count);
            prepared_line += suffix;
        }

        string output_line = prepared_line;
        if ((int)prepared_line.size() > max_length) {
            output_line = shorten(prepared_line, max_length, 0, suffix.length());
        }

        int left_offset_delta = 1;
        while (isDuplicate(output, output_line) && left_offset_delta < max_length) {
            output_line = shorten(prepared_line, max_length, left_offset_delta, suffix.length());
            left_offset_delta++;
        }

        output.push_back(output_line);
    }

    cout << "\nResult :" << endl;
    for (const auto& l : output) {
        cout << l << endl;
    }

    return 0;
}
