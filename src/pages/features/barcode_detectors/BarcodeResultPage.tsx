import { IonBackButton, IonButtons, IonContent, IonHeader, IonItem, IonLabel, IonList, IonPage, IonTitle, IonToolbar, useIonViewWillEnter } from "@ionic/react";
import { useState } from "react";
import { BarcodeRepository } from "../../../utils/BarcodeRepository";
import { BarcodeResultField } from "capacitor-plugin-scanbot-sdk";

const BarcodeResultPage: React.FC = () => {

    const [barcodeList, setBarcodeList] = useState<BarcodeResultField[]>([]);

    useIonViewWillEnter(() => {
        var barcodes = BarcodeRepository.getBarcodes();
        setBarcodeList(barcodes);
    })

    return (
        <IonPage>
            <IonHeader>
                <IonToolbar color="primary">
                    <IonButtons slot="start">
                        <IonBackButton />
                    </IonButtons>
                    <IonTitle>Barcode Result</IonTitle>
                </IonToolbar>
            </IonHeader>

            <IonContent fullscreen>
                <IonList>
                    {
                        barcodeList.map((barcode) => (
                            <IonItem>
                                <IonLabel>
                                    <h3>{barcode.textWithExtension}</h3>
                                    <p>{barcode.type}</p>
                                </IonLabel>
                            </IonItem>
                        ))
                    }
                </IonList>
            </IonContent>
        </IonPage>
    );
}

export default BarcodeResultPage;