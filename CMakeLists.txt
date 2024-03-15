cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Fetch SQLiteCpp
FetchContent_Declare(
  SQLiteCpp
  GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
  GIT_TAG 3.3.1
  GIT_CONFIG "core.autocrlf=false")
FetchContent_GetProperties(SQLiteCpp)

if(NOT SQLiteCpp_POPULATED)
  FetchContent_Populate(SQLiteCpp)
  add_subdirectory(${sqlitecpp_SOURCE_DIR} ${sqlitecpp_BINARY_DIR})
endif()

file(GLOB SRCS CONFIGURE_DEPENDS
  ${CMAKE_SOURCE_DIR}/src/*.cpp
  ${CMAKE_SOURCE_DIR}/src/framework/*.cpp
  ${CMAKE_SOURCE_DIR}/src/framework/exceptions/*.cpp
  ${CMAKE_SOURCE_DIR}/src/dictionary/*.cpp
  ${CMAKE_SOURCE_DIR}/src/activity/*.cpp
  ${CMAKE_SOURCE_DIR}/src/database/*.cpp
  ${CMAKE_SOURCE_DIR}/src/gui/*cpp
  ${CMAKE_SOURCE_DIR}/src/gui/template/*cpp
  ${CMAKE_SOURCE_DIR}/src/gui/button_factory/*.cpp
  ${CMAKE_SOURCE_DIR}/src/gui/textbox_factory/*.cpp
  ${CMAKE_SOURCE_DIR}/src/gui/rectangle_factory/*.cpp
)

# option(CMAKE_USE_WIN32_THREADS_INIT "using WIN32 threads" ON)
add_executable(app ${SRCS})
target_link_libraries(app PRIVATE sfml-graphics sfml-window sfml-system sfml-audio sqlite3 SQLiteCpp)

if(UNIX)
  target_link_libraries(app PRIVATE pthread dl)
endif()

target_compile_features(app PRIVATE cxx_std_17)
target_include_directories(app PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/include/framework
  ${CMAKE_SOURCE_DIR}/include/framework/exceptions
  ${CMAKE_SOURCE_DIR}/include/dictionary
  ${CMAKE_SOURCE_DIR}/include/activity
  ${CMAKE_SOURCE_DIR}/include/database
  ${CMAKE_SOURCE_DIR}/include/gui
  ${CMAKE_SOURCE_DIR}/include/gui/template
  ${CMAKE_SOURCE_DIR}/include/gui/button_factory
  ${CMAKE_SOURCE_DIR}/include/gui/textbox_factory
  ${CMAKE_SOURCE_DIR}/include/gui/rectangle_factory
)

if(WIN32)
  add_custom_command(
    TARGET app
    COMMENT "Copy OpenAL DLL"
    PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:app>
    VERBATIM)
endif()

install(TARGETS app)