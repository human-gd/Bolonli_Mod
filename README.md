# BolonliMod — Android Geode project

This is a Geode mod project prepared for Android.

## Easiest build route

1. Put this folder into a GitHub repository.
2. Push it to GitHub.
3. Open **Actions**.
4. Run **Build Android Geode Mod**.
5. Download the generated artifact.
6. The artifact contains the `.geode` package.

## Local build

Install the Geode CLI and Android NDK, then:

```bash
geode sdk install-binaries -p android64
geode build -p android64
```

For 32-bit Android:

```bash
geode sdk install-binaries -p android32
geode build -p android32
```

Geode's Android documentation says the resulting `.geode` can be copied to:

`/storage/emulated/0/Android/media/com.geode.launcher/game/geode/mods/`

## Current build target

The project targets Geometry Dash Android 2.2081, matching the current official Geode example template.
