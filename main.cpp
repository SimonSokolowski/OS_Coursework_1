#include "BankersAlgorithm.h"
#include <iostream>
#include <vector>

// Author: Szymon Sokolowski
// ID: M00948848

int main()
{
    int P, R;
    std::cout << "Enter number of processes: ";
    std::cin >> P;

    std::cout << "Enter number of resources: ";
    std::cin >> R;

    BankersAlgorithm bankers(P, R);

    std::vector<int> avail(R);
    std::cout << "Enter available resources (format: x y z ...): ";
    for (int &a : avail)
        std::cin >> a;
    bankers.setAvailable(avail);

    for (int i = 0; i < P; i++)
    {
        std::vector<int> maxReq(R), allocReq(R);

        std::cout << "Enter maximum resource request for Process " << i << " (format: x y z ...): ";
        for (int &m : maxReq)
            std::cin >> m;
        bankers.setMaximum(i, maxReq);

        std::cout << "Enter number of resources allocated to Process " << i << " (format: x y z ...): ";
        for (int &a : allocReq)
            std::cin >> a;
        bankers.setAllocation(i, allocReq);
    }

    bankers.isSafe();

    std::vector<int> request(R);
    int processId;
    bool continueRequesting = true; // Flag to control the loop

    while (continueRequesting)
    {
        std::cout << "Enter Process ID for resource request: ";
        std::cin >> processId;

        if (processId < 0 || processId >= P)
        {
            std::cout << "Invalid Process ID. Please enter a valid Process ID (0 to " << P - 1 << ")." << std::endl;
            continue; // Skip to the next iteration of the loop
        }

        std::cout << "Enter resource request (format: x y z ...): ";
        for (int &r : request)
            std::cin >> r;

        bankers.requestResources(processId, request);

        std::cout << "Continue requesting resources? (1 for yes, 0 for no): ";
        std::cin >> continueRequesting;
    }

    return 0;
}
