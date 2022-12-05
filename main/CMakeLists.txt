set(includedirs
  "."
  "../include/"
  )

set(includefiles 
  "main.c"
  "net.c"
  "mqtt.c"
  "sensors.c"
  "json.c"
  )

idf_component_register(
    SRCS ${includefiles}
    INCLUDE_DIRS  ${includedirs})