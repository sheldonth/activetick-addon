{
  "targets": [
    {
      "target_name": "NodeActivetickAddon",
      "sources": [ "NodeActivetickAddonTen.cpp"
                  ,"NodeActivetickTen.cpp"
                  ,"StdAfx.cpp"
                  ,"Session.cpp"
                  ,"Requestor.cpp"
                  ,"Streamer.cpp"
                  ,"AtJsonParserTen.cpp"
                  ,"Jsonifier.cpp"
                  ,"AtEnumConverter.cpp"
                  ,"import/atfeed-cppsdk/example/Helper.cpp"
                  ,"import/libjson/_internal/Source/JSONAllocator.cpp"
                  ,"import/libjson/_internal/Source/JSONChildren.cpp"
                  ,"import/libjson/_internal/Source/JSONIterators.cpp"
                  ,"import/libjson/_internal/Source/JSONMemory.cpp"
                  ,"import/libjson/_internal/Source/JSONNode.cpp"
                  ,"import/libjson/_internal/Source/JSONNode_Mutex.cpp"
                  ,"import/libjson/_internal/Source/JSONPreparse.cpp"
                  ,"import/libjson/_internal/Source/JSONStream.cpp"
                  ,"import/libjson/_internal/Source/JSONValidator.cpp"
                  ,"import/libjson/_internal/Source/JSONWorker.cpp"
                  ,"import/libjson/_internal/Source/JSONWriter.cpp"
                  ,"import/libjson/_internal/Source/internalJSONNode.cpp"
                  ,"import/libjson/_internal/Source/libjson.cpp"
                 ],
      'include_dirs': [
        './import/atfeed-cppsdk/include/',
        './import/atfeed-cppsdk/include/Shared/'
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
