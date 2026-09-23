#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
struct ChangeResult {
    int minCoins;
    int maxCoins;
};

ChangeResult getMinAndMaxCoins(const vector<int>& coins, int amount) {
    const int INF = amount + 1;

    vector<int> dpMin(amount + 1, INF);
    vector<int> dpMax(amount + 1, -1);

    dpMin[0] = 0;
    dpMax[0] = 0;

    for (int i = 1; i <= amount; i++) {
        for (int coin : coins) {
            if (i - coin >= 0) {
                if (dpMin[i - coin] != INF) {
                    dpMin[i] = min(dpMin[i], dpMin[i - coin] + 1);
                }

                if (dpMax[i - coin] != -1) {
                    dpMax[i] = max(dpMax[i], dpMax[i - coin] + 1);
                }
            }
        }
    }

    ChangeResult result;
    result.minCoins = (dpMin[amount] == INF) ? -1 : dpMin[amount];
    result.maxCoins = dpMax[amount];

    return result;
}

int main() {
    int numCoins, targetAmount;

    cout << "Enter the number of coin denominations available: ";
    if (!(cin >> numCoins) || numCoins <= 0) {
        cout << "Invalid number of coins." << endl;
        return 1;
    }

    vector<int> coins(numCoins);
    cout << "Enter the coin values (separated by spaces): ";
    for (int i = 0; i < numCoins; i++) {
        cin >> coins[i];
    }

    cout << "Enter the target amount: ";
    cin >> targetAmount;

    if (targetAmount < 0) {
        cout << "Target amount cannot be negative." << endl;
        return 1;
    }

    ChangeResult result = getMinAndMaxCoins(coins, targetAmount);

    if (result.minCoins == -1) {
        cout << "\nIt is impossible to make change for " <<
targetAmount << " with the given denominations." << endl;
    } else {
        cout << "\n--- Results ---" << endl;
        cout << "Minimum number of coins required: " << result.minCoins << endl;
        cout << "Maximum number of coins required: " << result.maxCoins << endl;
    }

    return 0;
}

