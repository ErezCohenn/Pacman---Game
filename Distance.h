#pragma once
#include "ghost.h"
#include "point.h"

class Distance
{
private:
    //-----------------------------------Private Member Functions-----------------------------------------//
    int distance;
    Point adjcent_p;
    int indexGhost;

public:
    //-----------------------------------Public Member Functions-----------------------------------------//
    Distance(int _distnace, int _indexGhost, const Point& point) : distance(_distnace), indexGhost(_indexGhost) , adjcent_p(point){}

    //--------------------------------------Get Functions-----------------------------------------------//
    const Point& getPoint() const{ return adjcent_p; }
    int getDistance() const { return distance; }
    int getIndexGhost() const { return indexGhost; }

    //impliment operator '<' for priority queue: priority by distance
    friend bool operator<(Distance const& p1, Distance const& p2)
    {
        return p1.distance > p2.distance;
    }
};