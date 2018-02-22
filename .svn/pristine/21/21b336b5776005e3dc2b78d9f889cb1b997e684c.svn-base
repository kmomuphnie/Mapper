#include "Ternalkdtreehelper.h"
#include "m1.h"
int kd_Cur;
bool cmp(Point a,Point b)
{
    return a.x[kd_Cur]<b.x[kd_Cur];
}
void Build(vector<Point> &p, int l,int r,int depth)
{
    if(l>=r)return;
    int mid=(l+r)>>1;
    kd_Cur= (depth&1 ) ;
    nth_element(p.begin()+l,p.begin()+mid,p.begin()+r+1,cmp);
    Build(p, l,mid-1,depth+1);
    Build(p, mid+1,r,depth+1);
}

  double kd_Dis(Point point1,Point point2 )
{
      double distance=0.0;
      double avgLat=(point1.x[1]+point2.x[1])/2*DEG_TO_RAD;
      double x1=point1.x[0]*DEG_TO_RAD*cos(avgLat),
            y1=point1.x[1]*DEG_TO_RAD;
      double x2=point2.x[0]*DEG_TO_RAD*cos(avgLat),
            y2=point2.x[1]*DEG_TO_RAD;
      double diffx=x1 - x2;
      double diffy=y1 - y2;
    distance=sqrt(diffx*diffx+diffy*diffy)*EARTH_RADIUS_IN_METERS;
    return distance ;
}
Ans  kd_Find(vector<Point> const&p,Point tar,int l,int r,int depth)
{
    int kd_Curfind= ( depth & 1) ;
    Ans  res ;
    if(l>=r)
    {
        if(l==r)
        {
            res.dd = kd_Dis(tar, p[l]) ;
            res.id = p[l].id  ;
            return res ;
        }
        res.dd = INF ;
        res.id = -1 ;
        return res ;
    }
    int mid=(l+r)>>1;
    res.dd = kd_Dis(tar, p[mid] ) ;
    res.id = p[mid].id ;
    if(res.dd <= 0 )
        return res ;
    Ans tmp ;

    if(tar.x[kd_Curfind] < p[mid].x[kd_Curfind])
    {
        tmp = kd_Find(p, tar,l,mid-1,depth+1);
        Point now ;
        now.x[kd_Curfind] = p[mid].x[kd_Curfind] ;
        now.x[kd_Curfind^1] = tar.x[kd_Curfind^1] ;
        //
        if(tmp.dd > kd_Dis(now , tar ) )
        {
            Ans temp = kd_Find(p, tar,mid+1,r,depth+1) ;
            if(tmp.dd > temp.dd )
                tmp.dd =temp.dd, tmp.id = temp.id ;
        }

    }
    else
    {
        tmp=kd_Find(p, tar,mid+1,r,depth+1);
         Point now ;
        now.x[kd_Curfind] = p[mid].x[kd_Curfind] ;
        now.x[kd_Curfind^1] = tar.x[kd_Curfind^1] ;
        //
        if(tmp.dd > kd_Dis(now , tar )   )
        {
            Ans temp = kd_Find(p, tar,l,mid-1,depth+1) ;
            if(tmp.dd > temp.dd)
                tmp.dd = temp.dd, tmp.id = temp.id ;
        }
    }
    if(res.dd > tmp.dd)
        return tmp ;
    return res ;

}
void kd_Build(vector<Point> &p )
{
    int N = p.size() ;
    Build(p, 0, N-1, 0 ) ;
}
double kd_Search(vector<Point> const&p,   double x,   double y )
{
    Point tmp ;
    tmp.x[0] = x, tmp.x[1] = y ;tmp.id = -1;
    int N = p.size() ;
    Ans rr = kd_Find( p, tmp, 0, N -1, 0) ;
    return rr.id ;
}