import React from "react";
import {
    IonContent,
    IonHeader,
    IonPage,
    IonTitle,
    IonToolbar,
    IonBackButton,
    IonButtons,
    IonList,
    IonItem,
    IonLabel,
   } from '@ionic/react';

import {BarcodeRepository} from "../utils/BarcodeRepository";

const BarcodeListView: React.FC = () => {
    let barcodes = BarcodeRepository.getBarcodes();

    return (
        <IonPage>
            <IonHeader>
                <IonToolbar>
                    <IonButtons slot="start">
                        <IonBackButton />
                    </IonButtons>
                    <IonTitle>Display Barcodes</IonTitle>
                </IonToolbar>
            </IonHeader>

            <IonContent fullscreen>
                <IonList lines="inset">
                        {barcodes.map((barcode) => (
                            <IonItem>
                                <IonLabel>
                                    <h3>{barcode.text}</h3>
                                    <p>{barcode.type}</p>
                                </IonLabel>
                            </IonItem>
                        ))}
                </IonList>
            </IonContent>
        </IonPage>
    );
};

export default BarcodeListView;