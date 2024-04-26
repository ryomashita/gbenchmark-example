# GoogleTestを使用するためのCMakeの設定 使用方法： - testフォルタかプロジェクトルートフォルダで、
# `include(install_gtest.cmake)` を追加 - テストターゲットに `enable_gtest(<target>)` を追加する

# GoogleTestをダウンロードする
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
      DOWNLOAD_EXTRACT_TIMESTAMP OFF)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 使用する場合は、 `GTest::gtest_main` をリンクする
function(link_gtest target)
  target_link_libraries(${target} PRIVATE GTest::gtest_main)
endfunction()

# ターゲットをGoogleTestに登録する
function(register_gtest target)
  include(GoogleTest)
  gtest_discover_tests(${target})
endfunction()

# gtestのリンクと登録を一括で行う
function(enable_gtest target)
  link_gtest(${target})
  register_gtest(${target})
endfunction()
