#include "utils/algorithms.h"
#include <fstream>
#include <chrono>
#include <iomanip>

int main() {
    const string inputFile = "input8x8.txt";
    const string outputFile = "output8x8.txt";

    try {
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

        ofstream fout(outputFile);
        if (!fout) {
            cerr << "Error: Cannot open output.txt\n";
            return 1;
        }

        fout << fixed << setprecision(3); // hiển thị 3 chữ số sau dấu phẩy

        Algorithms algo;

        // === GREEDY ===
        auto startTime = chrono::high_resolution_clock::now();
        auto greedy = Algorithms::greedy(city, start);
        auto endTime = chrono::high_resolution_clock::now();
        double greedyTime = chrono::duration<double, std::milli>(endTime - startTime).count();

        // === BACKTRACKING ===
        startTime = chrono::high_resolution_clock::now();
        auto backtrack = algo.backtracking(city);
        endTime = chrono::high_resolution_clock::now();
        double backtrackTime = chrono::duration<double, std::milli>(endTime - startTime).count();

        // === BITMASK DP ===
        startTime = chrono::high_resolution_clock::now();
        pair<vector<int>, float> dp;
        double dpTime = 0;
        bool dpSuccess = true;
        try {
            dp = Algorithms::bitmaskDP(city, start);
            endTime = chrono::high_resolution_clock::now();
            dpTime = chrono::duration<double, std::milli>(endTime - startTime).count();
        } catch (const exception& e) {
            endTime = chrono::high_resolution_clock::now();
            dpTime = chrono::duration<double, std::milli>(endTime - startTime).count();
            dpSuccess = false;
        }

        // Find minimum cost
        float minCost = 1e18;
        if (greedy.second >= 0.0) minCost = min(minCost, greedy.second);
        if (backtrack.second >= 0.0) minCost = min(minCost, backtrack.second);
        if (dpSuccess && dp.second >= 0.0) minCost = min(minCost, dp.second);

        // === GREEDY ===
        fout << "==== GREEDY ====\n";
        if (greedy.second >= 0.0) {
            if (greedy.second == minCost) fout << "Chi phí tối thiểu: ";
            else fout << "Chi phí: ";
            fout << static_cast<int>(greedy.second) << "\n";
            fout << "Lộ trình: ";
            for (int v : greedy.first) fout << v << " ";
            fout << "\n";
        } else fout << "Không tìm thấy lộ trình\n";
        fout << "Thời gian: " << greedyTime << " ms\n\n";

        // === BACKTRACKING ===
        fout << "==== BACKTRACKING ====\n";
        if (backtrack.second >= 0.0) {
            if (backtrack.second == minCost) fout << "Chi phí tối thiểu: ";
            else fout << "Chi phí: ";
            fout << static_cast<int>(backtrack.second) << "\n";
            fout << "Lộ trình: ";
            for (int v : backtrack.first) fout << v << " ";
            fout << "\n";
        } else fout << "Không tìm thấy lộ trình\n";
        fout << "Thời gian: " << backtrackTime << " ms\n\n";

        // === DP ===
        fout << "==== DP ====\n";
        if (dpSuccess && dp.second >= 0.0) {
            if (dp.second == minCost) fout << "Chi phí tối thiểu: ";
            else fout << "Chi phí: ";
            fout << static_cast<int>(dp.second) << "\n";
            fout << "Lộ trình: ";
            for (int v : dp.first) fout << v << " ";
            fout << "\n";
        } else fout << "Không tìm thấy lộ trình\n";
        fout << "Thời gian: " << dpTime << " ms\n\n";

        fout.close();
        cout << "Kết quả chạy đã được viết vào output.txt !\n";

    } catch (const exception &e) {
        cerr << "[Error] " << e.what() << "\n";
        return 2;
    }

    return 0;
}
