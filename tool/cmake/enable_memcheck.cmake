get_filename_component(USER_LOCAL_BIN_DIR $ENV{HOME}/.local/bin ABSOLUTE)
find_program(VALGRIND_EXECUTABLE valgrind PATHS ${USER_LOCAL_BIN_DIR})

# valgrind3.18 では clang ビルド時失敗するが, 3.22 では成功する (DWARF バージョン対応?が原因か)
function(enable_memcheck target)
  if(NOT VALGRIND_EXECUTABLE)
    message(WARNING "valgrind not found")
    return()
  endif()

  get_target_property(target_type ${target} TYPE)
  if(NOT target_type STREQUAL "EXECUTABLE")
    message(
      FATAL_ERROR "enable_memcheck() can only be used with executable targets")
  endif()

  add_custom_command(
    TARGET ${target}
    POST_BUILD
    COMMAND ${VALGRIND_EXECUTABLE} --leak-check=full --error-exitcode=1
            $<TARGET_FILE:${target}>
    # --tool=memcheck, -s は　--leak-check=full があれば不要
  )
endfunction()
