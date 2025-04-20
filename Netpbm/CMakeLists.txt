

set(LIB_SOURCES Netpbm.cpp Netpbm.h NetpbmUtil.h PBM.h PGM.h PPM.h)


add_library(netpbm STATIC ${LIB_SOURCES})
