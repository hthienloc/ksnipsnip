# KSnipSnip

**KSnipSnip** is a KDE Plasma 6 widget and standalone Qt application designed for quick screen captures that create clean reference windows.

Inspired by [Kasasa](https://github.com/KelvinNovais/Kasasa) and refined with patterns from [focus-plasmoid](https://gitlab.com/divinae/focus-plasmoid/).

## 🚀 Features

- **Quick Snipping**: Easily select any part of your screen.
- **Reference Window**: The captured area floats in a clean, frameless window.
- **Interactive Controls**:
  - **Zoom**: Scalable view via the scroll wheel.
  - **Move**: Drag the reference anywhere with your mouse.
  - **Close**: Right-click to dismiss the snip instantly.
- **Plasma 6 Ready**: Optimized for the latest KDE environment.

## 🛠️ Build and Install

### Dependencies

- Qt 6.6+ (Core, Gui, Widgets)

### Building

```bash
mkdir build && cd build
cmake ..
make -j$(nproc)
```

### Running

The standalone binary can be found at `build/src/ksnipsnip-helper`.

## 🖋️ Author

- **hthienloc**

## ⚖️ License

This project is licensed under the GNU General Public License v3.0 or later.
