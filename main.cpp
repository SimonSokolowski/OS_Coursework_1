#include "BankersAlgorithm.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int P, R;
    cout << "Enter number of processes: ";
    cin >> P;

    cout << "Enter number of resources: ";
    cin >> R;

    BankersAlgorithm bankers(P, R);

    vector<int> avail(R);
    cout << "Enter available resources (format: x y z ...): ";
    for (int &a : avail)
        cin >> a;
    bankers.setAvailable(avail);

    for (int i = 0; i < P; i++)
    {
        vector<int> maxReq(R), allocReq(R);

        cout << "Enter maximum resource request for Process " << i << " (format: x y z ...): ";
        for (int &m : maxReq)
            cin >> m;
        bankers.setMaximum(i, maxReq);

        cout << "Enter number of resources allocated to Process " << i << " (format: x y z ...): ";
        for (int &a : allocReq)
            cin >> a;
        bankers.setAllocation(i, allocReq);
    }

    bankers.isSafe();

    vector<int> request(R);
    int processId;
    bool continueRequesting = true; // Flag to control the loop

    while (continueRequesting)
    {
        cout << "Enter Process ID for resource request: ";
        cin >> processId;

        if (processId < 0 || processId >= P)
        {
            cout << "Invalid Process ID. Please enter a valid Process ID (0 to " << P - 1 << ")." << endl;
            continue; // Skip to the next iteration of the loop
        }

        cout << "Enter resource request (format: x y z ...): ";
        for (int &r : request)
            cin >> r;

        bankers.requestResources(processId, request);

        cout << "Continue requesting resources? (1 for yes, 0 for no): ";
        cin >> continueRequesting;
    }

    return 0;
}
