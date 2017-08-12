#include <set>
#include <cstdio>
#include <algorithm>

struct Event {
    int begin, end;
    Event() :
        begin(0), end(0) {}
    inline bool operator < (const Event & other) const {
        if (this->end == other.end)
            return this->begin < other.begin;
        return this->end < other.end;
    }
};

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    Event *a = new Event[n];
    for (int i = 0; i < n; ++i)
        scanf("%d %d", &a[i].begin, &a[i].end);
    std::sort(a, a + n);
    std::multiset < int > endtime;
    endtime.clear();
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        auto it = endtime.lower_bound(- a[i].begin);
        if (it == endtime.end()) {
            if (endtime.size() < m) {
                ++ans;
                endtime.insert(- a[i].end - 1);
            }
            continue;
        }
        ++ans;
        endtime.erase(it);
        endtime.insert(- a[i].end - 1);
    }
    printf("%d", ans);
    delete a;
    return 0;
}
