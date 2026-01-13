#!/bin/bash

# build_and_deploy.sh
# Script de développement pour vst_saturator
# Génère un hash unique et le stocke dans un fichier version.txt

PASSWORD="aaaa"

# Generate unique hash (5 chars, alphanumeric)
BUILD_HASH=$(openssl rand -hex 3 | cut -c1-5 | tr '[:lower:]' '[:upper:]')
TIMESTAMP=$(date '+%Y-%m-%d %H:%M:%S')

echo "🔨 Building vst_saturator..."
echo "📦 BUILD HASH: $BUILD_HASH"
echo "📅 TIMESTAMP: $TIMESTAMP"
echo ""

# Create version.txt file with build info
mkdir -p /Users/vava/Documents/GitHub/vst_saturator/Assets
cat > /Users/vava/Documents/GitHub/vst_saturator/Assets/version.txt << VERSIONEOF
$BUILD_HASH
$TIMESTAMP
VERSIONEOF

echo "✓ Created version.txt with hash: $BUILD_HASH"
echo ""

# Compile
cd /Users/vava/Documents/GitHub/vst_saturator
cmake -B build -DCMAKE_BUILD_TYPE=Release > /dev/null 2>&1
cmake --build build --config Release 2>&1 | grep -E "(Building|Linking|Built|error)" | tail -20

if [ $? -ne 0 ]; then
    echo "❌ Build failed!"
    exit 1
fi

echo ""
echo "📦 Deploying..."

# Use bash -c to avoid stdin conflict with sudo -S
echo "$PASSWORD" | sudo -S bash -c '
# 1. Clean destination
rm -rf /Library/Audio/Plug-Ins/VST3/vst_saturator.vst3

# 2. Copy new bundle
cp -r /Users/vava/Documents/GitHub/vst_saturator/build/vst_saturator_artefacts/Release/VST3/vst_saturator.vst3 /Library/Audio/Plug-Ins/VST3/vst_saturator.vst3

# 3. Ensure Resources directory exists
mkdir -p /Library/Audio/Plug-Ins/VST3/vst_saturator.vst3/Contents/Resources

# 4. Copy assets
cp /Users/vava/Documents/GitHub/vst_saturator/Assets/*.{png,txt} /Library/Audio/Plug-Ins/VST3/vst_saturator.vst3/Contents/Resources/ 2>/dev/null || true

# 5. Fix Permissions (Crucial for recognition)
chmod -R 755 /Library/Audio/Plug-Ins/VST3/vst_saturator.vst3
chown -R root:wheel /Library/Audio/Plug-Ins/VST3/vst_saturator.vst3

# 6. Remove Quarantine (Crucial for macOS)
xattr -rc /Library/Audio/Plug-Ins/VST3/vst_saturator.vst3 2>/dev/null

# 7. Ad-hoc Sign (Required for ARM64)
codesign --force --deep --sign - /Library/Audio/Plug-Ins/VST3/vst_saturator.vst3 2>&1 | grep -v "resource fork"
'

# Clear caches (Aggressive)
find ~/Library/Application\ Support/Ableton -type d -name "Cache" -exec rm -rf {} + 2>/dev/null
rm -rf ~/Library/Caches/Ableton 2>/dev/null
rm -f ~/Library/Preferences/Ableton/Live*/Library.cfg 2>/dev/null

echo ""
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "✨ BUILD COMPLETE!"
echo ""
echo "🔑 BUILD HASH: $BUILD_HASH"
echo "📅 TIMESTAMP: $TIMESTAMP"
echo ""
echo "version.txt created:"
cat /Users/vava/Documents/GitHub/vst_saturator/Assets/version.txt
echo ""
echo "You should see '$BUILD_HASH' in BIG ORANGE text at the BOTTOM"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo ""
echo "Next:"
echo "1. Restart Ableton (Cmd+Q)"
echo "2. Reopen Ableton"
echo "3. Rescan plugins (Preferences → File/Folder → Rescan)"
echo "4. Search for 'vst_saturator' (Company: MyEducationalPlugins)"
echo "5. Look at BOTTOM - should see '$BUILD_HASH' prominently"
