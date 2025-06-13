#include "switch.h"
#include "esphome/core/log.h"

using namespace esphome;

namespace esphome {
namespace somfy {

static const char *const TAG = "somfy";

void SomfySwitch::setup() {
  ESP_LOGCONFIG(TAG, "Somfy Switch setup");
  this->somfy_remote_.begin();
}

}  // namespace somfy
}  // namespace esphome

ESPHOME_SWITCH_PLATFORM_REGISTER(somfy::SomfySwitch, somfy, SomfySwitch)
