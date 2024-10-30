# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\OOPLAB10_11_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\OOPLAB10_11_autogen.dir\\ParseCache.txt"
  "OOPLAB10_11_autogen"
  )
endif()
