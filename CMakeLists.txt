cmake_minimum_required (VERSION 2.8) 
project (main) 

# Even though -fopenmp won’t appear in the GUI options, it does take effect
#SET(CMAKE_CXX_FLAGS “${CMAKE_CXX_FLAGS} -fopenmp”)
#SET(CMAKE_C_FLAGS “${CMAKE_C_FLAGS} -fopenmp”)

#SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++11)
ADD_DEFINITIONS("-std=c++0x -O3")

# taken from here to include openmp http://berenger.eu/blog/2011/04/06/cmake-openmp-with-cmake/
include(FindOpenMP)
if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()


#set(CMAKE_CXX_COMPILER mpicxx)
#set(CMAKE_C_COMPILER mpicc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc)
#set(CMAKE_CXX_COMPILER clang++)
#set(CMAKE_C_COMPILER clang)
#set(CMAKE_CXX_COMPILER icpc)
#set(CMAKE_C_COMPILER icc)

find_package(MPI REQUIRED)
set(CMAKE_CXX_COMPILE_FLAGS ${CMAKE_CXX_COMPILE_FLAGS} ${MPI_COMPILE_FLAGS})
set(CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} ${MPI_LINK_FLAGS})
include_directories(MPI_INCLUDE_PATH)


#There are lots of scripts with cmake
#for finding external libraries. 
#see /usr/local/share/cmake-2.6/Modules/Find*.cmake for more examples
find_package(Boost COMPONENTS mpi serialization program_options REQUIRED)
#find_package(Boost COMPONENTS program_options REQUIRED)

include_directories(${Boost_ROOT})
#include_directories(${Boost_INCLUDE_DIR})

find_package(Lua51 REQUIRED) 
include_directories( "/usr/include/lua5.1/")
#include_directories( "/global/home/users/kigumen/modules/lua/5.1.5/include/")

#find_package(Lua51 REQUIRED) 
#include_directories(${LUA_DIR}/include)
#include_directories(${LUA_INCLUDE_DIR})
#include_directories($LUA_INCLUDE_DIR)

SET(CMAKE_SOURCE_DIR ../source)


set_source_files_properties( ctags PROPERTIES GENERATED true)
add_custom_command ( OUTPUT ctags
    COMMAND ctags -R --c++-kinds=+p --fields=+iaS --extra=+q . 
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} )


add_executable(../main
  #source/lua_read.cpp
  #source/read_config.cpp
  source/o.cpp
  source/state.cpp
  #source/ran_pi.cpp
  source/p_from_n.cpp
  source/x_from_n.cpp
  source/make_wb.cpp
  source/c.cpp
  source/j.cpp
  source/make_cb.cpp
  source/make_bath.cpp
  source/make_initial_state.cpp
  source/spin_boson.cpp
  source/ode_step.cpp
  source/integrate_traj.cpp
  source/electronic_population.cpp
  source/main.cpp
  #ctags
  )


#target_link_libraries(dynamics sundials_cvode sundials_nvecserial m lapack blas gfortran quadmath)
#target_link_libraries(main ${Boost_LIBRARIES} ${GOBJECT_LIBRARIES} )
#target_link_libraries(../main ${LUA_LIBRARIES} ${Boost_LIBRARIES} ${GOBJECT_LIBRARIES} -lntl -lm -lgmp -llua5.1)
#target_link_libraries(../main ${LUA_LIBRARIES} ${Boost_LIBRARIES} ${GOBJECT_LIBRARIES})
target_link_libraries(../main ${LUA_LIBRARIES} ${Boost_LIBRARIES} ${GOBJECT_LIBRARIES} ${MPI_LIBRARIES} -lboost_mpi -lboost_serialization)


### Kirill's notes about cmake
# to compile with intel use cmake .. -DCMAKE_CXX_COMPILER=icpc -DCMAKE_CC_COMPILER=icc http://www.cmake.org/pipermail/cmake/2006-October/011635.html
# to see what make does run 'make VERBOSE=1'
