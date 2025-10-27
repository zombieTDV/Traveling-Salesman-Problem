#include "utils/cityMap.cpp"

// ----------------- tiny demo -----------------
int main() {
    CityMap cm(4, 0); // 4x4, start at city 0

    // simple symmetric example
    cm.setCost(0,1,10); cm.setCost(1,0,10);
    cm.setCost(0,2,15); cm.setCost(2,0,15);
    cm.setCost(0,3,20); cm.setCost(3,0,20);
    cm.setCost(1,2,35); cm.setCost(2,1,35);
    cm.setCost(1,3,25); cm.setCost(3,1,25);
    cm.setCost(2,3,30); cm.setCost(3,2,30);

    cout << "Start at city " << cm.current() << "\n";
    cout << "Move 1: " << (cm.move(1) ? "ok" : "fail") << "\n";
    cout << "Move 2: " << (cm.move(2) ? "ok" : "fail") << "\n";
    cout << "Undo last: " << (cm.undoMove() ? "undone" : "nothing") << "\n";
    cout << "Move 3: " << (cm.move(3) ? "ok" : "fail") << "\n";

    cout << "Path: ";
    for (int v : cm.getPath()) cout << v << " ";
    cout << "\nTotal cost: " << cm.getTotalCost() << "\n";

    return 0;
}
