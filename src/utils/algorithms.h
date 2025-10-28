#include "cityMap.h"

const float BIG = 1e18;

class Algorithms {
public:
    // Greedy
    static pair<vector<int>, float> greedy(const CityMap& m, int start = -1) {
        int n = m.getN();
        if (n < 2) throw invalid_argument("need n>=2");
        if (start == -1) start = m.getStart();
        vector<char> vis(n, 0);
        vector<int> route; route.reserve(n+1);
        int cur = start; route.push_back(cur); vis[cur]=1;
        float tot = 0.0;

        for (int step=1; step<n; ++step) {
            int best = -1; 
            float bestc = BIG;
            for (int j=0;j<n;++j) if (!vis[j]) {
                float c = m.getCost(cur,j);
                if (c < bestc) { bestc = c; best = j; }
            }
            if (best == -1) return {route, -1.0};
            route.push_back(best); tot += bestc; vis[best]=1; cur = best;
        }
        // return to start
        tot += m.getCost(cur, start);
        route.push_back(start);
        return {route, tot};
    }
};