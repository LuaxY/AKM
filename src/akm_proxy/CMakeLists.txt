file(GLOB sources *.cpp sessions/*.cpp)
file(GLOB headers *.hpp sessions/*.hpp)

include_directories(
    ${AKM_SOURCE_DIR}/src/akm_proxy
    ${AKM_SOURCE_DIR}/src/akm_core
)

link_directories(
    ${AKM_BINARY_DIR}/akm_core
    ${Boost_LIBRARY_DIRS}
)

add_executable(akm_proxy ${sources} ${headers})
target_link_libraries(akm_proxy akm_core ${Boost_LIBRARIES})