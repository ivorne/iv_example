cmake_minimum_required( VERSION 3.10 )

#-------- project ---------------------------------------------------
project( game )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED True )

#--------------------------------------------------------------------
#-------- GAME target -----------------------------------------------
file( GLOB_RECURSE game_SOURCES "src/*.cpp" )

if( CMAKE_SYSTEM_NAME MATCHES "Linux" OR CMAKE_SYSTEM_NAME MATCHES "Windows" OR CMAKE_SYSTEM_NAME MATCHES "Darwin" )
	
	# standalone binary
	add_executable( game "${game_SOURCES}" )
	set_target_properties( game PROPERTIES OUTPUT_NAME game )
	
endif()

if( CMAKE_SYSTEM_NAME MATCHES "Android" )
	
	add_library( game SHARED "${game_SOURCES}" )
	
endif()

if( CMAKE_SYSTEM_NAME MATCHES "Emscripten" )
	# executable
	add_executable( game "${game_SOURCES}" )
	set( CMAKE_EXECUTABLE_SUFFIX ".html" )
	
	target_link_options( game PUBLIC "SHELL:-s DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=0" )
	target_link_options( game PUBLIC "SHELL:--shell-file ${CMAKE_CURRENT_BINARY_DIR}/shell.html.in" )
	target_link_options( game PUBLIC "SHELL:--source-map-base http://localhost:8080/" )
	target_link_options( game PUBLIC "SHELL:-s ASSERTIONS=1" )
	target_link_options( game PUBLIC "SHELL:-s TOTAL_MEMORY=65536000" )
	#target_link_options( game PUBLIC --emrun )
	
	# resources
	target_link_options( game PUBLIC "SHELL:--preload-file data" )
	
endif()

target_include_directories( game PUBLIC "src" )
target_compile_options( game PUBLIC "-Werror=undef" )
set_property( TARGET game PROPERTY IVORIUM_RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources )

#--------------------------------------------------------------------
#-------- modules ---------------------------------------------------
# ivorium
add_subdirectory( "modules/ivorium" )
target_link_libraries( game PRIVATE ivorium )

# iv_components
add_subdirectory( "modules/iv_components" )
target_link_libraries( game PRIVATE iv_components )

# iv_rctools
if( CMAKE_SYSTEM_NAME MATCHES ${CMAKE_HOST_SYSTEM_NAME} )
	add_subdirectory( "modules/iv_rctools" )

	# add resources target
	iv_rctools_target( resources ${CMAKE_CURRENT_BINARY_DIR}/data game )
	add_dependencies( game resources )
endif()

#--------------------------------------------------------------------
#-------- custom debug targets --------------------------------------
add_custom_target(
	gdb
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMAND EDITOR=/usr/bin/geany gdb -ex "set print static-members off" ./game
)

add_custom_target(
	valgrind
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-below-main=yes ./game
)

add_custom_target(
	valgrind-gdb
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMAND valgrind --vgdb=yes --vgdb-error=0 --leak-check=full --show-leak-kinds=all --track-origins=yes --show-below-main=yes ./game
)

add_custom_target(
	callgrind
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMAND valgrind --tool=callgrind ./game
)
