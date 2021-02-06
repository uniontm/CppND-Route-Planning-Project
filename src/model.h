#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <cstddef>

class Model
{
public:
    struct Node {
        double x = 0.f;
        double y = 0.f;
    };
    
    struct Way {
        std::vector<int> nodes;
    };
    
    struct Road {
        enum Type { Invalid, Unclassified, Service, Residential,
            Tertiary, Secondary, Primary, Trunk, Motorway, Footway };
        int way;
        Type type;
    };
    
    struct Railway {
        int way;
    };    
    
    struct Multipolygon {
        std::vector<int> outer;
        std::vector<int> inner;
    };
    
    struct Building : Multipolygon {};
    
    struct Leisure : Multipolygon {};
    
    struct Water : Multipolygon {};
    
    struct Landuse : Multipolygon {
        enum Type { Invalid, Commercial, Construction, Grass, Forest, Industrial, Railway, Residential };
        Type type;
    };
    
    Model( const std::vector<std::byte> &xml );
    
    auto MetricScale() const noexcept { return m_MetricScale; }    
    
    auto &Nodes() const noexcept { return m_Nodes; }
    auto &Ways() const noexcept { return m_Ways; }
    auto &Roads() const noexcept { return m_Roads; }
    auto &Buildings() const noexcept { return m_Buildings; }
    auto &Leisures() const noexcept { return m_Leisures; }
    auto &Waters() const noexcept { return m_Waters; }
    auto &Landuses() const noexcept { return m_Landuses; }
    auto &Railways() const noexcept { return m_Railways; }
    
private:
    void AdjustCoordinates();
    void BuildRings( Multipolygon &mp );
    void LoadData(const std::vector<std::byte> &xml);
    
    std::vector<Node> m_Nodes;
    std::vector<Way> m_Ways;
    std::vector<Road> m_Roads;
    std::vector<Railway> m_Railways;
    std::vector<Building> m_Buildings;
    std::vector<Leisure> m_Leisures;
    std::vector<Water> m_Waters;
    std::vector<Landuse> m_Landuses;
    
    double m_MinLat = 0.;
    double m_MaxLat = 0.;
    double m_MinLon = 0.;
    double m_MaxLon = 0.;
    double m_MetricScale = 1.f;
};


/************************************srt comment begin**********************************************
1
00:00:00,080 --> 00:00:04,080
Now let's have a look at model.h which is the header file for

2
00:00:04,080 --> 00:00:07,855
the model class which is provided by the IO 2D OpenStreetMap.

3
00:00:07,855 --> 00:00:13,230
Example, this class stores all of the OpenStreetMap data that is read into

4
00:00:13,230 --> 00:00:16,550
the program and it provides structs

5
00:00:16,550 --> 00:00:20,420
for all of the objects which you might find in the OpenStreetMap data.

6
00:00:20,420 --> 00:00:23,600
In particular, we see a struct for node, for way,

7
00:00:23,600 --> 00:00:28,765
for road, railway, and other objects that come from OpenStreetMap.

8
00:00:28,765 --> 00:00:33,480
Below that there are getter functions nodes, ways, roads,

9
00:00:33,479 --> 00:00:36,384
buildings and these return the vector of nodes,

10
00:00:36,384 --> 00:00:40,174
vector of ways, and vector of roads that are stored in the model.

11
00:00:40,174 --> 00:00:44,189
Then at the bottom of this class there are some private methods.

12
00:00:44,189 --> 00:00:45,269
AdjustCoordinates,

13
00:00:45,270 --> 00:00:49,995
adjusts the OpenStreetMap node coordinates as they read into the model.

14
00:00:49,994 --> 00:00:56,984
BuildRings is used for building objects in the OpenStreetMap model and LoadData does all

15
00:00:56,984 --> 00:01:00,259
of the heavy work of parsing the XML data and

16
00:01:00,259 --> 00:01:04,084
storing all of that data in each one of these vectors.

17
00:01:04,084 --> 00:01:06,769
So here we see the private vectors for nodes,

18
00:01:06,769 --> 00:01:08,935
ways, roads and so on,

19
00:01:08,935 --> 00:01:16,460
and some other private variables that are useful when reading the data into the model.

20
00:01:16,459 --> 00:01:20,809
The last variable metric scale is used to convert

21
00:01:20,810 --> 00:01:24,980
the scale of the model to real-life meters and we will use that later on when we

22
00:01:24,980 --> 00:01:28,730
want to compute the actual meters that we

23
00:01:28,730 --> 00:01:34,350
traverse in the path from the beginning point to the end point of our path.

**************************************end****************************************************/
