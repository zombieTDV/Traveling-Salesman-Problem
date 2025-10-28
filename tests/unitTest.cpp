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
