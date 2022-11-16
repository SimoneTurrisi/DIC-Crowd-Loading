cmake -D CMAKE_BUILD_TYPE:STRING=RELEASE -D DICE_DEBUG_MSG:BOOL=ON -D CMAKE_INSTALL_PREFIX:FILEPATH=<path_to_target_install_location> -D DICE_USE_DOUBLE:BOOL=ON -D NetCDF_DIR:STRING=<path> -D HDF5_DIR:STRING=<path> -D OpenCV_DIR:STRING=<path> -D CMAKE_VERBOSE_MAKEFILE:BOOL=OFF -Wno-dev -D DICE_TRILINOS_DIR:FILEPATH=<path_to_trilinos_install> -D CLAPACK_DIR:PATH=<path_to_clapack_build> -G "NMake Makefiles" ..