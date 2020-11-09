/*
   Copyright (c) 2013, The Linux Foundation. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include <android-base/properties.h>
#include <android-base/logging.h>

#include "property_service.h"
#include "vendor_init.h"

using android::base::GetProperty;

void property_set(char const prop[], char const value[]) {
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (!pi)
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void property_override(char const prop[], char const value[])
{
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void property_override_triple(char const product_prop[], char const system_prop[], char const vendor_prop[], char const value[])
{
    property_override(product_prop, value);
    property_override(system_prop, value);
    property_override(vendor_prop, value);
}

void common_properties()
{
    property_override("rild.libargs", "-d /dev/smd0");
}

void cdma_properties(char const default_cdma_sub[], char const default_network[])
{
    property_override("ro.telephony.default_network", default_network);
    property_override("persist.radio.snapshot_enabled", "1");
    property_override("persist.radio.snapshot_timer", "22");
}

void gsm_properties(char const default_network[])
{
    property_override("ro.telephony.default_network", default_network);
    property_override("telephony.lteOnGsmDevice", "1");
}

void vendor_load_properties()
{
    std::string bootmid;
    std::string device;

    bootmid = GetProperty("ro.boot.mid", "");

    if (bootmid == "PN0731000") {
        /* m7vzw (m7wlv) */
        common_properties();
        cdma_properties("0", "10");
        property_override_triple("ro.product.model", "ro.product.system.model", "ro.product.vendor.model", "One");
        property_override_triple("ro.build.fingerprint", "ro.system.build.fingerprint", "ro.vendor.build.fingerprint", "htc/HTCOneVZW/m7wlv:5.0.2/LRX22G/495599.6:user/release-keys");
        property_override("ro.build.description", "6.22.605.6 CL495599 release-keys");
        property_override_triple("ro.product.device", "ro.product.system.device", "ro.product.vendor.device", "m7vzw");
        property_override("ro.build.product", "m7vzw");
        property_override("ro.telephony.get_imsi_from_sim", "true");
        property_override("ro.telephony.default_cdma_sub", "0");
        property_override("ro.ril.wp.feature", "1");
        property_override("ro.use_data_netmgrd", "true");
        property_override("telephony.lteOnCdmaDevice", "1");
        property_override("ril.subscription.types", "RUIM,NV");
        property_override("persist.radio.add_power_save", "1");
        property_override("rild.libpath", "/system/lib/libril-qc-qmi-1-vzw.so");
        property_override("vendor.rild.libpath", "/system/lib/libril-qc-qmi-1-vzw.so");
    } else if (bootmid == "PN0720000") {
        /* m7spr (m7wls) */
        common_properties();
        cdma_properties("1", "8");
        property_override_triple("ro.product.model", "ro.product.system.model", "ro.product.vendor.model", "One");
        property_override_triple("ro.build.fingerprint", "ro.system.build.fingerprint", "ro.vendor.build.fingerprint", "htc/sprint_wwe/m7wls:5.0.2/LRX22F/461956.2:user/release-keys");
        property_override("ro.build.description", "6.16.651.2 CL461956 release-keys");
        property_override_triple("ro.product.device", "ro.product.system.device", "ro.product.vendor.device", "m7spr");
        property_override("ro.build.product", "m7spr");
        property_override("telephony.sms.pseudo_multipart", "1");
        property_override("persist.radio.mode_pref_nv10", "1");
        property_override("persist.radio.dont_use_dsd", "true");
        property_override("ro.ril.scan.selection.rat", "1");
        property_override("ro.ril.set.mtusize", "1422");
        property_override("ro.ril.svdo", "true");
        property_override("ro.cdma.home.operator.numeric", "310120");
        property_override("ro.cdma.home.operator.alpha", "Sprint");
        property_override("gsm.sim.operator.alpha", "Sprint");
        property_override("gsm.sim.operator.numeric", "310120");
        property_override("gsm.sim.operator.iso-country", "us");
        property_override("gsm.operator.alpha", "Sprint");
        property_override("gsm.operator.iso-country", "us");
        property_override("rild.libpath", "/system/lib/libril-qc-qmi-1-spr.so");
        property_override("vendor.rild.libpath", "/system/lib/libril-qc-qmi-1-spr.so");
    } else {
        /* m7 */
        common_properties();
        gsm_properties("22");
        property_override_triple("ro.product.model", "ro.product.system.model", "ro.product.vendor.model", "One");
        property_override_triple("ro.build.fingerprint", "ro.system.build.fingerprint", "ro.vendor.build.fingerprint", "htc/m7_google/m7:5.1/LMY47O.H18/666675:user/release-keys");
        property_override("ro.build.description", "6.04.1700.18 CL536258 release-keys");
        property_override_triple("ro.product.device", "ro.product.system.device", "ro.product.vendor.device", "m7");
        property_override("ro.build.product", "m7");
        property_set("rild.libpath", "/system/lib/libril-qc-qmi-1-gsm.so");
        property_set("vendor.rild.libpath", "/system/lib/libril-qc-qmi-1-gsm.so");
    }

    device = GetProperty("ro.product.device", "");
    LOG(ERROR) << "Found bootmid '" << bootmid.c_str() << "' setting build properties for '" << device.c_str() << "' device\n";
}
