#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    // TODO 2: Use the m_Model.FindClosestNode method to find the closest nodes to the starting and ending coordinates.
    // Store the nodes you find in the RoutePlanner's start_node and end_node attributes.

}


// TODO 3: Implement the CalculateHValue method.
// Tips:
// - You can use the distance to the end_node for the h value.
// - Node objects have a distance method to determine the distance to another node.

float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {

}


// TODO 4: Complete the AddNeighbors method to expand the current node by adding all unvisited neighbors to the open list.
// Tips:
// - Use the FindNeighbors() method of the current_node to populate current_node.neighbors vector with all the neighbors.
// - For each node in current_node.neighbors, set the parent, the h_value, the g_value. 
// - Use CalculateHValue below to implement the h-Value calculation.
// - For each node in current_node.neighbors, add the neighbor to open_list and set the node's visited attribute to true.

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {

}


// TODO 5: Complete the NextNode method to sort the open list and return the next node.
// Tips:
// - Sort the open_list according to the sum of the h value and g value.
// - Create a pointer to the node in the list with the lowest sum.
// - Remove that node from the open_list.
// - Return the pointer.

RouteModel::Node *RoutePlanner::NextNode() {

}


// TODO 6: Complete the ConstructFinalPath method to return the final path found from your A* search.
// Tips:
// - This method should take the current (final) node as an argument and iteratively follow the 
//   chain of parents of nodes until the starting node is found.
// - For each node in the chain, add the distance from the node to its parent to the distance variable.
// - The returned vector should be in the correct order: the start node should be the first element
//   of the vector, the end node should be the last element.

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;

    // TODO: Implement your solution here.

    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    return path_found;

}


// TODO 7: Write the A* Search algorithm here.
// Tips:
// - Use the AddNeighbors method to add all of the neighbors of the current node to the open_list.
// - Use the NextNode() method to sort the open_list and return the next node.
// - When the search has reached the end_node, use the ConstructFinalPath method to return the final path that was found.
// - Store the final path in the m_Model.path attribute before the method exits. This path will then be displayed on the map tile.

void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;

    // TODO: Implement your solution here.

}



/****************************srt comment begine*******************************************
21
00:01:12,980 --> 00:01:16,290
Now let's have a look at route_planner.cpp.

22
00:01:16,290 --> 00:01:20,469
Route_planner.cpp starts with the definition of the class constructor.

23
00:01:20,469 --> 00:01:22,929
In this constructor we take the start x,

24
00:01:22,930 --> 00:01:24,625
start y, end x,

25
00:01:24,625 --> 00:01:30,129
and end y coordinates and multiply them by 0.01 to convert them to percentages.

26
00:01:30,129 --> 00:01:32,259
Start x, start y, end x,

27
00:01:32,260 --> 00:01:36,490
and end y are given by the user input in the range 0-100.

28
00:01:36,489 --> 00:01:38,979
We want to multiply them to convert them to

29
00:01:38,980 --> 00:01:42,895
percentages to be able to use them in m_Model.FindClosestNode.

30
00:01:42,894 --> 00:01:46,289
Your first to-do in this file is to use

31
00:01:46,290 --> 00:01:51,370
m_Model.FindClosestNode to find the closest nodes to the starting and ending coordinates.

32
00:01:51,370 --> 00:01:53,469
You want to store these nodes in

33
00:01:53,469 --> 00:01:57,409
the route planner as a start node and end node attributes.

34
00:01:57,409 --> 00:02:01,869
Your next to-do is to implement the CalculateHValue method.

35
00:02:01,870 --> 00:02:06,544
You can use the distance functions for nodes to determine

36
00:02:06,543 --> 00:02:12,659
the distance from the node to the end node and that should give you the h value.

37
00:02:13,550 --> 00:02:17,100
To-do four is to complete the AddNeighbors method.

38
00:02:17,099 --> 00:02:19,379
There are instructions here for doing that.

39
00:02:19,379 --> 00:02:22,280
To-do five is to complete the next node method

40
00:02:22,280 --> 00:02:25,360
which will sort the open_list and return the next node.

41
00:02:25,360 --> 00:02:27,410
To-do six is to complete

42
00:02:27,409 --> 00:02:29,599
the construct final path method which will return

43
00:02:29,599 --> 00:02:32,329
the final path found from your AStarSearch.

44
00:02:32,330 --> 00:02:36,485
There's some code already written for you in the ConstructFinalPath method.

45
00:02:36,485 --> 00:02:39,515
We start by setting distance equal to zero

46
00:02:39,514 --> 00:02:43,714
and creating a vector of nodes called the path_found.

47
00:02:43,715 --> 00:02:46,115
When you call ConstructFinalPath,

48
00:02:46,115 --> 00:02:49,580
it should be called with the current node as the final node in the search.

49
00:02:49,580 --> 00:02:54,080
Your job is to iterate through the parents of each node.

50
00:02:54,080 --> 00:02:55,715
So once you have the final node,

51
00:02:55,715 --> 00:02:58,474
you will look for the parent of that node,

52
00:02:58,474 --> 00:03:00,514
and then the parent of that node,

53
00:03:00,514 --> 00:03:02,164
and then the parent of the node before that.

54
00:03:02,164 --> 00:03:05,209
Each node you find you'll record in path_pound.

55
00:03:05,210 --> 00:03:08,629
If you're pushing these nodes onto the back path_found,

56
00:03:08,629 --> 00:03:10,294
then when you end,

57
00:03:10,294 --> 00:03:12,469
the vector of nodes will be in the wrong order so

58
00:03:12,469 --> 00:03:15,275
you'll need to reverse the vector before you return it.

59
00:03:15,275 --> 00:03:17,885
Afterwards on line 66,

60
00:03:17,884 --> 00:03:21,424
distance is multiplied by model metric scale.

61
00:03:21,425 --> 00:03:25,520
So at each iteration of this searching for the parent of

62
00:03:25,520 --> 00:03:29,430
the nodes you're recording the distance from each node,

63
00:03:29,430 --> 00:03:31,300
you're adding to the distance here.

64
00:03:31,300 --> 00:03:36,590
When you're done, we want to multiply by this value metric scale which

65
00:03:36,590 --> 00:03:39,125
converts the scale of these nodes

66
00:03:39,125 --> 00:03:43,259
into meters that we can display at the end of the program.

67
00:03:43,520 --> 00:03:47,990
To-do seven is to write the AStarSearch algorithm.

68
00:03:47,990 --> 00:03:52,520
So here you will implement the while loop that loops as long

69
00:03:52,520 --> 00:03:57,990
as the open list is not empty and you'll use all of the methods from above.

*************************************srt comment end*************************************/
