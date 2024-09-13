import { BarcodeResultField } from "capacitor-plugin-scanbot-sdk";

export class BarcodeRepository {
    private static barcodes: BarcodeResultField[] = [];

    public static async addBarcodes(barcodes: BarcodeResultField[]) {
        if (this.barcodes.length > 0) this.barcodes = [];
        this.barcodes = this.barcodes.concat(barcodes);
    }

    public static getBarcodes(): BarcodeResultField[] {
        return this.barcodes;
    }
}