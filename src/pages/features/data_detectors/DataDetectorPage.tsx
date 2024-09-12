import { useIonViewWillEnter } from "@ionic/react";
import { RouteComponentProps, useHistory } from "react-router";
import { CoreFeatureEnum } from "../../../enums/core_feature_enum";
import { GetItemList } from "../../../utils/data_util";
import { CoreFeatureIdEnum } from "../../../enums/core_feature_id_enum";
import { useState } from "react";
import CoreFeatureItemsView from "../../common_components/CoreFeatureItemsView";
import { ShowAlert } from "../../../services/alert_service";
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
            if (mrzResult!.status == 'CANCELED') {
                await ShowAlert('Information', 'MRZ detector has been cancelled.', ['OK']);
                return;
            };
            DataDetectorRepository.GeneratMRZResult(mrzResult);
            await history.push('/mrz_result');
        }
        catch (error) {
            await ShowAlert('Detect MRZ data Failed', JSON.stringify(error), ['OK']);
        }
    }

    /** Detect EHIC data */
    const startEHICScanner = async () => {
        if (!(await ScanbotService.validateLicense())) { return; }

        try {
            const ehicResult = await ScanbotService.startEHICScanner();
            if (ehicResult!.status == 'CANCELED') {
                await ShowAlert('Information', 'EHIC detector has been cancelled.', ['OK']);
                return;
            };
            DataDetectorRepository.GeneratEHICResult(ehicResult!);
            await history.push('/ehic_result');
        }
        catch (error) {
            await ShowAlert('Detect EHIC data Failed', JSON.stringify(error), ['OK']);
        }
    }

    /** Datect data from a check */
    const startCheckScanner = async () => {
        if (!(await ScanbotService.validateLicense())) { return; }

        try {
            const checkResult = await ScanbotService.startCheckRecognizer();
            if (checkResult!.status == 'CANCELED') {
                await ShowAlert('Information', 'Check data detector has been cancelled.', ['OK']);
                return;
            };
            DataDetectorRepository.GenerateCheckResult(checkResult!);
            await history.push('/check_result');
        }
        catch (error) {
            await ShowAlert('Detect Check data Failed', JSON.stringify(error), ['OK']);
        }
    }

    /** Detect check data from imported image */
    const detectCheckFromImage = async () => {
        if (!(await ScanbotService.validateLicense())) { return; }

        try {
            const originalImageFileUri = await PickImage();

            const checkResult = await ScanbotService.recognizeCheck(originalImageFileUri);
            if (checkResult!.status == 'CANCELED') {
                await ShowAlert('Information', 'Check data detector has been cancelled.', ['OK']);
                return;
            };
            DataDetectorRepository.GenerateCheckResult(checkResult!);
            await history.push('/check_result');
        }
        catch (error) {
            await ShowAlert('Detect Check data Failed', 'Please try again!', ['OK']);
        }
    }

    /** Detect license plate data */
    const startLicensePlateScaner = async () => {
        if (!(await ScanbotService.validateLicense())) { return; }

        try {
            const licensePlateResult = await ScanbotService.startLicensePlateScanner();
            if (licensePlateResult!.status == 'CANCELED') {
                await ShowAlert('Information', 'License plate data detector has been cancelled.', ['OK']);
                return;
            };
            alert(JSON.stringify(licensePlateResult));
        }
        catch (error) {
            await ShowAlert('Detect license plate data Failed', JSON.stringify(error), ['OK']);
        }
    }

    /** Detect medical certificate data */
    const startMedicalCertificateScanner = async () => {
        if (!(await ScanbotService.validateLicense())) { return; }

        try {
            const medicalCertificateResult = await ScanbotService.startMedicalCertificateRecognizer();
            console.log(JSON.stringify(medicalCertificateResult));
            if (medicalCertificateResult!.status == 'CANCELED') {
                await ShowAlert('Information', 'Medicle certificate data detector has been cancelled.', ['OK']);
                return;
            };
            DataDetectorRepository.GenerateMedData(medicalCertificateResult);
            await history.push('/medical_certificate_result');
        }
        catch (error) {
            await ShowAlert('Detect Medical data Failed', JSON.stringify(error), ['OK']);
        }
    }

    /** Detect text data */
    const startScanTextDataScaner = async () => {
        if (!(await ScanbotService.validateLicense())) { return; }

        try {
            const textResult = await ScanbotService.startTextDataScanner();
            if (textResult!.status == 'CANCELED') {
                await ShowAlert('Information', 'Text data detector has been cancelled.', ['OK']);
                return;
            };
            alert(JSON.stringify(textResult));
        }
        catch (error) {
            await ShowAlert('Detect text data Failed', JSON.stringify(error), ['OK']);
        }
    }

    /** Open generic document scanner */
    const startGenericDocumentScaner = async () => {
        if (!(await ScanbotService.validateLicense())) { return; }

        try {
            const genericDocumentResult = await ScanbotService.startGenericDocumentRecognizer();
            if (genericDocumentResult!.status == 'CANCELED') {
                await ShowAlert('Information', 'Generic document scanner has been cancelled.', ['OK']);
                return;
            };
            alert(JSON.stringify(genericDocumentResult));
        }
        catch (error) {
            await ShowAlert('Generic document scanner Failed', JSON.stringify(error), ['OK']);
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
                await ShowAlert('Selected item is wrong', 'Please try again!', ['OK']);
                break;
        }
    }

    return (
        <CoreFeatureItemsView title="Data Detectors" dataList={dataList} onItemClick={onItemClick} />
    );
};

export default DataDetectorPage;