# Bullet Heck

This is my attempt at a lua-powered bullet hell engine. If I keep it up, it'll be turned into a 

It's currently in testing phase, meaning there are no real features
other than documentation on how to script bullets.

See `resource/bullets/` for more info.

## Programmer notes

* Script::Manager may cause conflicting issues between objects fighting over it. Until this is (probably) refactored, be sure to reset & push necessary values to the lua stack on each script run.