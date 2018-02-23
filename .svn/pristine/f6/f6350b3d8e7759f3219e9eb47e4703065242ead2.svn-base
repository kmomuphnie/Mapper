/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ternalkdtreehelper.h
 * Author: wangha78
 *
 * Created on February 21, 2018, 6:21 PM
 */

#ifndef TERNALKDTREEHELPER_H
#define TERNALKDTREEHELPER_H
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<vector>
#include<cmath>
#include<queue>
#include<stack>
#include<map>
#include<set>
#include<algorithm>
using namespace std;
//constexpr   double EARTH_RADIUS_IN_METERS = 6372797.560856;
//constexpr   double  DEG_TO_RAD = 0.017453292519943295769236907684886 ;
const   double  INF=1e15;
struct Point
{
      double x[2];
    int id ;
};
struct Ans
{
      double dd ;
    int id ;
};
bool cmp(Point a,Point b);
void Build(vector<Point> &p, int l,int r,int depth);
double kd_Dis(Point point1,Point point2 );
Ans  kd_Find(vector<Point> const&p,Point tar,int l,int r,int depth);
void kd_Build(vector<Point> &p );
unsigned kd_Search(vector<Point> const&p,   double x,   double y );
#endif /* TERNALKDTREEHELPER_H */

