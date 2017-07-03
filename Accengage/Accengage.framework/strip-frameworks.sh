FRAMEWORKS_DIRECTORY="${BUILT_PRODUCTS_DIR}/${FRAMEWORKS_FOLDER_PATH}"

find "$FRAMEWORKS_DIRECTORY" -name 'Accengage*.framework' -type d | while read -r framework
do
    framework_name=`basename "$framework"`
    framework_binary_path=$framework"/${framework_name%.*}"

    archs="$(lipo -info "${framework_binary_path}" | rev | cut -d ':' -f1 | rev)"
    stripped=""
    for arch in $archs; do
        if ! [[ "${VALID_ARCHS}" == *"$arch"* ]]; then
            lipo -remove "$arch" -output "$framework_binary_path" "$framework_binary_path" || exit 1
            stripped="$stripped $arch"
        fi
    done
    if [[ "$stripped" != "" ]]; then
        echo "Stripped $framework_binary_path of architectures:$stripped"
        if [ "${CODE_SIGNING_REQUIRED}" == "YES" ]; then
            /usr/bin/codesign --force --sign ${EXPANDED_CODE_SIGN_IDENTITY} --preserve-metadata=identifier,entitlements "${framework_binary_path}"
        fi
    fi
done
