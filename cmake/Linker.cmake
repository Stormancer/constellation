macro(constellation_configure_linker project_name)
  set(constellation_USER_LINKER_OPTION
    "DEFAULT"
      CACHE STRING "Linker to be used")
    set(constellation_USER_LINKER_OPTION_VALUES "DEFAULT" "SYSTEM" "LLD" "GOLD" "BFD" "MOLD" "SOLD" "APPLE_CLASSIC" "MSVC")
  set_property(CACHE constellation_USER_LINKER_OPTION PROPERTY STRINGS ${constellation_USER_LINKER_OPTION_VALUES})
  list(
    FIND
    constellation_USER_LINKER_OPTION_VALUES
    ${constellation_USER_LINKER_OPTION}
    constellation_USER_LINKER_OPTION_INDEX)

  if(${constellation_USER_LINKER_OPTION_INDEX} EQUAL -1)
    message(
      STATUS
        "Using custom linker: '${constellation_USER_LINKER_OPTION}', explicitly supported entries are ${constellation_USER_LINKER_OPTION_VALUES}")
  endif()

  set_target_properties(${project_name} PROPERTIES LINKER_TYPE "${constellation_USER_LINKER_OPTION}")
endmacro()
