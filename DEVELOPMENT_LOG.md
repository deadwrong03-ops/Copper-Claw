# Copper&Claw Development Log

## Project Overview

Copper&Claw is a standalone Guild Wars 2 Nexus Trading Post watcher.

The project began by copying the already-working Trading Post framework from FoodReminder-Nexus into a new standalone addon. The original FoodReminder-Nexus Trading Post implementation remains intact; Copper&Claw is a separate project.

Display name: `Copper&Claw`  
Filesystem/data prefix: `CopperAndClaw`  
Current development version: `0.1.0`

---

## 2026-09-03 — Standalone Project Created

Created a new Visual Studio DLL project for Copper&Claw.

Initial project name: `Copper & Claw`

Configured:

- x64
- Dynamic Library
- Platform Toolset v143
- C++17
- Multi-Byte Character Set
- `/MP`
- no precompiled headers
- Debug `/MTd`
- Release `/MT`
- Windows subsystem
- UAC disabled

Initial build issues were caused by stale ImGui source references pointing outside the standalone project. The ImGui source references were removed and re-added from the correct project-local `imgui` folder.

**Result: Release x64 build passed.**

Current generated DLL: `Copper & Claw.dll`

---

## 2026-09-03 — Trading Post Framework Extracted

Copied the working Trading Post framework from FoodReminder-Nexus into Copper&Claw.

Core files include:

- `entry.cpp`
- `Settings.h`
- `Settings.cpp`
- `TradingPostUI.h`
- `TradingPostUI.cpp`
- `TradingPostWatchManager.h`
- `TradingPostWatchManager.cpp`
- `TradingPostPriceManager.h`
- `TradingPostPriceManager.cpp`
- `TradingPostHistoryManager.h`
- `TradingPostHistoryManager.cpp`
- `TradingPostItemIndexManager.h`
- `TradingPostItemIndexManager.cpp`

Standalone persistence names were changed to:

- `CopperAndClaw.ini`
- `CopperAndClaw_TradingPostWatch.ini`
- `CopperAndClaw_TradingPostHistory.tsv`
- `CopperAndClaw_TradingPostItemIndex.tsv`

HTTP user-agent changed to `CopperAndClaw/1.0`.

---

## 2026-09-03 — Standalone Nexus Entry Point

Created a standalone `entry.cpp`.

Current addon metadata:

- Name: `Copper&Claw`
- Version: `0.1.0`
- Author: `spectre9510`
- Description: Trading Post watch/history/trends/alerts

Startup initializes Settings, Price Manager, History Manager, Item Index Manager, and Watch Manager.

Nexus render and options-render callbacks are registered. Shutdown saves settings and shuts down the Trading Post systems.

**Pre-release note:** the current Nexus addon signature is provisional and must be replaced/registered before public release.

---

## 2026-09-03 — First In-Game Standalone Test

Copper&Claw loaded successfully through Nexus.

Verified:

- addon recognized by Nexus
- Copper&Claw options panel opens
- Trading Post UI renders
- Aurene's Bite loads
- sell price populates
- buy price populates
- 60-second automatic watch cycle runs
- Trading Post item index builds successfully
- trend/history system is active

**Result: PASS**

---

## 2026-09-03 — Multiple Watch Items Tested

Added multiple items to the watch list.

Functionality worked, but the original Trading Post layout became visually cluttered when several watched items were displayed.

Decision: redesign the main watch-list display into a compact item layout.

---

## 2026-09-03 — Compact Watch-List UI

Redesigned each watched item into a compact presentation.

Changes:

- item name made more prominent
- current sell price kept visible
- current buy price kept visible
- status kept visible
- Refresh / Remove actions kept visible
- Details / History collapsed by default
- trend data moved inside Details / History
- Deal information moved inside Details / History
- Spread information moved inside Details / History
- Signal information moved inside Details / History
- charts and historical statistics moved inside Details / History

The same compact layout was also ported back into FoodReminder-Nexus.

**Result: PASS**

---

## 2026-09-03 — Sell Target Visibility Fix

After the compact redesign, the Sell Target controls were still functional but had been moved inside the collapsed Details / History section.

Changed the compact main item row to keep the Sell Target gold/silver/copper controls directly visible. The duplicate target editor inside Details / History was removed.

The same target-row change was also prepared for FoodReminder-Nexus.

**Result: PASS**

---

## 2026-09-03 — Persistence Testing

Performed a full game restart with watched items already configured.

Verified:

- watched items persisted
- Trading Post item index loaded from cache without rebuilding
- existing history remained available
- new observations continued to accumulate after restart

**Result: PASS**

---

## 2026-09-03 — Target Alert Testing

Sell Target functionality tested in-game.

Verified:

- target value can be entered directly from the compact item row
- a qualifying fresh Trading Post observation triggers the alert
- active target state is shown in the watch list
- Dismiss Party clears the active alert
- multiple triggered target alerts are queued
- dismissing one alert advances to the next queued alert

**Result: PASS**

---

## 2026-09-03 — Target Alert UI Redesign

The original celebratory target overlay worked but was visually cramped.

Redesigned the alert into a taller card-style layout with clearer hierarchy:

1. TARGET REACHED!
2. item name
3. CURRENT SELL
4. YOUR TARGET
5. Dismiss Party

Removed the redundant explanatory sentence indicating that the current sell was at or below the target.

Preserved the Dragon Bash-style celebration:

- animated confetti
- animated burst effects
- pulsing celebratory border
- Dismiss Party button

The current dark card background may receive additional cosmetic polish later.

**Result: PASS**

---

## 2026-09-03 — Current Functional Validation

The following systems are currently working in-game:

- standalone Nexus loading
- multi-item watch list
- 60-second automatic refresh
- manual item refresh
- Refresh All
- persistent watched items
- cached searchable Trading Post item index
- local Trading Post history
- history continuity across game restarts
- current lowest sell price
- current highest buy price
- Sell Target editing
- target status
- target alert triggering
- queued target alerts
- Dismiss Party
- compact watch-list UI
- collapsible Details / History
- configurable trend windows
- trend calculations
- Deal assessment
- spread display
- opportunity signal
- sell/buy history sparklines
- historical min/avg/max values

**Current overall status: Core standalone functionality is working.**

---

## Current Known Notes / Decisions Still Open

### Aurene's Bite default item

Aurene's Bite is currently hard-coded as the default watched item.

Item ID: `96356`

Because it is marked as the default item, the UI does not offer a Remove button for it.

Decision still open:

- keep Aurene's Bite as the permanent default
- or make all watched items fully removable

### DLL / project naming

Current Visual Studio project: `Copper & Claw`  
Current DLL: `Copper & Claw.dll`  
User-facing addon display name: `Copper&Claw`

Possible future cleanup: rename the build target to `CopperAndClaw.dll` while retaining `Copper&Claw` as the visible addon name.

### Target alert appearance

The redesigned target alert is functionally good and clearer to read. The current dark card background may receive additional cosmetic polish later.

### Nexus signature

The current addon signature is provisional and must be replaced/registered before public release.

---

## Pre-Release Checklist

- decide whether Aurene's Bite remains permanently watched
- decide final DLL/build-target naming
- replace/register the provisional Nexus addon signature
- perform a clean Release x64 rebuild
- verify final DLL loads through Nexus
- verify watch persistence
- verify cached item index
- verify history continuity
- verify target alert
- verify queued alerts
- update `README.md`
- update `DEVELOPMENT_LOG.md`
- commit
- push
- create release/tag when ready

---

## Development Rule

When making future Copper&Claw changes, use the current project files as the source of truth.

Do not substitute older copies of files from prior work. When a current source file is needed for modification, request the current file first.
