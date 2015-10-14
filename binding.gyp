{
  "targets": [
    {
      "target_name": "NodeActiveTickAddon",
      "sources": [  "NodeActiveTickAddon.cpp",
                    "NodeActiveTick.cpp",
                    "Requestor.cpp",
                    "import/atfeed-cppsdk/example/Helper.cpp",
                    "AtEnumConverter.cpp",
                    "protobuf/messages.pb.cc"
                 ],
      'include_dirs': [
        './import/atfeed-cppsdk/include/',
        "<!(node -e \"require('nan')\")"
      ],
      "cflags":  ['-c -O3 -ffast-math -fexpensive-optimizations -DNDEBUG -fexceptions -std=c++11'],
      "cflags_cc": ['-c -O3 -ffast-math -fexpensive-optimizations -DNDEBUG -fexceptions'],
      'cflags!': [ '-fno-rtti' ],
      'cflags_cc!': [ '-fno-rtti' ],
      'conditions': [
        ['OS=="mac"', {
          'xcode_settings': {
            'MACOSX_DEPLOYMENT_TARGET': '10.11',
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
            'GCC_ENABLE_CPP_RTTI': 'YES',
            'OTHER_CPLUSPLUSFLAGS': [
                    ],
            'OTHER_CFLAGS': [
                      '<!@(pkg-config --cflags protobuf)'
                    ],
            'OTHER_LDFLAGS': [
                     ]
          },
          'link_settings': {
            'libraries': [
              '../import/atfeed-cppsdk/bin/libActiveTickServerAPI.dylib',
              '-lpthread',
              '-D_THREAD_SAFE',
              '<!@(pkg-config --libs protobuf)'
              '-Wl,-rpath,./libActiveTickServerAPI.dylib'
            ]
          }
        }],
        ['OS=="linux"', {
          'link_settings': {
            'ldflags': [
            ],
            'libraries': [
              '../import/atfeed-cppsdk/bin/libActiveTickServerAPI.so',
              '-lpthread',
              '<!@(pkg-config --libs protobuf)'
            ]
          }
        }],
      ]
    }
  ]
}
