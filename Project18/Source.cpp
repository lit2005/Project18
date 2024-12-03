#include <iostream>  
#include <fstream>  
#include <stack>  
#include <string>  
using namespace std;
bool isValidHTML(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "������: �� ������� ������� ����." << endl;
        return false;
    }

    stack<string> tags;
    string line;
    while (getline(file, line)) {
        size_t pos = 0;
        while ((pos = line.find('<', pos)) != string::npos) {
            size_t end = line.find('>', pos);
            if (end == string::npos) {
                cerr << "������: ������������ ��������� � ������: " << line << endl;
                return false;
            }

            string tag = line.substr(pos + 1, end - pos - 1);
            if (tag[0] != '/') {
                // ����������� ���  
                tags.push(tag);
            }
            else {
                // ����������� ���  
                tag = tag.substr(1); // ������� '/'  
                if (tags.empty() || tags.top() != tag) {
                    cerr << "������: �������������� ����� " << tag << endl;
                    return false;
                }
                tags.pop();
            }
            pos = end + 1;
        }
    }

    file.close();
    if (!tags.empty()) {
        cerr << "������: ���������� ���������� ����." << endl;
        return false;
    }

    return true;
}

int main() {
    setlocale(LC_ALL, "Russian");
    string filename;
    cout << "������� ���� � HTML-�����: ";
    cin >> filename;

    if (isValidHTML(filename)) {
        cout << "���� �������." << endl;
    }
    else {
        cout << "���� �� �������." << endl;
    }

    return 0;
}