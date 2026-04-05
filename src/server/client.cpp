#include "client.hpp"
#include "packets/pingpacket.hpp"
#include <iostream>
#include <network/packet.hpp>
#include <packets/handshakepacket.hpp>
#include <packets/statusresponsepacket.hpp>
#include <server/server.hpp>

Client::Client(int fd, Network* network) : fd(fd), state(ClientState::HANDSHAKING), network(network), shouldDisconnect(false) {}
Client::~Client() {}

void Client::update() {
    switch (state) {
        case ClientState::HANDSHAKING: handleHandshake(); break;
        case ClientState::WAITING_FOR_SLP: sendSLP(); break;
        case ClientState::PINGING: respondPing(); break;
    }
}

void Client::handleHandshake() {
    Packet p = Packet::recv(*network, fd);
    if (p.id != 0) return;

    HandshakePacket packet;
    packet.parse(p);

    if (packet.intent == 1) state = ClientState::WAITING_FOR_SLP;
}

void Client::sendSLP() {
    StatusResponsePacket packet;
    packet.version = Server::getInstance()->version;
    packet.protocolVersion = Server::getInstance()->protocolVersion;
    packet.maxPlayers = Server::getInstance()->maxPlayers;
    packet.onlinePlayers = 67;
    packet.motd = Server::getInstance()->motd;

    Packet::send(*network, fd, packet.encode());

    state = ClientState::PINGING;
}

void Client::respondPing() {
    Packet p = Packet::recv(*network, fd);
    if (p.id != 1) return;

    PingPacket packet;
    packet.parse(p);
    Packet::send(*network, fd, packet.encode());

    shouldDisconnect = true;
    network->close(fd);
}