

set(LIB_SOURCES Netpbm.cpp Netpbm.h NetpbmUtil.h PBM.h PGM.h PPM.h
        PBM_wrapper.h PBM_wrapper.cpp)


add_library(netpbm STATIC ${LIB_SOURCES})
