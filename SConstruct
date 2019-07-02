
#Program('test5.cpp')

src_files = Split('test5.cpp SnakeMatrix.cpp')

#Program(source = src_files, target = 't5')

Library('SnakeMatrix', ['SnakeMatrix.cpp'])

Program('test5.cpp', LIBS=['SnakeMatrix'], LIBPATH='.')
Program('test6', 'test6.cpp', LIBPATH='.')
Program('test7', 'test7.cpp', LIBPATH='.')
