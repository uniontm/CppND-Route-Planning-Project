#include <optional> //YY: 
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <io2d.h>
#include "route_model.h"
#include "render.h"
#include "route_planner.h"

using namespace std::experimental;

static std::optional<std::vector<std::byte>> ReadFile(const std::string &path) //YY: https://blog.csdn.net/ypshowm/article/details/89030194
{   
    std::ifstream is{path, std::ios::binary | std::ios::ate}; //YY: two options, binary, read the data  file as binary, not converting to any other data type. 
    if( !is )                                                 //YY: An ate stands for at the end,which means that it will immediately seek to the end of the InputStream.
                                                              //YY: The reason for doing that is that then we can use input string tellg to determine the size of the input stream,
                                                              //YY: and we can create a vector called Contents initialized to that size.
        return std::nullopt; //YY: std::nullopt is a constant of type std::nullopt_t that is used to indicate optional type with uninitialized state.
    
    auto size = is.tellg(); //YY: returns the position fo the current character in the input stream. http://www.cplusplus.com/reference/istream/istream/tellg/
    std::vector<std::byte> contents(size);    //YY: creat a 1D vector (type:byte) called contents with initialized size
    
    is.seekg(0); //YY: seek back to the beginning of the ifstream is. Then we can seek back to the beginning of the input stream.
    is.read((char*)contents.data(), size); //YY: read the stream into the contents. Read all of the input stream into the contents vector.

    if( contents.empty() )    //YY: returns whether the vector is empty. http://www.cplusplus.com/reference/vector/vector/empty/
        return std::nullopt;
    return std::move(contents); //YY: std::move: transfer the vector variable into the other variables  with pointers and references
                                //YY: When we're done, we will return the contents vector using the standard move of contents.
                                //YY: Basically, move allows you to transfer the contents of this vector to another variable without using pointers or references.
}

int main(int argc, const char **argv) //YY:  parse command line argument  parse command-line arguments.
{    
    std::string osm_data_file = ""; 
    if( argc > 1 ) {
        for( int i = 1; i < argc; ++i )
            if( std::string_view{argv[i]} == "-f" && ++i < argc ) //YY:-f is a possible command line argument which allows you to specify the osm datafile that you want to use.
                                                                  //YY: So you'll see that there's a possible command line argument of dash f,
                                                                  //YY: If you don't specify an osm datafile, then osm datafile will be set to map.osm,
                                                                  //YY: which is the data file we provide.
                osm_data_file = argv[i];
    } osm datafile that you want to use.
    else {
        std::cout << "To specify a map file use the following format: " << std::endl;
        std::cout << "Usage: [executable] [-f filename.osm]" << std::endl;
        osm_data_file = "../map.osm"; //YY: if you don't specify the osm data file, the osm data will be set to the map.osm provided by us. 
    }
    
    std::vector<std::byte> osm_data;  //YY: there's a vector of bytes called osm data
 
    if( osm_data.empty() && !osm_data_file.empty() ) { 
        std::cout << "Reading OpenStreetMap data from the following file: " <<  osm_data_file << std::endl;
        auto data = ReadFile(osm_data_file);
        if( !data )
            std::cout << "Failed to read." << std::endl;
        else
            osm_data = std::move(*data);
    }  //YY: use the ReadFile function to read the contents of this osm datafile into the vector osmdata.
    
    // TODO 1: Declare floats `start_x`, `start_y`, `end_x`, and `end_y` and get
    // user input for these values using std::cin. Pass the user input to the
    // RoutePlanner object below in place of 10, 10, 90, 90.

    //YY: Here in main is your first to do,which is to accept user input for the start_x,start_y, end_x, and end_y coordinates.
    //YY: You'll use this user input to replace these coordinates here.
    
    // Build Model.
    //YY: we create a route model object using the osm data. This route model object is called model.
    RouteModel model{osm_data};

    // Create RoutePlanner object and perform A* search.
    //YY: Then we create a route_planner object using that model and the coordinates 10, 10, 90, 90.
    //YY: 10, 10 are the x and y coordinates of the starting and 90,90 are the x and y coordinates at the ending point.
    RoutePlanner route_planner{model, 10, 10, 90, 90};
    route_planner.AStarSearch(); 
    //YY: AStarSearch, which performs the AStarSearch on the route planner and records the results in the route planner object.
    //YY: After we've created this routeplanner object, main calls routeplanner.  
    //YY: AStarSearch, which performs the AStarSearch on the route planner and records the results in the route planner object.

    std::cout << "Distance: " << route_planner.GetDistance() << " meters. \n";

    // Render results of search.
    Render render{model}; //YY: there's a random object created using the model.

    auto display = io2d::output_surface{400, 400, io2d::format::argb32, io2d::scaling::none, io2d::refresh_style::fixed, 30};
    display.size_change_callback([](io2d::output_surface& surface){
        surface.dimensions(surface.display_dimensions());
    });
    display.draw_callback([&](io2d::output_surface& surface){
        render.Display(surface);
    });
    display.begin_show();
}  //YY:some IO2D code to display the results.
