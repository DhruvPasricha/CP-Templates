#include<bits/stdc++.h>
using namespace std;

/*
    *   ConvexHull: just pass vector of points {x, y} to the constructor
    *   Methods: create
    *   Time Complexity: O(NLogN)
*/ 
struct ConvexHull {
    static const int UPPER_HALF = 1, LOWER_HALF = 2, COLINEAR = 3;
    static vector<vector<int>> create(vector<vector<int>> &points) {
        int n = points.size(); if(n <= 2) return points;
        sort(points.begin(), points.end());
        auto getPosition = [&](vector<int> p1, vector<int> p2, vector<int> p3) {
            int lhs = (p2.back() - p1.back()) * (p3.front() - p2.front());
            int rhs = (p3.back() - p2.back()) * (p2.front() - p1.front());
            if(lhs < rhs) return UPPER_HALF;
            if(lhs == rhs) return COLINEAR;
            return LOWER_HALF;
        };
        stack<vector<int>> upperHalf, lowerHalf;
        upperHalf.push(points.front());
        lowerHalf.push(points.front());
        for(int i = 1; i < n; ++i) {
            int position = getPosition(points.front(), points[i], points.back());   
            if(i == n - 1 or position != LOWER_HALF) {
                while(upperHalf.size() > 1) {
                    auto p2 = upperHalf.top(); upperHalf.pop();
                    auto p1 = upperHalf.top();
                    int position = getPosition(p1, p2, points[i]);
                    if(position == LOWER_HALF) continue;
                    upperHalf.push(p2); break;
                }
                upperHalf.push(points[i]);
            }
            if(i == n - 1 or position != UPPER_HALF) {
                while(lowerHalf.size() > 1)  {
                    auto p2 = lowerHalf.top(); lowerHalf.pop();
                    auto p1 = lowerHalf.top();
                    int position = getPosition(p1, p2, points[i]);
                    if(position == UPPER_HALF) continue;
                    lowerHalf.push(p2); break;
                }
                lowerHalf.push(points[i]);
            }
        }
        set<vector<int>> result;
        while(upperHalf.size()) { result.insert(upperHalf.top()); upperHalf.pop(); }
        while(lowerHalf.size()) { result.insert(lowerHalf.top()); lowerHalf.pop(); }
        return vector<vector<int>>(result.begin(), result.end());
    }
};
