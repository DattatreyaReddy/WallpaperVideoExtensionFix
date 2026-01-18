#!/bin/bash
set -e

BUILD_DIR="build"

echo "🔧 WallpaperAerialsExtensionFix build script"

# 1. Ensure Xcode Command Line Tools
if ! xcode-select -p &>/dev/null; then
  echo "📦 Installing Xcode Command Line Tools..."
  xcode-select --install
  echo "⚠️ Re-run this script after installation completes."
  exit 1
fi

# 2. Ensure Homebrew
if ! command -v brew &>/dev/null; then
  echo "❌ Homebrew not found."
  echo "Install it from https://brew.sh and re-run this script."
  exit 1
fi

# 3. Ensure CMake
if ! command -v cmake &>/dev/null; then
  echo "📦 Installing CMake..."
  brew install cmake
fi

# 4. Create build directory
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# 5. Configure and build
echo "⚙️ Running CMake..."
cmake ..

echo "🏗️ Building project..."
cmake --build .

echo "✅ Build complete!"
echo "📍 Output is located in: $(pwd)"
