# This script is just a template and has to be copied and modified per project
# This script should be called from .vscode/tasks.json with
#
#   scripts/Build-Release.ps1            - for Beta builds
#   scripts/Build-Release.ps1 Release    - for Release builds
#
# {
#     "label": "Build-Release",
#     "type": "shell",
#     "command": "scripts/Build-Release.ps1 Release",
#     "args": [],
#     "problemMatcher": [],
#     "group": "test"
# },
# {
#     "label": "Build-Beta",
#     "type": "shell",
#     "command": "scripts/Build-Release.ps1 ",
#     "args": [],
#     "problemMatcher": [],
#     "group": "test"
# }

# set product names, allows mapping of (devel) name in Project to a more consistent name in release
# $settings = scripts/OpenKNX-Build-Settings.ps1

# execute generic pre-build steps
lib/OGM-Common/scripts/setup/reusable/Build-Release-Preprocess.ps1 $args[0]
if (!$?) { exit 1 }

# build firmware based on generated headerfile 
# the following build steps are project specific and must be adopted accordingly
# see comment in Build-Step.ps1 for argument description


# Example call, the following 2 lines might be there multiple times for each firmware which should be built

../OGM-Common/scripts/setup/reusable/Build-Step.ps1 release_DEVICE_PIPICO_BCU_CONNECTOR OpenKNX-PiPico-BCU-Connector rp2040-tp
if (!$?) { exit 1 }

../OGM-Common/scripts/setup/reusable/Build-Step.ps1 release_DEVICE_SEN_UP1_8XTH OpenKNX-UP1-8xSensor rp2040-tp
if (!$?) { exit 1 }

../OGM-Common/scripts/setup/reusable/Build-Step.ps1 release_DEVICE_REG1_BASE_V0 OpenKNX-REG1-Basismodul-V0 rp2040-tp
if (!$?) { exit 1 }

../OGM-Common/scripts/setup/reusable/Build-Step.ps1 release_DEVICE_REG1_BASE OpenKNX-REG1-Basismodul rp2040-tp
if (!$?) { exit 1 }

../OGM-Common/scripts/setup/reusable/Build-Step.ps1 release_DEVICE_REG1_BASE_IP OpenKNX-REG1-Basismodul-IP rp2040-ip
if (!$?) { exit 1 }

../OGM-Common/scripts/setup/reusable/Build-Step.ps1 release_DEVICE_REG1_SEN_MULTI OpenKNX-REG1-MultiSensor rp2040-tp
if (!$?) { exit 1 }

../OGM-Common/scripts/setup/reusable/Build-Step.ps1 release_DEVICE_REG1_LAN_SEN_MULTI OpenKNX-REG1-LAN-MultiSensor esp32-ip
if (!$?) { exit 1 }

../OGM-Common/scripts/setup/reusable/Build-Step.ps1 release_DEVICE_REG2_PIPICO_V1_DD_METER OpenKNX-REG2-PiPico-V1-DeviceDisplay-Meter rp2040-tp
if (!$?) { exit 1 }

../OGM-Common/scripts/setup/reusable/Build-Step.ps1 release_DEVICE_SMARTMF_2SML_3BE Smart-MF-eHZ-Schnittstelle rp2040-tp
if (!$?) { exit 1 }

../OGM-Common/scripts/setup/reusable/Build-Step.ps1 release_DEVICE_SMARTMF_1TE_BE_3CH Smart-MF-S0-Zaehlermodul rp2040-tp
if (!$?) { exit 1 }

# execute generic post-build steps
lib/OGM-Common/scripts/setup/reusable/Build-Release-Postprocess.ps1 $args[0]
if (!$?) { exit 1 }

if (Test-Path -Path release-collection -PathType Container) {
  Copy-Item release/* release-collection/
}