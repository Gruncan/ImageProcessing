

#include "PBM_wrapper.h"
#include "PBM.h"


PBM create_PBM(unsigned int width, unsigned int height) {
    return new Netpbm::PBM(width, height);
}

PBM create_PBM_empty() {
    return new Netpbm::PBM();
}

void destroy_PBM(PBM handle) {
    delete static_cast<Netpbm::PBM*>(handle);
}



