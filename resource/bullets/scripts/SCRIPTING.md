# Bullet Scripting

## Global Tables

A unique lua script state instance is loaded for each bullet spawned. The script is initialized with objects listed below, that reference bullet instance member functions, such as position.

The script entry point is iterate().

Parameters may be passed to the iterate() function.

### Tables

These are the current objects made available in the lua script.

* `Bullet.`

    | Function | Returns | Comment |
    |----------|---------|---------|
    | `getPos()`  | `{x = number, y = number}` | The bullet's current position |
    | `getVel()` | `{x = number, y = number}` | The bullet's current velocity |
    | `getLife()` | `number` | (Approx) How long the bullet has been alive, in ms. |
    | `setPos(x, y)` | `nil` | Set the position of the bullet |
    | `setVel(x, y)` | `nil` | Set the velocity of the bullet |
    | `delete()` | `nil` | Flag the bullet for deletion |

* `GLOBALS`

    | Function | Returns | Comment |
    |----------|---------|---------|
    | `winsize()`  | `{x = number, y = number}` | The size of the window |
    | `msElapsed()` | `number` | The milliseconds elapsed since last frame