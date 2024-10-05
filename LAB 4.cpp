#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <stdexcept>

using namespace std;

int countInversionsBruteForce(const vector<int> &arr)
{
    int inversionCount = 0;
    int n = arr.size();

    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (arr[i] > arr[j])
            {
                inversionCount++;
            }
        }
    }

    return inversionCount;
}

int mergeAndCount(vector<int> &arr, int left, int mid, int right)
{
    int inversions = 0;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> leftArr(n1);
    vector<int> rightArr(n2);

    for (int i = 0; i < n1; ++i)
        leftArr[i] = arr[left + i];
    for (int i = 0; i < n2; ++i)
        rightArr[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (leftArr[i] <= rightArr[j])
        {
            arr[k++] = leftArr[i++];
        }
        else
        {
            arr[k++] = rightArr[j++];
            inversions += (n1 - i);
        }
    }

    while (i < n1)
        arr[k++] = leftArr[i++];

    while (j < n2)
        arr[k++] = rightArr[j++];

    return inversions;
}

int countInversionsDAC(vector<int> &arr, int left, int right)
{
    int inversions = 0;
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        inversions += countInversionsDAC(arr, left, mid);
        inversions += countInversionsDAC(arr, mid + 1, right);
        inversions += mergeAndCount(arr, left, mid, right);
    }
    return inversions;
}

void generateRandomChoices(vector<vector<int>> &courseChoices)
{
    vector<int> subjects = {1001, 1002, 1003, 1004, 1005, 1006};
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < 100; ++i)
    {
        random_shuffle(subjects.begin(), subjects.end());
        for (int j = 0; j < 6; ++j)
        {
            courseChoices[i][j] = subjects[j];
        }
    }
}

void addFakeCourseCodes(vector<vector<int>> &courseChoices)
{
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < 5; ++i)
    {
        int studentIndex = rand() % 100;
        int courseIndex = rand() % 6;
        if (rand() % 10 == 0)
        {
            courseChoices[studentIndex][courseIndex] = 9999;
        }
    }
}

void analyzeInversionCounts(const vector<vector<int>> &courseChoices)
{
    int zeroInversions = 0;
    int oneInversion = 0;
    int twoInversions = 0;
    int threeInversions = 0;

    for (const auto &choices : courseChoices)
    {
        for (int code : choices)
        {
            if (code < 1001 || code > 1006)
            {
                throw runtime_error("Error: Invalid course code encountered!");
            }
        }

        int inversions = countInversionsBruteForce(choices);
        if (inversions == 0)
        {
            zeroInversions++;
        }
        else if (inversions == 1)
        {
            oneInversion++;
        }
        else if (inversions == 2)
        {
            twoInversions++;
        }
        else if (inversions == 3)
        {
            threeInversions++;
        }
    }

    cout << "Brute Force:" << endl;
    cout << "Students with zero inversions: " << zeroInversions << endl;
    cout << "Students with one inversion: " << oneInversion << endl;
    cout << "Students with two inversions: " << twoInversions << endl;
    cout << "Students with three inversions: " << threeInversions << endl;
}

void analyzeInversionCountsDAC(const vector<vector<int>> &courseChoices)
{
    int zeroInversions = 0;
    int oneInversion = 0;
    int twoInversions = 0;
    int threeInversions = 0;

    for (const auto &choices : courseChoices)
    {
        for (int code : choices)
        {
            if (code < 1001 || code > 1006)
            {
                throw runtime_error("Error: Invalid course code encountered!");
            }
        }

        vector<int> arr = choices;
        int inversions = countInversionsDAC(arr, 0, arr.size() - 1);
        if (inversions == 0)
        {
            zeroInversions++;
        }
        else if (inversions == 1)
        {
            oneInversion++;
        }
        else if (inversions == 2)
        {
            twoInversions++;
        }
        else if (inversions == 3)
        {
            threeInversions++;
        }
    }
    cout << endl;
    cout << "*" << endl;
    cout << "Divide and Conquer:" << endl;
    cout << "Students with zero inversions: " << zeroInversions << endl;
    cout << "Students with one inversion: " << oneInversion << endl;
    cout << "Students with two inversions: " << twoInversions << endl;
    cout << "Students with three inversions: " << threeInversions << endl;
}

int main()
{
    vector<vector<int>> courseChoices(100, vector<int>(6));
    generateRandomChoices(courseChoices);
    addFakeCourseCodes(courseChoices);

    try
    {
        analyzeInversionCounts(courseChoices);
        analyzeInversionCountsDAC(courseChoices);
    }
    catch (const runtime_error &e)
    {
        cout << e.what() << endl;
    }

    return 0;
}