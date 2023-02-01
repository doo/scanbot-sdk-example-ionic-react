import { BarcodeFormat } from "cordova-plugin-scanbot-sdk";

export class BarcodeRepository{

    public static barcodeFormatList = [
        { key: 'AZTEC',        value: true },
        { key: 'CODABAR',      value: true },
        { key: 'CODE_39',      value: true },
        { key: 'CODE_93',      value: true },
        { key: 'CODE_128',     value: true },
        { key: 'DATA_MATRIX',  value: true },
        { key: 'EAN_8',        value: true },
        { key: 'EAN_13',       value: true },
        { key: 'ITF',          value: true },
        { key: 'PDF_417',      value: true },
        { key: 'QR_CODE',      value: true },
        { key: 'RSS_14',       value: true },
        { key: 'RSS_EXPANDED', value: true },
        { key: 'UPC_A',        value: true },
        { key: 'UPC_E',        value: true },
        { key: 'MSI_PLESSEY',  value: false }
    ];

    public static getAcceptedTypes() {
        const result:BarcodeFormat[] = [];

        for (let i = 0; i < BarcodeRepository.barcodeFormatList.length; i++) {
            if (BarcodeRepository.barcodeFormatList[i].value) {
                result.push(BarcodeRepository.barcodeFormatList[i].key as BarcodeFormat);
            }
        }

        return result;
    }
}