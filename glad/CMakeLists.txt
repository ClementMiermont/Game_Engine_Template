add_library(
	glad
	src/glad.c
	include/glad/glad.h
	include/KHR/khrplatform.h
)

target_include_directories(glad PUBLIC include)
set_target_properties(glad PROPERTIES PREFIX "")
set_target_properties(glad PROPERTIES OUTPUT_NAME "glad")