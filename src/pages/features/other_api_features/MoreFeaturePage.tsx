import { useIonViewWillEnter } from "@ionic/react";
import { RouteComponentProps, useHistory } from "react-router";
import { CoreFeatureEnum } from "../../../enums/core_feature_enum";
import { GetItemList } from "../../../utils/data_util";
import { CoreFeatureIdEnum } from "../../../enums/core_feature_id_enum";
import { useState } from "react";
import CoreFeatureItemsView from "../../common_components/CoreFeatureItemsView";
import ScanbotService from "../../../services/scanbot_service";

interface MoreFeaturePageProps extends RouteComponentProps<{ selectedItem: string; }> { }

let itemList: { key: CoreFeatureEnum; value: string; }[] = [];

const MoreFeaturePage: React.FC<MoreFeaturePageProps> = ({ match }) => {

    const [dataList, setDataList] = useState(itemList);

    const selectedItem = match.params.selectedItem as unknown as CoreFeatureIdEnum;

    useIonViewWillEnter(() => {
        let coreItems = GetItemList(selectedItem);
        setDataList(coreItems);
    });

    // get license info
    const getLicenseInfo = async () => {
        try {
            const licenseInfo = await ScanbotService.viewLicenseInfo();
            alert(JSON.stringify(licenseInfo));
        } catch (error) {
            console.log('Failed: ' + JSON.stringify(error));
        }
    }

    // get ocr info
    const getOCRInfo = async () => {
        try {
            const ocrInfo = await ScanbotService.viewOcrConfigs();
            alert(JSON.stringify(ocrInfo));
        } catch (error) {
            console.log('Failed: ', JSON.stringify(error));
        }
    }

    // -----------------
    // Item Click Event
    // -----------------
    const onItemClick = async (selectedItem: CoreFeatureEnum) => {
        switch (selectedItem) {
            case CoreFeatureEnum.LicenseInfo: {
                await getLicenseInfo();
                break;
            }
            case CoreFeatureEnum.OCRInfo: {
                await getOCRInfo();
                break;
            }
            case CoreFeatureEnum.LearnMore: {
                window.location.href = String('https://scanbot.io');
                break;
            }
            default: {
                alert('Please try again!');
                break;
            }
        }
    }

    return (
        <CoreFeatureItemsView title="Scan Documents" dataList={dataList} onItemClick={onItemClick} />
    );
};

export default MoreFeaturePage;