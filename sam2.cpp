#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Функція для скорочення рядка
string shorten(string s, int max_len) {
    if (s.length() <= max_len)
        return s;

    if (max_len <= 3)
        return s.substr(0, max_len);

    int middle = max_len - 3;
    int left = middle / 2;
    int right = middle - left;

    return s.substr(0, left) + "..." + s.substr(s.length() - right);
}

// Перевірка наявності рядка в списку
bool exists(const vector<string>& list, const string& value) {
    for (const auto& item : list) {
        if (item == value) return true;
    }
    return false;
}

int main() {
    int n, max_len;
    cout << "How many strings? ";
    cin >> n;
    cin.ignore(); // очищення після cin

    vector<string> input(n);
    cout << "Enter strings:\n";
    for (int i = 0; i < n; ++i)
        getline(cin, input[i]);

    cout << "Maximum lenght: ";
    cin >> max_len;

    vector<string> output;

    for (int i = 0; i < n; ++i) {
        string base = shorten(input[i], max_len);
        string unique = base;
        int counter = 1;

        while (exists(output, unique)) {
            string suffix = to_string(counter);
            int total = max_len - suffix.length();

            if (total <= 0)
                unique = suffix.substr(0, max_len);
            else
                unique = shorten(input[i], total) + suffix;

            counter++;
        }

        output.push_back(unique);
    }

    cout << "\nResult:\n";
    for (const auto& s : output)
        cout << s << endl;

    return 0;
}
