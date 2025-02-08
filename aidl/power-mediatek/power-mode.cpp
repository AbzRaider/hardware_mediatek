/*
 * Copyright (C) 2023 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <aidl/android/hardware/power/BnPower.h>
#include <android-base/file.h>
#include <android-base/logging.h>
#include <unistd.h>  // for close()

namespace aidl {
namespace android {
namespace hardware {
namespace power {
namespace impl {
namespace mediatek {

using ::aidl::android::hardware::power::Mode;

bool isDeviceSpecificModeSupported(Mode type, bool* _aidl_return) {
    switch (type) {
        case Mode::DOUBLE_TAP_TO_WAKE:
            *_aidl_return = true;
            return true;
        default:
            return false;
    }
}

bool setDeviceSpecificMode(Mode type, bool enabled) {
    switch (type) {
        case Mode::DOUBLE_TAP_TO_WAKE: {
            // For Realme RM6785, write "1" or "0" to the sysfs/procfs node.
            const char* node_path = "/proc/touchpanel/double_tap_enable";
            std::string value = enabled ? "1" : "0";

            
            if (!::android::base::WriteStringToFile(value, node_path)) {
                LOG(ERROR) << "Failed to write " << value << " to " << node_path;
                return false;
            }
            return true;
        }
        default:
            return false;
    }
}

}  // namespace mediatek
}  // namespace impl
}  // namespace power
}  // namespace hardware
}  // namespace android
}  // namespace aidl
