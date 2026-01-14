# 🎛️ Steverator — "Le Saturateur à Poisson" 🐟

![C++](https://img.shields.io/badge/C++-17-blue?style=for-the-badge&logo=c%2B%2B)
![JUCE](https://img.shields.io/badge/JUCE-Framework-8da033?style=for-the-badge&logo=juce)
![Platform](https://img.shields.io/badge/Platform-macOS%20%7C%20Windows-lightgrey?style=for-the-badge&logo=apple)
![VST3](https://img.shields.io/badge/Format-VST3-orange?style=for-the-badge)

---

## 📥 Téléchargement / Download

> **🚀 [➡️ Télécharger la dernière version / Download Latest Release](../../releases/latest)**

Visitez la [page des releases](../../releases) pour télécharger le plugin pour macOS ou Windows.

---

<details>
<summary>🇫🇷 <strong>MANUEL UTILISATEUR (Français)</strong> — Cliquez pour ouvrir</summary>

# 🇫🇷 MANUEL UTILISATEUR

## 🎉 Bienvenue dans le Steverator !

> **Le Steverator est un saturateur multi-bandes fun et puissant** qui va ajouter **chaleur**, **caractère** et **grain** à tous vos sons ! 🔥

Que vous vouliez :
- 🎸 **Réchauffer** une basse molle
- 🎤 **Donner du mordant** à une voix plate  
- 🥁 **Ajouter du punch** à vos drums
- 🎹 **Colorer** un synthé trop propre

...le Steverator est là pour vous ! Avec sa mascotte **Steve le poisson** 🐟 qui bouge au rythme de votre musique, mixer devient encore plus fun !

---

## 🎮 L'Interface en un Coup d'Œil

L'interface est divisée en **4 zones principales** super intuitives :

```
┌─────────────┬─────────────────────┬─────────────────┐
│   🐟 STEVE  │   🎚️ BANDES FREQ   │  🔥 SATURATION  │
│   + INPUT   │   Low/Mid/High      │   + MASTER      │
│   + PRESETS │   Crossovers        │   Wave/Shape    │
└─────────────┴─────────────────────┴─────────────────┘
```

---

## 🎚️ Section 1 : Entrée & Steve (Gauche)

| Contrôle | Description |
|----------|-------------|
| **🔊 Input** | Contrôle le niveau d'entrée (-24dB à +24dB). **Plus c'est fort, plus ça sature !** |
| **🐟 Steve** | Notre mascotte animée ! Il danse avec votre musique 💃 |
| **📁 Presets** | Des préréglages tout faits pour démarrer rapidement |

> 💡 **Astuce** : Montez l'Input pour **attaquer fort** la saturation, ou baissez-le pour un effet plus subtil !

---

## 📊 Section 2 : Bandes de Fréquences (Centre)

Le Steverator divise votre son en **3 bandes indépendantes** :

```
🔈 BASSES ──────┬────── MÉDIUMS ──────┬────── AIGUS 🔊
              Low Freq            High Freq
```

| Contrôle | Ce que ça fait |
|----------|----------------|
| **Low Freq** | Point de séparation Basses/Médiums (en Hz) |
| **High Freq** | Point de séparation Médiums/Aigus (en Hz) |
| **🔥 Low Warmth** | Ajoute une saturation **ronde et chaleureuse** aux basses |
| **✨ High Softness** | Saturation **douce** pour des aigus non-agressifs |
| **📊 Level Low/High** | Volume de sortie de chaque bande |

> 💡 **Astuce** : Voulez-vous des basses massives sans toucher aux aigus ? Montez le **Low Warmth** et gardez le **High Softness** bas !

---

## 🔥 Section 3 : Saturation Globale (Droite)

**C'est ici que la magie opère !** ✨

| Contrôle | Ce que ça fait |
|----------|----------------|
| **🌊 Wave** | Le **type** de distorsion (Tube, Tape, Diode, Fold, etc.) |
| **🎛️ Saturation** | LE gros bouton ! L'**intensité** de l'effet |
| **🔧 Shape** | La **texture** : plus tranchant ou plus rond ? |

### 🌊 Les différents types de Waves :

```
┌──────────────────────────────────────────────────┐
│  🎸 Tube    → Chaleureux, vintage, rock         │
│  📼 Tape    → Doux, compression naturelle       │
│  💡 Diode   → Agressif, mordant, rock/metal     │
│  🔄 Fold    → Créatif, synthwave, expérimental  │
│  📐 Clip    → Digital, brutal, EDM              │
│  ... et plein d'autres !                        │
└──────────────────────────────────────────────────┘
```

---

## 🎯 Section 4 : Master (Droite & Bas)

| Contrôle | Description |
|----------|-------------|
| **🔀 Mix** | Mélange Wet/Dry (0% = original, 100% = saturé) |
| **🔊 Output** | Volume de sortie final |
| **👁️ Delta Monitor** | Écoutez **UNIQUEMENT** la distorsion ajoutée ! |
| **📈 Delta Gain** | Volume du signal Delta |
| **🛡️ Limiter** | Protection contre le clipping numérique |

> 💡 **Pro tip** : Utilisez le **Delta Monitor** pour entendre exactement ce que vous ajoutez au mix. Super utile pour régler finement !

---

## 🚀 Quick Start : Vos Premiers Pas

1. **Chargez le plugin** sur une piste audio
2. **Choisissez un preset** ou partez de zéro
3. **Sélectionnez un Wave** (commencez par "Tube" !)
4. **Montez la Saturation** petit à petit
5. **Ajustez le Mix** à votre goût
6. **Profitez** du son chaud et fuzzy ! 🔥

</details>

---

<details open>
<summary>🇬🇧 <strong>USER MANUAL (English)</strong> — Click to expand</summary>

# 🇬🇧 USER MANUAL

## 🎉 Welcome to Steverator!

> **Steverator is a fun and powerful multi-band saturator** that adds **warmth**, **character**, and **grit** to all your sounds! 🔥

Whether you want to:
- 🎸 **Warm up** a thin bass
- 🎤 **Add bite** to a flat vocal
- 🥁 **Punch up** your drums
- 🎹 **Color** a too-clean synth

...Steverator's got you covered! With our dancing mascot **Steve the Fish** 🐟 moving to the beat, mixing becomes even more fun!

---

## 🎮 Interface at a Glance

The interface is divided into **4 super intuitive zones**:

```
┌─────────────┬─────────────────────┬─────────────────┐
│   🐟 STEVE  │   🎚️ FREQ BANDS    │  🔥 SATURATION  │
│   + INPUT   │   Low/Mid/High      │   + MASTER      │
│   + PRESETS │   Crossovers        │   Wave/Shape    │
└─────────────┴─────────────────────┴─────────────────┘
```

---

## 🎚️ Section 1: Input & Steve (Left)

| Control | Description |
|---------|-------------|
| **🔊 Input** | Controls input level (-24dB to +24dB). **More = more saturation!** |
| **🐟 Steve** | Our animated mascot! He dances with your music 💃 |
| **📁 Presets** | Ready-made presets to get you started fast |

> 💡 **Tip**: Crank the Input to **hit the saturation hard**, or lower it for a more subtle effect!

---

## 📊 Section 2: Frequency Bands (Center)

Steverator splits your audio into **3 independent bands**:

```
🔈 LOWS ────────┬────── MIDS ────────┬────── HIGHS 🔊
              Low Freq            High Freq
```

| Control | What it does |
|---------|--------------|
| **Low Freq** | Lows/Mids crossover point (in Hz) |
| **High Freq** | Mids/Highs crossover point (in Hz) |
| **🔥 Low Warmth** | Adds **round, warm** saturation to the lows |
| **✨ High Softness** | **Smooth** saturation for non-harsh highs |
| **📊 Level Low/High** | Output volume for each band |

> 💡 **Tip**: Want massive bass without touching the highs? Crank **Low Warmth** and keep **High Softness** low!

---

## 🔥 Section 3: Global Saturation (Right)

**This is where the magic happens!** ✨

| Control | What it does |
|---------|--------------|
| **🌊 Wave** | The **type** of distortion (Tube, Tape, Diode, Fold, etc.) |
| **🎛️ Saturation** | THE big knob! The **intensity** of the effect |
| **🔧 Shape** | The **texture**: sharper or rounder? |

### 🌊 Wave Types Cheat Sheet:

```
┌──────────────────────────────────────────────────┐
│  🎸 Tube    → Warm, vintage, rock vibes         │
│  📼 Tape    → Soft, natural compression         │
│  💡 Diode   → Aggressive, biting, rock/metal    │
│  🔄 Fold    → Creative, synthwave, experimental │
│  📐 Clip    → Digital, brutal, EDM              │
│  ... and many more!                             │
└──────────────────────────────────────────────────┘
```

---

## 🎯 Section 4: Master (Right & Bottom)

| Control | Description |
|---------|-------------|
| **🔀 Mix** | Wet/Dry blend (0% = original, 100% = saturated) |
| **🔊 Output** | Final output volume |
| **👁️ Delta Monitor** | Listen to **ONLY** the added distortion! |
| **📈 Delta Gain** | Volume of the Delta signal |
| **🛡️ Limiter** | Protection against digital clipping |

> 💡 **Pro tip**: Use **Delta Monitor** to hear exactly what you're adding to the mix. Super useful for fine-tuning!

---

## 🚀 Quick Start: Your First Steps

1. **Load the plugin** on an audio track
2. **Choose a preset** or start from scratch
3. **Pick a Wave** (start with "Tube"!)
4. **Turn up Saturation** gradually
5. **Adjust Mix** to taste
6. **Enjoy** the warm, fuzzy goodness! 🔥

</details>

---

# 🛠️ DEVELOPER DOCUMENTATION

*(AI Context & Technical Architectures)*

## 🎯 Project Vision
The `steverator` project is a VST3 audio plugin built with JUCE.
Themed around "Le Poisson Steve" (Steve the Fish), this plugin showcases how to structure a modern audio project cleanly using industry-standard practices.

## 🤖 Technical Guide & Architecture

### 🏗 Global Architecture (Model-View-Controller)
The project uses **JUCE** and strictly separates audio processing from the graphical interface:

*   **MODEL (State)**: `AudioProcessorValueTreeState (apvts)`
    *   Located in `PluginProcessor`.
    *   Single source of truth for all parameters.
    *   Handles preset saving/loading (`getStateInformation`).

*   **CONTROLLER (DSP & Logic)**: `PluginProcessor`
    *   **File**: `Source/PluginProcessor.cpp`
    *   **Core**: `processBlock()` is the real-time audio loop. **Critical:** No memory allocation, no locks here.
    *   **Init**: `createParameterLayout()` defines all parameters at startup.

*   **VIEW (Interface)**: `PluginEditor`
    *   **File**: `Source/PluginEditor.cpp`
    *   **Role**: Receives a reference to `PluginProcessor` to link Sliders to Parameters via `Attachments`.
    *   **Rendering**: Uses `CustomLookAndFeel` for vector drawing (procedural knobs, custom fonts).

### 📍 Critical Entry Points

| Action | Target File | Function / Zone |
| :--- | :--- | :--- |
| **Add a Parameter** | `PluginProcessor.cpp` | `createParameterLayout()` (ID & Range definition) |
| **Modify Sound** | `PluginProcessor.cpp` | `processBlock()` (DSP Algorithm) |
| **Modify UI Layout** | `PluginEditor.cpp` | `resized()` (FlexBox Positioning) |
| **Style Knobs** | `CustomLookAndFeel.cpp` | `drawRotarySlider()` |
| **Build & Test** | Root | `./build_and_deploy.sh` (Master Script) |

### ⚠️ Golden Rules
1.  **Real-Time**: In `processBlock`, **FORBIDDEN** to use `new`, `malloc`, `std::vector::push_back`, or blocking functions.
2.  **State Management**: Never store UI state separate from APVTS if it affects the sound.
3.  **Assets**: Images (e.g., mascot) and Fonts are in `Assets/` and loaded in `PluginEditor`/`CustomLookAndFeel`.

## 📦 Functional Scale (DSP)

`steverator` is a 3-band audio saturation effect with multi-frequency processing.

**Main Function:**
Apply soft saturation and wave-shaping to the incoming audio signal with independent control of low, mid, and high frequencies.

**Tech Stack:**
*   **Language**: C++
*   **Framework**: JUCE
*   **Plugin Format**: VST3
*   **Platforms**: macOS (Universal), Windows x64

## 📁 File Architecture

```plaintext
steverator/
├── CMakeLists.txt              # 🛠 Build configuration (JUCE VST3 settings)
├── build_and_deploy.sh         # 🚀 MASTER SCRIPT: Builds, signs, and launches standalone
├── Source/
│   ├── PluginProcessor.h/cpp   # 🧠 BRAIN (Controller & DSP) relative to AudioProcessor
│   ├── PluginEditor.h/cpp      # 🎨 FACE (View & UI) relative to AudioProcessorEditor
│   ├── CustomLookAndFeel.h/cpp # 💅 STYLE (vector graphics, fonts, colors)
│
└── Assets/
    ├── steve.png               # 🐟 Mascot image
    ├── indicator.png           # 🟠 Knob position indicator
    └── NanumPenScript-Regular.ttf # 📝 Custom Handwriting Font
```