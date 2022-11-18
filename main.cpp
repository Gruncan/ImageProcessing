
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

    Netpbm::PGM inImage;
    Netpbm::importImageInto(inImage, "test2.pgm");

    std::cout << inImage << std::endl;

    inImage.invertImage();

    std::cout << "\n" << inImage << std::endl;

    Netpbm::PGM image2 = Netpbm::PGM();
    inImage.copy(image2);


    image2.invertImage();
    image2 + 2;

    std::cout << "\n" << image2;


    Netpbm::exportImage(inImage, "test3.pgm");


}

