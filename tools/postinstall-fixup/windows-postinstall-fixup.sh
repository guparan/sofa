#!bash

usage() {
    echo "Usage: windows-postinstall-fixup.sh <build-dir> <install-dir>"
}

if [ "$#" -ge 2 ]; then
    BUILD_DIR="$(cd $1 && pwd)"
    INSTALL_DIR="$(cd $2 && pwd)"
    QT_LIB_DIR="$(cd $3 && pwd)"
    QT_DATA_DIR="$(cd $4 && pwd)"
else
    usage; exit 1
fi

# Adapt INSTALL_DIR to NSIS install
INSTALL_DIR_BIN="$INSTALL_DIR/bin"
if [[ "$INSTALL_DIR" == *"/NSIS/"* ]] && [[ -e "$INSTALL_DIR/../applications/bin" ]]; then
    INSTALL_DIR="$(cd $INSTALL_DIR/.. && pwd)"
    INSTALL_DIR_BIN="$INSTALL_DIR/applications/bin"
fi

echo "BUILD_DIR = $BUILD_DIR"
echo "INSTALL_DIR = $INSTALL_DIR"
echo "INSTALL_DIR_BIN = $INSTALL_DIR_BIN"
echo "QT_LIB_DIR = $QT_LIB_DIR"
echo "QT_DATA_DIR = $QT_DATA_DIR"

# Generate RCC file for dynamic qt.conf loading
# see SofaPython3/bindings/SofaGui/src/SofaPython3/SofaGui/Module_SofaGui.cpp
if [ -e "$QT_DATA_DIR/bin/rcc.exe" ] && [ -e "$INSTALL_DIR/bin/qt.conf" ]; then
    echo '<!DOCTYPE RCC>
          <RCC version="1.0">
            <qresource prefix="/qt/etc/">
              <file>qt.conf</file>
            </qresource>
          </RCC>' > "$INSTALL_DIR/bin/qt.conf.qrc"
    $QT_DATA_DIR/bin/rcc.exe "$INSTALL_DIR/bin/qt.conf.qrc" -binary -o "$INSTALL_DIR/bin/qt.conf.rcc"
fi

# Keep plugin_list as short as possible
echo "" > "$INSTALL_DIR/bin/plugin_list.conf"
disabled_plugins='plugins_ignored_by_default'
for plugin in \
        SofaEulerianFluid     \
        SofaDistanceGrid      \
        SofaImplicitField     \
        MultiThreading        \
        DiffusionSolver       \
        image                 \
        Compliant             \
        SofaPython            \
        Flexible              \
        Registration          \
        ExternalBehaviorModel \
        ManifoldTopologies    \
        ManualMapping         \
        THMPGSpatialHashing   \
        SofaCarving           \
        RigidScale            \
    ; do
    disabled_plugins=$disabled_plugins'\|'$plugin
done
grep -v $disabled_plugins "$INSTALL_DIR/bin/plugin_list.conf.default" >> "$INSTALL_DIR/bin/plugin_list.conf"

# Link all plugin libs in install/bin to make them easily findable
cd "$INSTALL_DIR" && find "plugins" -name "*.dll" | while read lib; do
    libname="$(basename $lib)"
    ln -s "../$lib" "bin/$libname"
done
