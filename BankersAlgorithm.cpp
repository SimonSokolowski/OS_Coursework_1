#include "BankersAlgorithm.h"
#include <iostream>
#include <vector>

// Constructor for the Banker's Algorithm class.
BankersAlgorithm::BankersAlgorithm(int P, int R) : numProcesses(P), numResources(R)
{
    processes.resize(P);
    available.resize(R);
    maximum.resize(P, std::vector<int>(R));
    allocation.resize(P, std::vector<int>(R));
}

// Function to set the available amount of each resource in the system.
void BankersAlgorithm::setAvailable(std::vector<int> &avail)
{

    available = avail;
}

// Function to set the maximum demand of each resource for a specific process.
void BankersAlgorithm::setMaximum(int processId, std::vector<int> &maxReq)
{

    maximum[processId] = maxReq;
}

// Function to set the number of resources currently allocated to a specific process.
void BankersAlgorithm::setAllocation(int processId, std::vector<int> &alloc)
{

    allocation[processId] = alloc;
}

// Function to check if the system is in a safe state.
bool BankersAlgorithm::isSafe()
{

    // Initialize work vector with available resources and a finish vector to track process completion.
    std::vector<int> work = available;
    std::vector<bool> finish(numProcesses, false);
    std::vector<int> safeSeq(numProcesses);

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
                {
                    // If all resources for p are available add p's allocated resources back to work
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
            std::cout << "System is not in safe state\n";
            return false; // No safe sequence found
        }
    }

    // If all processes can finish safely, print the safe sequence and return true.
    std::cout << "System is in safe state.\nSafe sequence is: ";
    for (int i = 0; i < numProcesses; i++)
    {
        std::cout << "P" << safeSeq[i] << " ";
    }
    std::cout << "\n";
    return true; // Safe sequence found
}

// Function to handle a request for resources by a process.
bool BankersAlgorithm::requestResources(int processId, std::vector<int> request)
{

    // Check if request exceeds maximum demand
    for (int i = 0; i < numResources; i++)
    {
        if (request[i] > maximum[processId][i] - allocation[processId][i])
        {
            std::cout << "Error: Process has exceeded its maximum claim. ";
            return false;
        }
    }

    // Check if resources are available
    for (int i = 0; i < numResources; i++)
    {
        if (request[i] > available[i])
        {
            std::cout << "Resources are not available. ";
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
        std::cout << "Resources allocated successfully. ";
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
        std::cout << "Cannot allocate resources as it leads to an unsafe state. ";
        return false;
    }
}