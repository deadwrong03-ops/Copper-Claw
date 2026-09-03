# Copper&Claw

Copper&Claw is a standalone Guild Wars 2 Nexus addon for watching Trading Post prices, building local price history, and alerting when watched items reach a user-defined sell target.

## Current Status

**Version:** 0.1.0  
**Status:** Functional standalone build / pre-release testing

Core Trading Post functionality has been separated into its own addon and tested in-game.

## Features

- Watch multiple Guild Wars 2 Trading Post items
- Automatic price refresh every 60 seconds
- Manual per-item refresh
- Refresh all watched items
- Current lowest sell listing
- Current highest buy order
- Per-item Sell Target using gold / silver / copper inputs
- Target status: No Target / Wait / Target Reached
- Queued target alerts
- Dragon Bash-style celebratory target popup
- Dismiss Party action for active alerts
- Persistent watched-item list
- Persistent target prices
- Persistent local Trading Post price history
- Cached searchable Trading Post item index
- Item search without requiring manual item IDs
- Configurable trend window
- Collapsible Details / History section
- Sell and buy trend calculations
- Deal assessment
- Spread information
- Buy opportunity signal
- Sell and buy history sparklines
- Historical minimum / average / maximum prices

## Local Data

Copper&Claw stores its data alongside the loaded addon module.

Files currently used:

- `CopperAndClaw.ini`
- `CopperAndClaw_TradingPostWatch.ini`
- `CopperAndClaw_TradingPostHistory.tsv`
- `CopperAndClaw_TradingPostItemIndex.tsv`

These files allow the addon to restore settings, watched items, targets, cached item-search data, and locally collected price history between game sessions.

## Price History Retention

Copper&Claw keeps local Trading Post observations and compacts older data over time.

- Newest 24 hours: every recorded observation
- 24 hours to 7 days: approximately one observation every 5 minutes
- Older than 7 days: approximately one observation every 30 minutes

## Trading Post Item Search

Copper&Claw builds a local searchable index of Trading Post items using the Guild Wars 2 public API.

The index is cached locally, remains searchable between sessions, can rebuild when needed, and ranks exact matches before broader matches.

Current cache file:

`CopperAndClaw_TradingPostItemIndex.tsv`

## Target Alerts

A Sell Target represents the maximum sell listing price the user is willing to pay.

If the current lowest sell listing reaches or drops below the configured target, Copper&Claw triggers a celebratory alert.

The alert includes:

- TARGET REACHED!
- item name
- current sell price
- user target price
- animated confetti and celebration effects
- Dismiss Party button

Multiple triggered targets are queued and shown one at a time.

## Trend Windows

Current trend-window options:

- 15m
- 30m
- 1h
- 6h
- 24h
- 3d
- 7d
- 30d
- 90d

The selected window is persisted in `CopperAndClaw.ini`.

## Current Testing Results

The following have been tested successfully in-game:

- standalone Nexus addon load
- watched-item persistence after restart
- cached item index loading without rebuild
- local history continuity after restart
- automatic 60-second refresh
- multiple watched items
- Sell Target editing
- target alert triggering
- queued target alerts
- Dismiss Party behavior
- compact watched-item UI
- collapsed Details / History layout
- item search/index operation

## Known Pre-Release Notes

- Aurene's Bite is currently treated as the built-in default watched item and cannot be removed.
- The current Visual Studio project produces `Copper & Claw.dll`.
- The Nexus addon display name is `Copper&Claw`.
- The current addon signature is provisional and must be replaced/registered before public release.
- Target-alert background styling may receive additional cosmetic polish later.

## Build Environment

Current project configuration:

- Visual Studio
- x64
- Dynamic Library
- Platform Toolset: v143
- C++17
- Multi-Byte Character Set
- Precompiled Headers: disabled
- Release Runtime Library: `/MT`
- Debug Runtime Library: `/MTd`
- Windows subsystem

## API

Copper&Claw uses ArenaNet's public Guild Wars 2 API for Trading Post and item information.

Current API functionality includes commerce prices, item information, and Trading Post item discovery/indexing.

HTTP requests use the `CopperAndClaw/1.0` user agent.

## Project Direction

Copper&Claw was created by extracting the working Trading Post watcher framework from FoodReminder-Nexus into a dedicated standalone addon. FoodReminder-Nexus remains intact and continues to retain its own Trading Post functionality.

Future improvements may include additional UI polish, expanded market analysis, and further Trading Post quality-of-life features.

## Author

**spectre9510**
