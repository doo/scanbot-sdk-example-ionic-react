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

import { Page, PDFPageSize } from 'cordova-plugin-scanbot-sdk';
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
        if(!(await ScanbotSDKService.checkLicense())) {
            alert('Scanbot SDK (trial) license has expired!');
            return;
        }
        if (!pages || pages.length === 0) {
            alert('No scanned images were found. Please scan at least one page.');
            return;
        }

        try {
            for (const page of pages) {
                const url = page.documentPreviewImageFileUri as string;
                const imageURL = await ScanbotSDKService.fetchDataFromUri(url);
                if(imageURL === '' || imageURL === undefined) break;

                setImageData((imageData: any) => [...imageData, {id: page.pageId, url: imageURL}]);
            }
        }
        catch (error) {
            console.error(error);
        }
    }

    /* Navigate to cropping page */
    function navigateToCroppingPage(pageId: string): void {
        history.push("/imageeditview/" + pageId);
        setImageData(() => initialState)
    }

    /* Create PDF */
    const createPDF = async (pageSize:string) => {
        if(!(await ScanbotSDKService.checkLicense())) {
            pdfModal.current?.dismiss();
            alert('Scanbot SDK (trial) license has expired!');
            return;
        }
        if (!pages || pages.length === 0) {
            pdfModal.current?.dismiss();
            alert('No scanned images were found. Please scan at least one page.');
            return;
        }

        try {
            pdfModal.current?.dismiss();
            await present({
                message: 'Loading...',
                spinner: 'circles'
            })
            const result = await ScanbotSDKService.SDK.createPdf({
                images: pages.map(p => p.documentImageFileUri!),
                pageSize: pageSize as PDFPageSize
            });
            await dismiss();
            if(result.status === "CANCELED") {
                await presentAlert({
                    header: 'Information',
                    message: result.message,
                    buttons: ['OK'],
                })
                return;
            }
            await presentAlert({
                header: 'Success',
                message: result.pdfFileUri,
                buttons: ['OK'],
            })
        }
        catch (error) {
            await dismiss();
            console.error(error);
        }
    }

    /* Create TIFF */
    const createTIFF = async (tiffCompression: string) => {
        if(!(await ScanbotSDKService.checkLicense())) {
            tiffModal.current?.dismiss();
            alert('Scanbot SDK (trial) license has expired!');
            return;
        }
        if (!pages || pages.length === 0) {
            tiffModal.current?.dismiss();
            alert('No scanned images were found. Please scan at least one page.');
            return;
        }

        try {
            tiffModal.current?.dismiss();
            await present({
                message: 'Loading...',
                spinner: 'circles'
            })
            var oneBitEncoded = tiffCompression === "Binarized Images (1-bit)" ? true : false;
            const result = await ScanbotSDKService.SDK.writeTiff({
                images: pages.map(p => p.documentImageFileUri!),
                oneBitEncoded: oneBitEncoded,
                dpi: 300,
                compression: oneBitEncoded ? 'CCITT_T6' : 'ADOBE_DEFLATE',
            });
            await dismiss();
            if (result.status !== "CANCELED") {
                await presentAlert({
                    header: 'Success',
                    message: result.tiffFileUri,
                    buttons: ['OK'],
                })
            }
            else {
                await presentAlert({
                    header: 'Information',
                    message: result.message,
                    buttons: ['OK'],
                })
                return;
            }
        }
        catch (error) {
            await dismiss();
            console.error(error);
        }
    }

    return (
        <IonPage>
            <IonHeader>
                <IonToolbar color="primary">
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