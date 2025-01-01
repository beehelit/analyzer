include(FetchContent)

FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.7.1
)

FetchContent_MakeAvailable(catch2)

include(CTest)
include(Catch)

add_subdirectory(log)



