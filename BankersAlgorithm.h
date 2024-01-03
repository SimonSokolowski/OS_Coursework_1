#ifndef BANKERS_ALGORITHM_H
#define BANKERS_ALGORITHM_H

#include <vector>

// Author: Szymon Sokolowski
// ID: M00948848

class BankersAlgorithm {
private:
    std::vector<int> processes;
    std::vector<int> available;
    std::vector<std::vector<int>> maximum;
    std::vector<std::vector<int>> allocation;
    int numProcesses;
    int numResources;

public:
    BankersAlgorithm(int P, int R);
    void setAvailable(std::vector<int> &avail);
    void setMaximum(int processId, std::vector<int> &maxReq);
    void setAllocation(int processId, std::vector<int> &alloc);
    bool isSafe();
    bool requestResources(int processId, std::vector<int> request);
};

#endif // BANKERS_ALGORITHM_H
