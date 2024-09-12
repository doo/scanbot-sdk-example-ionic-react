import { useIonViewWillEnter } from "@ionic/react";
import { RouteComponentProps, useHistory } from "react-router";
import { CoreFeatureEnum } from "../../../enums/core_feature_enum";
import { GetItemList } from "../../../utils/data_util";
import { CoreFeatureIdEnum } from "../../../enums/core_feature_id_enum";
import { useState } from "react";
import CoreFeatureItemsView from "../../common_components/CoreFeatureItemsView";
import ScanbotService from "../../../services/scanbot_service";
import { ShowAlert } from "../../../services/alert_service";
import { ImageResultsRepository } from "../../../utils/ImageRepository";

interface DocumentScannerProps extends RouteComponentProps<{ selectedItem: string; }> { }

let itemList: { key: CoreFeatureEnum; value: string; }[] = [];

const DocumentScannerPage: React.FC<DocumentScannerProps> = ({ match }) => {
    const history = useHistory();

    const [dataList, setDataList] = useState(itemList);

    const selectedItem = match.params.selectedItem as unknown as CoreFeatureIdEnum;

    useIonViewWillEnter(() => {
        let coreItems = GetItemList(selectedItem);
        setDataList(coreItems);
    });

    /** Start document scanner for capture documents */
    const startDocumentScanner = async () => {
        if (!(await ScanbotService.validateLicense())) { return; }

        try {
            const documentResult = await ScanbotService.startDocumentScanner();
            if (documentResult.status === 'CANCELED') {
                await ShowAlert('Information', 'Document scanner has been canceled.', ['OK']);
                return;
            }
            await ImageResultsRepository.INSTANCE.addPages(documentResult.pages);
            history.push("/imagepreview");
        }
        catch (error) {
            await ShowAlert('Scan Document Failed', JSON.stringify(error), ['OK']);
        }
    }

    /** Start finder socument scanner for capture documents */
    const startFinderDocumentScanner = async () => {
        if (!await ScanbotService.validateLicense()) return;

        try {
            const finderDocumentResult = await ScanbotService.startFinderDocumentScanner();
            if (finderDocumentResult!.status == 'CANCELED') {
                await ShowAlert('Information', 'Finder Document scanner has been canceled.', ['OK']);
                return;
            };
            await ImageResultsRepository.INSTANCE.addPages(finderDocumentResult!.pages);
            await history.push('/imagepreview');
        }
        catch (error) {
            await ShowAlert('Scan Document Failed', JSON.stringify(error), ['OK']);
        }
    }

    // -----------------
    // Item Click Event
    // -----------------
    const onItemClick = async (selectedItem: CoreFeatureEnum) => {
        switch (selectedItem) {
            case CoreFeatureEnum.Document: {
                await startDocumentScanner();
                break;
            }
            case CoreFeatureEnum.FinderDocument: {
                await startFinderDocumentScanner();
                break;
            }
            case CoreFeatureEnum.ImageResult: {
                if (!await ScanbotService.validateLicense()) return;
                await history.push('/imagepreview');
                break;
            }
            default: {
                await ShowAlert('Selected item is wrong', 'Please try again!', ['OK']);
                break;
            }
        }
    }

    return (
        <CoreFeatureItemsView title="Scan Documents" dataList={dataList} onItemClick={onItemClick} />
    );
};

export default DocumentScannerPage;