include_directories(${PROJECT_SOURCE_DIR}/GridEvol)
include_directories(${PROJECT_SOURCE_DIR}/External/Hippocrates/Core/Sources/Headers/)
include_directories(${PROJECT_SOURCE_DIR}/External/googletest/googletest/include/)
include_directories(${PROJECT_SOURCE_DIR}/GridEvol/Sources)
include_directories(${PROJECT_SOURCE_DIR}/GridEvol/Tests)


set(ALL_SOURCES
    Sources/Normalizable.cpp
    Sources/Normalizable.h
)

set(TEST_SOURCES
    Tests/NormalizableTest.cpp
)

add_executable(Controller Mains/Controller.cpp)
target_sources(Controller PUBLIC ${ALL_SOURCES})
target_link_libraries(Controller Hippocrates)

add_executable(Tests Mains/TestMain.cpp)
target_sources(Tests PUBLIC ${ALL_SOURCES})
target_sources(Tests PUBLIC ${TEST_SOURCES})
target_link_libraries(Tests gtest)
