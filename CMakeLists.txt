cmake_minimum_required(VERSION 3.9)
project(DZ04)

set(CMAKE_CXX_STANDARD 98)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")

add_executable(DZ04 main.cpp GameWorld.cpp GameWorld.h BaseGameEntity.h Vector2D.h utils.h MovingEntity.h Vehicle.cpp Vehicle.h SteeringBehaviors.cpp SteeringBehaviors.h geometry.h Matrix.h opengl_helpers.h Path.cpp Path.h Obstacle.cpp Obstacle.h Graph.cpp Graph.h GraphNode.h MapNode.cpp MapNode.h MapHelpers.h globals.h Map.cpp Map.h GraphEdge.h AStar.cpp AStar.h)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})

target_link_libraries(DZ04 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})