#include <bits/stdc++.h>
using namespace std;

#define N 5
typedef pair<int, string> pi;

// string usedd for output the optimal path
vector<string> PlacesOutput = {
    "1st block",
    "2nd block",
    "3rd block",
    "4th block",
    "5th block",
    "6th block",
    "7th block",
    "8th block",
    "9th block",
    "10th block",
    "11th block",
    "12th block",
    "MAC",
    "Library",
    "Ground",
    "FOod court"};

// cost tto various points from the respective points
vector<vector<int>> Places = {
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
    {1, 0, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18},
    {2, 5, 0, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19},
    {3, 6, 7, 0, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
    {4, 7, 8, 9, 0, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21},
    {5, 8, 9, 10, 11, 0, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22},
    {6, 9, 10, 11, 12, 13, 0, 15, 16, 17, 18, 19, 20, 21, 22, 23},
    {7, 10, 11, 12, 13, 14, 15, 0, 17, 18, 19, 20, 21, 22, 23, 24},
    {8, 11, 12, 13, 14, 15, 16, 17, 0, 19, 20, 21, 22, 23, 24, 25},
    {9, 12, 13, 14, 15, 16, 17, 18, 19, 0, 21, 22, 23, 24, 25, 26},
    {10, 13, 14, 15, 16, 17, 18, 19, 20, 21, 0, 23, 24, 25, 26, 27},
    {11, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 0, 25, 26, 27, 28},
    {12, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 0, 27, 28, 29},
    {13, 16, 17, 19, 19, 20, 21, 22, 23, 24, 25, 26, 27, 0, 29, 30},
    {14, 17, 18, 20, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 0, 31},
    {15, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 0}};

bool check(string s, char c)
{
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == c)
            return true;
    }
    return false;
}

// Function for finding the minimum length path
pair<int, string> dijkstra(vector<vector<int>> cost)
{
    int n = cost.size();

    priority_queue<pi, vector<pi>, greater<pi>> pq, anspq;

    // selecting the next node moving from 0
    for (int i = 1; i < n; i++)
    {
        char c = '0' + i;
        string tmp = "0";
        tmp += c;
        pq.push({cost[0][i], tmp}); // adding the key as the second stop of the
    }

    // using dijkstra for detemining the shortest path upto rest of the nodes
    while (!pq.empty())
    {

        int cst = pq.top().first;                 // cst till now for travelling upto this point
        string str = pq.top().second;             // string storing the path
        int len = str.size();                     // num of cities covered
        int lastNode = (int)(str[len - 1] - '0'); // last Node

        // cout << cst << " " << str << "\n";

        if (len == n) // condition for checking the salesman has covered all the nodes or not
        {
            anspq.push({cst + cost[lastNode][0], str + '0'});
            pq.pop();
            continue;
        }

        pq.pop();

        for (int i = 1; i < n; i++)
            if (!check(str, (char)('0' + i))) // conditon for checking,  whether it was earlier visited or not
            {
                char c = '0' + i;
                pq.push({cost[lastNode][i] + cst, str + c});
            }
    }
    return anspq.top();
}

pair<int, vector<int>> bruteForce(vector<vector<int>> graph)
{
    int s = 0;
    int n = graph.size();
    // store all vertex apart from source vertex
    vector<int> vertex, ans;
    for (int i = 0; i < n; i++)
        if (i != s)
            vertex.push_back(i);

    // store minimum weight Hamiltonian Cycle.
    int min_path = INT_MAX;
    do
    {

        // store current Path weight(cost)
        int current_pathweight = 0;

        // compute current path weight
        int k = s;
        for (int i = 0; i < vertex.size(); i++)
        {
            current_pathweight += graph[k][vertex[i]];
            k = vertex[i];
        }
        current_pathweight += graph[k][s];

        // update minimum
        min_path = min(min_path, current_pathweight);
        if (min_path == current_pathweight)
        {
            ans.clear();
            for (int i = 0; i < vertex.size(); i++)
                ans.push_back(vertex[i]);
        }

    } while (
        next_permutation(vertex.begin(), vertex.end()));

    return {min_path, ans};
}

int main()
{
    int inf = 1e9;

    vector<vector<int>> cost = {{inf, 5, 7, 6, 0},
                                {5, inf, 3, 8, 5},
                                {7, 3, inf, 2, 7},
                                {6, 8, 2, inf, 9},
                                {0, 5, 7, 9, inf}};
    int n = 5;

    cout << "----------------Location label---------------------" << endl
         << "0:1st block \n1:2nd block \n2:3rd block \n3:4th block \n4:5th block \n5:6th block \n6:7th block \n7:8th block \n8:9th block \n9:10th block \n10:11th block \n11:12th block \n12:MAC \n13:Library \n14:Ground \n15:Food court \n";
    cout << "\nEnter all the 5 distinct location" << endl;
    int inputLocation[N];

    for (int i = 0; i < N; i++)
    {
        if (i == 0)
            cout << "Enter the Start point \t";
        cin >> inputLocation[i];
        for (int j = 0; j < i; j++)
        {
            if (inputLocation[i] == inputLocation[j])
            {
                cout << "Oops!! You have entered the same location as earlier kindly enter some other loaction\n";
                i--;
                break;
            }
        }
    }

    // using the previous matrix for finding the cost matrix
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == j)
                cost[i][j] = inf;
            else
                cost[i][j] = Places[inputLocation[i]][inputLocation[j]];
        }
    }

    cout << "\n";

    pair<int, string> anspq = dijkstra(cost);

    int cst = anspq.first;
    string ansstr = anspq.second;

    cout << "Path-\nFrom";
    for (int i = 0; i < ansstr.size(); i++)
    {
        int idx = ansstr[i] - '0';
        cout << " - " << PlacesOutput[inputLocation[idx]];
    }
    cout << "\nThe stated path cost us " << cst << "\n";

    pair<int, vector<int>> dpans = bruteForce(cost);

    cst = dpans.first;
    vector<int> ansvec = dpans.second;

    cout << "Path Using Brute Force-\nFrom ";
    cout << PlacesOutput[0] << " - ";
    for (int i = 0; i < ansvec.size(); i++)
    {
        cout << " - " << PlacesOutput[inputLocation[ansvec[i]]];
    }
    cout << " - " << PlacesOutput[0];

    cout << "\nThe stated path cost us " << cst << "\n";

    return 0;
}