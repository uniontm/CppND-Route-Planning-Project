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
    std::ifstream is{path, std::ios::binary | std::ios::ate}; //YY: two options, binary, not converting to any other data type. ate: at the end, see the 
    if( !is )
        return std::nullopt;
    
    auto size = is.tellg(); //YY: returns the position fo the current character in the input stream. http://www.cplusplus.com/reference/istream/istream/tellg/
    std::vector<std::byte> contents(size);    //YY: creat a 1D vector called contents with initialized size
    
    is.seekg(0); //YY: seek back to the beginning of the ifstream
    is.read((char*)contents.data(), size); //YY: read the stream into the contents

    if( contents.empty() )    //YY: returns whether the vector is empty. http://www.cplusplus.com/reference/vector/vector/empty/
        return std::nullopt;
    return std::move(contents); //YY: std::move: transfer the vector variable into the other variables ???? with pointers and references
}

int main(int argc, const char **argv)
{    
    std::string osm_data_file = ""; //YY: 
    if( argc > 1 ) {
        for( int i = 1; i < argc; ++i )
            if( std::string_view{argv[i]} == "-f" && ++i < argc )
                osm_data_file = argv[i];
    }
    else {
        std::cout << "To specify a map file use the following format: " << std::endl;
        std::cout << "Usage: [executable] [-f filename.osm]" << std::endl;
        osm_data_file = "../map.osm";
    }
    
    std::vector<std::byte> osm_data;
 
    if( osm_data.empty() && !osm_data_file.empty() ) {
        std::cout << "Reading OpenStreetMap data from the following file: " <<  osm_data_file << std::endl;
        auto data = ReadFile(osm_data_file);
        if( !data )
            std::cout << "Failed to read." << std::endl;
        else
            osm_data = std::move(*data);
    }
    
    // TODO 1: Declare floats `start_x`, `start_y`, `end_x`, and `end_y` and get
    // user input for these values using std::cin. Pass the user input to the
    // RoutePlanner object below in place of 10, 10, 90, 90.

    // Build Model.
    RouteModel model{osm_data};

    // Create RoutePlanner object and perform A* search.
    RoutePlanner route_planner{model, 10, 10, 90, 90};
    route_planner.AStarSearch();

    std::cout << "Distance: " << route_planner.GetDistance() << " meters. \n";

    // Render results of search.
    Render render{model};

    auto display = io2d::output_surface{400, 400, io2d::format::argb32, io2d::scaling::none, io2d::refresh_style::fixed, 30};
    display.size_change_callback([](io2d::output_surface& surface){
        surface.dimensions(surface.display_dimensions());
    });
    display.draw_callback([&](io2d::output_surface& surface){
        render.Display(surface);
    });
    display.begin_show();
}
