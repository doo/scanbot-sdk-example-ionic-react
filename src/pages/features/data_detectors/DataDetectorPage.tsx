import { useIonViewWillEnter } from "@ionic/react";
import { RouteComponentProps, useHistory } from "react-router";
import { CoreFeatureEnum } from "../../../enums/core_feature_enum";
import { GetItemList } from "../../../utils/data_util";
import { CoreFeatureIdEnum } from "../../../enums/core_feature_id_enum";
import { useState } from "react";
import CoreFeatureItemsView from "../../common_components/CoreFeatureItemsView";
import ScanbotService from "../../../services/scanbot_service";
import { DataDetectorRepository } from "../../../utils/data_detector_repository";
import { PickImage } from "../../../utils/camera_util";

interface DataDetectorPageProps extends RouteComponentProps<{ selectedItem: string; }> { }

let itemList: { key: CoreFeatureEnum; value: string; }[] = [];

const DataDetectorPage: React.FC<DataDetectorPageProps> = ({ match }) => {

    const history = useHistory();

    const [dataList, setDataList] = useState(itemList);

    const selectedItem = match.params.selectedItem as unknown as CoreFeatureIdEnum;

    useIonViewWillEnter(() => {
        let coreItems = GetItemList(selectedItem);
        setDataList(coreItems);
    });

    /** Detect MRZ data */
    const startMRZScanner = async () => {
        if (!(await ScanbotService.validateLicense())) { return; }

        try {
            const mrzResult = await ScanbotService.startMrzScanner();
            if (mrzResult!.status === 'CANCELED') {
                alert('MRZ detector has been cancelled.');
                return;
            };
            DataDetectorRepository.GeneratMRZResult(mrzResult);
            await history.push('/mrz_result');
        }
        catch (error) {
            console.log('Detect MRZ data Failed: ' + JSON.stringify(error));
        }
    }

    /** Detect EHIC data */
    const startEHICScanner = async () => {
        if (!(await ScanbotService.validateLicense())) { return; }

        try {
            const ehicResult = await ScanbotService.startEHICScanner();
            if (ehicResult!.status === 'CANCELED') {
                alert('EHIC detector has been cancelled.');
                return;
            };
            DataDetectorRepository.GeneratEHICResult(ehicResult!);
            await history.push('/ehic_result');
        }
        catch (error) {
            console.log('Detect EHIC data Failed: ' + JSON.stringify(error));
        }
    }

    /** Datect data from a check */
    const startCheckScanner = async () => {
        if (!(await ScanbotService.validateLicense())) { return; }

        try {
            const checkResult = await ScanbotService.startCheckRecognizer();
            if (checkResult!.status === 'CANCELED') {
                alert('Check data detector has been cancelled.');
                return;
            };
            DataDetectorRepository.GenerateCheckResult(checkResult!);
            await history.push('/check_result');
        }
        catch (error) {
            console.log('Detect Check data Failed:' + JSON.stringify(error));
        }
    }

    /** Detect check data from imported image */
    const detectCheckFromImage = async () => {
        if (!(await ScanbotService.validateLicense())) { return; }

        try {
            const originalImageFileUri = await PickImage();

            const checkResult = await ScanbotService.recognizeCheck(originalImageFileUri);
            if (checkResult!.status === 'CANCELED') {
                alert('Check data detector has been cancelled.');
                return;
            };
            DataDetectorRepository.GenerateCheckResult(checkResult!);
            await history.push('/check_result');
        }
        catch (error) {
            console.log('Detect Check data Failed: ' + JSON.stringify(error));
        }
    }

    /** Detect license plate data */
    const startLicensePlateScaner = async () => {
        if (!(await ScanbotService.validateLicense())) { return; }

        try {
            const licensePlateResult = await ScanbotService.startLicensePlateScanner();
            if (licensePlateResult!.status === 'CANCELED') {
                alert('License plate data detector has been cancelled.');
                return;
            };
            alert(JSON.stringify(licensePlateResult));
        }
        catch (error) {
            console.log('Detect license plate data Failed: ' + JSON.stringify(error));
        }
    }

    /** Detect medical certificate data */
    const startMedicalCertificateScanner = async () => {
        if (!(await ScanbotService.validateLicense())) { return; }

        try {
            const medicalCertificateResult = await ScanbotService.startMedicalCertificateRecognizer();
            console.log(JSON.stringify(medicalCertificateResult));
            if (medicalCertificateResult!.status === 'CANCELED') {
                alert('Medicle certificate data detector has been cancelled.');
                return;
            };
            DataDetectorRepository.GenerateMedData(medicalCertificateResult);
            await history.push('/medical_certificate_result');
        }
        catch (error) {
            console.log('Detect Medical data Failed: ' + JSON.stringify(error));
        }
    }

    /** Detect text data */
    const startScanTextDataScaner = async () => {
        if (!(await ScanbotService.validateLicense())) { return; }

        try {
            const textResult = await ScanbotService.startTextDataScanner();
            if (textResult!.status == 'CANCELED') {
                alert('Text data detector has been cancelled.');
                return;
            };
            alert(JSON.stringify(textResult));
        }
        catch (error) {
            console.log('Detect text data Failed: ' + JSON.stringify(error));
        }
    }

    /** Open generic document scanner */
    const startGenericDocumentScaner = async () => {
        if (!(await ScanbotService.validateLicense())) { return; }

        try {
            const genericDocumentResult = await ScanbotService.startGenericDocumentRecognizer();
            if (genericDocumentResult!.status == 'CANCELED') {
                alert('Generic document scanner has been cancelled.');
                return;
            };
            alert(JSON.stringify(genericDocumentResult));
        }
        catch (error) {
            console.log('Generic document scanner Failed: ' + JSON.stringify(error));
        }
    }

    // -----------------
    // Item Click Event
    // -----------------
    const onItemClick = async (selectedItem: CoreFeatureEnum) => {
        switch (selectedItem) {
            case CoreFeatureEnum.MRZ:
                await startMRZScanner();
                break;
            case CoreFeatureEnum.EHIC:
                await startEHICScanner();
                break;
            case CoreFeatureEnum.Check:
                await startCheckScanner();
                break;
            case CoreFeatureEnum.ImportCheckOnImage:
                await detectCheckFromImage();
                break;
            case CoreFeatureEnum.LicensePlate:
                await startLicensePlateScaner();
                break;
            case CoreFeatureEnum.MedicalCertificate:
                await startMedicalCertificateScanner();
                break;
            case CoreFeatureEnum.TextData:
                await startScanTextDataScaner();
                break;
            case CoreFeatureEnum.GenericDocument:
                await startGenericDocumentScaner();
                break;
            default:
                alert('Please try again!');
                break;
        }
    }

    return (
        <CoreFeatureItemsView title="Data Detectors" dataList={dataList} onItemClick={onItemClick} />
    );
};

export default DataDetectorPage;