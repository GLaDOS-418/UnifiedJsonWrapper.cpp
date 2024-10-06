#
# add clang-tidy
#

# to use clang-tidy, make sure it's installed in the system
find_program(CLANGTIDY clang-tidy)

if(CLANGTIDY)
  # do not clutter the output with throwing warnings for unknowsn items. e.g.
  # warning: unknown warning option '-Wunrecognized-warning'; did you mean
  # '-Wrecognized-warning'?
  set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY})
endif()

#
# add include-what-you-use
#
# to use include-what-you-use, make sure it's installed in the system
# NOTE: disable this for now.
# find_program(IWYU include-what-you-use)

if(IWYU)
  set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "include-what-you-use")
endif()
