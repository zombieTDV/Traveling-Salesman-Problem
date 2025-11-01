#include "utils/algorithms.h"

int main() {
    try {
        cout << "=== Travel Route Optimization ===\n";
        int n;
        while (true) {
            cout << "Enter number of cities (n >= 2): ";
            cout.flush();
            if (!(cin >> n)) { cerr << "Invalid input\n"; return 1; }
            if (n >= 2) break;
            cout << "  [Error] n must be >= 2. Try again.\n";
        }

        CityMap city(n, 0);

        // interactive input matrix (enforces non-negative numeric entries)
        city.inputCosts();
        city.printMatrix();
        
        int start = 0;
        city.setStart(start);

        // run 3 algorithms
        cout << "\nRunning Greedy (NN)...\n";
        cout << "Start at (0,0) \n";
        auto g = Algorithms::greedy(city, start);
        if (g.second < 0.0) cout << "Greedy: failed\n";
        else {
            cout << "Greedy cost: " << g.second << "\nRoute: ";
            for (int v: g.first) {cout << v << " "; }
            cout << "\n";
        }
        cout << "\nRunning Backtracking...\n";
        cout << "Start at (0,0) \n";
        Algorithms a;
        auto b = a.backtracking(city);
        if (b.second < 0.0) cout << "Backtracking: failed\n";
        else {
            cout << "Backtracking cost: " << b.second << "\nRoute: ";
            for (int v: b.first) {cout << v << " "; }
            cout << "\n";
        }
        // write best to output.txt if any found
        float bestC = 1e18; 
        vector<int> bestR;
        auto consider = [&](const pair<vector<int>,float>& p){
            if (p.second >= 0.0 && p.second < bestC) { bestC = p.second; bestR = p.first; }
        };
        consider(g);
        if (!bestR.empty()) {
            ofstream fout("output.txt");
            fout << "Best cost: " << bestC << "\nRoute: ";
            for (int v: bestR) fout << v << " ";
            fout << "\n";
            fout.close();
            cout << "\nWrote best result to output.txt\n";
        } else cout << "\nNo valid tour found by any algorithm.\n";

    } catch (const exception &e) {
        cerr << "[Error] " << e.what() << "\n";
        return 2;
    }

    return 0;
}