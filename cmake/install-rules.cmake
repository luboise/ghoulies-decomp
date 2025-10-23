install(
    TARGETS ghoulies_launcher_exe
    RUNTIME COMPONENT ghoulies_launcher_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
