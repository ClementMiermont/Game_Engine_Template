# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\GAME_ENGINE_TEMPLATE_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\GAME_ENGINE_TEMPLATE_autogen.dir\\ParseCache.txt"
  "GAME_ENGINE_TEMPLATE_autogen"
  )
endif()
