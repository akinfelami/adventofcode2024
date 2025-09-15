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
    if (map[next_x][curr_y] == 'O') {
        int check_x = next_x;
        while (check_x < map_size && map[check_x][curr_y] == 'O') {
            check_x++;
        }
        if (check_x < map_size && map[check_x][curr_y] == '.') {
            map[check_x][curr_y] = 'O';
            map[curr_x][curr_y] = '.';
            curr_x = next_x;
            map[curr_x][curr_y] = '@';
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
    if (map[curr_x][next_y] == 'O') {
        int check_y = next_y;
        while (check_y < map_size && map[curr_x][check_y] == 'O')
            check_y++;
        if (check_y < map_size && map[curr_x][check_y] == '.') {
            map[curr_x][check_y] = 'O';
            map[curr_x][curr_y] = '.';
            curr_y = next_y;
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
    if (map[next_x][curr_y] == 'O') {
        int check_x = next_x;
        while (check_x >= 0 && map[check_x][curr_y] == 'O') {
            check_x--;
        }
        if (check_x >= 0 && map[check_x][curr_y] == '.') {
            map[check_x][curr_y] = 'O';
            map[curr_x][curr_y] = '.';
            curr_x = next_x;
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
    if (map[curr_x][next_y] == 'O') {
        int check_y = next_y;
        while (check_y >= 0 && map[curr_x][check_y] == 'O')
            check_y--;
        if (check_y >= 0 && map[curr_x][check_y] == '.') {
            map[curr_x][check_y] = 'O';
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