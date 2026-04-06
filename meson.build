project('nitrate', 'cpp')

if host_machine.system() == 'windows'
    network_impl = 'src/network/windows.cpp'
elif host_machine.system() == 'linux'
    network_impl = 'src/network/linux.cpp'
elif host_machine.system() == 'darwin'
    error('MacOS build is not supported yet!')
endif

srcs = [
    'src/main.cpp',
    'src/network/packet.cpp',
    'src/util/util.cpp',
    'src/server/client.cpp',
    'src/server/server.cpp',
    network_impl,

    'src/packets/handshakepacket.cpp',
    'src/packets/statusresponsepacket.cpp',
    'src/packets/pingpacket.cpp'
]

executable(
    'nitrate',
    srcs,
    include_directories: include_directories('src')
)