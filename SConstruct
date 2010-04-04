env = Environment()
conf = Configure(env)
env.Append(CCFLAGS='-O3 -mtune=core2 -Wall -I./src')

# Check for headers

def require_headers(headers):
    '''Go through a list of header file names, requiring them all to
    be present for the build to succeed.'''
    for header in headers:
        if not conf.CheckCHeader(header):
            print '%s not found, aborting build.'%header
            Exit(1)

require_headers(Split('stdint.h'))
env = conf.Finish()

lib_sources = ['src/threefish512.c']
lib = env.Library(target='kittyskein', source=lib_sources)
testprog = env.Program('benchmarktf512', source='test/benchmarktf512.c',
                       LIBS='kittyskein', LIBPATH='.')

Default(lib)
Default(testprog)
