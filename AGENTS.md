# 🤖 AGENTS.md — Instructions for Development Agents

This file contains instructions for Claude (or other AI agents) working on the vst_saturator project.

---

## 📋 Overview

**vst_saturator** is an educational VST3 audio plugin built with JUCE. It demonstrates audio processing, UI design, and plugin architecture.

**Key constraints:**
- Written in C++17 with JUCE framework
- Builds to VST3 format
- macOS target (Apple Silicon compatible)
- Focus on clarity and education over performance

---

## 🔨 Build & Deploy Workflow

### When the User Requests Changes

If the user asks to modify the plugin (code, UI, images, etc.), always follow this workflow:

1. **Read and understand** the relevant source files
2. **Make changes** to the code/assets
3. **Build and deploy** using the script
4. **Verify** the changes work in Ableton

### Build Command

After making code changes, always run:

```bash
cd /Users/vava/Documents/GitHub/vst_saturator
./build_and_deploy.sh
```

**This script:**
- ✅ Generates a **unique 5-character build hash** (e.g., `A3F7K`)
- ✅ CMake compilation (Release mode) with hash embedded
- ✅ Plugin signing (codesign)
- ✅ Asset copying (images from /Assets/)
- ✅ Cache clearing (Ableton)
- ✅ Deployment to `/Library/Audio/Plug-Ins/VST3/vst_saturator2.vst3`
- ✅ Displays build hash prominently

**Important:** The script will output the build hash like this:
```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
✨ BUILD COMPLETE!

🔑 BUILD HASH: A3F7K

You should see 'A3F7K' at the bottom of the plugin UI
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

### After Build - Tell the User

**Always include the build hash when telling the user:**

```
🔨 Build complete!
🔑 Build hash: A3F7K

Steps:
1. Restart Ableton (Cmd+Q)
2. Reopen Ableton
3. Rescan plugins: Preferences → File/Folder → Rescan
4. Open vst_saturator2 and look at the bottom
5. You should see "A3F7K" displayed in orange text
6. If you see a different hash or "DEV", the cache wasn't cleared
```

This hash verification ensures the user is testing the fresh build, not a cached version.

---

## 📁 Project Structure

```
vst_saturator/
├── CMakeLists.txt              # Build configuration
├── build_and_deploy.sh         # Development script ⭐ USE THIS
├── Assets/                     # UI images (PNG format)
│   ├── background.png          # Plugin background
│   └── knob.png                # Rotary slider knob
├── Source/
│   ├── PluginProcessor.h/cpp   # Audio engine (DSP)
│   ├── PluginEditor.h/cpp      # UI layout & rendering
│   └── CustomLookAndFeel.h/cpp # Custom UI styling
├── libs/
│   └── JUCE/                   # JUCE framework (submodule)
└── build/                      # Build artifacts (generated)
```

---

## 🎨 Working with Images

### Asset Management

- **Location:** `/Assets/` directory
- **Format:** PNG (24-bit RGB for background, 32-bit RGBA for knob)
- **Resolution:** High quality recommended (background: 1200+px, knob: 1024x1024 minimum)

### Knob Image Requirements

- **Dimensions:** Square (preferably 1024x1024)
- **Design:** Symmetrical (will be rotated)
- **Indicator:** Should have a visible marker (top, white line, etc.)
- **Transparency:** Can use alpha channel

### Background Image Requirements

- **Dimensions:** Any size (will be scaled to fit)
- **Format:** 24-bit PNG
- **Aspect ratio:** Flexible (scales to plugin window)

### Updating Images

1. Replace files in `/Assets/`
2. Run `./build_and_deploy.sh`
3. User restarts Ableton & rescans plugins

---

## 💾 Key Files to Know

| File | Purpose | Can Edit? |
|------|---------|-----------|
| `Source/PluginProcessor.cpp` | Audio processing (DSP) | ✅ Yes |
| `Source/PluginEditor.cpp` | UI layout & background rendering | ✅ Yes |
| `Source/CustomLookAndFeel.cpp` | Knob rotation & styling | ✅ Yes |
| `CMakeLists.txt` | Build configuration | ✅ Yes (carefully) |
| `Assets/background.png` | Background image | ✅ Yes (replace) |
| `Assets/knob.png` | Knob image | ✅ Yes (replace) |
| `libs/JUCE/` | JUCE framework | ❌ Don't edit |
| `build/` | Build artifacts | ❌ Don't edit |

---

## 🐛 Troubleshooting

### Plugin doesn't appear in Ableton

1. Run `./build_and_deploy.sh`
2. Close Ableton completely (Cmd+Q)
3. Reopen Ableton
4. Rescan plugins
5. Search for "vst_saturator2"

### Knob isn't rotating correctly

- Check `CustomLookAndFeel.cpp` for rotation math
- Ensure `knob.png` is square and symmetrical
- Verify `AffineTransform::rotation()` calculations

### Images aren't displaying

- Verify PNG files exist in `/Assets/`
- Run `./build_and_deploy.sh` to copy them
- Check image dimensions (knob should be square, minimum 256x256)
- Clear Ableton cache and restart

### Build fails

- Check compiler warnings
- Ensure JUCE submodule is initialized: `git submodule update --init`
- Verify CMake is installed: `cmake --version`

---

## 📝 Code Style & Conventions

- **Language:** C++17
- **Comments:** Educational, explain the "why" not just "what"
- **Naming:** camelCase for variables, PascalCase for classes
- **Real-time rules:** No allocations in `processBlock()`
- **Dependencies:** Only JUCE, no external libraries

---

## 🎯 Common Tasks

### To change the background color/image

Edit: `Source/PluginEditor.cpp` → `paint()` method

OR replace: `Assets/background.png`

Then run: `./build_and_deploy.sh`

### To change slider behavior

Edit: `Source/PluginEditor.cpp` → `resized()` method

Adjust:
- Slider size calculations
- Position calculations
- Parameter ranges

Then run: `./build_and_deploy.sh`

### To add a new parameter

Edit: `Source/PluginProcessor.cpp` → `createParameterLayout()`

Add new parameter, then:
- Create slider in `PluginEditor.cpp`
- Add attachment
- Adjust layout in `resized()`

Then run: `./build_and_deploy.sh`

### To modify DSP (audio processing)

Edit: `Source/PluginProcessor.cpp` → `processBlock()` method

Keep in mind:
- ⚠️ No memory allocation
- ⚠️ No logging
- ⚠️ No locks/mutexes
- ✅ Fast, real-time safe code

Then run: `./build_and_deploy.sh`

---

## ✅ Checklist Before Asking User to Test

- [ ] Code compiles without errors
- [ ] Build script ran successfully
- [ ] Plugin deployed to `/Library/Audio/Plug-Ins/VST3/vst_saturator2.vst3`
- [ ] All assets (images) are in place
- [ ] User notified to: restart Ableton, rescan plugins
- [ ] Plugin signature is valid (no codesign errors)
- [ ] Ableton caches were cleared

---

## 📚 References

- JUCE Framework: https://juce.com/
- VST3 Specification: https://www.steinberg.net/vst3
- CMake: https://cmake.org/

---

**Last updated:** January 2026
