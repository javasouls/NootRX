// Copyright © 2023-2024 ChefKiss. Licensed under the Thou Shalt Not Profit License version 1.5.
// See LICENSE for details.

#pragma once
#include "AMDCommon.hpp"
#include "ObjectField.hpp"
#include <Headers/kern_patcher.hpp>
#include <Headers/kern_util.hpp>

class HWLibs {
    static HWLibs *callback;

    public:
    void init();
    bool processKext(KernelPatcher &patcher, size_t id, mach_vm_address_t slide, size_t size);

    private:
    ObjectField<UInt8 *> pspCommandDataField {};

    mach_vm_address_t orgPspCmdKmSubmit {0};
    mach_vm_address_t orgSmu1107SendMessageWithParameter {0};

    static const char *wrapGetMatchProperty(void);
    static CAILResult wrapPspCmdKmSubmit(void *ctx, void *cmd, void *outData, void *outResponse);
    static CAILResult wrapSmu1107SendMessageWithParameter(void *smum, UInt32 msgId, UInt32 param);
};

//------ Patterns ------//

static const UInt8 kDeviceTypeTablePattern[] = {0x60, 0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0x68, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x62, 0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x68, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x64, 0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x67, 0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const UInt8 kCailAsicCapsTableHWLibsPattern[] = {0x6E, 0x00, 0x00, 0x00, 0x98, 0x67, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00};

static const UInt8 kCAILAsicCapsInitTablePattern[] = {0x6E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x98, 0x67, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00};

static const UInt8 kDeviceCapabilityTblPattern[] = {0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x73, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xCA, 0xAD, 0xDE, 0x00, 0x00,
    0x00, 0x00, 0xFE, 0xCA, 0xAD, 0xDE, 0x00, 0x00, 0x00, 0x00};

static const UInt8 kPspCmdKmSubmitPattern[] = {0x55, 0x48, 0x89, 0xE5, 0x41, 0x57, 0x41, 0x56, 0x41, 0x55, 0x41, 0x54,
    0x53, 0x50, 0x49, 0x89, 0xCD, 0x49, 0x89, 0xD7, 0x49, 0x89, 0xF4, 0x48, 0x89, 0xFB, 0x48, 0x8D, 0x75, 0xD0, 0xC7,
    0x06, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00};
static const UInt8 kPspCmdKmSubmitMask[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00};

static const UInt8 kPspCmdKmSubmitPattern14_4[] = {0x55, 0x48, 0x89, 0xE5, 0x41, 0x57, 0x41, 0x56, 0x41, 0x55, 0x41,
    0x54, 0x53, 0x48, 0x83, 0xEC, 0x18, 0x49, 0x89, 0xCD, 0x49, 0x89, 0xD7, 0x49, 0x89, 0xF4, 0x49, 0x89, 0xFE, 0x48,
    0x8D, 0x75, 0xD0, 0xC7, 0x06, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00};
static const UInt8 kPspCmdKmSubmitMask14_4[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00};

static const UInt8 kSmu1107SendMessageWithParameterPattern[] = {0x55, 0x48, 0x89, 0xE5, 0x41, 0x57, 0x41, 0x56, 0x41,
    0x54, 0x53, 0x41, 0x89, 0xD6, 0x41, 0x89, 0xF7, 0x48, 0x89, 0xFB, 0x8B, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x48, 0x8D,
    0x35};
static const UInt8 kSmu1107SendMessageWithParameterPatternMask[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF};
static const UInt8 kSmu1107SendMessageWithParameterPattern14_4[] = {0x55, 0x48, 0x89, 0xE5, 0x41, 0x57, 0x41, 0x56,
    0x41, 0x54, 0x53, 0x89, 0xD3, 0x41, 0x89, 0xF6, 0x49, 0x89, 0xFF, 0x8B, 0x8F, 0x00, 0x00, 0x00, 0x00};
static const UInt8 kSmu1107SendMessageWithParameterPatternMask14_4[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF};

static const UInt8 kCosReadConfigurationSettingPattern[] = {0x55, 0x48, 0x89, 0xE5, 0x41, 0x57, 0x41, 0x56, 0x41, 0x54,
    0x53, 0x48, 0x85, 0xF6, 0x74, 0x00, 0x40, 0x89, 0xD0};
static const UInt8 kCosReadConfigurationSettingPatternMask[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xF0, 0xFF, 0xF0};

//------ Patches ------//

// Replace call in `_gc_sw_init` to `_gc_get_hw_version` with constant (0x0A0304).
static const UInt8 kGcSwInitOriginal[] = {0x7B, 0x0C, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x41, 0x89, 0xC7};
static const UInt8 kGcSwInitOriginalMask[] = {0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF};
static const UInt8 kGcSwInitPatched[] = {0x00, 0x00, 0xB8, 0x04, 0x03, 0x0A, 0x00, 0x00, 0x00, 0x00};
static const UInt8 kGcSwInitPatchedMask[] = {0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00};

// Replace call in `_gc_set_fw_entry_info` to `_gc_get_hw_version` with constant (0x0A0304).
static const UInt8 kGcSetFwEntryInfoOriginal[] = {0xE8, 0x00, 0x00, 0x00, 0x00, 0x31, 0x00, 0x41, 0x89, 0x00, 0x10,
    0x41, 0x89, 0x00, 0x00, 0x00};
static const UInt8 kGcSetFwEntryInfoOriginalMask[] = {0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF,
    0xFF, 0xFF, 0x00, 0x00, 0x00};
static const UInt8 kGcSetFwEntryInfoPatched[] = {0xB8, 0x04, 0x03, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00};
static const UInt8 kGcSetFwEntryInfoPatchedMask[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00};
static const UInt8 kGcSetFwEntryInfoOriginal14_4[] = {0xE8, 0x00, 0x00, 0x00, 0x00, 0x45, 0x31, 0xFF, 0x45, 0x89, 0x7E,
    0x10};
static const UInt8 kGcSetFwEntryInfoOriginalMask14_4[] = {0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF};
static const UInt8 kGcSetFwEntryInfoPatched14_4[] = {0xB8, 0x04, 0x03, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00};
static const UInt8 kGcSetFwEntryInfoPatchedMask14_4[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00};

// `_psp_sw_init`: Force `pIn->pspVerMinor == 0x5` path.
static const UInt8 kPspSwInit1Original[] = {0x8B, 0x43, 0x10, 0x83, 0xF8, 0x05, 0x74, 0x00, 0x85, 0xC0};
static const UInt8 kPspSwInit1OriginalMask[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF};
static const UInt8 kPspSwInit1Patched[] = {0x66, 0x90, 0x66, 0x90, 0x66, 0x90, 0xEB, 0x00, 0x00, 0x00};
static const UInt8 kPspSwInit1PatchedMask[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00};
static const UInt8 kPspSwInit1Original14_4[] = {0x41, 0x8B, 0x46, 0x0C, 0x83, 0xF8, 0x05, 0x74, 0x00, 0x85, 0xC0};
static const UInt8 kPspSwInit1OriginalMask14_4[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF};
static const UInt8 kPspSwInit1Patched14_4[] = {0x66, 0x90, 0x66, 0x90, 0x66, 0x90, 0x90, 0xEB, 0x00, 0x00, 0x00};
static const UInt8 kPspSwInit1PatchedMask14_4[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00};

// `_psp_sw_init`: Force `pIn->pspVerPatch == 0x0` path.
static const UInt8 kPspSwInit2Original[] = {0x83, 0x7B, 0x14, 0x00, 0x74, 0x00, 0x41};
static const UInt8 kPspSwInit2OriginalMask[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF};
static const UInt8 kPspSwInit2Patched[] = {0x66, 0x90, 0x66, 0x90, 0xEB, 0x00, 0x00};
static const UInt8 kPspSwInit2PatchedMask[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00};
static const UInt8 kPspSwInit2Original14_4[] = {0x41, 0x83, 0x7E, 0x10, 0x00, 0x74, 0x00, 0xC7, 0x83};
static const UInt8 kPspSwInit2OriginalMask14_4[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF};
static const UInt8 kPspSwInit2Patched14_4[] = {0x66, 0x90, 0x66, 0x90, 0x90, 0xEB, 0x00, 0x00, 0x00};
static const UInt8 kPspSwInit2PatchedMask14_4[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00};

// `_psp_sw_init`: Set field `0x7???` to `0xE`.
static const UInt8 kPspSwInit3Original[] = {0x41, 0xC7, 0x84, 0x24, 0x00, 0x70, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00};
static const UInt8 kPspSwInit3OriginalMask[] = {0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
static const UInt8 kPspSwInit3Patched[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00};
static const UInt8 kPspSwInit3PatchedMask[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00};
static const UInt8 kPspSwInit3Original14_4[] = {0xC7, 0x83, 0x94, 0x7D, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0xE9};
static const UInt8 kPspSwInit3Patched14_4[] = {0xC7, 0x83, 0x94, 0x7D, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0xE9};

// Skip check for firmware version in `_smu_11_0_7_check_fw_version`.
static const UInt8 kSmu1107CheckFwVersionOriginal[] = {0x83, 0xFE, 0x40, 0x75, 0x00, 0xEB, 0x00};
static const UInt8 kSmu1107CheckFwVersionOriginalMask[] = {0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00};
static const UInt8 kSmu1107CheckFwVersionPatched[] = {0x66, 0x90, 0x66, 0x90, 0x90, 0x00, 0x00};
static const UInt8 kSmu1107CheckFwVersionPatchedMask[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00};

// Ditto for 11.0, X6800.
static const UInt8 kSmu1107CheckFwVersionNavi21Original[] = {0x83, 0xF9, 0x3E, 0x74, 0x00, 0xEB, 0x00};
static const UInt8 kSmu1107CheckFwVersionNavi21OriginalMask[] = {0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00};
static const UInt8 kSmu1107CheckFwVersionNavi21Patched[] = {0x90, 0x90, 0x90, 0xEB, 0x00, 0x00, 0x00};
static const UInt8 kSmu1107CheckFwVersionNavi21PatchedMask[] = {0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00};

// Ditto for 12.0+, X6800.
static const UInt8 kSmu1107CheckFwVersionNavi21Original_12[] = {0x83, 0xF9, 0x40, 0x74, 0x00, 0xEB, 0x00};
static const UInt8 kSmu1107CheckFwVersionNavi21OriginalMask_12[] = {0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0x00};
static const UInt8 kSmu1107CheckFwVersionNavi21Patched_12[] = {0x90, 0x90, 0x90, 0xEB, 0x00, 0x00, 0x00};
static const UInt8 kSmu1107CheckFwVersionNavi21PatchedMask_12[] = {0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00};

// Ventura cleaned up some code and removed support for SDMA 5.2.2, force 5.2.4 route.
static const UInt8 kSdmaInitFunctionPointerOriginal[] = {0x00, 0x00, 0x00, 0x41, 0x83, 0xFE, 0x04, 0x75, 0x00};
static const UInt8 kSdmaInitFunctionPointerOriginalMask[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00};
static const UInt8 kSdmaInitFunctionPointerPatched[] = {0x00, 0x00, 0x00, 0x66, 0x90, 0x66, 0x90, 0x66, 0x90};
static const UInt8 kSdmaInitFunctionPointerOriginal14_4[] = {0xB8, 0x02, 0x00, 0x00, 0x00, 0x83, 0xF9, 0x04, 0x75,
    0x00};
static const UInt8 kSdmaInitFunctionPointerOriginalMask14_4[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00};
static const UInt8 kSdmaInitFunctionPointerPatched14_4[] = {0xB8, 0x02, 0x00, 0x00, 0x00, 0x66, 0x90, 0x66, 0x90, 0x90};

// Enable all MCIL debug prints (debugLevel = 0xFFFFFFFF, mostly for PP_Log).
static const UInt8 kAtiPowerPlayServicesConstructorOriginal[] = {0x8B, 0x40, 0x60, 0x48, 0x8D};
static const UInt8 kAtiPowerPlayServicesConstructorPatched[] = {0x83, 0xC8, 0xFF, 0x48, 0x8D};

// Enable printing of all PSP event logs
static const UInt8 kAmdLogPspOriginal[] = {0x83, 0x00, 0x02, 0x0F, 0x85, 0x00, 0x00, 0x00, 0x00, 0x41, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x83, 0x00, 0x02, 0x72, 0x00, 0x41, 0x00, 0x00, 0x09, 0x02, 0x18, 0x00, 0x74, 0x00, 0x41, 0x00,
    0x00, 0x01, 0x06, 0x10, 0x00, 0x0f, 0x85, 0x00, 0x00, 0x00, 0x00};
static const UInt8 kAmdLogPspOriginalMask[] = {0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF,
    0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00};
static const UInt8 kAmdLogPspPatched[] = {0x66, 0x90, 0x66, 0x90, 0x66, 0x90, 0x66, 0x90, 0x66, 0x90, 0x66, 0x90, 0x66,
    0x90, 0x66, 0x90, 0x66, 0x90, 0x66, 0x90, 0x66, 0x90, 0x66, 0x90, 0x66, 0x90, 0x66, 0x90, 0x66, 0x90, 0x66, 0x90,
    0x66, 0x90, 0x66, 0x90, 0x66, 0x90, 0x66, 0x90, 0x66, 0x90, 0x90};
