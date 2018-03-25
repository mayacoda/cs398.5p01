cmake_minimum_required(VERSION 3.9)
project(DZ04)

set(CMAKE_CXX_STANDARD 98)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")

add_executable(DZ04 main.cpp game-world/GameWorld.cpp game-world/GameWorld.h game-world/BaseGameEntity.h geometry/Vector2D.h helpers/utils.h game-world/MovingEntity.h character/Character.cpp character/Character.h character/SteeringBehaviors.cpp character/SteeringBehaviors.h geometry/geometry.h geometry/Matrix.h graphics/opengl_helpers.h map/Path.cpp map/Path.h game-world/Obstacle.cpp game-world/Obstacle.h map/Graph.cpp map/Graph.h map/GraphNode.h map/MapNode.cpp map/MapNode.h helpers/globals.h map/Map.cpp map/Map.h map/GraphEdge.h map/AStar.cpp map/AStar.h map/MapGraphicsHelper.h graphics/bmp-mac.cpp character/costFunctions.h character/costFunctions.cpp character/derived/Sneak.cpp character/derived/Sneak.h)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})

target_link_libraries(DZ04 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})