#include <iostream>
#include "interface.h"
#include "straightsmodel.h"
#include <chrono>
#include <memory>

int main( int argc, char * argv[] ) {
	// use a time-based seed for the default seed value
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

        if ( argc > 1 ) {
                try {
                        seed = std::stoi( std::string{ argv[1] } );
                } catch( std::invalid_argument & e ) {
                        std::cerr << e.what() << std::endl;
                        return 1;
                } catch( std::out_of_range & e ) {
                        std::cerr << e.what() << std::endl;
                        return -1;
                } // catch
        } // if


	std::shared_ptr<StraightsModel> model = std::make_shared<StraightsModel>(seed);
	Interface view{ model };
}

