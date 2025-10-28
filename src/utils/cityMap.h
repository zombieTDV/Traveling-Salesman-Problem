#include <bits/stdc++.h>
using namespace std;

class CityMap {
private:
    int n = 0;
    int startCity = 0;
    int currentCity = -1;
    vector<vector<float>> cost;
    vector<char> visited;
    vector<int> path;
    float totalCost = 0.0;

    bool validIndex(int x) const { return x >= 0 && x < n; }

public:
    CityMap(int n = 0, int start = 0) { setSize(n); setStart(start); }

    void setSize(int nn) {
        if (nn < 2) throw invalid_argument("n must be >= 2");
        n = nn;
        cost.assign(n, vector<float>(n, 0.0));
        for (int i = 0; i < n; ++i) cost[i][i] = 0.0;
        reset();
    }

    void setStart(int s) {
        if (s < 0 || s >= n) throw out_of_range("start out of range");
        startCity = s;
        reset();
    }

    void setCost(int i, int j, float c) {
        if (!validIndex(i) || !validIndex(j)) throw out_of_range("index out of range");
        if (c < 0.0) throw invalid_argument("cost must be >= 0");
        if (i == j) cost[i][j] = 0.0;
        else cost[i][j] = c;
    }

    float getCost(int i, int j) const {
        if (!validIndex(i) || !validIndex(j)) throw out_of_range("index out of range");
        return cost[i][j];
    }

    // Interactive input: reads row-by-row, skipping diagonal.
    // If user types non-number or negative, print error and ask again for that same cell.
    void inputCosts() {
        if (n < 2) throw logic_error("setSize first with n>=2");
        cout << "\nEnter the cost matrix (" << n << "x" << n << ").\n";
        cout << "Diagonal entries are set to 0 and won't be asked.\n";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == j) { cost[i][j] = 0.0; continue; }
                while (true) {
                    cout << "Cost from " << i << " -> " << j << " (>=0): ";
                    cout.flush();
                    string token;
                    if (!(cin >> token)) {
                        throw runtime_error("input failed");
                    }
                    // try parse
                    char *endp = nullptr;
                    errno = 0;
                    double v = strtod(token.c_str(), &endp);
                    if (endp == token.c_str() || *endp != '\0' || errno == ERANGE) {
                        cout << "  [Error] Not a number. Please enter a non-negative number.\n";
                        continue; // ask again
                    }
                    if (v < 0.0) {
                        cout << "  [Error] Negative cost is not allowed. Please enter >= 0.\n";
                        continue; // ask again
                    }
                    cost[i][j] = v;
                    break;
                }
            }
        }
        cout << "Matrix input complete.\n";
    }

    void reset() {
        visited.assign(n, false);
        path.clear();
        totalCost = 0.0;
        if (n > 0) {
            currentCity = startCity;
            path.push_back(startCity);
            visited[startCity] = true;
        } else currentCity = -1;
    }

    bool canMove(int to) const {
        return validIndex(to) && to != currentCity && !visited[to];
    }

    void move(int to) {
        if (!validIndex(to)) throw out_of_range("move: index out of range");
        if (!canMove(to)) throw logic_error("move: cannot move (visited or same)");
        totalCost += cost[currentCity][to];
        path.push_back(to);
        visited[to] = true;
        currentCity = to;
    }

    void undoMove() {
        if (path.size() <= 1) throw logic_error("undoMove: nothing to undo");
        int last = path.back();
        int prev = path[path.size() - 2];
        totalCost -= cost[prev][last];
        visited[last] = false;
        path.pop_back();
        currentCity = prev;
    }

    void printMatrix() const {
        cout << "\nCost matrix:\n";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << cost[i][j] << (j+1==n? "" : " ");
            }
            cout << "\n";
        }
    }

    const vector<int>& getPath() const { return path; }
    float getTotalCost() const { return totalCost; }
    int getN() const { return n; }
    int getStart() const { return startCity; }
    int current() const { return currentCity; }
};