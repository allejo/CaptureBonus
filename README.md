Development for this project has officially ended. This plug-in has been superseded by [ctfOverseer](https://github.com/allejo/ctfOverseer).

---

# Capture Bonus

[![GitHub release](https://img.shields.io/github/release/allejo/CaptureBonus.svg)](https://github.com/allejo/CaptureBonus/releases/latest)
![Minimum BZFlag Version](https://img.shields.io/badge/BZFlag-v2.4.14+-blue.svg)
[![License](https://img.shields.io/github/license/allejo/CaptureBonus.svg)](LICENSE.md)

A BZFlag plugin that awards a static bonus to players who capture the flag.

## Requirements

- BZFlag 2.4.14+

This plug-in follows [my standard instructions for compiling plug-ins](https://github.com/allejo/docs.allejo.io/wiki/BZFlag-Plug-in-Distribution).

## Usage

### Loading the plug-in

This plug-in does not require any special configuration at load time.

```
-loadplugin CaptureBonus
```

### Custom BZDB Variables

These custom BZDB variables can be configured with `-set` in configuration files and may be changed at any time in-game by using the `/set` command.

```
-set <name> <value>
```

| Name | Type | Default | Description |
| ---- | ---- | ------- | ----------- |
| `_captureBonus` | int | 10 | The number of extra points a player will be awarded on capturing a flag. |
| `_penalizeSelfCapture` | bool | true | When set to true, deduct the extra points when a player self-caps. Otherwise, it'll always grant extra points. |

## License

[MIT](LICENSE.md)
