
#include <fstream>
#include <iostream>
#include "Netpbm/PGM.h"
#include "Netpbm/PBM.h"
#include "Netpbm/NetpbmUtil.h"

#include "Netpbm/NetPbm_wrapper.h"
#include "Netpbm/PBM_wrapper.h"

using namespace std;

int main() {
    auto* pbm = static_cast<Netpbm::PBM*>(create_PBM_empty());

    Netpbm::importImageInto(*pbm, "images/letterj.pbm");

    std::cout << *pbm << std::endl;

    pbm->invertImage();

    std::cout << *pbm << std::endl;

    // Netpbm::exportImage(pbm, "image2.ppm");


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

