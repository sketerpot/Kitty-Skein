env = Environment()
env.Append(CCFLAGS='-O3 -mtune=core2 -Wall -I./src')

lib_sources = ['src/threefish512.c']
lib = env.SharedLibrary(target='kittyskein', source=lib_sources)
testprog = env.Program('benchmarktf512', source='test/benchmarktf512.c',
                       LIBS='kittyskein', LIBPATH='.')

Default(lib)
Default(testprog)
