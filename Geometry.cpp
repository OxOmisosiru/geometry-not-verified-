#include <string>
#include <algorithm>

using namespace std;

struct Point{
    long double x,y;
};

Point operator+(const Point &p , const Point &q){ 
    Point ret;
    ret.x = p.x + q.x; ret.y = p.y + q.y;
    return ret;
}
Point operator-(const Point &p , const Point &q){ 
    Point ret;
    ret.x = p.x - q.x; ret.y = p.y - q.y;
    return ret;
}
Point operator*(const Point &p , const Point &q){ 
    Point ret;
    ret.x = p.x * q.x; ret.y = p.y * q.y;
    return ret;
}
Point operator*(const Point &p , const long double &a){ 
    Point ret;
    ret.x = p.x * a; ret.y = p.y * a;
    return ret;
}
Point operator/(const Point &p , const Point &q){ 
    Point ret;
    ret.x = p.x / q.x; ret.y = p.y / q.y;
    return ret;
}
Point operator/(const Point &p , const long double &a){ 
    Point ret;
    ret.x = p.x / a; ret.y = p.y / a;
    return ret;
}

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
    Point a = l.p2 - l.p1;
    Point b = m.p2 - m.p1;
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
    return gp;
};

Point turn90(Point p){
    long double hozon = p.x;
    p.x = -p.y; p.y = hozon;
    return p;
}

pair<Point,string> Intersection(Line l , Line m){
    /*
        THIS MAY CAUSE BUGS !
    */
    // Intersection of l,m.
    Point intersection;
    long double d = cross(l,m);
    long double EPS = 1e-10;
    pair<Point,string> RETURN;
    if(d < EPS){
        // l,m are Parallel.
        RETURN.first = Point{0,0};
        RETURN.second = "FAIL";
        return RETURN;
    }
    else{
        // y = ax+b
        //cout << l.p2.x - l.p1.x << " " << d << endl;
        if(abs(l.p2.x - l.p1.x) < EPS || abs(m.p2.x - m.p1.x) < EPS){
            // Div0
            RETURN.first = Point{0,0};
            RETURN.second = "FAIL";
            return RETURN;
        }
        long double al = (l.p2.y - l.p1.y) / (l.p2.x - l.p1.x);
        long double am = (m.p2.y - m.p1.y) / (m.p2.x - m.p1.x);
        long double bunbo = al-am;
        if(abs(bunbo) < EPS){
            // Div0
            RETURN.first = Point{0,0};
            RETURN.second = "FAIL";
            return RETURN;
        }
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

Point CircumCenter(Point pa, Point pb, Point pc){
    Point cp;
    // pa,pb,pc aren't on the same Line.
    // Reference HERE: https://en.wikipedia.org/wiki/Circumscribed_circle#Cartesian_coordinates
    long double D = 2.0*(pa.x*(pb.y-pc.y) + pb.x*(pc.y-pa.y) + pc.x*(pa.y-pb.y));
    cp.x = ((pa.x*pa.x + pa.y*pa.y)*(pb.y-pc.y) + (pb.x*pb.x + pb.y*pb.y)*(pc.y-pa.y) + (pc.x*pc.x + pc.y*pc.y)*(pa.y-pb.y)) / D;
    cp.y = ((pa.x*pa.x + pa.y*pa.y)*(pc.x-pb.x) + (pb.x*pb.x + pb.y*pb.y)*(pa.x-pc.x) + (pc.x*pc.x + pc.y*pc.y)*(pb.x-pa.x)) / D;
    return cp;
}
