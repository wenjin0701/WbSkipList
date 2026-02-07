# SkipList CMakeLists.txt

# Add the test executable
add_executable(test_skipList test_skipList.cpp)

# Include directories
target_include_directories(test_skipList PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src/common/include
)

# Link libraries
target_link_libraries(test_skipList PRIVATE
    boost_serialization
    boost_system
)

# Set C++ standard
target_compile_features(test_skipList PRIVATE cxx_std_11)
