# Nitrate
## A simple, lightweight, cross-platform and fast Minecraft 1.16.5 server, written in C++ completely from scratch

### Supported platforms

Supported platforms are:
- Windows
- Linux

Other platforms are unsupported because of not implemented networking  
If you want to add support for other platforms like Android, MacOS, see `src/network/windows/linux.cpp` as reference and add your platform network implementation to `meson.build`

### TODOs and finished features

Complete features are:
- Server list info and pinging

Currently WIP features are:
- Player login

Wanted features for future:
- Full Bukkit-like plugin system
- Server network support, like BungeeCord or Velocity