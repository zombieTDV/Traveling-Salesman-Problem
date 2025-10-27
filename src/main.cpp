#include "utils/cityMap.cpp"

// ---------------- DEMO ----------------
int main() {
    int n;
    cout << "Enter number of cities: ";
    cout.flush();
    cin >> n;

    CityMap cm(n, 0);
    cm.inputCosts();
    cm.printMatrix();

    cout << "Starting at city " << cm.current() << "\n";

    int next;
    cout << "\nEnter next city to move to: ";
    cout.flush();
    cin >> next;

    if (cm.move(next))
        cout << "Moved successfully! Total cost = " << cm.getTotalCost() << "\n";
    else
        cout << "Invalid move.\n";

    cout << "Path: ";
    for (int v : cm.getPath()) cout << v << " ";
    cout << "\n";
}