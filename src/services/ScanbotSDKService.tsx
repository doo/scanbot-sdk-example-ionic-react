// /* Scanbot SDK */
// import ScanbotSdk from 'cordova-plugin-scanbot-sdk';

// class ScanbotSDKService {
//     public SDK = ScanbotSdk.promisify!();
//     private ImageExtension: String = 'JPG';

//     // -------------------------
//     // Validate license
//     // -------------------------
//     public validateLicense = async () => {
//         try {
//             const result = await this.SDK.getLicenseInfo();
//             if (result?.isLicenseValid) {
//                 // OK - we have a trial session, a valid trial license or valid production license.
//                 return true;
//             }
//             alert('Scanbot SDK (trial) license has expired!');
//             return false;
//         }
//         catch (error) {
//             //ShowAlert('License Validation Failed', JSON.stringify(error), ['OK']);
//             return false;
//         }
//     }

//     // public static async fetchDataFromUri(path: string): Promise<string> {
//     //     const result = await this.SDK.getImageData({ imageFileUri: path });
//     //     // ScanbotSDK return the raw base64 data. Add prefix to convert it to a dataUri
//     //     return `data:image/${(ScanbotSDKService.ImageExtension)};base64,` + result.base64ImageData;
//     // }
// }

// export default new ScanbotSDKService();