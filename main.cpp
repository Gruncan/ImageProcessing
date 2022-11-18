
#include <fstream>
#include <iostream>
#include "Netpbm/PGM.h"


using namespace std;

int main() {

    Netpbm::PGM image = Netpbm::PGM(5, 5);


    int array[] = {0, 3, 3, 3, 3,
                   0, 3, 0, 0, 0,
                   0, 3, 3, 3, 0,
                   0, 3, 0, 0, 0,
                   0, 3, 0, 0, 0};

    image.setImageArray(array);

//    std::cout << image;

    Netpbm::exportImage(image, "test.pgm");


}

