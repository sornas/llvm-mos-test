build target:
  make -C {{target}} -j

clean-build target:
  make -C {{target}} -B -j

retroarch target:
  just build {{target}}
  retroarch -L /usr/lib/libretro/mesen_libretro.so {{target}}/main.nes

compiledb target:
  (cd {{target}}; bear -- make -B -j)
