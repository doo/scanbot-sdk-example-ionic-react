import { 
    IonContent,
    IonHeader, 
    IonPage, 
    IonTitle, 
    IonToolbar, 
    IonBackButton, 
    IonButtons, 
    IonImg, 
    useIonAlert, 
    useIonViewWillEnter,
    IonGrid,
    IonRow,
    IonCol } from '@ionic/react';

import { useHistory } from 'react-router';
import React, {useState } from 'react';

import ScanbotSdk, { Page } from 'cordova-plugin-scanbot-sdk';
import { ImageResultsRepository } from '../utils/ImageRepository';

const ImagePreview: React.FC = () => {

    const [presentAlert] = useIonAlert(); 
    const history = useHistory();
    const initialState = useState<any>([]);
    const [imageData, setImageData] = initialState;

    let pages: Page[] = [];

    useIonViewWillEnter(() => {
        reloadPages();
    });

    const reloadPages = () => {
        pages = ImageResultsRepository.INSTANCE.getPages();

        for (const page of pages) {

            const url = page.documentPreviewImageFileUri as string;

            ScanbotSdk.getImageData((result) => {

                const extension = 'png';
    
                let url = `data:image/${extension};base64,` + result.base64ImageData;

                setImageData((imageData: any) => [...imageData, {id: page.pageId, url: url}])
            },
            (error) => {
                presentAlert({
                    header: 'Error',
                    message: error.message,
                    buttons: ['OK'],
                })
             },
            { imageFileUri: url }); 
        }
    }

    function navigateToCroppingPage(pageId: string): void {

        history.push("/imageeditview/" + pageId);
        setImageData(() => initialState)
    }

    return (
        <IonPage>
            <IonHeader>
                <IonToolbar>
                    <IonButtons slot="start">
                        <IonBackButton />
                    </IonButtons>
                <IonTitle>Display Images</IonTitle>
                </IonToolbar>
            </IonHeader>

            <IonContent fullscreen>
                <IonGrid>
                <IonRow>
                    {imageData.map((page: any) => (
                    <IonCol size="6" key={page.id}>
                        <IonImg onClick={() => navigateToCroppingPage(page.id)} src={page.url} />
                    </IonCol>
                    ))}
                </IonRow>
                </IonGrid>
            </IonContent>
        </IonPage>
    );
};

export default ImagePreview;