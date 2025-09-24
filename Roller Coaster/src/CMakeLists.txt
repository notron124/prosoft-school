add_library(roller_coaster STATIC roller_coaster.cpp)

target_include_directories(roller_coaster PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/../inc
)

install(TARGETS roller_coaster
   ARCHIVE DESTINATION lib
   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   PUBLIC_HEADER DESTINATION inc/roller_coaster
)

install(DIRECTORY ../inc
   DESTINATION /
)