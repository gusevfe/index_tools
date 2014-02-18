cmake_minimum_required(VERSION 2.8.4)

include(ExternalProject)

# Seqan stuff
ExternalProject_Add(seqan
  URL http://packages.seqan.de/seqan-library/seqan-library-1.4.1.tar.bz2
  SOURCE_DIR "${CMAKE_BINARY_DIR}/seqan"
  BINARY_DIR "${CMAKE_BINARY_DIR}/seqan"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""  
  ) 

add_definitions(-DSEQAN_HAS_ZLIB)

include_directories(${CMAKE_BINARY_DIR}/seqan/include)

add_executable(index_stats index_stats.cpp)
target_link_libraries(index_stats z)
add_dependencies(index_stats seqan)

add_executable(select_indices_from_single_reads select_indices_from_single_reads.cpp)
target_link_libraries(select_indices_from_single_reads z)
add_dependencies(select_indices_from_single_reads seqan)
