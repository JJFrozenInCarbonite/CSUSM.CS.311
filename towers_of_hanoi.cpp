#include <iostream>
#include <stack>
#include <algorithm>
#include <iomanip>

using namespace std;

const int N = 20;

void print_stacks(stack<int> s1, stack<int> s2, stack<int> s3);
void move_disks(int n, stack<int>& source, stack<int>& target, stack<int>& auxiliary, int& move_count);

int main() {
    stack<int> s1, s2, s3;
    for (int i = N; i > 0; i--) {
        s1.push(i);
    }

    int move_count = 0;
    move_disks(N, s1, s3, s2, move_count);
    cout << "Total Moves: " << move_count;
    return 0;
}

void move_disks(int n, stack<int>& source, stack<int>& target, stack<int>& auxiliary, int& move_count) {
    if (n > 0) {
        // Move n-1 disks from source to auxiliary, so they are out of the way
        move_disks(n - 1, source, auxiliary, target, move_count);

        // Move the nth disk from source to target
        target.push(source.top());
        source.pop();
        move_count++;

        // Move the n-1 disks that we left on auxiliary to target
        move_disks(n - 1, auxiliary, target, source, move_count);
    }
}