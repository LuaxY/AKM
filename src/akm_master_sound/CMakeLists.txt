file(GLOB sources *.cpp sessions/*.cpp)
file(GLOB headers *.hpp sessions/*.hpp)

include_directories(
    ${AKM_SOURCE_DIR}/src/akm_master_sound
    ${AKM_SOURCE_DIR}/src/akm_core
)

link_directories(
    ${AKM_BINARY_DIR}/akm_core
    ${BOOST_LIB_DIR}
)

add_executable(akm_master_sound ${sources} ${headers})
target_link_libraries(akm_master_sound akm_core)