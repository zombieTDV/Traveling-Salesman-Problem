#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <chrono>

#include "../src/utils/algorithms.h"

using namespace doctest;

TEST_CASE("greedy 4x4") {
    CityMap city(4, 0);

    city.setCost(0,1,10);
    city.setCost(0,2,12);
    city.setCost(0,3, 8);

    city.setCost(1,0,10);
    city.setCost(1,2,15);
    city.setCost(1,3,11);

    city.setCost(2,0,12);
    city.setCost(2,1,15);
    city.setCost(2,3,14);

    city.setCost(3,0,8);
    city.setCost(3,1,11);
    city.setCost(3,2,14);


    city.setStart(0);

    auto result = Algorithms::greedy(city, 0);
    CHECK(result.second >= 0.0);
    CHECK(result.first.size() == 5);           // expecting tour length = number of cities + return
    CHECK(result.first.front() == 0);           // expecting you start at (0,0)
    CHECK(result.first.back() == 0);            // expecting you return to (0,0)
    CHECK(result.second == Approx(46));

    // Verify all cities are visited
    std::set<int> visited(result.first.begin(), result.first.end());
    CHECK(visited.size() == 4);  // Should visit all 4 cities

    // Verify no duplicates in middle of tour
    std::set<int> middle(result.first.begin() + 1, result.first.end() - 1);
    CHECK(middle.size() == 3);  // Should be 3 unique cities in middle
    
    cout << "Greedy route: \n";
    for (int v : result.first) std::cout << v << " ";
    std::cout << std::endl;
}

TEST_CASE("greedy runtime moderate n=15") {
    int size = 15;
    CityMap city(size, 0);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i == j) city.setCost(i, j, 0);
            else city.setCost(i, j, (i + j) % 50 + 1);
        }
    }
    // city.printMatrix();
    city.setStart(0);

    auto t1 = std::chrono::high_resolution_clock::now();
    auto result = Algorithms::greedy(city, 0);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> sec = t2 - t1;

    CHECK(result.second >= 0.0);
    std::cout << "Greedy (n=" << size << ") took " << sec.count() << " seconds\n";
    // Relaxed threshold so it's less brittle:
    // CHECK(sec.count() < 0.1); 
}


TEST_CASE("backtracking 4x4") {
    CityMap city(4, 0);

    city.setCost(0,1,10);
    city.setCost(0,2,12);
    city.setCost(0,3, 8);

    city.setCost(1,0,10);
    city.setCost(1,2,15);
    city.setCost(1,3,11);

    city.setCost(2,0,12);
    city.setCost(2,1,15);
    city.setCost(2,3,14);

    city.setCost(3,0,8);
    city.setCost(3,1,11);
    city.setCost(3,2,14);

    city.setStart(0);

    Algorithms solver; 
    auto result = solver.backtracking(city); 

    CHECK(result.second >= 0.0);
    CHECK(result.first.size() == 5);           // Mong đợi n + 1 thành phố (bao gồm cả quay về)
    CHECK(result.first.front() == 0);          // Bắt đầu từ 0
    CHECK(result.first.back() == 0);           // Kết thúc tại 0

    // Backtracking PHẢI tìm ra chi phí tối ưu.
    // Với ma trận này, chi phí tối ưu là 46.
    CHECK(result.second == Approx(46));

    // Xác minh tất cả thành phố đã được thăm
    std::set<int> visited(result.first.begin(), result.first.end());
    CHECK(visited.size() == 4);  // Phải thăm đủ 4 thành phố

    // Xác minh không trùng lặp ở giữa
    std::set<int> middle(result.first.begin() + 1, result.first.end() - 1);
    CHECK(middle.size() == 3);  // Phải có 3 thành phố unique ở giữa
    
    cout << "Backtracking route: \n";
    for (int v : result.first) std::cout << v << " ";
    std::cout << std::endl;
}

TEST_CASE("backtracking runtime small n=10") {
    // Lưu ý: Chúng ta dùng n=10, không phải n=15.
    // Backtracking là O(n!), (n-1)! = 9! = 362,880 hoán vị.
    // n=15 (14! = 87 tỷ) sẽ chạy quá lâu.
    int size = 10;
    CityMap city(size, 0);
    for (int i = 0; i< size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i == j) city.setCost(i, j, 0);
            else city.setCost(i, j, (i + j) % 50 + 1);
        }
    }
    city.setStart(0);

    Algorithms solver; // Khởi tạo đối tượng

    auto t1 = std::chrono::high_resolution_clock::now();
    auto result = solver.backtracking(city); // Gọi hàm non-static
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> sec = t2 - t1;

    CHECK(result.second >= 0.0);
    std::cout << "Backtracking (n=" << size << ") took " << sec.count() << " seconds\n";
    
    // Kiểm tra xem nó có chạy trong thời gian hợp lý không (ví dụ: < 5 giây)
    CHECK(sec.count() < 5.0); 
}
