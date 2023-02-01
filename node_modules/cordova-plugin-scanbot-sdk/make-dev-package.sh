#!/bin/bash

set -e

PACKAGE_VERSION=$(node -p -e "require('./package.json').version")
npm pack

rm -rf dev-package
mkdir dev-package
mv cordova-plugin-scanbot-sdk-$PACKAGE_VERSION.tgz dev-package/
cd dev-package/
tar xvf cordova-plugin-scanbot-sdk-$PACKAGE_VERSION.tgz
rm cordova-plugin-scanbot-sdk-$PACKAGE_VERSION.tgz
cd ..

echo
echo "DONE! 🎉"
echo
