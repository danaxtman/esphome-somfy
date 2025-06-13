#pragma once

#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"
#include <SomfyRemote.h>

// Define your CC1101 pins here
#define CC1101_CS_PIN 5
#define CC1101_GDO0_PIN 4

namespace esphome {
namespace somfy {

class SomfySwitch : public Component, public switch_::Switch {
 public:
  void set_address(uint32_t address) { this->address_ = address; }
  void set_command(uint8_t command) { this->command_ = command; }

  void setup() override {
    this->somfy_remote_.begin();
  }

  void dump_config() override {
    ESP_LOGCONFIG("somfy", "Somfy Switch:");
    ESP_LOGCONFIG("somfy", "  Address: 0x%08X", this->address_);
    ESP_LOGCONFIG("somfy", "  Command: %u", this->command_);
  }

  void write_state(bool state) override {
    if (state) {
      this->somfy_remote_.sendCommand(this->address_, this->command_);
      this->publish_state(false);
    }
  }

 protected:
  SomfyRemote somfy_remote_ = SomfyRemote(CC1101_CS_PIN, CC1101_GDO0_PIN);
  uint32_t address_;
  uint8_t command_;
};

}  // namespace somfy
}  // namespace esphome
