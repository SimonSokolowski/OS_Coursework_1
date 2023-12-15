#include "BankersAlgorithm.h"

#include <iostream>
#include <vector>

using namespace std;

BankersAlgorithm::BankersAlgorithm(int P, int R) : numProcesses(P), numResources(R)
{
    processes.resize(P);
    available.resize(R);
    maximum.resize(P, vector<int>(R));
    allocation.resize(P, vector<int>(R));
}

void BankersAlgorithm::setAvailable(std::vector<int> &avail)
{

    available = avail;
}

void BankersAlgorithm::setMaximum(int processId, std::vector<int> &maxReq)
{

    maximum[processId] = maxReq;
}

void BankersAlgorithm::setAllocation(int processId, std::vector<int> &alloc)
{

    allocation[processId] = alloc;
}

bool BankersAlgorithm::isSafe()
{

    vector<int> work = available;
    vector<bool> finish(numProcesses, false);
    vector<int> safeSeq(numProcesses);

    int count = 0;
    while (count < numProcesses)
    {
        bool found = false;
        for (int p = 0; p < numProcesses; p++)
        {
            if (!finish[p])
            {
                int j;
                for (j = 0; j < numResources; j++)
                {
                    // Check if resources needed by p are available
                    if (maximum[p][j] - allocation[p][j] > work[j])
                    {
                        break; // Not enough resources for p
                    }
                }
                if (j == numResources)
                { // If all resources for p are available
                    // Add p's allocated resources back to work
                    for (int k = 0; k < numResources; k++)
                    {
                        work[k] += allocation[p][k];
                    }
                    safeSeq[count++] = p; // Add p to safe sequence
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found)
        {
            cout << "System is not in safe state\n";
            return false; // No safe sequence found
        }
    }

    cout << "System is in safe state.\nSafe sequence is: ";
    for (int i = 0; i < numProcesses; i++)
    {
        cout << "P" << safeSeq[i] << " ";
    }
    cout << "\n";
    return true; // Safe sequence found
}

bool BankersAlgorithm::requestResources(int processId, std::vector<int> request)
{

    // Check if request exceeds maximum demand
    for (int i = 0; i < numResources; i++)
    {
        if (request[i] > maximum[processId][i] - allocation[processId][i])
        {
            cout << "Error: Process has exceeded its maximum claim. ";
            return false;
        }
    }

    // Check if resources are available
    for (int i = 0; i < numResources; i++)
    {
        if (request[i] > available[i])
        {
            cout << "Resources are not available. ";
            return false;
        }
    }

    // Allocate resources
    for (int i = 0; i < numResources; i++)
    {
        available[i] -= request[i];
        allocation[processId][i] += request[i];
    }

    // Check if new state is safe
    if (isSafe())
    {
        cout << "Resources allocated successfully. ";
        return true;
    }
    else
    {
        // Rollback allocation if not safe
        for (int i = 0; i < numResources; i++)
        {
            available[i] += request[i];
            allocation[processId][i] -= request[i];
        }
        cout << "Cannot allocate resources as it leads to an unsafe state. ";
        return false;
    }
}