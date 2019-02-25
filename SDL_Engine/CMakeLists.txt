aux_source_directory(. SRCFILES)

include_directories(${SDL2_INCLUDE_DIR})

add_library(SDL_Engine STATIC ${SRCFILES})


set_target_properties(SDL_Engine
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        )
        
target_link_libraries(SDL_Engine z pugixml ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})
