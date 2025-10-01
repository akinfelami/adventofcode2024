#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void move_down(int& curr_x, int& curr_y, vector<string>& map, int map_size) {
    int next_x = curr_x + 1;
    if (next_x >= map_size || map[next_x][curr_y] == '#') {
        return;
    }
    if (map[next_x][curr_y] == '.') {
        map[curr_x][curr_y] = '.';
        curr_x = next_x;
        map[curr_x][curr_y] = '@';
        return;
    }

    if (map[next_x][curr_y] == '[') {
        int check_x = next_x;
        while (check_x < map_size && map[check_x][curr_y] == '[' &&
               map[check_x][curr_y + 1] == ']') {
            check_x++;
        }
        if (check_x < map_size && map[check_x][curr_y] == '.' &&
            map[check_x][curr_y + 1] == '.') {
            map[check_x][curr_y] = '[';
            map[check_x][curr_y + 1] = ']';
            curr_x = next_x;
            map[curr_x][curr_y] = '@';
        }

    } else if (map[next_x][curr_y] == ']') {
        int check_x = next_x;
        while (check_x < map_size && map[check_x][curr_y] == ']' &&
               map[check_x][curr_y - 1] == '[') {
            check_x++;
        }
        if (check_x < map_size && map[check_x][curr_y] == '.' &&
            map[check_x][curr_y - 1] == '.') {
            map[check_x][curr_y] = ']';
            map[check_x][curr_y - 1] = '[';
            curr_x = next_x;
            map[curr_x][curr_y] = '@';
        }
    }
}

void move_up(int& curr_x, int& curr_y, vector<string>& map, int map_size) {
    int next_x = curr_x - 1;
    if (next_x < 0 || map[next_x][curr_y] == '#')
        return;
    if (map[next_x][curr_y] == '.') {
        map[curr_x][curr_y] = '.';
        curr_x = next_x;
        map[curr_x][curr_y] = '@';
        return;
    }

    if (map[next_x][curr_y] == '[') {
        int check_x = next_x;

        if (check_x - 1 >= 0 && map[check_x - 1][curr_y] == ']') {
            cout << "unhappy path" << endl;
            // unhappy path
            //          [][]
            //           []
            //           @
            // }
            // happy path []
            //            @
            // while (check_x >= 0 && (map[check_x][curr_y] == '[' ||
            //        map[check_x][curr_y + 1] == ']')) {
            //     check_x--;
            // }

        } else {
            while (check_x >= 0 && map[check_x][curr_y] == '[' &&
                   map[check_x][curr_y + 1] == ']') {
                check_x--;
            }
            if (check_x >= 0 && map[check_x][curr_y] == '.' &&
                map[check_x][curr_y + 1] == '.') {
                while (check_x < curr_x) {
                    map[check_x][curr_y] = '[';
                    map[check_x][curr_y + 1] = ']';
                    check_x += 1;
                }
                map[curr_x][curr_y] = '.';
                curr_x = next_x;
                map[curr_x][curr_y] = '@';
                map[curr_x][curr_y + 1] = '.';
            }
        }
    } else if (map[next_x][curr_y] == ']') {
        int check_x = next_x;
        if (check_x - 1 >= 0 && map[check_x - 1][curr_y] == '[') {
            cout << "unhappy path" << endl;
        } else {
            while (check_x >= 0 && map[check_x][curr_y] == ']' &&
                   map[check_x][curr_y - 1] == '[')
                check_x--;
            if (check_x < map_size && map[check_x][curr_y] == '.' &&
                map[check_x][curr_y - 1] == '.') {
                while (check_x < curr_x) {
                    map[check_x][curr_y] = ']';
                    map[check_x][curr_y - 1] = '[';
                    check_x += 1;
                }
                map[curr_x][curr_y] = '.';
                curr_x = next_x;
                map[curr_x][curr_y] = '@';
                map[curr_x][curr_y - 1] = '.';
            }
        }
    }
}

void move_right(int& curr_x, int& curr_y, vector<string>& map, int map_size) {
    int next_y = curr_y + 1;
    if (next_y >= (int)map[curr_x].length() || map[curr_x][next_y] == '#')
        return;
    if (map[curr_x][next_y] == '.') {
        map[curr_x][curr_y] = '.';
        curr_y = next_y;
        map[curr_x][curr_y] = '@';
        return;
    }
    if (map[curr_x][next_y] == '[') {
        int check_y = next_y;
        while (check_y < map_size && map[curr_x][check_y] == '[')
            check_y += 2;
        if (check_y + 1 < map_size && map[curr_x][check_y] == '.') {
            while (check_y > curr_y) {
                map[curr_x][check_y] = ']';
                map[curr_x][check_y - 1] = ']';
                check_y -= 2;
            }
            map[curr_x][curr_y] = '.';
            curr_y = next_y;
            map[curr_x][curr_y] = '@';
        }
    }
}

void move_left(int& curr_x, int& curr_y, vector<string>& map, int map_size) {
    int next_y = curr_y - 1;
    if (next_y < 0 || map[curr_x][next_y] == '#')
        return;
    if (map[curr_x][next_y] == '.') {
        map[curr_x][curr_y] = '.';
        curr_y = next_y;
        map[curr_x][curr_y] = '@';
        return;
    }
    if (map[curr_x][next_y] == ']') {
        int check_y = next_y;
        while (check_y >= 0 && map[curr_x][check_y] == ']') {
            check_y -= 2;
        }
        if (check_y >= 0 && map[curr_x][check_y] == '.') {
            while (check_y < curr_y) {
                map[curr_x][check_y] = '[';
                map[curr_x][check_y + 1] = ']';
                check_y += 2;
            }
            map[curr_x][curr_y] = '.';
            curr_y = next_y;
            map[curr_x][curr_y] = '@';
        }
    }
}

int main() {
    ifstream file("input.txt");
    if (file.is_open()) {
        string line;
        vector<string> map;
        int rx = 0, ry = 0;
        bool found = false;
        while (getline(file, line)) {
            if (line.empty())
                break;
            size_t at = line.find('@');
            if (at != string::npos) {
                ry = (int)at;
                found = true;
            }
            if (!found)
                rx++;
            map.push_back(line);
        }
        for (string& s : map) {
            string new_s = "";
            for (int i = 0; i < s.length(); i++) {
                if (s[i] == '#') {
                    new_s += "##";
                } else if (s[i] == 'O') {
                    new_s += "[]";
                } else if (s[i] == '.') {
                    new_s += "..";
                } else if (s[i] == '@') {
                    new_s += "@.";
                } else {
                    new_s += s[i];
                }
            }
            s = new_s;
        }
        for (string s : map) {
            for (char c : s) {
                cout << c;
            }
            cout << endl;
        }
        for (size_t i = 0; i < map.size(); i++) {
            for (size_t j = 0; j < map[i].length(); j++) {
                if (map[i][j] == '@') {
                    rx = i;
                    ry = j;
                }
            }
        }
        string moves;
        while (getline(file, line)) {
            moves += line;
        }
        int map_size = (int)map.size();
        for (char move : moves) {
            switch (move) {
            case '^':
                cout << "move up" << endl;
                move_up(rx, ry, map, map_size);
                for (string s : map) {
                    for (char c : s) {
                        cout << c;
                    }
                    cout << endl;
                }
                cout << endl;
                break;
            case 'v':
                cout << "move down" << endl;
                move_down(rx, ry, map, map_size);
                for (string s : map) {
                    for (char c : s) {
                        cout << c;
                    }
                    cout << endl;
                }
                cout << endl;

                break;
            case '<':
                cout << "move left" << endl;
                move_left(rx, ry, map, map_size);
                for (string s : map) {
                    for (char c : s) {
                        cout << c;
                    }
                    cout << endl;
                }
                cout << endl;

                break;
            case '>':
                cout << "move rigght" << endl;

                move_right(rx, ry, map, map_size);
                for (string s : map) {
                    for (char c : s) {
                        cout << c;
                    }
                    cout << endl;
                }
                cout << endl;

                break;
            default:
                break;
            }
        }
        for (string s : map) {
            for (char c : s) {
                cout << c;
            }
            cout << endl;
        }
        int corrds = 0;
        for (int i = 0; i < map_size; i++) {
            for (int j = 0; j < (int)map[i].length(); j++) {
                if (map[i][j] == 'O') {
                    corrds += (100 * i + j);
                }
            }
        }
        cout << corrds;
    } else {
        cout << "Unable to open file" << endl;
    }

    return 0;
}