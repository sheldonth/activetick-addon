{
  "targets": [
    {
      "target_name": "NodeActiveTickAddon",
      "sources": [  "NodeActiveTickAddon.cpp",
                    "NodeActiveTick.cpp",
                    "import/atfeed-cppsdk/example/Helper.cpp"
                 ],
      'include_dirs': [
        './import/atfeed-cppsdk/include/',
        "<!(node -e \"require('nan')\")"
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
