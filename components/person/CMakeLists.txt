set(srcs "src/Person.c" )
set(requires st7789 fontx pngle decode_png keyboardlib esp_adc driver my_board speaker)

idf_component_register(SRCS "${srcs}"
                       PRIV_REQUIRES driver
                       INCLUDE_DIRS "include"
                       REQUIRES "${requires}")
