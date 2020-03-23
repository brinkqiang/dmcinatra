
#include "dmsys.h"
#include "dmformat.h"

int main( int argc, char* argv[] ) {
    std::cout << fmt::format("{0} {1}", "hello world! ", DMSYS_MAIN(argc, argv));
    return 0;
}
