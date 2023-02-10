import { 
    IonContent,
    IonHeader, 
    IonFooter,
    IonPage, 
    IonTitle, 
    IonToolbar, 
    IonBackButton, 
    IonButtons,
    IonButton,
    IonImg, 
    useIonAlert, 
    useIonViewWillEnter,
    IonGrid,
    IonRow,
    IonCol,
    IonModal,
    IonList,
    IonItem,
    IonLabel,
    useIonLoading, } from '@ionic/react';

import { useHistory } from 'react-router';
import React, {useState, useRef } from 'react';

import { Page, PDFPageSize, TIFFCompression } from 'cordova-plugin-scanbot-sdk';
import { ImageResultsRepository } from '../utils/ImageRepository';

/* Scanbot SDK Service */
import { ScanbotSDKService } from '../services/ScanbotSDKService';

const ImagePreview: React.FC = () => {

    const [presentAlert] = useIonAlert();
    const pdfModal = useRef<HTMLIonModalElement>(null);
    const tiffModal = useRef<HTMLIonModalElement>(null);
    const [present, dismiss] = useIonLoading();
    const history = useHistory();
    const initialState = useState<any>([]);
    const [imageData, setImageData] = initialState;

    let pages: Page[] = ImageResultsRepository.INSTANCE.getPages();

    useIonViewWillEnter(async () => {
        await reloadPages();
    });

    /* load scanned documents */
    const reloadPages = async () => {

        if(!(ScanbotSDKService.checkLicense())) return;

        try {
            for (const page of pages) {

                const url = page.documentPreviewImageFileUri as string;

                const imageURL = await ScanbotSDKService.fetchDataFromUri(url);

                if(imageURL == '' || imageURL == undefined) break;

                setImageData((imageData: any) => [...imageData, {id: page.pageId, url: imageURL}]);
            }

        } catch (error) {
            console.error(error);
        }
    }

    /* navigate to cropping page */
    function navigateToCroppingPage(pageId: string): void {
        history.push("/imageeditview/" + pageId);
        setImageData(() => initialState)
    }

    /* scanbot create pdf feature */
    const createPDF = async (pageSize:string) => {
        try {

            pdfModal.current?.dismiss();
            
            if(pages == undefined) return;

            present({
                message: 'Loading...',
                spinner: 'circles'
            })

            const result = await ScanbotSDKService.SDK.createPdf({
                images: pages.map(p => p.documentImageFileUri!),
                pageSize: pageSize as PDFPageSize
            });

            if(result.status == "CANCELED") {
                presentAlert({
                    header: 'Error',
                    message: result.message,
                    buttons: ['OK'],
                })
                dismiss();
                return;
            }

            presentAlert({
                header: 'Success',
                message: result.pdfFileUri,
                buttons: ['OK'],
            })

            dismiss();

        } catch (error) {
            console.error(error);
        }
    }

    /* scanbot create tiff feature */
    const createTIFF = async (tiffCompression: string) => {
        try {
            tiffModal.current?.dismiss();

            if(pages == undefined) return;

            present({
                message: 'Loading...',
                spinner: 'circles'
            })

            const result = await ScanbotSDKService.SDK.writeTiff({
                images: pages.map(p => p.documentImageFileUri!),
                oneBitEncoded: true,
                dpi: 300,
                compression: tiffCompression as TIFFCompression
            });

            if(result.status == "CANCELED") {
                presentAlert({
                    header: 'Error',
                    message: result.message,
                    buttons: ['OK'],
                })

                dismiss();
                return;
            }

            presentAlert({
                header: 'Success',
                message: result.tiffFileUri,
                buttons: ['OK'],
            })

            dismiss();
        } catch (error) {
            console.error(error);
        }
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

            <IonFooter>
                <IonToolbar>
                   
                    <IonButtons slot="start">
                        <IonButton id="open-pagesize-list" expand="block"> Create PDF </IonButton>

                        <IonModal id="example-modal" ref={pdfModal} trigger="open-pagesize-list">
                            <div className="wrapper">
                                <h1>Page Size</h1>

                                <IonList lines="inset">
                                    {ImageResultsRepository.INSTANCE.pdfPageSizeList.map((item) => (
                                        <IonItem button={true} detail={false} onClick={() => createPDF(item)}>
                                            <IonLabel>{item}</IonLabel>
                                        </IonItem>
                                    ))}

                                </IonList>
                            </div>
                        </IonModal>
                    </IonButtons>

                    <IonButtons slot="end">
                        <IonButton id="open-tiff-dialog" expand="block"> Create TIFF </IonButton>
                        <IonModal id="example-modal" ref={tiffModal} trigger="open-tiff-dialog">
                            <div className="wrapper">
                                <h1>Page Size</h1>

                                <IonList lines="inset">
                                    {ImageResultsRepository.INSTANCE.TIFFCompressionList.map((item) => (
                                        <IonItem button={true} detail={false} onClick={() => createTIFF(item)}>
                                            <IonLabel>{item}</IonLabel>
                                        </IonItem>
                                    ))}

                                </IonList>
                            </div>
                        </IonModal>
                    </IonButtons>
                </IonToolbar>
            </IonFooter>
        </IonPage>
    );
};

export default ImagePreview;