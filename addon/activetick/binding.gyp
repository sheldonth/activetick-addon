{
  "targets": [
    {
      "target_name": "NodeActivetickAddon",
      "sources": [ "NodeActiveTickAddon.cpp",
                    "NodeActiveTick.cpp"
                 ],
      'include_dirs': [
        './import/atfeed-cppsdk/include/'
      ],
      "cflags":  ['-c -O3 -ffast-math -fexpensive-optimizations -DNDEBUG -fexceptions'],
      "cflags_cc": ['-c -O3 -ffast-math -fexpensive-optimizations -DNDEBUG -fexceptions'],
      'cflags!': [ '-fno-rtti' ],
      'cflags_cc!': [ '-fno-rtti' ],
      'conditions': [
        ['OS=="mac"', {
          'xcode_settings': {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
          },
          'link_settings': {
            'libraries': [
              "../import/atfeed-cppsdk/bin/libActiveTickServerAPI.dylib",
              "-lpthread"
            ]
          }
        }],
        ['OS=="linux"', {
          'link_settings': {
            'libraries': [
              "../import/atfeed-cppsdk/bin/libActiveTickServerAPI.so",
              "-lpthread"
            ]
          }
        }],
      ]
    }
  ]
}
