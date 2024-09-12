import { useIonViewWillEnter } from "@ionic/react";
import { useState } from "react";
import { DataDetectorRepository } from "../../../utils/data_detector_repository";
import CommonDataDetectorResultView from "./CommonDataDetectorResultView";

const CheckResultPage: React.FC = () => {
    var itemList: { name: string; value: string; }[] = [];
    const [dataList, setDataList] = useState(itemList);

    useIonViewWillEnter(() => {
        setDataList(DataDetectorRepository.CheckResult)
    });

    return (
        <CommonDataDetectorResultView title="EHIC Result" dataList={dataList} />
    );
}

export default CheckResultPage;