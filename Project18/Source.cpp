#include <iostream>  
#include <fstream>  
#include <stack>  
#include <string>  
using namespace std;
bool isValidHTML(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл." << endl;
        return false;
    }

    stack<string> tags;
    string line;
    while (getline(file, line)) {
        size_t pos = 0;
        while ((pos = line.find('<', pos)) != string::npos) {
            size_t end = line.find('>', pos);
            if (end == string::npos) {
                cerr << "Ошибка: неправильный синтаксис в строке: " << line << endl;
                return false;
            }

            string tag = line.substr(pos + 1, end - pos - 1);
            if (tag[0] != '/') {
                // Открывающий тег  
                tags.push(tag);
            }
            else {
                // Закрывающий тег  
                tag = tag.substr(1); // удаляем '/'  
                if (tags.empty() || tags.top() != tag) {
                    cerr << "Ошибка: несоответствие тегов " << tag << endl;
                    return false;
                }
                tags.pop();
            }
            pos = end + 1;
        }
    }

    file.close();
    if (!tags.empty()) {
        cerr << "Ошибка: существуют незакрытые теги." << endl;
        return false;
    }

    return true;
}

int main() {
    setlocale(LC_ALL, "Russian");
    string filename;
    cout << "Введите путь к HTML-файлу: ";
    cin >> filename;

    if (isValidHTML(filename)) {
        cout << "Файл валиден." << endl;
    }
    else {
        cout << "Файл не валиден." << endl;
    }

    return 0;
}