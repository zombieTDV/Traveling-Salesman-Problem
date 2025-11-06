#include "utils/algorithms.h"
#include <fstream>
#include <chrono>
#include <iomanip>

int main() {
    const string inputFile = "input.txt";
    const string outputFile = "output.txt";

    try {
        // Read from input.txt
        ifstream fin(inputFile);
        if (!fin) {
            cerr << "Error: Cannot open input.txt\n";
            return 1;
        }

        int n;
        fin >> n;
        
        if (n < 2) {
            cerr << "Error: n must be >= 2\n";
            return 1;
        }

        CityMap city(n, 0);
        
        // Read cost matrix from file
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                float cost;
                fin >> cost;
                city.setCost(i, j, cost);
            }
        }
        fin.close();

        int start = 0;
        city.setStart(start);

        // Open output file
        ofstream fout(outputFile);
        if (!fout) {
            cerr << "Error: Cannot open output.txt\n";
            return 1;
        }

        // Run all algorithms and store results
        auto startTime = chrono::high_resolution_clock::now();
        Algorithms algo;
        auto backtrack = algo.backtracking(city);
        auto endTime = chrono::high_resolution_clock::now();
        auto backtrackTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

        startTime = chrono::high_resolution_clock::now();
        auto greedy = Algorithms::greedy(city, start);
        endTime = chrono::high_resolution_clock::now();
        auto greedyTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

        startTime = chrono::high_resolution_clock::now();
        pair<vector<int>, float> dp;
        long long dpTime = 0;
        bool dpSuccess = true;
        try {
            dp = Algorithms::bitmaskDP(city, start);
            endTime = chrono::high_resolution_clock::now();
            dpTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
        } catch (const exception& e) {
            endTime = chrono::high_resolution_clock::now();
            dpTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
            dpSuccess = false;
        }

        // Find minimum cost
        float minCost = 1e18;
        if (backtrack.second >= 0.0) minCost = min(minCost, backtrack.second);
        if (greedy.second >= 0.0) minCost = min(minCost, greedy.second);
        if (dpSuccess && dp.second >= 0.0) minCost = min(minCost, dp.second);

        // Write Backtracking results
        fout << "====BACKTRACKING====\n";
        if (backtrack.second >= 0.0) {
            if (backtrack.second == minCost) {
                fout << "Chi phí tối thiểu: " << static_cast<int>(backtrack.second) << "\n";
            } else {
                fout << "Chi phí: " << static_cast<int>(backtrack.second) << "\n";
            }
            fout << "Lộ trình: ";
            for (int v : backtrack.first) {
                fout << v << " ";
            }
            fout << "\n";
        } else {
            fout << "Không tìm thấy lộ trình\n";
        }
        fout << "Thời gian: " << backtrackTime << " ms\n";

        // Write Greedy results
        fout << "==== GREEDY ====\n";
        if (greedy.second >= 0.0) {
            if (greedy.second == minCost) {
                fout << "Chi phí tối thiểu: " << static_cast<int>(greedy.second) << "\n";
            } else {
                fout << "Chi phí: " << static_cast<int>(greedy.second) << "\n";
            }
            fout << "Lộ trình: ";
            for (int v : greedy.first) {
                fout << v << " ";
            }
            fout << "\n";
        } else {
            fout << "Không tìm thấy lộ trình\n";
        }
        fout << "Thời gian: " << greedyTime << " ms\n";

        // Write DP results
        fout << "==== DP ====\n";
        if (dpSuccess && dp.second >= 0.0) {
            if (dp.second == minCost) {
                fout << "Chi phí tối thiểu: " << static_cast<int>(dp.second) << "\n";
            } else {
                fout << "Chi phí: " << static_cast<int>(dp.second) << "\n";
            }
            fout << "Lộ trình: ";
            for (int v : dp.first) {
                fout << v << " ";
            }
            fout << "\n";
        } else if (!dpSuccess) {
            fout << "Không tìm thấy lộ trình\n";
        } else {
            fout << "Không tìm thấy lộ trình\n";
        }
        fout << "Thời gian: " << dpTime << " ms\n";

        fout.close();
        cout << "Kết quả chạy đã được viết vào output.txt !\n";

    } catch (const exception &e) {
        cerr << "[Error] " << e.what() << "\n";
        return 2;
    }

    return 0;
}