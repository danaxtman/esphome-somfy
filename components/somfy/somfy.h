#pragma once

#include "somfy_switch.h"
#include "somfy_secrets.h"

class SomfyESPRemote : public Component {
 public:
  void setup() override {
    somfyRemote.begin();
  }

  void loop() override {
    somfyRemote.loop();
  }

 private:
  SomfyRemote somfyRemote = SomfyRemote(CC1101_CS_PIN, CC1101_GDO0_PIN);
};
