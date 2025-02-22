macro(FetchRubyMinGW)
  # Mingw based ruby lib (only the dll stub library) from Ruby Installer
  # We need this for stand alone ruby bindings
  # target to use with typical ruby installations (those that are not msvc)
  # Only need this on Windows systems
  if(WIN32)
    if(NOT EXISTS ${RUBY_MINGW_LIB_DIR})
      set(RUBY_MINGW_LIB_ZIP_FILENAME "Ruby322-mingw-install.tar.gz")
      set(RUBY_MINGW_LIB_ZIP_EXPECTED_MD5 "34583cb818feff74ac50b3c140825694")

      set(RUBY_MINGW_LIB_ZIP_LOCAL_PATH "${PROJECT_BINARY_DIR}/${RUBY_MINGW_LIB_ZIP_FILENAME}")
      if(EXISTS "${RUBY_MINGW_LIB_ZIP_LOCAL_PATH}")
        file(MD5 "${RUBY_MINGW_LIB_ZIP_LOCAL_PATH}" RUBY_MINGW_LIB_ZIP_MD5)
      endif()

      if(NOT RUBY_MINGW_LIB_ZIP_MD5 STREQUAL RUBY_MINGW_LIB_ZIP_EXPECTED_MD5)
        message(STATUS "Downloading Ruby Mingw Lib: ${RUBY_MINGW_LIB_ZIP_FILENAME}")
        file(DOWNLOAD "http://openstudio-resources.s3.amazonaws.com/dependencies/${RUBY_MINGW_LIB_ZIP_FILENAME}"
          ${RUBY_MINGW_LIB_ZIP_LOCAL_PATH}
          INACTIVITY_TIMEOUT 120
          SHOW_PROGRESS
          EXPECTED_MD5 ${RUBY_MINGW_LIB_ZIP_EXPECTED_MD5})

        execute_process(COMMAND ${CMAKE_COMMAND} -E tar xfz ${RUBY_MINGW_LIB_ZIP_LOCAL_PATH} WORKING_DIRECTORY "${PROJECT_BINARY_DIR}")
      endif()
      # TODO: I botched the tar.gz, it extracts to the root of the project_binary dir
      set(RUBY_MINGW_STUB_LIB "${PROJECT_BINARY_DIR}/libx64-ucrt-ruby320.dll.a")
      # set(RUBY_MINGW_STUB_LIB "${PROJECT_BINARY_DIR}/Ruby-mingw-install/libx64-ucrt-ruby320.dll.a")
    endif()
  endif()
endmacro()
