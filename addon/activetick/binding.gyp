{
  "targets": [
    {
      "target_name": "NodeActiveTickAddon",
      "sources": [  "NodeActiveTickAddon.cpp",
                    "NodeActiveTick.cpp",
                    "Requestor.cpp",
                    "Streamor.cpp",
                    "import/atfeed-cppsdk/example/Helper.cpp",
                    "protobuf/messages.pb.cc"
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
            'MACOSX_DEPLOYMENT_TARGET': '10.10',
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
            'GCC_ENABLE_CPP_RTTI': 'YES',
            'OTHER_CPLUSPLUSFLAGS': [
                    ],
            'OTHER_CFLAGS': [
                      '<!@(pkg-config --cflags protobuf)'
                    ]
          },
          'link_settings': {
            'libraries': [
              '../import/atfeed-cppsdk/bin/libActiveTickServerAPI.dylib',
              '-lpthread',
              '-D_THREAD_SAFE',
              '<!@(pkg-config --libs protobuf)'
            ]
          }
        }],
        ['OS=="linux"', {
          'link_settings': {
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
