#include <algorithm>
#include <utility> 
#include <vector>
#include <string>

using namespace std;

struct Point{
    long double x,y;
    
    Point operator+(const Point &rhs){ return Point{x + rhs.x , y + rhs.y}; }
    Point operator-(const Point &rhs){ return Point{x - rhs.x , y - rhs.y}; }
    Point operator*(const long double scalar){return Point{x * scalar , y * scalar}; }
    Point operator/(const long double scalar){return Point{x / scalar , y / scalar}; }
};

bool onSameLine_3points(Point p1, Point p2, Point p3){
    if((p1.x*p2.y + p2.x*p3.y + p3.x*p1.y) - (p1.x*p3.y + p2.x*p1.y + p3.x*p2.y) == 0){
        return true;
    }
    else{
        return false;
    }
}

struct Line{
    // Express Line by using p1 and p2.
    Point p1,p2;
    Line(Point P1 , Point P2){
        p1 = P1 , p2 = P2;
    }
};

long double dist_notsqrted(Point p1, Point p2){
    return ((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

long double cross(Line l ,Line m){
    // l:Point a,b , m:Point c,d
    Point a(l.p2 - l.p1);
    Point b(m.p2 - m.p1);
    // return (by-ay)*(dx-cx) - (dy-cy)*(bx-ax)
    return abs(a.y * b.x - b.y * a.x);
}

Point MiddlePoint(Point p1, Point p2){
    Point mp;
    mp.x = (p1.x + p2.x)/2.0;
    mp.y = (p1.y + p2.y)/2.0;
    return mp;
}

Point Centroid(Point p1, Point p2, Point p3){
    Point gp;
    // p1,p2,p3 are not on the same Line.
    gp.x = (p1.x + p2.x + p3.x) / 3.0;
    gp.y = (p1.y + p2.y + p3.y) / 3.0;
};

Point turn90(Point p){
    long double hozon = p.x;
    p.x = -p.y; p.y = p.x;
    return p;
}

pair<Point,string> Intersection(Line l , Line m){
    // Intersection of l,m.
    Point intersection;
    long double d = cross(l,m);
    long double EPS = 1e-12;
    pair<Point,string> RETURN;
    if(d < EPS){
        // l,m are Parallel.
        RETURN.first = Point{0,0};
        RETURN.second = "FAIL";
        return RETURN;
    }
    else{
        // y = ax+b
        long double al = (l.p2.y - l.p1.y) / (l.p2.x - l.p1.x);
        long double am = (m.p2.y - m.p1.y) / (m.p2.x - m.p1.x);
        long double bunbo = al-am;
        // bunbo isn't 0.
        long double bl = l.p1.y - al * l.p1.x;
        long double bm = m.p1.y - am * m.p1.x;
        long double bunsix = bm-bl;
        long double bunsiy = al*bm - bl*am;
        intersection.x = bunsix / bunbo;
        intersection.y = bunsiy / bunbo;
        RETURN.first = intersection;
        RETURN.second = "SUCCESS";
        return RETURN;
    }
}

pair<Point,string> CircumCenter(Point pa, Point pb, Point pc){
    Point cp;
    // pa,pb,pc aren't on the same Line.
    Line ab((pa+pb)/2.0 , turn90(pa));
    Line bc((pb+pc)/2.0 , turn90(pb));
    pair<Point,string> cpstatus = Intersection(ab,bc);
    return cpstatus;
}