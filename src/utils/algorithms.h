#include "cityMap.h"

const float BIG = 1e18;

class Algorithms {
    private:
    //Backtracking algorithms
        void backtracking_slove (CityMap& cost_city, int start, int start_city, float&min_cost, vector <int>&best_path)
    {
        int n = cost_city.getN();
        if (start == -1) start = cost_city.getStart();
        if (start == n)
        {
            float current_cost = cost_city.getTotalCost();
            int last_city = cost_city.current();
            float total_cost = current_cost + cost_city.getCost(last_city, start_city);
            if (total_cost < min_cost)
            {
                min_cost = total_cost;
                best_path = cost_city.getPath();
            }
        }
        int last_city = cost_city.current();
        for (int i = 0; i < n; i++)
        {
            if (cost_city.canMove(i))
            {
                float new_cost = cost_city.getTotalCost() + cost_city.getCost(last_city, i);
                if (new_cost < min_cost)
                {
                    cost_city.move(i);
                    backtracking_slove(cost_city, start+1, start_city, min_cost, best_path);
                    cost_city.undoMove();
                }
            }
        }
        
    }
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
    //Backtracking
    pair<vector<int>, float> backtracking (CityMap& cost_city)
    {
        int n = cost_city.getN();
        if (n<2) throw invalid_argument("need n>=2");
        float min_cost = FLT_MAX;
        vector<int> best_path;
        int start_city = cost_city.getStart();
        cost_city.reset();
        backtracking_slove(cost_city, 1, start_city, min_cost, best_path); 

        if (!best_path.empty()) {
            best_path.push_back(start_city);
        }
        return {best_path, min_cost};
    }
    // Dynamic Programming
    static pair<vector<int>, float> bitmaskDP(const CityMap& m, int start = -1) {
        int n = m.getN();
        if (n < 2) throw invalid_argument("need n>=2");

        if (n > 22) {
            throw invalid_argument("N > 22 is too large for Bitmask DP");
        }

        if (start == -1) start = m.getStart();
        vector<vector<float>> dp(1 << n, vector<float>(n, BIG));
        vector<vector<int>> parent(1 << n, vector<int>(n, -1));

        dp[1 << start][start] = 0.0;
        for (int mask = 1; mask < (1 << n); ++mask) {
            if (!(mask & (1 << start))) continue;

            for (int j = 0; j < n; ++j) {
                if ((mask & (1 << j)) && dp[mask][j] < BIG) {
                    for (int i = 0; i < n; ++i) {
                        if (!(mask & (1 << i))) {
                            int new_mask = mask | (1 << i);
                            float new_cost = dp[mask][j] + m.getCost(j, i);

                            if (new_cost < dp[new_mask][i]) {
                                dp[new_mask][i] = new_cost;
                                parent[new_mask][i] = j;
                            }
                        }
                    }
                }
            }
        }

        int final_mask = (1 << n) - 1; 
        float min_cost = BIG;
        int last_city = -1;

        for (int i = 0; i < n; ++i) {
            float final_cost = dp[final_mask][i] + m.getCost(i, start);
            if (final_cost < min_cost) {
                min_cost = final_cost;
                last_city = i;
            }
        }

        if (last_city == -1 || min_cost >= BIG) {
            return { {}, -1.0 };
        }

        vector<int> path;
        int curr = last_city;
        int mask = final_mask;

        while (curr != -1) {
            path.push_back(curr);
            int prev = parent[mask][curr];
            mask ^= (1 << curr);
            curr = prev;
        }
        std::reverse(path.begin(), path.end());
        path.push_back(start);
        return { path, min_cost };
    }
};
