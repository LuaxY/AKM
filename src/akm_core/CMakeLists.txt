set(sources
    akm/logger/logger.cpp
)

set(headers
    akm/logger/logger.hpp

    akm/network/server.hpp
    akm/network/session.hpp

    akm/serialization/singleton.hpp
)

add_library(akm_core ${sources} ${headers})