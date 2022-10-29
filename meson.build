project('leptjson', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

curl = dependency('libcurl')

executable('prog', 'test.c', 'leptjson.c')
executable('st', 'st.c', 'leptjson.c', 'caiyun.c', dependencies: curl)
