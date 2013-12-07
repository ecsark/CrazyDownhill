#include <iostream>
using namespace std;

template <class T>
class Line
{
public:
    T x1,y1,x2,y2;
    T rx,ry;
    Line(T x1, T y1, T x2, T y2) {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
        this->rx = x2-x1;
        this->ry = y2-y1;
    }

    //parallel=>false
    bool intersects(Line& t) {
        double C = (double)t.rx*ry-t.ry*rx;
        if(C==0)
            return false;
        double A = (double)(t.rx*t.y1 - t.ry*t.x1)*ry;
        double B = (double)t.ry*(ry*x1 - rx*y1);
        double y = (A+B)/C;
        if(y>=min(y1,y2) && y<= max(y1,y2)
        && y>=min(t.y1,t.y2) && y<=max(t.y1,t.y2)) {
            if(ry==0 || t.ry==0) { //t.ry!=0 for sure!
                double x = t.rx*(y-t.y1)/t.ry+t.x1;
                if(x>=min(x1,x2) && x<=max(x1,x2))
                    return true;
                else return false;
            }
            return true;

        }

        else return false;
    }
};
