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
    const pdfPageSizeList: PDFPageSize[] = [
        "FROM_IMAGE",
        "A4",
        "FIXED_A4",
        "US_LETTER",
        "FIXED_US_LETTER",
        "AUTO_LOCALE",
        "AUTO"
    ];
    const tiffOptions = [
        {
            label: "Binarized Images (1-bit)",
            binarized: true
        },
        {
            label: "Color Images",
            binarized: false
        },
    ];

    const [presentAlert] = useIonAlert();
    const pdfModal = useRef<HTMLIonModalElement>(null);
    const tiffModal = useRef<HTMLIonModalElement>(null);
    const [present, dismiss] = useIonLoading();
    const history = useHistory();
    const initialState = useState<any>([]);
    const [imageData, setImageData] = initialState;

    const pages: Page[] = ImageResultsRepository.INSTANCE.getPages();

    useIonViewWillEnter(async () => {
        await reloadPages();
    });

    async function checkLicense(): Promise<boolean> {
        if (!(await ScanbotSDKService.checkLicense())) {
            alert('Scanbot SDK (trial) license has expired!');
            return false;
        }
        return true;
    }

    function hasScannedPages(): boolean {
        if (!pages || pages.length === 0) {
            alert('No scanned images were found. Please scan at least one page.');
            return false;
        }
        return true;
    }

    /* load scanned documents */
    async function reloadPages() {
        if (!(await checkLicense())) { return; }
        if (!hasScannedPages()) { return; }

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
    async function createPDF(pageSize: PDFPageSize) {
        pdfModal.current?.dismiss();

        if (!(await checkLicense())) { return; }
        if (!hasScannedPages()) { return; }

        try {
            await present({
                message: 'Loading...',
                spinner: 'circles'
            })
            const result = await ScanbotSDKService.SDK.createPdf({
                images: pages.map(p => p.documentImageFileUri!),
                pageSize: pageSize
            });
            await dismiss();
            if (result.status === "CANCELED") {
                await presentAlert({
                    header: 'Information',
                    message: result.message,
                    buttons: ['OK'],
                });
                return;
            }
            await presentAlert({
                header: 'Success',
                message: result.pdfFileUri,
                buttons: ['OK'],
            });
        }
        catch (error) {
            await dismiss();
            console.error(error);
        }
    }

    /* Create TIFF */
    async function createTIFF(binarized: boolean) {
        tiffModal.current?.dismiss();

        if (!(await checkLicense())) { return; }
        if (!hasScannedPages()) { return; }

        try {
            await present({
                message: 'Loading...',
                spinner: 'circles'
            });
            const result = await ScanbotSDKService.SDK.writeTiff({
                images: pages.map(p => p.documentImageFileUri!),
                oneBitEncoded: binarized,
                dpi: 300,
                compression: binarized ? 'CCITT_T6' : 'ADOBE_DEFLATE',
            });
            await dismiss();
            if (result.status !== "CANCELED") {
                await presentAlert({
                    header: 'Success',
                    message: result.tiffFileUri,
                    buttons: ['OK'],
                });
            }
            else {
                await presentAlert({
                    header: 'Information',
                    message: result.message,
                    buttons: ['OK'],
                });
                return;
            }
        }
        catch (error) {
            await dismiss();
            console.error(error);
        }
    }

    /* Perform OCR, read text from images */
    async function runOCR() {
        if (!(await checkLicense())) { return; }
        if (!hasScannedPages()) { return; }

        try {
            await present({
                message: 'Processing...',
                spinner: 'circles'
            });
            const ocrResult = await ScanbotSDKService.SDK.performOcr({
                images: pages.map(p => p.documentImageFileUri!),
                languages: ['en', 'de'],
                outputFormat: 'FULL_OCR_RESULT',
            });
            await dismiss();
            if (ocrResult.status === 'CANCELED') {
                await presentAlert({
                    header: 'Information',
                    message: 'OCR process canceled.',
                    buttons: ['OK'],
                });
                return;
            }
            await presentAlert({
                header: 'OCR Results',
                message: JSON.stringify(ocrResult),
                buttons: ['OK'],
            });
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
                        <IonButton id="open-pagesize-list" expand="block">Create PDF</IonButton>
                        <IonModal id="example-modal" ref={pdfModal} trigger="open-pagesize-list">
                            <div className="wrapper">
                                <h1>Page Size</h1>
                                <IonList lines="inset">
                                    {pdfPageSizeList.map((item) => (
                                        <IonItem button={true} detail={false} onClick={() => createPDF(item)}>
                                            <IonLabel>{item}</IonLabel>
                                        </IonItem>
                                    ))}
                                </IonList>
                            </div>
                        </IonModal>
                        <IonButton onClick={() => runOCR()}>Run OCR</IonButton>
                    </IonButtons>

                    <IonButtons slot="end">
                        <IonButton id="open-tiff-dialog" expand="block">Create TIFF</IonButton>
                        <IonModal id="example-modal" ref={tiffModal} trigger="open-tiff-dialog">
                            <div className="wrapper">
                                <h1>Image Type</h1>
                                <IonList lines="inset">
                                    {tiffOptions.map((item) => (
                                        <IonItem button={true} detail={false} onClick={() => createTIFF(item.binarized)}>
                                            <IonLabel>{item.label}</IonLabel>
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