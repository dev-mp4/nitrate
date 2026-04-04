project('nitrate', 'cpp')

executable(
    'nitrate',
    [
        'src/main.cpp',
        'src/network/windows.cpp',
        'src/network/packet.cpp',
        'src/util/util.cpp',
        'src/server/client.cpp',
        'src/server/server.cpp',

        'src/packets/handshakepacket.cpp',
        'src/packets/statusresponsepacket.cpp',
        'src/packets/pingpacket.cpp'
    ],
    include_directories: include_directories('src')
)