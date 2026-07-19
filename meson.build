project(
  'llvm-mos-test',
  'c',
   default_options: ['c_std=gnu23', 'warning_level=2', 'b_lto=true'],
)

cc = meson.get_compiler('c')

neslib = cc.find_library('neslib', required: true)
nesdoug = cc.find_library('nesdoug', required: true)

src_files = ['main.c', 'chr.s']

executable(
  'main.nes',
  src_files,
  c_args: ['-Oz'],
  link_args: ['-Tcommon.ld', '-Tc-in-prg-ram-0.ld', '-Tprg-rom-fixed.ld'],
  dependencies: [neslib, nesdoug],
)
