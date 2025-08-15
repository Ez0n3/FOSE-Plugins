#pragma once
#include "fose_common/fose_version.h" // FOSE
#include "IVersionCheck.h" // Common plugin version check, found in ..\plugins_common\
// #include "../plugin_common/common.h" // EG: Common plugin functions for this sdk if needed

// ================================
// Plugin Information
// ================================

// Plugin info
#define PLUGIN_AUTHOR				"Ez0n3"					// Author of the plugin

#define PLUGIN_NAME_SHORT			"ez_fose_plugin_example"	// Plugin name without spaces
#define PLUGIN_NAME_LONG			"Ez FOSE Plugin Example"	// Plugin name with spaces

// Plugin version, Major, Minor, Build. EG: (1.0.0) equals (Major.Minor.Build)
#define PLUGIN_VERSION_MAJOR		1
#define PLUGIN_VERSION_MINOR		0
#define PLUGIN_VERSION_BUILD		0

// ================================
// Nothing below this needs changing between plugins except maybe MINIMUM_RUNTIME_VERSION and/or SUPPORTED_RUNTIME_VERSION_STRICT
// ================================

// Plugin log file
#define PLUGIN_LOG_FILE				"\\My Games\\" GAME_SAVE_FOLDER_NAME("Fallout3") "\\FOSE\\" PLUGIN_LOG_FILE_NAME(PLUGIN_NAME_SHORT) // plugin log file location

// Common definitions
#define SDK_VERSION_STRING			VERSION_TO_STRING(FOSE_VERSION_INTEGER, FOSE_VERSION_INTEGER_MINOR, FOSE_VERSION_INTEGER_BETA)
#define PLUGIN_VERSION_STRING		VERSION_TO_STRING(PLUGIN_VERSION_MAJOR, PLUGIN_VERSION_MINOR, PLUGIN_VERSION_BUILD)

#define PLUGIN_VERSION_DLL			MAKE_EXE_VERSION(PLUGIN_VERSION_MAJOR, PLUGIN_VERSION_MINOR, PLUGIN_VERSION_BUILD)
#define PLUGIN_VERSION_INFO			PLUGIN_NAME_SHORT " v%s (0x%08X) (SDK v%s)", PLUGIN_VERSION_STRING, PLUGIN_VERSION_DLL, SDK_VERSION_STRING

// ================================
// Plugin Version Information
// ================================

// The minimum runtime version allowed by the plugin. EG: I need function X, which was added in runtime Y, therefore Y is the minimum runtime version
#define MINIMUM_RUNTIME_VERSION				FALLOUT_VERSION_1_0	// The lowest version

// The runtime version the plugin was designed for
// #define SUPPORTED_RUNTIME_VERSION		CURRENT_RELEASE_RUNTIME
#define SUPPORTED_RUNTIME_VERSION			RUNTIME_VERSION // Set in /config/_Plugins.props, controls core and plugin versions - normally latest

// Strict runtime version. If strict=true, runtime and supported versions must match. If strict=false, runtime version must be above the minimum
#define SUPPORTED_RUNTIME_VERSION_STRICT	false

// The compatible runtime version - set automatically
#define COMPATIBLE(runtimeVersion)			(runtimeVersion == SUPPORTED_RUNTIME_VERSION)

// The compatible editor version
// #define SUPPORTED_RUNTIME_VERSION_CS		CS_VERSION_1_5_19 // latest editor
#define SUPPORTED_RUNTIME_VERSION_CS		CS_VERSION // Set in /config/_Plugins.props

// ================================

/*
// From fose_version.h - Note: FALLOUT_VERSION_1_0 rather than RUNTIME_VERSION_1_0 like most SDK's

#define FALLOUT_VERSION_1_0		MAKE_FALLOUT_VERSION(1, 0, 12)			// 0x010000C0
#define FALLOUT_VERSION_1_0_15	MAKE_FALLOUT_VERSION(1, 0, 15)			// 0x010000F0
#define FALLOUT_VERSION_1_1_35	MAKE_FALLOUT_VERSION(1, 1, 35)			// 0x01010230
#define FALLOUT_VERSION_1_4_6	MAKE_FALLOUT_VERSION(1, 4, 6)			// 0x01040060
#define FALLOUT_VERSION_1_4_6b	MAKE_FALLOUT_VERSION_EX(1, 4, 6, 1)		// 0x01040061
#define FALLOUT_VERSION_1_5_22	MAKE_FALLOUT_VERSION(1, 5, 22)			// 0x01050160
#define FALLOUT_VERSION_1_6		MAKE_FALLOUT_VERSION(1, 6, 3)			// 0x01060030
#define FALLOUT_VERSION_1_7		MAKE_FALLOUT_VERSION(1, 7, 3)			// 0x01070030
#define FALLOUT_VERSION_1_7ng	MAKE_FALLOUT_VERSION_EX(1, 7, 3, 1)		// 0x01070031 // ng = No Gore

#define CS_VERSION_1_1_36		MAKE_FALLOUT_VERSION(1, 1, 36)			// 0x01010240
#define CS_VERSION_1_5_19		MAKE_FALLOUT_VERSION(1, 5, 19)			// 0x01050130
*/
