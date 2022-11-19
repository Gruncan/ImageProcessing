
#include <fstream>
#include <iostream>
#include "Netpbm/PGM.h"
#include "Netpbm/PBM.h"
#include "Netpbm/NetpbmUtil.h"


using namespace std;

int main() {
    Netpbm::PPM ppm;

    Netpbm::importImageInto(ppm, "image.ppm");


    std::cout << ppm << std::endl;

}

void test2() {
    Netpbm::PGM pgm;

    Netpbm::importImageInto(pgm, "test.pgm");

    std::cout << pgm << std::endl << std::endl;

    Netpbm::PBM pbm = Netpbm::fromPGMToPBM(pgm);

    std::cout << std::endl << pbm;

    Netpbm::exportImage(pbm, "test111.pbm");
}


void test() {
    Netpbm::PGM image = Netpbm::PGM(5, 5);


    unsigned int array[] = {0, 3, 3, 3, 3,
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

