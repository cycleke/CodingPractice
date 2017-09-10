#include <queue>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
using namespace std;

struct Data {
    int cx, cy, cost, have;
    Data(int cx, int cy, int cost, int have) :
        cx(cx), cy(cy), cost(cost), have(have) {}
    bool operator < (const Data &b) const {
        return this->cost < b.cost;
    }
    bool operator > (const Data &b) const {
        return this->cost > b.cost;
    }
};

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

class MovingCandies {
	public:
	int disc[21][21][403];
	priority_queue<Data, vector<Data>, greater<Data> > Heap;
	int minMoved(vector <string> t) {
        int n = t.size();
        int m = t.begin()->size();
        int cnt = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                cnt += t[i][j] == '#';
        memset(disc, 63, sizeof disc);
        disc[0][0][1] = (t[0][0] == '.');
        Heap.push(Data(0, 0, disc[0][0][1], 1));
        int ans = 0x3f3f3f3f;
        while (!Heap.empty()) {
            int cx = Heap.top().cx;
            int cy = Heap.top().cy;
            int cost = Heap.top().cost;
            int have = Heap.top().have;
            Heap.pop();
            if (cx == n - 1 && cy == m - 1)
                ans = min(ans, cost);

            if (disc[cx][cy][have] != cost || have >= cnt)
                continue;
            for (int i = 0; i < 4; ++i) {
                int nx = cx + dx[i], ny = cy + dy[i];
                if (nx < 0 || ny < 0 || nx >= n || ny >= m)
                    continue;
                int delta = (t[nx][ny] == '.');
                if (disc[nx][ny][have + 1] > cost + delta)
                    Heap.push(Data(nx, ny, disc[nx][ny][have + 1] = cost + delta, have + 1));
            }
        }
        return ans == 0x3f3f3f3f ? -1 : ans;
	}
};
