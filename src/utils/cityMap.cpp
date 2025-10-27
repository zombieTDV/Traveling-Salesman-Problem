// city_map_simple.cpp
// Minimal CityMap for an n x n cost matrix.
// Provides: setSize, setCost, move, undoMove, reset, getPath, getTotalCost.

#include <iostream>
#include <vector>
using namespace std;

class CityMap {
private:
    int n = 0;
    int startCity = 0;
    int currentCity = -1;
    vector<vector<float>> cost;
    vector<char> visited;
    vector<int> path;
    float totalCost = 0;

    bool validIndex(int x) const { return x >= 0 && x < n; }

public:
    CityMap(int n = 0, int start = 0) { 
        setSize(n); 
        setStart(start); 
    }

    void setSize(int n) {
        this->n = n;
        cost.assign(n, vector<float>(n, 0));
        reset();
    }

    void setStart(int s) {
        if (s >= 0 && s < n) startCity = s;
        reset();
    }

    void setCost(int i, int j, float c) {
        if (i == j) cost[i][j] = 0.0;
        if (validIndex(i) && validIndex(j)) cost[i][j] = c;
    }

    float getCost(int i, int j) const {
        if (!validIndex(i) || !validIndex(j)) return 0;
        return cost[i][j];
    }

    // Reset runtime state (does not clear cost matrix)
    void reset() {
        visited.assign(n, false);
        path.clear();
        totalCost = 0;
        if (n > 0) {
            currentCity = startCity;
            path.push_back(startCity);
            visited[startCity] = true;
        } else {
            currentCity = -1;
        }
    }

    // Can we move from currentCity -> destination ? (no revisits afloatowed)
    bool canMove(int destination) const {
        return validIndex(destination) && (destination != currentCity) && (!visited[destination]);
    }

    // Move to city 'destination'. Returns true if succeeded.
    bool move(int to) {
        if (!canMove(to)) return false;
        totalCost += cost[currentCity][to];
        path.push_back(to);
        visited[to] = true;
        currentCity = to;
        return true;
    }

    // Undo the last move. Returns true if undone (cannot undo start).
    bool undoMove() {
        if (path.size() <= 1) return false; // nothing to undo
        int last = path.back();
        int prev = path[path.size() - 2];
        totalCost -= cost[prev][last];
        visited[last] = false;
        path.pop_back();
        currentCity = prev;
        return true;
    }

    // Accessors
    const vector<int>& getPath() const { return path; }
    float getTotalCost() const { return totalCost; }
    int current() const { return currentCity; }
};