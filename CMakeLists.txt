cmake_minimum_required(VERSION 3.9)
project(DZ04)

set(CMAKE_CXX_STANDARD 11)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")

add_executable(DZ04 main.cpp GameWorld.cpp GameWorld.h BaseGameEntity.cpp BaseGameEntity.h Vector2D.h Vector3D.h utils.h MovingEntity.cpp MovingEntity.h Vehicle.cpp Vehicle.h SteeringBehaviors.cpp SteeringBehaviors.h Graphics.h INIReader.h geometry.h Matrix.h opengl_helpers.h)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})

target_link_libraries(DZ04 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})