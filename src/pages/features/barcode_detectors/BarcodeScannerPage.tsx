import { useIonViewWillEnter } from "@ionic/react";
import { RouteComponentProps, useHistory } from "react-router";
import { CoreFeatureEnum } from "../../../enums/core_feature_enum";
import { GetItemList } from "../../../utils/data_util";
import { CoreFeatureIdEnum } from "../../../enums/core_feature_id_enum";
import { useState } from "react";
import CoreFeatureItemsView from "../../common_components/CoreFeatureItemsView";
import ScanbotService from "../../../services/scanbot_service";
import { BarcodeRepository } from "../../../utils/BarcodeRepository";
import { PickImage } from "../../../utils/camera_util";

interface BarcodeScannerProps extends RouteComponentProps<{ selectedItem: string; }> { }

let itemList: { key: CoreFeatureEnum; value: string; }[] = [];

const BarcodeScannerPage: React.FC<BarcodeScannerProps> = ({ match }) => {

    const history = useHistory();

    const [dataList, setDataList] = useState(itemList);

    const selectedItem = match.params.selectedItem as unknown as CoreFeatureIdEnum;

    useIonViewWillEnter(() => {
        let coreItems = GetItemList(selectedItem);
        setDataList(coreItems);
    });

    /** Start RTU UI Single Scanner */
    const startSingleBarcodeScanner = async () => {
        if (!(await ScanbotService.validateLicense())) { return; }

        try {
            const barcodeResult = await ScanbotService.startSingleBarcodeScanner();
            if (barcodeResult!.status === 'CANCELED') {
                alert('Single Barcode Scanner has been cancelled.');
                return;
            };

            await navigateToBarcodeResultPage(barcodeResult.items!);
        }
        catch (error) {
            console.log('Scan Barcodes Failed: ' + JSON.stringify(error));
        }
    }

    /** Start RTU UI Multi Scanner */
    const startMultiBarcodeScanner = async () => {
        if (!(await ScanbotService.validateLicense())) { return; }

        try {
            const batchBarcodeResult = await ScanbotService.startMultiBarcodeScanner();
            if (batchBarcodeResult!.status === 'CANCELED') {
                alert('Multi Barcode Scanner has been cancelled.');
                return;
            };
            await navigateToBarcodeResultPage(batchBarcodeResult.items!);
        }
        catch (error) {
            console.log('Scan Barcodes Failed: ' + JSON.stringify(error));
        }
    }

    /** Start RTU UI Multi with AR Scanner */
    const startMultiARBarcodeScanner = async () => {
        if (!(await ScanbotService.validateLicense())) { return; }

        try {
            const batchBarcodeResult = await ScanbotService.startMultiARBarcodeScanner();
            if (batchBarcodeResult!.status === 'CANCELED') {
                alert('Multi Barcode Scanner has been cancelled.');
                return;
            };
            await navigateToBarcodeResultPage(batchBarcodeResult.items!);
        }
        catch (error) {
            console.log('Scan Barcodes Failed: ' + JSON.stringify(error));
        }
    }

    /** Detect barcodes from a imported image */
    const detectBarcodesFromImage = async () => {
        if (!(await ScanbotService.validateLicense())) { return; }

        try {
            const originalImageFileUri = await PickImage();
            const detectedBarcodesResult = await ScanbotService.detectBarcodesOnImage(originalImageFileUri);
            if (detectedBarcodesResult!.status === 'CANCELED') {
                alert('Barcode detector has been cancelled.');
                return;
            };
            await navigateToBarcodeResultPage(detectedBarcodesResult!.barcodes);
        }
        catch (error) {
            console.log('Detect Barcodes Failed: ' + JSON.stringify(error));
        }
    }

    /** Navigate to barcode result page */
    const navigateToBarcodeResultPage = async (barcodes: any) => {
        try {
            await BarcodeRepository.addBarcodes(barcodes);
            await history.push('/barcode_result');
        }
        catch (error) {
            console.log('Navigate to barcode result page failed: ' + JSON.stringify(error));
        }
    }

    // -----------------
    // Item Click Event
    // -----------------
    const onItemClick = async (selectedItem: CoreFeatureEnum) => {
        switch (selectedItem) {
            case CoreFeatureEnum.SingleBarcode:
                await startSingleBarcodeScanner();
                break;
            case CoreFeatureEnum.MultiBarcode:
                await startMultiBarcodeScanner();
                break;
            case CoreFeatureEnum.MultiARBarcode:
                await startMultiARBarcodeScanner();
                break;
            case CoreFeatureEnum.ImportBarcodeImage:
                await detectBarcodesFromImage();
                break;
            default:
                alert('Please try again!');
                break;
        }
    }

    return (
        <CoreFeatureItemsView title="Scan Barcodes" dataList={dataList} onItemClick={onItemClick} />
    );
}

export default BarcodeScannerPage;