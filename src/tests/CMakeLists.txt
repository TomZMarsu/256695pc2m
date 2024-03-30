#cmake_minimum_required(VERSION 3.5)

#set(skola_TEST_SRC
#    test_cmake_demo.cpp
#)
#set(skola_TEST_HEADER
#    catch.hpp
#)

PREPEND(skola_TEST_SRC)

# Make an executable target that depends on the test source code we specified
# above.
#add_executable(TestSkola ${skola_TEST_SRC} ${skola_TEST_HEADER})

# Enable testing via CTest
#enable_testing()
# Add our test as runnable via CTest
#add_test(NAME TestCMakeDemo  COMMAND TestCMakeDemo)

# Link our unit tests against the library we compiled
#target_link_libraries(TestCMakeDemo CMakeDemo)
