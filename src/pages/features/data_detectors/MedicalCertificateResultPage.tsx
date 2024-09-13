import { IonBackButton, IonButtons, IonContent, IonHeader, IonItem, IonItemDivider, IonItemGroup, IonLabel, IonList, IonPage, IonTitle, IonToolbar, useIonViewWillEnter } from "@ionic/react";
import { useState } from "react";
import { DataDetectorRepository } from "../../../utils/data_detector_repository";

const MedicalCertificateResultPage: React.FC = () => {

    var itemList: { title: string; items: { key: string; value: string; }[]; }[] = [];
    const [dataList, setDataList] = useState(itemList);

    useIonViewWillEnter(() => {
        setDataList(DataDetectorRepository.MedicalCertifacteResult)
    });

    return (
        <IonPage>
            <IonHeader>
                <IonToolbar color="primary">
                    <IonButtons slot="start">
                        <IonBackButton />
                    </IonButtons>
                    <IonTitle> Med Result </IonTitle>
                </IonToolbar>
            </IonHeader>

            <IonContent fullscreen>
                <IonList>
                    {
                        dataList.map((medItem, index) => (
                            <IonItemGroup key={index}>
                                <IonItemDivider>
                                    <IonLabel>{medItem.title}</IonLabel>
                                </IonItemDivider>

                                {
                                    medItem.items.map((item, index) => (
                                        <IonItem key={index}>
                                            <IonLabel>
                                                <h3>{item.key}</h3>
                                                <p>{item.value}</p>
                                            </IonLabel>
                                        </IonItem>
                                    ))
                                }
                            </IonItemGroup>
                        ))
                    }
                </IonList>
            </IonContent>
        </IonPage>
    );
}

export default MedicalCertificateResultPage;