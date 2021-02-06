#ifndef ROUTE_PLANNER_H
#define ROUTE_PLANNER_H

#include <iostream>
#include <vector>
#include <string>
#include "route_model.h"


class RoutePlanner {
  public:
    RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y);
    // Add public variables or methods declarations here.
    float GetDistance() const {return distance;}
    void AStarSearch();

    // The following methods have been made public so we can test them individually.
    void AddNeighbors(RouteModel::Node *current_node);
    float CalculateHValue(RouteModel::Node const *node);
    std::vector<RouteModel::Node> ConstructFinalPath(RouteModel::Node *);
    RouteModel::Node *NextNode();

  private:
    // Add private variables or methods declarations here.
    std::vector<RouteModel::Node*> open_list;
    RouteModel::Node *start_node;
    RouteModel::Node *end_node;

    float distance = 0.0f;
    RouteModel &m_Model;
};

#endif

/*************************srt beginning*************************
1
00:00:00,080 --> 00:00:04,485
Now let's have a look at the RoutePlanner header file route_planner.h.

2
00:00:04,485 --> 00:00:08,234
Here we have the RoutePlanner class definition.

3
00:00:08,234 --> 00:00:10,949
Begins with the constructor RoutePlanner which

4
00:00:10,949 --> 00:00:13,844
takes a RouteModel and then coordinate start x,

5
00:00:13,845 --> 00:00:15,419
start y, end x,

6
00:00:15,419 --> 00:00:19,980
and end y for the starting and ending x, y coordinates.

7
00:00:19,980 --> 00:00:23,339
Next there is a GetDistance method which

8
00:00:23,339 --> 00:00:28,515
returns the distance that is stored here as a private variable in the model.

9
00:00:28,515 --> 00:00:31,820
That distance will be used to store the complete distance

10
00:00:31,820 --> 00:00:35,314
of the path that you find from starting point to end point.

11
00:00:35,314 --> 00:00:39,280
After that is the declaration of the AStarSearch method.

12
00:00:39,280 --> 00:00:44,740
Then down below that on line 17 through 21 are the AddNeighbors, CalculateHValue,

13
00:00:44,740 --> 00:00:47,480
constructFinaPath, and NextNode methods

14
00:00:47,479 --> 00:00:50,979
which will all be used to conduct the AStarSearch.

15
00:00:50,979 --> 00:00:56,209
Then down at the very bottom there are private variables for the open list.

16
00:00:56,210 --> 00:00:59,240
So it's a vector of node pointers for the open_list.

17
00:00:59,240 --> 00:01:02,420
Then a pointer to the start_node,

18
00:01:02,420 --> 00:01:03,995
pointer to the end_node,

19
00:01:03,994 --> 00:01:06,765
the distance which was mentioned before,

20
00:01:06,765 --> 00:01:11,560
and then the RouteModel that we're using. 

**************************srt ending**************************/
