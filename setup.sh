#!/usr/bin/env bash
set -euo pipefail

GBDK_VERSION="4.5.0"
EMULICIOUS_URL="https://emulicious.net/download/emulicious/"

REPO_ROOT="$(cd "$(dirname "$0")" && pwd)"
cd "$REPO_ROOT"

echo "=== GameBoyForever Setup ==="
echo ""

# --- Prerequisites ---
check_prereq() {
    if ! command -v "$1" &>/dev/null; then
        echo "ERROR: '$1' is required but not installed."
        echo "  $2"
        exit 1
    fi
}

check_prereq git    "Install git: https://git-scm.com/downloads"
check_prereq make   "Install Xcode CLI tools: xcode-select --install"
check_prereq java   "Install Java: brew install --cask temurin"
check_prereq curl   "Install curl (usually pre-installed on macOS/Linux)"

echo "[OK] Prerequisites: git, make, java, curl"
echo ""

# --- GBDK-2020 ---
if [ -f "gbdk/bin/lcc" ]; then
    echo "[OK] GBDK-2020 already installed at gbdk/"
else
    echo "[..] Downloading GBDK-2020 v${GBDK_VERSION}..."

    OS="$(uname -s)"
    ARCH="$(uname -m)"

    case "${OS}-${ARCH}" in
        Darwin-arm64)  GBDK_FILE="gbdk-macos-arm64.tar.gz" ;;
        Darwin-x86_64) GBDK_FILE="gbdk-macos-x64.tar.gz" ;;
        Linux-x86_64)  GBDK_FILE="gbdk-linux64.tar.gz" ;;
        Linux-aarch64) GBDK_FILE="gbdk-linux-arm64.tar.gz" ;;
        *)
            echo "ERROR: Unsupported platform ${OS}-${ARCH}"
            echo "Download manually from https://github.com/gbdk-2020/gbdk-2020/releases"
            exit 1
            ;;
    esac

    GBDK_URL="https://github.com/gbdk-2020/gbdk-2020/releases/download/${GBDK_VERSION}/${GBDK_FILE}"
    curl -L -o /tmp/gbdk.tar.gz "$GBDK_URL"
    tar xzf /tmp/gbdk.tar.gz -C "$REPO_ROOT"
    rm /tmp/gbdk.tar.gz

    if [ "$OS" = "Darwin" ]; then
        echo "[..] Removing macOS quarantine flags..."
        xattr -dr com.apple.quarantine gbdk/ 2>/dev/null || true
    fi

    echo "[OK] GBDK-2020 v${GBDK_VERSION} installed to gbdk/"
fi
echo ""

# --- Emulicious ---
if [ -f "Emulicious/Emulicious.jar" ]; then
    echo "[OK] Emulicious already installed at Emulicious/"
else
    echo "[..] Downloading Emulicious..."
    curl -L -o /tmp/emulicious.zip "$EMULICIOUS_URL"
    mkdir -p Emulicious
    unzip -q -o /tmp/emulicious.zip -d Emulicious/
    rm /tmp/emulicious.zip
    echo "[OK] Emulicious installed to Emulicious/"
fi
echo ""

# --- Reference repos ---
echo "[..] Cloning reference repos into references/..."
mkdir -p references

if [ -d "references/BlackCastle/.git" ]; then
    echo "[OK] references/BlackCastle already present"
else
    echo "[..] Cloning BlackCastle..."
    git clone git@github.com:PlebeiusGaragicus/BlackCastle.git references/BlackCastle
    echo "[OK] BlackCastle cloned"
fi

if [ -d "references/gb-studio/.git" ]; then
    echo "[OK] references/gb-studio already present"
else
    echo "[..] Cloning gb-studio (with submodules)..."
    git clone --recurse-submodules git@github.com:PlebeiusGaragicus/gb-studio.git references/gb-studio
    echo "[OK] gb-studio cloned"
fi

if [ -d "references/gbdk-2020/.git" ]; then
    echo "[OK] references/gbdk-2020 already present"
else
    echo "[..] Cloning gbdk-2020..."
    git clone https://github.com/gbdk-2020/gbdk-2020.git references/gbdk-2020
    echo "[OK] gbdk-2020 cloned"
fi
echo ""

# --- Verify ---
echo "[..] Verifying toolchain..."
if GBDK_HOME="${REPO_ROOT}/gbdk/" "${REPO_ROOT}/gbdk/bin/lcc" -v 2>&1 | head -1; then
    echo "[OK] lcc compiler works"
fi

echo ""
echo "=== Setup complete! ==="
echo ""
echo "Next steps:"
echo "  cd games/_template"
echo "  make gb"
echo "  java -jar ../../Emulicious/Emulicious.jar build/gb/mygame.gb"
echo ""
