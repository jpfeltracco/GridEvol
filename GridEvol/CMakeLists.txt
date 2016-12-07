include_directories(${PROJECT_SOURCE_DIR}/GridEvol)
include_directories(${PROJECT_SOURCE_DIR}/External/Hippocrates/Core/Sources/Headers/)
include_directories(${PROJECT_SOURCE_DIR}/External/googletest/googletest/include/)
include_directories(${PROJECT_SOURCE_DIR}/GridEvol/Sources)
include_directories(${PROJECT_SOURCE_DIR}/GridEvol/Tests)


set(ALL_SOURCES
    Sources/Controller.h
    Sources/Controller.cpp
    Sources/Norm.h
    Sources/Norm.cpp
    Sources/Simulation.h
    Sources/GridSimulation.h
    Sources/GridSimulation.cpp
    Sources/Nets.h
    Sources/HippocratesNets.h
    Sources/HippocratesNets.cpp
)

set(TEST_SOURCES
    Tests/NormTest.cpp
    Tests/EntityTest.cpp
    Tests/GridTest.cpp
    Tests/GridSimulationTest.cpp
)

add_executable(RunController Mains/RunControllerMain.cpp)
target_sources(RunController PUBLIC ${ALL_SOURCES})
target_link_libraries(RunController Hippocrates)

# Remove later!
add_executable(NNet Mains/NeuralNetMain.cpp)
target_sources(NNet PUBLIC ${ALL_SOURCES})
target_link_libraries(NNet Hippocrates)

add_executable(Tests Mains/TestMain.cpp)
target_sources(Tests PUBLIC ${ALL_SOURCES})
target_sources(Tests PUBLIC ${TEST_SOURCES})
target_link_libraries(Tests gtest)
target_link_libraries(Tests Hippocrates)
