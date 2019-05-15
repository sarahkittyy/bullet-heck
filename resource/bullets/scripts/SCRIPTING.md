# Bullet Scripting

## Global Tables

The scripting engine stores bullet & other information in global tables
updated on every script run.

The script entry point is iterate().

### Tables

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