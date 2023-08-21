# Scanbot Barcode & Document Scanning Example App for Capacitor with Ionic

This example app shows how to integrate the [Scanbot Barcode Scanner SDK](https://scanbot.io/developer/ionic-barcode-scanner/), [Scanbot Document Scanner SDK](https://scanbot.io/developer/ionic-document-scanner/), and [Scanbot Data Capture SDK](https://scanbot.io/developer/ionic-data-capture/) for Capacitor.

The Scanbot SDK Cordova Plugin is available as an [npm package](https://www.npmjs.com/package/cordova-plugin-scanbot-sdk).

For more details about the Scanbot SDK Cordova Plugin please refer to the [documentation](https://docs.scanbot.io/document-scanner-sdk/cordova/).

## What is the Scanbot SDK?

The Scanbot SDK lets you integrate barcode & document scanning, as well as data extraction functionalities, into your mobile apps and website. It contains different modules that are licensable for an annual fixed price. For more details, visit our website https://scanbot.io.


## Trial License

The Scanbot SDK will run without a license for one minute per session!

After the trial period has expired, all SDK functions and UI components will stop working. You have to restart the app to get another one-minute trial period.

To test the Scanbot SDK without crashing, you can get a free “no-strings-attached” trial license. Please submit the [Trial License Form](https://scanbot.io/trial/) on our website.

## Free Developer Support

We provide free "no-strings-attached" developer support for the implementation & testing of the Scanbot SDK.
If you encounter technical issues with integrating the Scanbot SDK or need advice on choosing the appropriate
framework or features, please visit our [Support Page](https://docs.scanbot.io/support/).

## Documentation
👉 [Scanbot SDK documentation](https://docs.scanbot.io/document-scanner-sdk/cordova/introduction/)

## How to run this app

### Requirements

- [Node.js v12](https://nodejs.org) or higher, with NPM v6.9 or higher
- For Android Apps:
    * Latest [Android Studio](https://developer.android.com/studio/) with Android SDK installed
- For iOS Apps:
    * Mac with latest version of [Xcode](https://developer.apple.com/xcode/)
    * [CocoaPods](https://cocoapods.org)

Please check the full [requirements for Capacitor](https://capacitorjs.com/docs/getting-started/environment-setup).

### Install

Install the node modules of this project:

```
cd scanbot-sdk-example-ionic-react/
npm install
```

### Build

Build the web assets and sync with the Capacitor native projects:

```
npm run build
npx cap sync
```

### Run

Connect an Android or iOS device via USB and run the app from IDE or Command Line Interface (CLI).


#### IDE
Open the native projects in corresponding IDEs (Android Studio or Xcode) and hit the "Run" button:

```
npx cap open android
npx cap open ios
```

#### CLI
Or alternatively run the projects via CLI (Android or iOS):

```
npx cap run android
npx cap run ios
```
