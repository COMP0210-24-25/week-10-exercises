add_executable(HashCracking HashCracking.cpp RubbishHash.cpp)
target_include_directories(HashCracking PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(HashCracking PUBLIC MPI::MPI_CXX)

add_executable(SyncHashCracking SynchronousHashCracking.cpp RubbishHash.cpp)
target_include_directories(SyncHashCracking PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(SyncHashCracking PUBLIC MPI::MPI_CXX)

add_executable(AsyncHashCracking AsynchronousHashCracking.cpp RubbishHash.cpp)
target_include_directories(AsyncHashCracking PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(AsyncHashCracking PUBLIC MPI::MPI_CXX)
