
#include "esphome.h"
#include <ELECHOUSE_CC1101_SRC_DRV.h>
#include <NVSRollingCodeStorage.h>
#include <SomfyRemote.h>

#define EMITTER_GPIO 2

#define CC1101_FREQUENCY 433.42

#define COVER_OPEN 1.0f
#define COVER_CLOSED 0.0f


class SomfySwitch : public Component, public Switch {
private:
  SomfyRemote *remote;
  Command command;

public:
  SomfySwitch(Command command, SomfyRemote *remote)
      : Switch() {
    this->remote = remote;
    this->command = command;
  }

  void write_state(bool state) override {
    if(state) {
      ELECHOUSE_cc1101.SetTx();
      remote->sendCommand(command);
      ELECHOUSE_cc1101.setSidle();
    }

    // Acknowledge new state by publishing it
    publish_state(state);
  }
};

class SomfyTarget : public Component {
private:
  SomfyRemote *remote;
  NVSRollingCodeStorage *storage;

public:
  SomfySwitch *open;
  SomfySwitch *close;
  SomfySwitch *stop;
  SomfySwitch *program;
  std::vector<esphome::switch_::Switch*> switches;

public:
  SomfyTarget(const char *name, const char *key, uint32_t remoteCode)
      : Component() {
    storage = new NVSRollingCodeStorage(name, key);
    remote = new SomfyRemote(EMITTER_GPIO, remoteCode, storage);

    open = new SomfySwitch(Command::Up, remote);
    close = new SomfySwitch(Command::Down, remote);
    stop = new SomfySwitch(Command::My, remote);
    program = new SomfySwitch(Command::Prog, remote);
    switches.push_back(open);
    switches.push_back(close);
    switches.push_back(stop);
    switches.push_back(program);
  }

};


class SomfyESPRemote : public Component {
public:
  void setup() override {
    // need to set GPIO PIN 4 as OUTPUT, otherwise no commands will be sent
    pinMode(EMITTER_GPIO, OUTPUT);
    digitalWrite(EMITTER_GPIO, LOW);

    ELECHOUSE_cc1101.Init();
    ELECHOUSE_cc1101.setMHZ(CC1101_FREQUENCY);
  }

};
