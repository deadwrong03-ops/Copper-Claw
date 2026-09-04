# Copper&Claw

Copper&Claw is a standalone Guild Wars 2 Nexus addon for watching Trading Post prices, building local price history, analyzing market movement, and alerting when watched items reach a user-defined sell target.

## Current Status

**Version:** 0.1.0  
**Status:** Release candidate / final pre-release validation passed

Core Trading Post functionality has been separated into its own addon, tested successfully in-game, and has completed the current release-candidate validation pass.

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
- Variant-aware search for duplicate-name Trading Post items
- Player-friendly stat labels for item variants
- Searchable stat variants such as Power, Precision, Concentration, and Expertise
- Configurable trend window
- Persisted trend-window selection
- Collapsible Details / History section
- Separate Sell Listings and Buy Orders market analysis
- Sell-listing direction and percentage change
- Buy-order direction and percentage change
- Recent-average comparisons
- Price-position analysis
- Buyer-facing market signal
- Seller-facing market signal
- Analysis confidence level
- Selected-window coverage display
- Observation/sample count
- Current Trading Post spread
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

## Local Price History

Copper&Claw builds its own Trading Post price-history database from observations collected while an item is being watched.

Copper&Claw does **not** have access to historical Trading Post prices from before the item began being tracked locally.

On a new installation, market history begins accumulating from the time tracking starts.

The addon displays the following notice in-game:

> Historical note: Copper&Claw builds its own price history from the time you begin tracking an item. No earlier market history is available on initial install.

Developing analysis may also display:

> Analysis is based only on locally collected history.

This is important when interpreting longer trend windows such as 7d, 30d, or 90d on newly tracked items.

## Price History Retention

Copper&Claw keeps local Trading Post observations and compacts older data over time.

- Newest 24 hours: every recorded observation
- 24 hours to 7 days: approximately one observation every 5 minutes
- Older than 7 days: approximately one observation every 30 minutes

This allows recent market movement to retain higher detail while keeping long-term history storage manageable.

## Market Analysis

Copper&Claw separates Trading Post analysis into the two different sides of the market so rising prices do not produce confusing or contradictory wording.

### Sell Listings

Sell Listings represent the lowest current price a buyer would pay to purchase an item immediately.

Copper&Claw can display:

- Direction
  - Getting More Expensive
  - Getting Cheaper
  - Stable
  - Developing
- Percentage change over the selected trend window
- Recent average
- Percentage difference from the recent average
- Price position
  - Well Below Recent Avg
  - Below Recent Avg
  - Near Recent Avg
  - Above Recent Avg
  - Well Above Recent Avg
- Buyer-facing signal
  - Favorable
  - Worth Watching
  - Typical
  - Caution
  - Developing

Price position is given greater importance than trend direction so a rising market is not automatically labeled overpriced.

For example, a sell listing can be rising while still remaining below its recent average.

### Buy Orders

Buy Orders represent the highest current amount another player is offering to pay for the item.

Copper&Claw can display:

- Direction
  - Buyers Offering More
  - Buyers Offering Less
  - Stable
  - Developing
- Percentage change over the selected trend window
- Recent average
- Percentage difference from the recent average
- Price position
  - Well Above Recent Avg
  - Above Recent Avg
  - Near Recent Avg
  - Below Recent Avg
  - Well Below Recent Avg
- Seller-facing signal
  - Favorable
  - Worth Watching
  - Typical
  - Weak
  - Developing

Sell Listings and Buy Orders are analyzed separately because the same movement has different meaning depending on which side of the Trading Post market is being viewed.

### Compact Market Summary

Each watched item can display a compact summary such as:

`Listings: More Expensive +1.19% | Buy Orders: Higher +0.38% | Conf HIGH`

This provides a quick market snapshot without requiring the Details / History section to remain expanded.

### Confidence and Coverage

Copper&Claw avoids presenting newly collected data as mature historical analysis.

Analysis considers:

- available observation count
- amount of locally collected history
- selected trend window
- whether sufficient history exists for the requested comparison
- percentage of the selected window currently covered

Current confidence levels include:

- LOW
- MEDIUM
- HIGH

The UI also displays:

- coverage
- sample count
- selected history window

This helps distinguish a mature analysis from one that is still developing.

## Trading Post Item Search

Copper&Claw builds a local searchable index of Trading Post items using the Guild Wars 2 public API.

The index is cached locally, remains searchable between sessions, can rebuild when needed, and ranks exact matches before broader matches.

Current cache file:

`CopperAndClaw_TradingPostItemIndex.tsv`

### Duplicate-Name / Stat Variants

Some Guild Wars 2 Trading Post items share the same visible item name while using different item IDs and separate Trading Post listings.

Copper&Claw detects available stat/attribute metadata for these items and uses it to distinguish variants directly in search results.

For example, instead of several identical entries such as:

`Festive Confetti Infusion (Item ID: ...)`

search results can display:

- `Festive Confetti Infusion - Power`
- `Festive Confetti Infusion - Precision`
- `Festive Confetti Infusion - Toughness`
- `Festive Confetti Infusion - Vitality`
- `Festive Confetti Infusion - Healing Power`
- `Festive Confetti Infusion - Concentration`
- `Festive Confetti Infusion - Expertise`
- `Festive Confetti Infusion - Condition Damage`

This makes it easier to select the exact Trading Post listing being watched without relying on item IDs alone.

Player-facing labels are used where the API exposes internal attribute names.

Current mappings include:

- `ConditionDamage` → `Condition Damage`
- `Healing` → `Healing Power`
- `BoonDuration` → `Concentration`
- `ConditionDuration` → `Expertise`
- `AgonyResistance` → omitted from the visible label when it would only add clutter

Variant labels are also included in search matching, allowing searches such as:

`festive confetti concentration`

to narrow toward the appropriate stat version.

Older item-index cache files without variant metadata can still be read, but Copper&Claw will rebuild the index so newer variant information can be added.

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

Dismissed alerts remain latched rather than immediately retriggering from the same already-reached price condition.

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

The selected window is persisted in:

`CopperAndClaw.ini`

Longer windows become more meaningful as Copper&Claw accumulates additional local history.

## Current Testing Results

The following have been tested successfully in-game:

- standalone Nexus addon load
- `Copper&Claw` addon display name
- `Copper&Claw` in-app heading
- automatic 60-second refresh
- manual per-item refresh
- Refresh All
- multiple watched items
- watched-item persistence after full Guild Wars 2 restart
- Sell Target editing
- Sell Target persistence after full Guild Wars 2 restart
- trend-window persistence after full Guild Wars 2 restart
- cached item index loading without rebuild
- local history continuity after restart
- observation counts retained across restart
- market analysis retained and rendered normally after restart
- target alert triggering
- queued target alerts
- Dismiss Party behavior
- compact watched-item UI
- collapsed Details / History layout
- separate Sell Listings / Buy Orders analysis
- direction percentages
- recent-average comparisons
- price-position analysis
- buyer and seller market signals
- confidence and coverage display
- local-history disclaimer
- item search/index operation
- duplicate-name Trading Post item detection
- stat-variant identification
- player-friendly variant labels
- searchable stat variants
- rebuilt variant-aware item-index cache
- Sell and Buy history sparklines
- historical min / avg / max display
- clean Release x64 rebuild and fresh DLL load
- final release-candidate smoke test

## Known Pre-Release Notes

- Aurene's Bite is currently treated as the built-in default watched item and cannot be removed.
- The current Visual Studio project produces `Copper & Claw.dll`.
- The Nexus addon display name is `Copper&Claw`.
- Copper&Claw currently uses a unique negative Nexus addon signature for standalone/non-Raidcore use.
- A Raidcore-hosted release would require the signature assigned by Raidcore.
- All historical analysis is based only on locally collected observations.
- New installations begin with no historical market data.
- Target-alert background styling may receive additional cosmetic polish later.
- The current build is a release candidate; public release/tag packaging is the remaining release step.

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

Current Release DLL name:

`Copper & Claw.dll`

## API

Copper&Claw uses ArenaNet's public Guild Wars 2 API for Trading Post and item information.

Current API functionality includes:

- commerce prices
- item information
- Trading Post item discovery
- searchable item-index construction

HTTP requests use the:

`CopperAndClaw/1.0`

user agent.

## Project Direction

Copper&Claw was created by extracting the working Trading Post watcher framework originally developed inside FoodReminder-Nexus into a dedicated standalone addon.

Copper&Claw is now maintained independently as the dedicated Trading Post project.

Copper&Claw is intended to provide a stock-market-style view of Guild Wars 2 Trading Post information while keeping the interface understandable and avoiding unnecessary market jargon or clutter.

Current development priorities emphasize:

- accurate interpretation of locally collected price data
- clear separation between Sell Listings and Buy Orders
- cautious analysis when historical coverage is limited
- persistent local price history
- practical Trading Post alerts and watch-list functionality
- clean in-game usability

Future improvements may include additional UI polish, expanded market-analysis tools, and further Trading Post quality-of-life features.

## Author

**spectre9510**