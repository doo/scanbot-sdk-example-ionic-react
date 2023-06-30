/* Scanbot SDK */
import ScanbotSdk from 'cordova-plugin-scanbot-sdk';

export class ScanbotSDKService {
    public static SDK = ScanbotSdk.promisify!();

    public static async checkLicense() {
        const result = await this.SDK.getLicenseInfo();
        if (result.info.isLicenseValid) {
            // OK - we have a trial session, a valid trial license or valid production license.
            return true;
        }
        console.log('Scanbot SDK (trial) license has expired!');
        return false;
    }

    public static async fetchDataFromUri(path: string): Promise<string> {
        const result = await this.SDK.getImageData({ imageFileUri: path });
        const extension = 'JPG';
        // ScanbotSDK return the raw base64 data. Add prefix to convert it to a dataUri
        return `data:image/${extension};base64,` + result.base64ImageData;
    }
}