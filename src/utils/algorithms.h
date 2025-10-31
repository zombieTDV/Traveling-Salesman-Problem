#include "cityMap.h"

const float BIG = 1e18;

class Algorithms {
    private:
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
};
