
#ifndef PBM_WRAPPER_H
#define PBM_WRAPPER_H

#include "PBM.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void* PBM;

PBM create_PBM(unsigned int width, unsigned int height);

PBM create_PBM_empty();

void destroy_PBM(PBM handle);

#ifdef __cplusplus
}
#endif




#endif //PBM_WRAPPER_H
