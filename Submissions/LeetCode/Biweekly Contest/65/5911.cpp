#include <bits/stdc++.h>
using namespace std;

class Robot {
    int width, height;
    const int dx[4] = {0, 1, 0, -1};
    const int dy[4] = {-1, 0, 1, 0};
    const string dir_string[4] = {"South", "East", "North", "West"};
    int dir;
    int at_x, at_y;

    bool is_valid() {
        int new_x = at_x + dx[dir];
        int new_y = at_y + dy[dir];
        return (0 <= new_x and new_x < width and 0 <= new_y and new_y < height);
    }
public:
    Robot(int width, int height) {
        this->width = width, this->height = height;
        at_x = 0, at_y = 0;
        dir = 1;
    }

    void move(int num) {
        while (num and is_valid()) {
            num--;
            at_x += dx[dir];
            at_y += dy[dir];
        }
        num %= (2 * width + 2 * height);
        while (num) {
            while (!is_valid()) dir = (dir + 1) % 4;
            num--;
            at_x += dx[dir];
            at_y += dy[dir];
        }
    }

    vector<int> getPos() {
        return {at_x, at_y};
    }

    string getDir() {
        return dir_string[dir];
    }
};

/**
 * Your Robot object will be instantiated and called as such:
 * Robot* obj = new Robot(width, height);
 * obj->move(num);
 * vector<int> param_2 = obj->getPos();
 * string param_3 = obj->getDir();
 */